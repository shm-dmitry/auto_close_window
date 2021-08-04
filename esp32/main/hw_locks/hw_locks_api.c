#include "hw_locks_api.h"

#include "driver/gpio.h"
#include "hwlocks_nvs.h"
#include "../log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "../cjson/cjson_helper.h"
#include "../init/mqtt.h"
#include "string.h"

static int hwlocks_softlock = 0;
static int hwlocks_hall = 0;
static int hwlocks_switch = 0;
static xQueueHandle hwlocks_isr_queue = NULL;
static char * hwlocks_status_topic = NULL;

static void IRAM_ATTR hwlocks_isr_handler(void* arg) {
    uint32_t gpio_num = (uint32_t) arg;
    xQueueSendFromISR(hwlocks_isr_queue, &gpio_num, NULL);
}

void hwlocks_send_mqtt_status_message() {
	uint8_t status = hwlocks_read();

	cJSON *root = cJSON_CreateObject();
	cJSON_AddBoolToObject(root, "hall", !(status & HWLOCK_STATE_HALL));
	cJSON_AddBoolToObject(root, "switch", !(status & HWLOCK_STATE_SWITCH));
	cJSON_AddBoolToObject(root, "soft", !(status & HWLOCK_STATE_SOFTLOCK));

	char * json = cJSON_Print(root);
	mqtt_publish(hwlocks_status_topic, json);
	cJSON_free(json);

	cJSON_Delete(root);
}

static void hwlocks_isr_task(void* arg) {
    uint32_t io_num;
    for(;;) {
        if(xQueueReceive(hwlocks_isr_queue, &io_num, portMAX_DELAY)) {
            if (io_num == hwlocks_hall || io_num == hwlocks_switch) {
            	hwlocks_send_mqtt_status_message();
            }
        }
    }
}

void hwlocks_publish_init_state(void * arg) {
	vTaskDelay(5000 / portTICK_PERIOD_MS);

	hwlocks_send_mqtt_status_message();

	vTaskDelete(NULL);
}

void hwlocks_mqtt_softlock_command(const char * topic, const char * data) {
	cJSON *root = cJSON_Parse(data);
	if (root == NULL) {
		return;
	}

	uint8_t res = get_boolean_from_json(cJSON_GetObjectItem(root, "value"), 0x01, 0x00, 0x02);
	if (res == 0x00 || res == 0x01) {
		hwlocks_softlock_set(res ? true : false);
	}

	cJSON_Delete(root);
}

esp_err_t hwlocks_softlock_raw_set(bool on);

esp_err_t hwlocks_init(int gpio_hall, int gpio_switch, int gpio_softlock, const char * softlock_topic, const char * status_topic) {
	hwlocks_status_topic = malloc(strlen(status_topic) + 1);
	strcpy(hwlocks_status_topic, status_topic);

	hwlocks_isr_queue = xQueueCreate(10, sizeof(uint32_t));

	gpio_config_t config = {
		.intr_type = GPIO_INTR_ANYEDGE,
	    .mode = GPIO_MODE_INPUT,
		.pin_bit_mask = (1ULL << gpio_hall) | (1ULL << gpio_switch),
		.pull_down_en = GPIO_PULLDOWN_DISABLE,
		.pull_up_en = GPIO_PULLUP_DISABLE,
	};

	esp_err_t res = gpio_config(&config);
	if (res) {
		ESP_LOGI(HWLOCK_LOG, "Cant init INPUT GPIO. error %d", res);
		return res;
	}

	res = gpio_install_isr_service(0);
	if (res) {
		ESP_LOGI(HWLOCK_LOG, "Cant install isr service. error %d", res);
		return res;
	}

	gpio_isr_handler_add(gpio_hall, hwlocks_isr_handler, (void *) gpio_hall);
	gpio_isr_handler_add(gpio_switch, hwlocks_isr_handler, (void *) gpio_switch);

	xTaskCreate(hwlocks_isr_task, "hwlocks_isr_task", 2048, NULL, 10, NULL);

	config.pin_bit_mask = 1ULL << gpio_softlock;
	config.mode = GPIO_MODE_INPUT_OUTPUT;
	config.pull_up_en = GPIO_PULLUP_ENABLE;

	res = gpio_config(&config);
	if (res) {
		ESP_LOGI(HWLOCK_LOG, "Cant init OUTPUT GPIO. error %d", res);
		return res;
	}

	hwlocks_softlock = gpio_softlock;
	hwlocks_hall = gpio_hall;
	hwlocks_switch = gpio_switch;

	res = hwlocks_softlock_raw_set(hwlocks_nvs_read_soft_lock_state());;
	if (res) {
		ESP_LOGI(HWLOCK_LOG, "Cant set softlock state. error %d", res);
		return res;
	}

	mqtt_subscribe(softlock_topic, hwlocks_mqtt_softlock_command);

	xTaskCreate(hwlocks_publish_init_state, "publish_init_state", 2048, NULL, 10, NULL);

	return ESP_OK;
}

esp_err_t hwlocks_softlock_set(bool on) {
	hwlocks_nvs_save_softlock_state(on);

	return hwlocks_softlock_raw_set(on);
}

esp_err_t hwlocks_softlock_raw_set(bool on) {
	uint32_t level = on ? 0 : 1; // inverted

	esp_err_t res = gpio_set_level(hwlocks_softlock, level);
	if (res) {
		ESP_LOGE(HWLOCK_LOG, "Cant set level %d on pin %d: %d", level, hwlocks_softlock, res);
	} else {
		ESP_LOGI(HWLOCK_LOG, "level %d on pin %d activated.", level, hwlocks_softlock);
	}

	hwlocks_send_mqtt_status_message();

	return res;
}

bool hwlocks_read_inverted(int gpio) {
	int val = gpio_get_level(gpio);

	return val ? false : true;
}

uint8_t hwlocks_read() {
	uint8_t result = HWLOCK_STATE_OK;

	if (!hwlocks_read_inverted(hwlocks_softlock)) {
		result = result | HWLOCK_STATE_SOFTLOCK;
	}

	if (!hwlocks_read_inverted(hwlocks_hall)) {
		result = result | HWLOCK_STATE_HALL;
	}

	if (!hwlocks_read_inverted(hwlocks_switch)) {
		result = result | HWLOCK_STATE_SWITCH;
	}

	return result;
}

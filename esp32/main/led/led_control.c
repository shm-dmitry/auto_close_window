#include "led_control.h"

#include "led_api.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

QueueHandle_t led_control_commands_queue = NULL;

static void led_control_task(void* arg) {
	uint8_t * command = NULL;
    for(;;) {
        if(xQueueReceive(led_control_commands_queue, &command, portMAX_DELAY)) {
        	if (command) {
        		if (*command == LED_CONTROL_ON_OFF) {
        			led_on();
        			vTaskDelay(1000 / portTICK_PERIOD_MS);
        			led_off();
        			vTaskDelay(500 / portTICK_PERIOD_MS);
        		} else if (*command == LED_CONTROL_BLINK) {
        			for (int i = 0; i<5; i++) {
						led_on();
						vTaskDelay(200 / portTICK_PERIOD_MS);
						led_off();
						vTaskDelay(200 / portTICK_PERIOD_MS);
        			}
        			vTaskDelay(300 / portTICK_PERIOD_MS);
        		} else if (*command == LED_CONTROL_BLINK_2) {
        			for (int i = 0; i<5; i++) {
						led_on();
						vTaskDelay(300 / portTICK_PERIOD_MS);
						led_off();
						vTaskDelay(100 / portTICK_PERIOD_MS);
        			}
        			vTaskDelay(400 / portTICK_PERIOD_MS);
        		} else if (*command == LED_CONTROL_BLINK_3) {
        			for (int i = 0; i<10; i++) {
						led_on();
						vTaskDelay(100 / portTICK_PERIOD_MS);
						led_off();
						vTaskDelay(100 / portTICK_PERIOD_MS);
        			}
        			vTaskDelay(400 / portTICK_PERIOD_MS);
        		}

        		free(command);
        		command = NULL;
        	}
        }
    }
}

esp_err_t led_control_init(int gpio) {
	esp_err_t res = led_init(gpio);
	if (res) {
		return res;
	}

	led_control_commands_queue = xQueueCreate( 10, sizeof( uint8_t * ) );
	if (led_control_commands_queue == NULL) {
		return ESP_FAIL;
	}

	xTaskCreate(led_control_task, "led_control_task", 2048, NULL, 10, NULL);

	return ESP_OK;
}

void led_control_submit(uint8_t code) {
	if (led_control_commands_queue) {
		uint8_t * msg = malloc(1);
		*msg = code;
		xQueueSend( led_control_commands_queue, &msg, ( TickType_t ) 0 );
	}
}


#include "cjson_helper.h"

#include "stdlib.h"

uint8_t get_boolean_from_json(cJSON * elem, uint8_t if_true, uint8_t if_false, uint8_t if_not_set) {
	if (cJSON_IsBool(elem)) {
		return cJSON_IsTrue(elem) ? if_true : if_false;
	} else {
		return if_not_set;
	}
}

uint8_t get_number8_from_json(cJSON * elem, uint8_t if_not_set) {
	if (cJSON_IsNumber(elem)) {
		return cJSON_GetNumberValue(elem);
	} else {
		return if_not_set;
	}
}

uint16_t get_number16_from_json(cJSON * elem, uint16_t if_not_set) {
	if (cJSON_IsNumber(elem)) {
		return cJSON_GetNumberValue(elem);
	} else {
		return if_not_set;
	}
}

uint32_t get_number32_from_json(cJSON * elem, uint32_t if_not_set) {
	if (cJSON_IsNumber(elem)) {
		return cJSON_GetNumberValue(elem);
	} else {
		return if_not_set;
	}
}

float get_float_from_json(cJSON * elem, float if_not_set) {
	if (cJSON_IsNumber(elem)) {
		return cJSON_GetNumberValue(elem);
	} else {
		return if_not_set;
	}
}

uint32_t parse_number32_from_json_string(cJSON * elem, uint32_t if_not_set) {
	if (cJSON_IsString(elem)) {
		const char* str = cJSON_GetStringValue(elem);
		char* invptr = NULL;
		long v = strtol(str, &invptr, 0);
		return invptr[0] == 0 ? v : if_not_set;
	} else {
		return if_not_set;
	}
}

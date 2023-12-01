#ifndef MAIN_CJSON_CJSON_HELPER_H_
#define MAIN_CJSON_CJSON_HELPER_H_

#include "cJSON.h"
#include "stdint.h"

uint8_t get_boolean_from_json(cJSON * elem, uint8_t if_true, uint8_t if_false, uint8_t if_not_set);

uint8_t get_number8_from_json(cJSON * elem, uint8_t if_not_set);

uint16_t get_number16_from_json(cJSON * elem, uint16_t if_not_set);

uint32_t get_number32_from_json(cJSON * elem, uint32_t if_not_set);

float get_float_from_json(cJSON * elem, float if_not_set);

uint32_t parse_number32_from_json_string(cJSON * elem, uint32_t if_not_set);

#endif /* MAIN_CJSON_CJSON_HELPER_H_ */

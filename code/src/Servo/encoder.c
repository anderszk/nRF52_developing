#include "encoder.h"

#define LOG_MODULE_NAME ENCODER
LOG_MODULE_REGISTER(LOG_MODULE_NAME);

void test_me_3(){
    LOG_INF("dsadsahehhehehe");
}

int16_t get_encoder(){
    static int16_t value = -1;
    value+=1;
    return value;
}
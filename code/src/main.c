/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */



// #include "initiater.h"
#include "search.h"


#define LOG_MODULE_NAME app
#define WORKING_AREA 270
#define THRESHOLD_DEGREES 3



K_SEM_DEFINE(my_sem,0,1);
LOG_MODULE_REGISTER(LOG_MODULE_NAME);

matrix_3x3 azimuth_reading[WORKING_AREA];
int zero_point_index_azimuth;
int16_t min_encoder_search = 0;
int16_t max_encoder_search = 270;
int increment = 3;

void main(void)
{
	LOG_INF("Hello World! %s\n", CONFIG_BOARD);
	int err = timer_init();
	err = timer_start();
	err = init_bluethooth_scan();	
	init_encoder();
	int16_t size = (max_encoder_search-min_encoder_search)/increment;
	k_sem_take(&my_sem, K_FOREVER);
	sweep_search(0, min_encoder_search, max_encoder_search,increment);
	getReadings(&azimuth_reading, size);
	// set_fake_values(&azimuth_reading);

	value_validater(&azimuth_reading, size);
	for(int i = 0; i < size; i++){
		printk("Encoder: %d,  delta: %d, zigma: %d \n", azimuth_reading[i].encoder, azimuth_reading[i].delta, azimuth_reading[i].zigma);
	}
	update_matrix(&azimuth_reading, &size);
	for(int i = 0; i < size; i++){
		printk("Encoder: %d,  delta: %d, zigma: %d \n", azimuth_reading[i].encoder, azimuth_reading[i].delta, azimuth_reading[i].zigma);
	}
	zero_point_index_azimuth = find_zero_point(azimuth_reading, size);
	printk("Azimuth search done\n");
	printk("Main:\n");

	printk("zero: %d", azimuth_reading[zero_point_index_azimuth].delta);

	// if(err){
	// 	LOG_ERR("err:%d", err);
	// }
	while(1){

	}
}

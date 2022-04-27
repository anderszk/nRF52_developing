/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */



// #include "initiater.h"

#include "initiater.h"
#include "nrfx_qdec.h"
#define LOG_MODULE_NAME app

K_SEM_DEFINE(my_sem,0,1);
K_SEM_DEFINE(servo_sem, 0,1);
LOG_MODULE_REGISTER(LOG_MODULE_NAME);

zeros zero_enc_values;


void main(void)
{
	LOG_INF("Hello World! %s\n", CONFIG_BOARD);
	initiate_modules();
	k_sem_take(&my_sem, K_FOREVER);
	k_sem_give(&servo_sem);
	zero_enc_values = coarse_search();
	printk("azimuth zero enc: %d, horizontal zero end: %d\n", zero_enc_values.azimuth, zero_enc_values.elevation);
	zero_enc_values = fine_search(zero_enc_values);
	printk("Search is done\n");
	printk("Zeroes found at Azimuth: %d, Elevation: %d\n", zero_enc_values.azimuth, zero_enc_values.elevation);
	angle_move_servo(0,zero_enc_values.azimuth);
	// angle_move_servo(1, zero_enc_values.elevation);
	laser_set(0);

	while(1){
		k_sleep(K_FOREVER);
	}
}

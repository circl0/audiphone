/* audiphone - a device to help listen-disabled people with 32-bit MCU
 * Copyright (C) 2016  Allen Yuan
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, mail to <allu_yuan@163.com>
 *
*/

#ifdef USE_AGC_SIMPLE

#include "ap_agc.h"
#include "ap_ringbuffer.h"
#include "platform/ap_hardware.h"
#include "common/ap_log.h"

#define AP_AGC_BUFFER_LENGTH 256

struct ap_agc {
	/* g argument */
	ap_uint32_t arg;

	ap_uint32_t peak;
	
	ap_uint32_t goal;
	
	ap_int16_t data[AP_AGC_BUFFER_LENGTH];

};

static inline ap_int16_t ap_abs(ap_int16_t val) {
	return val > 0 ? val : -val;
}

static ap_agc_t instance;

ap_bool ap_agc_get(ap_agc_t** agc)
{
	*agc = &instance;
	return AP_TRUE;
}

ap_bool ap_agc_init(ap_agc_t* agc)
{
	agc->peak = 1800;
	agc->goal = 1800;
	return AP_TRUE;
}

static ap_bool ap_agc_run(ap_agc_t* agc) {
	ap_uint16_t cur_peak = agc->peak;
	for(ap_uint32_t i = 0; i < AP_AGC_BUFFER_LENGTH; ++i) {
		if (abs(agc->data[i]) < 300) {
			continue;
		}
		if (abs(agc->data[i]) > cur_peak) {
			cur_peak = abs(agc->data[i]);
		}
		//ap_log("******************data:%d, peak:%d\r\n", agc->data[i], cur_peak);
		agc->data[i] = agc->data[i] * (float)(agc->goal / cur_peak);
		//ap_log("==================data:%d\r\n", agc->data[i]);
	}
	if (cur_peak < agc->peak) {
		agc->peak = cur_peak;
	}
	return AP_TRUE;
}

ap_bool ap_agc_start(ap_agc_t* agc)
{
	while(1) {
		ap_agc_read_one_frame(agc);
		//ap_agc_dump_raw_data(agc);
		ap_agc_run(agc);
		//ap_agc_dump_raw_data(agc);
		ap_agc_write_one_frame(agc);
	}
	return AP_TRUE;
}

ap_bool ap_agc_set_one_frame_finish_callback(ap_agc_t* agc, ap_agc_one_frame_finish_callback cb)
{
	return AP_TRUE;
}

ap_bool ap_agc_dump_raw_data(ap_agc_t* agc)
{
	ap_int32_t sum = 0;
	if (agc == NULL) {
		return AP_FALSE;
	}
	ap_log("dump agc data:\r\n");
	for(ap_uint32_t i = 0; i < AP_AGC_BUFFER_LENGTH; ++i) {
		ap_log("%d ", agc->data[i]);
		sum += agc->data[i];
	}
	ap_log("\r\naverage:%d\r\n", sum / AP_AGC_BUFFER_LENGTH);
	return AP_TRUE;
}

ap_bool ap_agc_read_one_frame(ap_agc_t* agc)
{
	ap_uint32_t peak = 0;
	ap_uint32_t trough = 2048;
	if (agc == NULL) {
		return AP_FALSE;
	}
	ap_adc_read_one_frame((ap_uint16_t*)agc->data, AP_AGC_BUFFER_LENGTH);
	
	for(ap_uint32_t i = 0; i < AP_AGC_BUFFER_LENGTH; ++i) {
		agc->data[i] -= 2048;
	}
	return AP_TRUE;
}

ap_bool ap_agc_write_one_frame(ap_agc_t* agc)
{
	if (agc == NULL) {
		return AP_FALSE;
	}
	for(ap_uint32_t i = 0; i < AP_AGC_BUFFER_LENGTH; ++i) {
		agc->data[i] += 2048;
	}
	ap_dac_write_one_frame((ap_uint16_t*)agc->data, AP_AGC_BUFFER_LENGTH);
	return AP_TRUE;
}

#endif
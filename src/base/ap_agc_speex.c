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

#ifdef USE_AGC_SPEEX

#include <string.h>
#include <speex/speex.h>
#include <speex/speex_preprocess.h>
#include "ap_agc.h"
#include "platform/ap_hardware.h"
#include "common/ap_log.h"

#define AP_AGC_BUFFER_LENGTH 250

void _speex_putc(int ch, void *file)
{
  while(1)
  {
  };
}

void _speex_fatal(const char *str, const char *file, int line)
{
  while(1)
  {
  };
}

struct ap_agc {
	ap_int16_t data[AP_AGC_BUFFER_LENGTH];
	ap_uint32_t data_size;
	SpeexPreprocessState *st;
	ap_uint32_t sample_per_second;
	ap_uint32_t resolution;
	ap_uint32_t enable;
	ap_uint32_t vad;
	ap_agc_one_frame_finish_callback cb;
};

static ap_agc_t instance;

ap_bool ap_agc_get(ap_agc_t** agc)
{
	*agc = &instance;
	return AP_TRUE;
}

ap_bool ap_agc_init(ap_agc_t* agc)
{
	if (agc == NULL) {
		return AP_FALSE;
	}
	ap_int32_t ret = 0;
	agc->sample_per_second = 15625;
	agc->resolution = 16;
	agc->st = speex_preprocess_state_init(AP_AGC_BUFFER_LENGTH, agc->sample_per_second);
	if (agc->st < 0) {
		ap_log("speex_preprocess_state_init failed\r\n");
	}
	agc->enable = 1;
	agc->data_size = 0;
	agc->cb = NULL;
	ret = speex_preprocess_ctl(agc->st, SPEEX_PREPROCESS_SET_AGC, &agc->enable);
	if (ret < 0) {
		ap_log("SPEEX_PREPROCESS_SET_AGC failed\r\n");
	}
	float f = 500;
	ret = speex_preprocess_ctl(agc->st, SPEEX_PREPROCESS_SET_AGC_LEVEL, &f);
	if (ret < 0) {
		ap_log("SPEEX_PREPROCESS_SET_AGC_LEVEL failed\r\n");
	}
	
	return AP_TRUE;
}

ap_bool ap_agc_start(ap_agc_t* agc)
{
	ap_int32_t gain = 0;
	ap_int32_t ret = 0;
	while(1) {
		ap_agc_read_one_frame(agc);
		ret = speex_preprocess_run(agc->st, agc->data);
		ap_log("speex_preprocess_run: %d\r\n", ret);
		speex_preprocess_ctl(agc->st, SPEEX_PREPROCESS_GET_AGC_GAIN, &gain);
		ap_log("current gain: %d\r\n", gain);
		ap_agc_dump_raw_data(agc);
		ap_agc_write_one_frame(agc);
	}
}
ap_bool ap_agc_set_one_frame_finish_callback(ap_agc_t* agc, ap_agc_one_frame_finish_callback cb)
{
	if (agc == NULL) {
		return AP_FALSE;
	}
	agc->cb = cb;
	return AP_TRUE;
}

ap_bool ap_agc_dump_raw_data(ap_agc_t* agc)
{
	if (agc == NULL) {
		return AP_FALSE;
	}
	ap_log("dump agc data:\r\n");
	for(ap_uint32_t i = 0; i < AP_AGC_BUFFER_LENGTH; ++i) {
		ap_log("%d ", agc->data[i]);
	}
	ap_log("\r\n");
	return AP_TRUE;
}

ap_bool ap_agc_read_one_frame(ap_agc_t* agc)
{
	if (agc == NULL) {
		return AP_FALSE;
	}
	agc->data_size = ap_adc_read_one_frame((ap_uint16_t*)agc->data, AP_AGC_BUFFER_LENGTH);
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
	ap_dac_write_one_frame((ap_uint16_t*)agc->data, agc->data_size * 2);
	return AP_TRUE;
}
#endif

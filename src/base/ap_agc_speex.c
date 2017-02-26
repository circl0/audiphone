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

#define AP_AGC_BUFFER_LENGTH 10

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
	ap_uint32_t bps;
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
	agc->bps = 16000;
	agc->resolution = 16;
	agc->st = speex_preprocess_state_init(AP_AGC_BUFFER_LENGTH, agc->bps);
	agc->enable = 1;
	agc->data_size = 0;
	agc->cb = NULL;
	speex_preprocess_ctl(agc->st, SPEEX_PREPROCESS_SET_AGC, &agc->enable);
	speex_preprocess_ctl(agc->st, SPEEX_PREPROCESS_SET_AGC_LEVEL, &agc->bps);
	
	return AP_TRUE;
}

ap_bool ap_agc_start(ap_agc_t* agc)
{
	while(1) {
		ap_agc_read_one_frame(agc);
		speex_preprocess_run(agc->st, agc->data);
		//ap_agc_write_one_frame(agc);
		if (agc->cb) {
			agc->cb(agc->data, agc->data_size);
		}
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
	return AP_TRUE;
}

ap_bool ap_agc_write_one_frame(ap_agc_t* agc)
{
	if (agc == NULL) {
		return AP_FALSE;
	}
	ap_dac_write_one_frame((ap_uint16_t*)agc->data, agc->data_size);
	return AP_TRUE;
}
#endif

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

#define AP_AGC_RINGBUFFER_LENGTH 100
#define AP_AGC_THRESHOLD 1024

struct ap_agc {

	/* current peak */
	ap_uint16_t cur_peak;
	ap_uint16_t arg;

	/* period check */
	ap_uint16_t period_count;
	ap_uint16_t period_peak;

	/* agc cal buffer */
	ap_ringbuffer_t rb;
	ap_int16_t data[AP_AGC_RINGBUFFER_LENGTH];

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
	ap_ringbuffer_init(&agc->rb, agc->data, AP_AGC_RINGBUFFER_LENGTH);
	agc->cur_peak = 0;
	agc->arg = 1;
	agc->period_count = 0;
	agc->period_peak = 0;
	return AP_TRUE;
}

ap_bool ap_agc_adjust(ap_agc_t* agc, ap_int16_t val, ap_int16_t* out)
{
	if (agc == NULL) {
		return AP_FALSE;
	}

	/* period check (per 1024 samples) */
	if (agc->period_count < AP_AGC_RINGBUFFER_LENGTH) {
		agc->period_count++;
	}
	else {
		agc->period_count = 0;
		agc->period_peak = ap_ringbuffer_get_max_mod(&agc->rb);
	}
	ap_ringbuffer_add(&agc->rb, val);

	/* single check */
	if (ap_abs(val) > AP_AGC_THRESHOLD) {
		if (ap_abs(val) > agc->cur_peak) {
			agc->cur_peak = ap_abs(val);
		}
	}
	else {
		*out = val;
		return AP_TRUE;
	}

	if (agc->period_peak < agc->cur_peak) {
		agc->cur_peak = agc->period_peak;
		agc->arg = (AP_AGC_THRESHOLD << 4) / agc->cur_peak;
	}

	*out = (val * agc->arg) >> 4;

	return AP_TRUE;
}
#endif
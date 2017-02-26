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

#include "ap_ringbuffer.h"

ap_bool ap_ringbuffer_init(ap_ringbuffer_t* buf, ap_int16_t* rb, ap_uint16_t len)
{
	if (buf == NULL) {
		return AP_FALSE;
	}
	buf->rb = rb;
	buf->capity = len;
	buf->size = 0;
	buf->cur = rb;
	return AP_TRUE;
}

ap_bool ap_ringbuffer_add(ap_ringbuffer_t* buf, ap_int16_t val)
{
	if (buf == NULL) {
		return AP_FALSE;
	}
	if (buf->rb == NULL || buf->cur == NULL) {
		return AP_FALSE;
	}
	*buf->cur = val;
	buf->cur++;
	if (buf->size < buf->capity) {
		buf->size++;
	}
	if (buf->cur - buf->rb > buf->size) {
		buf->cur = buf->rb;
	}
	return AP_TRUE;
}

ap_uint16_t ap_ringbuffer_get_max_mod(ap_ringbuffer_t* buf)
{
	ap_uint16_t i;
	ap_uint16_t ret = 0;

	for (i = 0; i < buf->size; ++i) {
		ret = ret > abs(buf->rb[i]) ? ret : abs(buf->rb[i]);
	}
	return ret;
}

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

#ifndef SRC_BASE_AP_RINGBUFFER_H_
#define SRC_BASE_AP_RINGBUFFER_H_

#include "common/ap_type.h"

typedef struct ap_ringbuffer {
	ap_int16_t* rb;
	ap_uint16_t capity;
	ap_uint16_t size;
	ap_int16_t* cur;
} ap_ringbuffer_t;

ap_bool ap_ringbuffer_init(ap_ringbuffer_t* buf, ap_int16_t* rb, ap_uint16_t len);
ap_bool ap_ringbuffer_add(ap_ringbuffer_t* buf, ap_int16_t val);
ap_uint16_t ap_ringbuffer_get_max_mod(ap_ringbuffer_t* buf);


#endif /* SRC_BASE_AP_RINGBUFFER_H_ */

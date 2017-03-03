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

#ifndef SRC_BASE_AP_AGC_H_
#define SRC_BASE_AP_AGC_H_

#include "common/ap_type.h"

typedef struct ap_agc ap_agc_t;
typedef ap_bool(*ap_agc_one_frame_finish_callback)(ap_int16_t* buffer, ap_uint32_t len);

ap_bool ap_agc_get(ap_agc_t** agc);
ap_bool ap_agc_init(ap_agc_t* agc);
ap_bool ap_agc_start(ap_agc_t* agc);
ap_bool ap_agc_dump_raw_data(ap_agc_t* agc);
ap_bool ap_agc_read_one_frame(ap_agc_t* agc);
ap_bool ap_agc_write_one_frame(ap_agc_t* agc);

#endif /* SRC_BASE_AP_AGC_H_ */

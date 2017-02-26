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

#ifndef SRC_AP_TYPE_H_
#define SRC_AP_TYPE_H_

#include <stdint.h>
#include <stdlib.h>

#define ap_uint8_t uint8_t
#define ap_int8_t int8_t
#define ap_uint16_t uint16_t
#define ap_int16_t int16_t
#define ap_uint32_t uint32_t
#define ap_int32_t int32_t

#define AP_TRUE 1
#define AP_FALSE 0
#define ap_bool ap_uint16_t

#define AP_NULL NULL


#endif /* SRC_AP_TYPE_H_ */

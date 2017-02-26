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

#ifndef SRC_COMMON_AP_LOG_H_
#define SRC_COMMON_AP_LOG_H_

#include "ap_type.h"

#define AP_LOG_ENABLE  1

ap_bool ap_log_system_init();

void ap_log(const ap_int8_t* fmt, ...);

#endif /* SRC_COMMON_AP_LOG_H_ */

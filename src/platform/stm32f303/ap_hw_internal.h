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

#ifndef SRC_HW_MSP430F43X_AP_HW_INTERNAL_H_
#define SRC_HW_MSP430F43X_AP_HW_INTERNAL_H_


#include "common/ap_type.h"

ap_bool ap_systick_timer_init();

ap_bool ap_adc_dac_timer_init();

ap_bool ap_op_init();

ap_bool ap_i2c_init();

ap_bool ap_i2c_write(ap_int8_t ad, ap_int8_t* buf, ap_uint16_t len);


#endif /* SRC_HW_MSP430F43X_AP_HW_INTERNAL_H_ */
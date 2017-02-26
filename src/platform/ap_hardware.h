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

#ifndef SRC_HW_AP_HARDWARE_H_
#define SRC_HW_AP_HARDWARE_H_

#include "common/ap_type.h"

enum ap_adc_type {
	AP_ADC_INVALID = -1,
	AP_ADC_10BIT = 0,
	AP_ADC_11BIT = 1,
	AP_ADC_12BIT = 2,
};

enum ap_dac_type {
	AP_DAC_INVALID = -1,
	AP_DAC_10BIT = 0,
	AP_DAC_11BIT = 1,
	AP_DAC_12BIT = 2,
};


/**
 * Initial the AudiPhone supported hardware system
 *
 * @return Initial result.
 *
 * @since 0.1
 */
ap_bool ap_system_init();

/**
 * Enable the interrupts.
 *
 * @return Interrupts enable result.
 *
 * @since 0.1
 */
ap_bool ap_interrupt_enable();

/**
 * Disable the interrupts.
 *
 * @return Interrupts disable result.
 *
 * @since 0.1
 */
ap_bool ap_interrupt_disable();

/**
 * Initial the adc.
 *
 * @param[in] type adc resolution type
 *
 * @return Adc initial result.
 *
 * @since 0.1
 */
ap_bool ap_adc_init(ap_int16_t type);

/**
 * Read from adc.
 *
 * @param[out] val adc value
 *
 * @return Adc read result.
 *
 * @since 0.2
 */
ap_uint32_t ap_adc_read_one_frame(ap_uint16_t* buf, ap_uint32_t len);

/**
 * Initial the dac.
 *
 * @param[in] type dac resolution type
 *
 * @return Dac initial result.
 *
 * @since 0.1
 */
ap_bool ap_dac_init(ap_int16_t type);

/**
 * Write to adc.
 *
 * @param[in] val dac value
 *
 * @return Dac write result.
 *
 * @since 0.2
 */
ap_uint32_t ap_dac_write_one_frame(ap_uint16_t* buf, ap_uint32_t len);

/**
 * Initial the uart.
 *
 * @return Uart initial result.
 *
 * @since 0.1
 */
ap_bool ap_uart_init();

/**
 * Write to uart.
 *
 * @param[in] val uart value
 *
 * @return Uart write result.
 *
 * @since 0.1
 */
ap_bool ap_uart_putchar(ap_int8_t val);

/**
 * Get the tickcount.
 *
 * @return tickcount.
 *
 * @since 0.1
 */
ap_uint32_t ap_get_tickcount();

#endif /* SRC_HW_AP_HARDWARE_H_ */

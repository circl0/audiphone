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

#include "ap_hardware.h"
#include "ap_hw_config.h"
#include "ap_hw_internal.h"

static ap_bool ap_system_timer_init()
{
	ap_systick_timer_init();
	ap_adc_dac_timer_init();
	return AP_TRUE;
}

static ap_bool ap_system_clock_init()
{
  	return AP_TRUE;
}

ap_bool ap_interrupt_enable()
{
	__enable_irq();
	return AP_TRUE;
}

ap_bool ap_interrupt_disable()
{
	__disable_irq();
	return AP_TRUE;
}

ap_bool ap_system_init()
{
	//ap_interrupt_disable();
	
	ap_system_clock_init();
	ap_system_timer_init();
	
	ap_uart_init();
	//ap_op_init();
	ap_adc_init(AP_ADC_12BIT);
	//ap_dac_init(AP_DAC_12BIT);

	//ap_interrupt_enable();
	
	return AP_TRUE;
}

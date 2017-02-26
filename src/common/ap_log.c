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

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "ap_log.h"
#include "ap_hardware.h"



ap_bool ap_log_system_init()
{
#ifdef AP_LOG_ENABLE
	return ap_uart_init();
#else
	return AP_TRUE;
#endif
}

void ap_log(const ap_int8_t* fmt, ...)
{
#ifdef AP_LOG_ENABLE
	va_list args;
	va_start(args, fmt);
	vprintf((const char*)fmt, args);
	va_end(args);
#endif
}

/* redirect stdout(override methods in msp430 runtime libc) */
int fputc(int ch, FILE *f)
{
	return (int) ap_uart_putchar((ap_uint8_t) ch);
}

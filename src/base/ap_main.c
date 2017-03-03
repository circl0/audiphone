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

#include "platform/ap_hardware.h"
#include "base/ap_agc.h"
#include "common/ap_log.h"
#include "common/ap_delay.h"

static ap_agc_t* agc;

int main(void) 
{
	ap_system_init();
	
	ap_log("ap system init has finished...\r\n");
	
	ap_agc_get(&agc);
	
	ap_agc_init(agc);

	ap_log("ap_agc_start\r\n");
	ap_agc_start(agc);

}

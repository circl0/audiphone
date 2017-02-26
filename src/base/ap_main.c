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

static ap_bool ap_dump(ap_int16_t* buffer, ap_uint32_t len)
{
	ap_agc_dump_raw_data(agc);
	return AP_TRUE;
}

int main(void) {
	
	ap_uint16_t val;
	ap_int16_t in;
	ap_int16_t out;

	ap_system_init();
	
	ap_log("ap system init has finished...\r\n");
	
	ap_agc_get(&agc);
	
	ap_agc_init(agc);
	ap_agc_set_one_frame_finish_callback(agc, ap_dump);
	ap_log("ap_agc_start\r\n");
	ap_agc_start(agc);

}

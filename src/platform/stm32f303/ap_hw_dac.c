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

#include <string.h>
#include "ap_hardware.h"
#include "ap_hw_config.h"
#include "ap_hw_internal.h"

#define AP_AGC_BUFFER_LENGTH 10

static volatile ap_bool ap_dac_writable;
static ap_uint16_t ap_dac_val[AP_AGC_BUFFER_LENGTH];

#define DAC_DHR12R1_ADDRESS      0x40007408 

ap_bool ap_dac_init(ap_int16_t type)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	DAC_InitTypeDef DAC_InitStructure;
	DAC_InitStructure.DAC_Trigger = DAC_Trigger_T2_TRGO;
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_Buffer_Switch = DAC_BufferSwitch_Disable;
	DAC_Init(DAC1, DAC_Channel_1, &DAC_InitStructure);
	DAC_Cmd(DAC1, DAC_Channel_1, ENABLE);
	
	DMA_InitTypeDef DMA_InitStructure;
	DMA_InitStructure.DMA_PeripheralBaseAddr = DAC_DHR12R1_ADDRESS;
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ap_dac_val;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStructure.DMA_BufferSize = 10;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA2_Channel3, &DMA_InitStructure);
	
	DMA_ITConfig(DMA2_Channel3, DMA_IT_TC, ENABLE);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Channel3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	DMA_Cmd(DMA2_Channel3, ENABLE);
	DAC_DMACmd(DAC1, DAC_Channel_1, ENABLE);
	
	return AP_TRUE;
}

ap_uint32_t ap_dac_write_one_frame(ap_uint16_t* buf, ap_uint32_t len)
{
	ap_uint32_t cpy_len = AP_AGC_BUFFER_LENGTH;
	while (!ap_dac_writable);
	ap_interrupt_disable();
	ap_dac_writable = AP_FALSE;
	if (len < AP_AGC_BUFFER_LENGTH) {
		cpy_len = len;
	}
	memcpy(ap_dac_val, buf, sizeof(ap_uint16_t) * cpy_len);
	ap_interrupt_enable();
	return cpy_len / sizeof(ap_uint16_t);
}

void DMA2_Channel3_IRQHandler(void)
{
  if(DMA_GetITStatus(DMA2_IT_TC3))
  {
    ap_dac_writable = AP_TRUE;
    DMA_ClearITPendingBit(DMA2_IT_TC3);
  }
}

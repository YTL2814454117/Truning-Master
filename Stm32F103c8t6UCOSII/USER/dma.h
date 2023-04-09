/*
 * @Author: 睦疏
 * @Date: 2023-03-10 16:31:34
 * @LastEditors: 睦疏
 * @LastEditTime: 2023-04-02 09:08:30
 * @FilePath: \Sample\User\dma.h
 * @Description:
 *
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved.
 */
#ifndef DMA_H
#define DMA_H

#include "stm32f10x_dma.h"
#include "misc.h"
#include "stm32f10x_rcc.h"
#define SENDBUFF_SIZE 5000
#define USART1_DR_Base 0x40013804 // Define usart1 data register base
extern uint8_t SendBuff[SENDBUFF_SIZE];
void DMAConfig(void);

#endif
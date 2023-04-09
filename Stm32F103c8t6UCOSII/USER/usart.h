/*
 * @Author: 睦疏
 * @Date: 2023-03-09 09:25:45
 * @LastEditors: 睦疏
 * @LastEditTime: 2023-03-30 08:24:02
 * @FilePath: \Sample\User\usart.h
 * @Description:
 *
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved.
 */
#ifndef USART_H
#define USART_H

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "stdio.h"

void Usart1Config(void);
void Usart2Config(void);
void Usart3Config(void);

#endif
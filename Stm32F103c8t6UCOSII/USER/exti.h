/*
 * @Author: 睦疏
 * @Date: 2023-03-08 21:14:07
 * @LastEditors: 睦疏
 * @LastEditTime: 2023-04-01 15:04:49
 * @FilePath: \Sample\User\exti.h
 * @Description:
 *
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved.
 */
#ifndef EXTI_H
#define EXTI_H
#include "stm32f10x_gpio.h"
#include "stm32f10x.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
#include "stm32f10x.h"

void Key13ExtiConfig(void);
void Key2ExtiConfig(void);
void Key4ExtiConfig(void);

#endif
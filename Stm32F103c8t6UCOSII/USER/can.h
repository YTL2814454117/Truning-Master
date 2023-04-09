/*
 * @Author: 睦疏
 * @Date: 2023-04-04 19:28:56
 * @LastEditors: 睦疏
 * @LastEditTime: 2023-04-04 20:38:11
 * @FilePath: \Sample\User\can.h
 * @Description:
 *
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved.
 */
#ifndef CAN_H
#define CAN_H

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
#include "stm32f10x.h"
#include "stm32f10x_can.h"

void CAN_Config(void);
void CAN_SetMsg(void);
extern CanTxMsg TxMessage; // 发送缓冲区
extern CanRxMsg RxMessage; // 接收缓冲区
extern int flag;
#endif
/*
 * @Author: 睦疏
 * @Date: 2023-03-08 18:49:29
 * @LastEditors: 睦疏
 * @LastEditTime: 2023-04-01 08:10:32
 * @FilePath: \Sample\User\led.c
 * @Description:
 *
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved.
 */
/*
 * @Author: 睦疏
 * @Date: 2023-03-08 18:49:29
 * @LastEditors: 睦疏
 * @LastEditTime: 2023-03-12 21:57:27
 * @FilePath: \STM32F103Template\User\src\led.c
 * @Description:
 *
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved.
 */
#include "led.h"
#include "stdio.h"
#include "delay.h"
#include "stm32f10x_bkp.h"

Led L2 = {.GPIO = GPIOB, .Pin = GPIO_Pin_5};
Led L3 = {.GPIO = GPIOC, .Pin = GPIO_Pin_14};
Led L4 = {.GPIO = GPIOC, .Pin = GPIO_Pin_13};
Led L5 = {.GPIO = GPIOB, .Pin = GPIO_Pin_15};
Led L6 = {.GPIO = GPIOA, .Pin = GPIO_Pin_8};
Led L7 = {.GPIO = GPIOA, .Pin = GPIO_Pin_15};
Led L8 = {.GPIO = GPIOB, .Pin = GPIO_Pin_3};
Led L9 = {.GPIO = GPIOB, .Pin = GPIO_Pin_4};

// LED IO 初始化
void LEDInit(void)
{

    // GPIO 初始化设置
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);   // 使能GPIO时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_8; // LED对应 IO 口
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;       // 50MHz
    GPIO_Init(GPIOA, &GPIO_InitStructure);                  // 初始化 GPIO

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_5 | GPIO_Pin_15; // LED对应 IO 口
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                     // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;                    // 50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);     // 使能AFIO
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); // 改变指定管脚的映射 GPIO_Remap_SWJ_JTAGDisable ，JTAG-DP 禁用 + SW-DP 使能
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);    // 使能 PB 端口时钟
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;                // LED1-->PB.4 端口配置, 推挽输出
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;         // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        // IO 口速度为 50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);                   // 初始化 GPIOB.4
    GPIO_SetBits(GPIOB, GPIO_Pin_4);                         // PB.4 输出高

    BKP_TamperPinCmd(DISABLE);                               // 禁用rtc
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14; // LED对应 IO 口
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;         // 推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;        // 50MHz
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_SetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_15);
    GPIO_SetBits(GPIOB, GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_15);
    GPIO_SetBits(GPIOC, GPIO_Pin_13 | GPIO_Pin_14); // GPIO 设置灯的初始状态
}

void WaterLamp()
{
    // Running water lamp
    LedOFF(L2);
    delay_ms(200);
    LedON(L2);
    LedOFF(L3);
    delay_ms(200);
    LedON(L3);
    LedOFF(L4);
    delay_ms(200);
    LedON(L4);
    LedOFF(L5);
    delay_ms(200);
    LedON(L5);
    LedOFF(L6);
    delay_ms(200);
    LedON(L6);
    LedOFF(L7);
    delay_ms(200);
    LedON(L7);
    LedOFF(L8);
    delay_ms(200);
    LedON(L8);
    LedOFF(L9);
    delay_ms(200);
    LedON(L9);
}

/**
 * @brief
 *
 * @param L
 */
void LedOFF(Led L)
{
    GPIO_ResetBits(L.GPIO, L.Pin);
}

void LedON(Led L)
{
    GPIO_SetBits(L.GPIO, L.Pin);
}

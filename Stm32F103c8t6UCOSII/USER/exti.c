/*
 * @Author: 睦疏
 * @Date: 2023-03-08 21:14:39
 * @LastEditors: 睦疏
 * @LastEditTime: 2023-04-02 08:27:47
 * @FilePath: \Sample\User\exti.c
 * @Description:
 *
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved.
 */
#include "exti.h"
// Creat function for NVIC config
// Static keyword makes the function be only transferred in this file
static void Key4NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    /*Configure one bit for preemption priority*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    /*配置P[A|B|C|D|E]0为中断源*/
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

static void Key123NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    /*Configure one bit for preemption priority*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    /*配置P[A|B|C|D|E]0为中断源*/
    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void Key13ExtiConfig(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure; // Create initialization structure for gpio and exti
    /*config the extiline(PD01）clock and AFIO clock*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
    /*config the NVIC（PD01）*/
    Key123NVIC_Configuration();
    /*EXTI line gpio config（PD01）*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; // Pull up input
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    /*EXTI line(PD01)mode config*/
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource13);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);
    EXTI_InitStructure.EXTI_Line = EXTI_Line13;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; // Falling edge interrupt
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
    EXTI_InitStructure.EXTI_Line = EXTI_Line14;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; // Falling edge interrupt
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
}

void Key2ExtiConfig(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure; // Create initialization structure for gpio and exti
    /*config the extiline(PC15）clock and AFIO clock*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);
    /*config the NVIC（PC15）*/
    Key123NVIC_Configuration();
    /*EXTI line gpio config（PC15）*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; // Pull up input
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    /*EXTI line(PC15)mode config*/
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource15);
    EXTI_InitStructure.EXTI_Line = EXTI_Line15;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; // Falling edge interrupt
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
}

/**
 * @brief Key4中断配置
 *
 */
void Key4ExtiConfig(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure; // Create initialization structure for gpio and exti
    /*config the extiline(PA0）clock and AFIO clock*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    /*config the NVIC（PA0）*/
    Key4NVIC_Configuration();
    /*EXTI line gpio config（PA0）*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; // Pull up input
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    /*EXTI line(PA0)mode config*/
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
    EXTI_InitStructure.EXTI_Line = EXTI_Line0;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; // Falling edge interrupt
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
}
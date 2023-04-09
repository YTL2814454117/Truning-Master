/*
 * @Author: 睦疏
 * @Date: 2022-01-15 15:17:29
 * @LastEditors: 睦疏
 * @LastEditTime: 2023-04-09 20:22:08
 * @FilePath: \Stm32f103c8t6UCOSII\USER\main.c
 * @Description:
 *
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved.
 */
#include "sys.h"
#include "delay.h"
#include "bmp.h"
#include "includes.h"

/////////////////////////UCOSII任务设置///////////////////////////////////
// START 任务
// 设置任务优先级
#define START_TASK_PRIO 10 // 开始任务的优先级设置为最低
// 设置任务堆栈大小
#define START_STK_SIZE 64
// 任务堆栈
OS_STK START_TASK_STK[START_STK_SIZE];
// 任务函数
void start_task(void *pdata);

// LED任务
// 设置任务优先级
#define LED_TASK_PRIO 6
// 设置任务堆栈大小
#define LED_STK_SIZE 64
// 任务堆栈
OS_STK LED_TASK_STK[LED_STK_SIZE];
// 任务函数
void led_task(void *pdata);

// oled任务
// 设置任务优先级
#define Oled_TASK_PRIO 7
// 设置任务堆栈大小
#define Oled_STK_SIZE 64
// 任务堆栈
OS_STK Oled_TASK_STK[Oled_STK_SIZE];
// 任务函数
void Oled_task(void *pdata);

uint8_t SendBuff[SENDBUFF_SIZE]; // Create buffer array for data to be transferred
CanTxMsg TxMessage;				 // 发送缓冲区
CanRxMsg RxMessage;				 // 接收缓冲区
uint16_t i;
u8 t = ' ';
int flag = 0;

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	delay_init();									// 延时函数初始化
	LEDInit();
	OLED_Init();
	OSInit();																							 // 初始
	OSTaskCreate(start_task, (void *)0, (OS_STK *)&START_TASK_STK[START_STK_SIZE - 1], START_TASK_PRIO); // 创建起始任务
	OSStart();
}

// 开始任务
void start_task(void *pdata)
{
	OS_CPU_SR cpu_sr = 0;
	pdata = pdata;
	OS_ENTER_CRITICAL(); // 进入临界区(无法被中断打断)
	OSTaskCreate(led_task, (void *)0, (OS_STK *)&LED_TASK_STK[LED_STK_SIZE - 1], LED_TASK_PRIO);
	OSTaskCreate(Oled_task, (void *)0, (OS_STK *)&Oled_TASK_STK[Oled_STK_SIZE - 1], Oled_TASK_PRIO);
	OSTaskSuspend(START_TASK_PRIO); // 挂起起始任务.
	OS_EXIT_CRITICAL();				// 退出临界区(可以被中断打断)
}

// LED0任务
void led_task(void *pdata)
{
	while (1)
	{
		WaterLamp();
	};
}

// Oled任务
void Oled_task(void *pdata)
{
	while (1)
	{
		OLED_Refresh();
		OLED_ScrollDisplay(16, 4, 1);
		OLED_Refresh();
	};
}

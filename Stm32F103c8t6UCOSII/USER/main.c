/*
 * @Author: ����
 * @Date: 2022-01-15 15:17:29
 * @LastEditors: ����
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

/////////////////////////UCOSII��������///////////////////////////////////
// START ����
// �����������ȼ�
#define START_TASK_PRIO 10 // ��ʼ��������ȼ�����Ϊ���
// ���������ջ��С
#define START_STK_SIZE 64
// �����ջ
OS_STK START_TASK_STK[START_STK_SIZE];
// ������
void start_task(void *pdata);

// LED����
// �����������ȼ�
#define LED_TASK_PRIO 6
// ���������ջ��С
#define LED_STK_SIZE 64
// �����ջ
OS_STK LED_TASK_STK[LED_STK_SIZE];
// ������
void led_task(void *pdata);

// oled����
// �����������ȼ�
#define Oled_TASK_PRIO 7
// ���������ջ��С
#define Oled_STK_SIZE 64
// �����ջ
OS_STK Oled_TASK_STK[Oled_STK_SIZE];
// ������
void Oled_task(void *pdata);

uint8_t SendBuff[SENDBUFF_SIZE]; // Create buffer array for data to be transferred
CanTxMsg TxMessage;				 // ���ͻ�����
CanRxMsg RxMessage;				 // ���ջ�����
uint16_t i;
u8 t = ' ';
int flag = 0;

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // �����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	delay_init();									// ��ʱ������ʼ��
	LEDInit();
	OLED_Init();
	OSInit();																							 // ��ʼ
	OSTaskCreate(start_task, (void *)0, (OS_STK *)&START_TASK_STK[START_STK_SIZE - 1], START_TASK_PRIO); // ������ʼ����
	OSStart();
}

// ��ʼ����
void start_task(void *pdata)
{
	OS_CPU_SR cpu_sr = 0;
	pdata = pdata;
	OS_ENTER_CRITICAL(); // �����ٽ���(�޷����жϴ��)
	OSTaskCreate(led_task, (void *)0, (OS_STK *)&LED_TASK_STK[LED_STK_SIZE - 1], LED_TASK_PRIO);
	OSTaskCreate(Oled_task, (void *)0, (OS_STK *)&Oled_TASK_STK[Oled_STK_SIZE - 1], Oled_TASK_PRIO);
	OSTaskSuspend(START_TASK_PRIO); // ������ʼ����.
	OS_EXIT_CRITICAL();				// �˳��ٽ���(���Ա��жϴ��)
}

// LED0����
void led_task(void *pdata)
{
	while (1)
	{
		WaterLamp();
	};
}

// Oled����
void Oled_task(void *pdata)
{
	while (1)
	{
		OLED_Refresh();
		OLED_ScrollDisplay(16, 4, 1);
		OLED_Refresh();
	};
}

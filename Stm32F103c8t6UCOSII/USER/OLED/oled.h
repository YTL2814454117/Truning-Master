/*
 * @Author: ����
 * @Date: 2020-04-10 09:47:04
 * @LastEditors: 睦疏
 * @LastEditTime: 2023-04-10 21:48:46
 * @FilePath: \Truning-Master(UCOSII)\Stm32F103c8t6UCOSII\USER\OLED\oled.h
 * @Description:
 *
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved.
 */

#ifndef __OLED_H
#define __OLED_H

// #include "sys.h"
#include "stdlib.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

//-----------------OLED�˿ڶ���----------------

#define OLED_SCL_Clr() GPIO_ResetBits(GPIOB, GPIO_Pin_6) // SCL
#define OLED_SCL_Set() GPIO_SetBits(GPIOB, GPIO_Pin_6)

#define OLED_SDA_Clr() GPIO_ResetBits(GPIOB, GPIO_Pin_7) // DIN
#define OLED_SDA_Set() GPIO_SetBits(GPIOB, GPIO_Pin_7)

#define OLED_RES_Clr() GPIO_ResetBits(GPIOB, GPIO_Pin_2) // RES
#define OLED_RES_Set() GPIO_SetBits(GPIOB, GPIO_Pin_2)

#define OLED_CMD 0  // д����
#define OLED_DATA 1 // д����

#define DELAY_TIME 100 // 延迟时间（ms）
#define SCROLL_SPEED 1 // 滚动速度，每次滚动的像素数

void OLED_ClearPoint(u8 x, u8 y);
void OLED_ColorTurn(u8 i);
void OLED_DisplayTurn(u8 i);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_WaitAck(void);
void Send_Byte(u8 dat);
void OLED_WR_Byte(u8 dat, u8 mode);
void OLED_DisPlay_On(void);
void OLED_DisPlay_Off(void);
void OLED_Refresh(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x, u8 y, u8 t);
void OLED_DrawLine(u8 x1, u8 y1, u8 x2, u8 y2, u8 mode);
void OLED_DrawCircle(u8 x, u8 y, u8 r);
void OLED_ShowChar(u8 x, u8 y, u8 chr, u8 size1, u8 mode);
void OLED_ShowChar6x8(u8 x, u8 y, u8 chr, u8 mode);
void OLED_ShowString(u8 x, u8 y, u8 *chr, u8 size1, u8 mode);
void OLED_ShowNum(u8 x, u8 y, u32 num, u8 len, u8 size1, u8 mode);
void OLED_ShowChinese(u8 x, u8 y, u8 num, u8 size1, u8 mode);
void OLED_ScrollDisplay(u8 num, u8 space, u8 mode);
void OLED_ShowPicture(u8 x, u8 y, u8 sizex, u8 sizey, u8 BMP[], u8 mode);
void OLED_ScrollDisplayPicture(u8 BMP[], u8 space, u8 mode);
void OLED_Init(void);

#endif

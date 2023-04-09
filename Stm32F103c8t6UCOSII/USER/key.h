#ifndef KEY_H
#define KEY_H

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "delay.h"

#define KeyON 1  // 按键按下
#define KeyOFF 0 // 按键没按下

typedef struct
{
    GPIO_TypeDef *GPIO;
    uint16_t Pin;
} Key;

extern Key K1;
extern Key K2;
extern Key K3;
extern Key K4; // 声明成外部变量

void KeyGPIOInit(void);
int KeyScan(Key K);

#endif
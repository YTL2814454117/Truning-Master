#ifndef LED_H
#define LED_H

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

typedef struct Led
{
    GPIO_TypeDef *GPIO;
    uint16_t Pin;
} Led;

#define LED
#ifdef LED
extern Led L2;
extern Led L3;
extern Led L4;
extern Led L5;
extern Led L6;
extern Led L7;
extern Led L8;
extern Led L9;
#endif

void LEDInit(void);
void WaterLamp();
void LedOFF(Led L);
void LedON(Led L);
#endif
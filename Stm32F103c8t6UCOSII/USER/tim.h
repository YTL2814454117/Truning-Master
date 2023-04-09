#ifndef TIM_H
#define TIM_H

#include "misc.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"
#include "led.h"

void TIM3_Int_Init(u16 arr, u16 psc);

#endif
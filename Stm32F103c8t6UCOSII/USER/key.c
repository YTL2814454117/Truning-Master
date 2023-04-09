/**
 * @file key.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-04-01
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "key.h"
// 初始化按键结构体
Key K1 = {.GPIO = GPIOB, .Pin = GPIO_Pin_14};
Key K2 = {.GPIO = GPIOC, .Pin = GPIO_Pin_15};
Key K3 = {.GPIO = GPIOB, .Pin = GPIO_Pin_13};
Key K4 = {.GPIO = GPIOA, .Pin = GPIO_Pin_0};

void KeyGPIOInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    /*开启按键端口的时钟*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    // GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14;
    // GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    // GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

int KeyScan(Key K)
{
    /*检测是否有按键按下*/
    if (GPIO_ReadInputDataBit(K.GPIO, K.Pin) == 1)
        return KeyOFF;
    {
        /*延时消抖*/
        delay_ms(10);
        if (GPIO_ReadInputDataBit(K.GPIO, K.Pin) == 1)
            return KeyOFF;
        {
            /*等待按键释放*/
            while (GPIO_ReadInputDataBit(K.GPIO, K.Pin) == KeyON)
                ;
            return KeyON;
        }
    }
}
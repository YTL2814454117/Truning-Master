/*
 * @Author: 睦疏
 * @Date: 2023-04-04 19:12:50
 * @LastEditors: 睦疏
 * @LastEditTime: 2023-04-04 22:09:43
 * @FilePath: \Sample\User\can.c
 * @Description:
 *
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved.
 */
/*
 * @Author: 睦疏
 * @Date: 2023-04-04 19:28:43
 * @LastEditors: 睦疏
 * @LastEditTime: 2023-04-04 20:27:49
 * @FilePath: \Sample\User\can.c
 * @Description:
 *
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved.
 */
#include "can.h"

/*
 *函数名：CAN_GPIO_Config
 *描述：CAN的GPIO配置,PB8上拉输入,PB9推挽输出
 *输入：无
 *输出：无
 *调用：内部调用
 */
static void CAN_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /*外设时钟设置*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

    /*IO设置*/
    GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE); // 使用GPIO的重映射功能

    /*Configure CAN pin：RX PB8*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // 上拉输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /*Configure CAN pin：TX PB9*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; // 复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/*
2.*函数名：CAN_NVIC_Config
3.*描述：CAN的NVIC配置,第1优先级组,0优先级
4.*输入：无
5.*输出：无
6.*调用：内部调用
7.*/
static void CAN_NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
    /*Configure one bit for preemption priority*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    /*中断设置*/ /*CAN1 RX0中断*/
    NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // 抢先级0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;        // 子优先级为0
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/*
 *函数名：CAN_Mode_Config
 *描述：CAN的模式配置
 *输入：无
 *输出：无
 *调用：内部调用
 */
static void CAN_Mode_Config(void)
{
    CAN_InitTypeDef CAN_InitStructure;
    /*******************CAN通信参数设置*******************/
    /*CAN寄存器初始化*/
    CAN_DeInit(CAN1);
    CAN_StructInit(&CAN_InitStructure);
    /*CAN单元初始化*/
    CAN_InitStructure.CAN_TTCM = DISABLE;
    /*MCR-TTCM关闭时间触发通信模式使能*/
    CAN_InitStructure.CAN_ABOM = ENABLE;
    /*MCR-ABOM自动离线管理*/
    CAN_InitStructure.CAN_AWUM = ENABLE;
    /*MCR-AWUM自动唤醒模式*/
    CAN_InitStructure.CAN_NART = DISABLE;
    /*MCR-NART禁止报文自动重传DISABLE=自动重传*/
    CAN_InitStructure.CAN_RFLM = DISABLE;
    /*MCR-RFLM接收FIFO锁定模式DISABLE-溢出时新报文会覆盖原有报文*/
    CAN_InitStructure.CAN_TXFP = DISABLE;
    /*MCR-TXFP发送FIFO优先级DISABLE-优先级取决于报文标示符*/
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal; /*正常工作模式*/
    CAN_InitStructure.CAN_SJW = CAN_SJW_2tq;
    /*BTR-SJW重新同步跳跃宽度2个时间单元*/
    CAN_InitStructure.CAN_BS1 = CAN_BS1_7tq;
    /*BTR-TS1时间段1占用了6个时间单元*/
    CAN_InitStructure.CAN_BS2 = CAN_BS2_4tq;
    /*BTR-TS1时间段2占用了3个时间单元*/
    CAN_InitStructure.CAN_Prescaler = 3;
    /*BTR-BRP波特率分频器定义了时间单元的时间长度36/
    (1+7+4)/3=1Mbps*/
    CAN_Init(CAN1, &CAN_InitStructure);
}

/*
 *函数名：CAN_Filter_Config
 *描述：CAN的过滤器配置
 *输入：无
 *输出：无
 *调用：内部调用
 */
static void CAN_Filter_Config(void)
{
    CAN_FilterInitTypeDef CAN_FilterInitStructure;
    /*CAN过滤器初始化*/
    CAN_FilterInitStructure.CAN_FilterNumber = 0; // 过滤器组0
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
    /*工作在标识符屏蔽位模式*/
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
    /*过滤器位宽为单个32位。*/
    /*使能报文标示符过滤器按照标示符的内容进行比对过滤,扩展ID不是如
    下的就抛弃掉,是的话,会存入FIFO0*/
    CAN_FilterInitStructure.CAN_FilterIdHigh = (((u32)0x1314 << 3) & 0xFFFF0000) >> 16;                  /*要过滤的ID高位*/
    CAN_FilterInitStructure.CAN_FilterIdLow = (((u32)0x1314 << 3) | CAN_ID_EXT | CAN_RTR_DATA) & 0xFFFF; /*要过滤的ID低位*/
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0xFFFF;                                               /*过滤器高16位每位必须匹配*/
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0xFFFF;                                                /*过滤器低16位每位必须匹配*/
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0;                                 /*过滤器被关联到FIFO0*/
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
    /*使能过滤器*/
    CAN_FilterInit(&CAN_FilterInitStructure);
    /*CAN通信中断使能*/
    CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
}

/*
 *函数名：CAN_Config
 *描述：完整配置CAN的功能
 *输入：无
 *输出：无
 *调用：外部调用
 */
void CAN_Config(void)
{
    CAN_GPIO_Config();
    CAN_NVIC_Config();
    CAN_Mode_Config();
    CAN_Filter_Config();
}

/*
 *函数名：CAN_SetMsg
 *描述："主机"的CAN通信报文内容设置
 *输入：无
 *输出：无
 *调用：外部调用
 */
void CAN_SetMsg(void)
{
    // TxMessage.StdId=0x00;
    TxMessage.ExtId = 0x1314;     // 使用的扩展ID
    TxMessage.IDE = CAN_ID_EXT;   // 扩展模式
    TxMessage.RTR = CAN_RTR_DATA; // 发送的是数据
    TxMessage.DLC = 2;            // 数据长度为2字节
    TxMessage.Data[0] = 0xAB;
    TxMessage.Data[1] = 0xCD;
}

void USB_LP_CAN1_RX0_IRQHandler(void)
{

    /*从邮箱中读出报文*/
    CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);

    /*比较ID和数据是否为0x1314及DCBA*/
    if ((RxMessage.ExtId == 0x1314) &&
        (RxMessage.IDE == CAN_ID_EXT) && (RxMessage.DLC == 2) &&
        ((RxMessage.Data[1] | RxMessage.Data[0] << 8) == 0xDCBA))
    {
        flag = 0; // 接收成功
    }
    else
    {
        flag = 0xff; // 接收失败
    }
}
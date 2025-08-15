/**
 ******************************************************************************
 * @file     main.c
 * @author   ����ԭ���Ŷ�(ALIENTEK)
 * @version  V1.0
 * @date     2020-08-20
 * @brief    �½�����ʵ��-HAL��汾 ʵ��
 * @license  Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ******************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� STM32F103 ������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 ******************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "LED.H"
#include "KEY.h"
#include "uart.h"
#include "WATCHDOG.h"
uint16_t cnt;
uint16_t b;

uint8_t Key_val, Key_down, Key_old;

int main(void)
{

    HAL_Init();                         /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9); /* ����ʱ��, 72Mhz */
    delay_init(72);                     /* ��ʱ��ʼ�� */
    LED_Init();
    UART_INIT(115200);

    if (__HAL_RCC_GET_FLAG(RCC_FLAG_WWDGRST) != RESET)
    {
        printf("���Ź���λ\n");
        __HAL_RCC_CLEAR_RESET_FLAGS();
    }
    else
    {
        printf("ϵͳ��λ\n");
    }
   
    //Wwdg_Init();
    //Iwdg_Init();
    //Key_Init();
    //Key_Exti_Init();

    while (1)
    {
        // if(G_RX_FLAG)
        // {
        //     HAL_UART_Transmit(&UART1,&G_RX_BUFFER,1,1000);
        //     while(__HAL_UART_GET_FLAG(&UART1,UART_FLAG_TC) != 1);
        //     G_RX_FLAG = 0;
        //     printf("���\n");
        // }

    }
}

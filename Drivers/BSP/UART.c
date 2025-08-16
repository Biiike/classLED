#include "uart.h"
uint8_t G_RX_BUFFER;
UART_HandleTypeDef UART1;
uint8_t G_RX_FLAG;
#include "stdio.h"

#pragma import(__use_no_semihosting)

struct __FILE
{
    int handle;
};

FILE __stdout;

int fputc(int ch, FILE *f)
{
    while ((USART1->SR & 0X40) == 0)
        ;

    USART1->DR = (uint8_t)ch;
    return ch;
}

void UART_INIT(uint32_t baud)
{
    UART1.Instance = USART1;
    UART1.Init.BaudRate = baud;
    UART1.Init.HwFlowCtl = 0;
    UART1.Init.Mode = UART_MODE_TX_RX;
    UART1.Init.Parity = UART_PARITY_NONE;
    UART1.Init.StopBits = UART_STOPBITS_1;
    UART1.Init.WordLength = UART_WORDLENGTH_8B;

    HAL_UART_Init(&UART1);
    HAL_UART_Receive_IT(&UART1, &G_RX_BUFFER, 1);
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_USART1_CLK_ENABLE();

        GPIO_InitTypeDef UART1_GPIO = {0};
        UART1_GPIO.Mode = GPIO_MODE_AF_PP;
        UART1_GPIO.Pin = GPIO_PIN_9;
        UART1_GPIO.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &UART1_GPIO);

        UART1_GPIO.Mode = GPIO_MODE_AF_INPUT;
        UART1_GPIO.Pin = GPIO_PIN_10;
        UART1_GPIO.Pull = GPIO_PULLUP;
        UART1_GPIO.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &UART1_GPIO);

        HAL_NVIC_SetPriority(USART1_IRQn, 2, 0);
        HAL_NVIC_EnableIRQ(USART1_IRQn);
    }
}

void USART1_IRQHandler(void)
{
    HAL_UART_IRQHandler(&UART1);
    HAL_UART_Receive_IT(&UART1, &G_RX_BUFFER, 1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        G_RX_FLAG = 1;
    }
}

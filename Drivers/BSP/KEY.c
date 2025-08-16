#include "KEY.h"

void Key_Init(void)
{
    __HAL_RCC_GPIOE_CLK_ENABLE();

    GPIO_InitTypeDef KEY = {0};
    KEY.Mode = GPIO_MODE_INPUT;
    KEY.Pin = GPIO_PIN_4 | GPIO_PIN_3;
    KEY.Pull = GPIO_PULLUP;
    KEY.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(GPIOE, &KEY);
}

void Key_Exti_Init(void)
{
    __HAL_RCC_GPIOE_CLK_ENABLE();
    GPIO_InitTypeDef Key_Exit = {0};
    Key_Exit.Mode = GPIO_MODE_IT_FALLING;
    Key_Exit.Pin = GPIO_PIN_4 | GPIO_PIN_3;
    Key_Exit.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(GPIOE, &Key_Exit);

    HAL_NVIC_SetPriority(EXTI3_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);

    HAL_NVIC_SetPriority(EXTI4_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(EXTI4_IRQn);
}

void EXTI3_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
}

void EXTI4_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN)
{
    switch (GPIO_PIN)
    {
    case GPIO_PIN_4:
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
        break;
    case GPIO_PIN_3:
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
        break;
    default:
        break;
    }
}

uint8_t Key_Read(void)
{
    if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3) == 0)
    {
        delay_ms(2);
        if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3) == 0)
        {
            while (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3) == 0)
                return 1;
        }
    }
    else if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4) == 0)
    {
        delay_ms(2);
        if (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4) == 0)
        {
            while (HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4) == 0)
                return 2;
        }
    }

    return 0;
}
#include "TIMER.h"

TIM_HandleTypeDef Timer6;
uint16_t g_led_flag;

void Timer6_Init(void)
{
    Timer6.Instance = TIM6;
    Timer6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    Timer6.Init.Prescaler = 7199; // (72MHz / (7199 + 1)) = 10kHz
    Timer6.Init.Period = 9;       // 10kHz / (9 + 1) = 1kHz -> 1ms

    HAL_TIM_Base_Init(&Timer6);
    HAL_TIM_Base_Start_IT(&Timer6);
}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    if(htim->Instance == TIM6)
    {
        __HAL_RCC_TIM6_CLK_ENABLE();
        HAL_NVIC_SetPriority(TIM6_IRQn,1,1);
        HAL_NVIC_EnableIRQ(TIM6_IRQn);
    }
}

void TIM6_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&Timer6);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim -> Instance == TIM6)
    {
        if(++g_led_flag >= 500)
        {
            g_led_flag = 0;
            HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_5);
        }
    }

}






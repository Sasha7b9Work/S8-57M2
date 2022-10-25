#include <stm32f4xx.h>
#include "Timer4XX.h"
#include "Hardware/Timer.h"



void Timer4XX::Init(TIM_TypeDef *instance, uint prescaler, uint counterMode, uint period, uint clcDiv)
{
    if (instance == TIM2) //-V2571
    {
        __HAL_RCC_TIM2_CLK_ENABLE(); //-V2571
    }
    else if (instance == TIM3) //-V2571
    {
        __HAL_RCC_TIM3_CLK_ENABLE(); //-V2571
    }
    else
    {
        // ������ �������� �� ������
    }

    handler.Instance = instance;
    handler.Init.Prescaler = prescaler;
    handler.Init.CounterMode = counterMode;
    handler.Init.Period = period;
    handler.Init.ClockDivision = clcDiv;

    HAL_TIM_Base_Init(&handler);
}


void Timer4XX::EnabledIRQ(uint mainPriority, uint subPriority)
{
    IRQn_Type type = GetIRQn_Type();

    HAL_NVIC_EnableIRQ(type);

    HAL_NVIC_SetPriority(type, mainPriority, subPriority);
}


IRQn_Type Timer4XX::GetIRQn_Type() //-V2506
{
    if (handler.Instance == TIM3) //-V2571
    {
        return TIM3_IRQn;
    }

    return SysTick_IRQn;
}


void Timer4XX::DisableIRQ()
{
    HAL_NVIC_DisableIRQ(GetIRQn_Type());
}


void Timer4XX::Start()
{
    HAL_TIM_Base_Start(&handler);
}


void Timer4XX::Stop()
{
    HAL_TIM_Base_Stop(&handler);
}


void Timer4XX::StartIT(uint period)
{
    handler.Init.Period = period;
    HAL_TIM_Base_Init(&handler);
    HAL_TIM_Base_Start_IT(&handler);
}


void Timer4XX::StopIT()
{
    HAL_TIM_Base_Stop_IT(&handler);
}


void Timer4XX::DeInit()
{
    HAL_TIM_Base_DeInit(&handler);

    if (handler.Instance == TIM2) //-V2571
    {
        __HAL_RCC_TIM2_CLK_DISABLE(); //-V2571
    }
    else if (handler.Instance == TIM3) //-V2571
    {
        __HAL_RCC_TIM3_CLK_DISABLE(); //-V2571
    }
    else
    {
        // ������ �������� �� ������
    }
}


void Timer::PauseOnOPS(uint ops)
{
    volatile uint i = 0;
    for (; i < ops; i++)
    {

    }
}

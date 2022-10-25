#pragma once
#include "Hardware/stm32/stm429.h"



class CPU : public STM429
{
public:

    static void Init();

private:

    static void SystemClockConfig();
};



#ifdef __cplusplus
extern "C" {
#endif
    
    // Timer.cpp
    void TIM3_IRQHandler();
    
    void SysTick_Handler();
    void MemManage_Handler();
    void UsageFault_Handler();
    void PendSV_Handler();
    void NMI_Handler();
    void HardFault_Handler();
    void BusFault_Handler();
    void SVC_Handler();
    void DebugMon_Handler();

#ifdef __cplusplus
}
#endif

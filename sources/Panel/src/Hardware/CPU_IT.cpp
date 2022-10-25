#include "defines.h"
#include "Hardware/CPU.h"
#include "Utils/Debug.h"


#ifdef __cplusplus
extern "C" {
#endif

    //---------------------------
    void SysTick_Handler()
    {
        HAL_IncTick();
        HAL_SYSTICK_IRQHandler();
    }

    //---------------------------
    __attribute((noreturn)) void MemManage_Handler()
    {
        volatile int line = Debug::line;
        volatile char *file = Debug::file;
        
        while (1) //-V776
        {
            line = line;
            file = file; //-V570
        }
    }

    //---------------------------
    __attribute((noreturn)) void UsageFault_Handler()
    {
        volatile int line = Debug::line;
        volatile char *file = Debug::file;
        
        while (1) //-V776
        {
            line = line;
            file = file; //-V570
        }
    }

    //---------------------------
    __attribute((noreturn)) void HardFault_Handler()
    {
        volatile int line = Debug::line;
        volatile char *file = Debug::file;
        
        while (1) //-V776
        {
            line = line;
            file = file; //-V570
        }
    }

    //---------------------------
    __attribute((noreturn)) void BusFault_Handler()
    {
        while (1)
        {
        }
    }

    //---------------------------
    void PendSV_Handler()
    {
    }

    //---------------------------
    void NMI_Handler()
    {
    }

    //---------------------------
    void SVC_Handler()
    {
    }

    //---------------------------
    void DebugMon_Handler()
    {
    }
    
    void EXTI9_5_IRQHandler(void)
    {
        /* USER CODE BEGIN EXTI9_5_IRQn 0 */

        /* USER CODE END EXTI9_5_IRQn 0 */
        HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);
        /* USER CODE BEGIN EXTI9_5_IRQn 1 */

        /* USER CODE END EXTI9_5_IRQn 1 */
    }

#ifdef __cplusplus
}
#endif

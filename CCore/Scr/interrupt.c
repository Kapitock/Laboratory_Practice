#include "../Inc/interrupt.h"

extern uint16_t GlobalTickCount;
extern uint8_t btnCount;
extern bool LedState;
extern uint16_t DelayTickCount;

void delay(uint16_t number)
{
    while(DelayTickCount < number){}
    DelayTickCount = 0;
}

void SysTick_Handler(void)
{
    GlobalTickCount++;
    DelayTickCount++;
}

void EXTI15_10_IRQHandler(void)
{
    btnCount++;
    if (btnCount >= 2)
    {
        LedState = !LedState;
        btnCount = 0;
    }
    SET_BIT(EXTI->PR, EXTI_PR_PR13);
}
#include "../Inc/interrupt.h"

extern uint16_t GlobalTickCount;
extern uint8_t btnCount;
extern bool LedState;
uint16_t DelayTickCount = 0;
extern uint16_t ButtonTickCount;

void delay(uint16_t time_delay)
{
    while(DelayTickCount < time_delay){}
    DelayTickCount = 0;
}

void SysTick_Handler(void)
{
    GlobalTickCount++;
    DelayTickCount++;
    ButtonTickCount++;
}

void EXTI3_IRQHandler(void)
{
    SET_BIT(EXTI->PR, EXTI_PR_PR3);
    btnCount++;
    if (READ_BIT(GPIOC->IDR, GPIO_IDR_ID3) == RESET)
    {
        ButtonTickCount = 0;
        btnCount = 0;
    }
    if(ButtonTickCount >= 2000)
    {
        LedState = !LedState;
        btnCount = 0;
        ButtonTickCount = 0;
    }
    else if (ButtonTickCount <= 2000){}
}
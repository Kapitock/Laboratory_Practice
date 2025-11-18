#include "../Inc/interrupt.h"

uint8_t counter = 0;
extern uint32_t counter_timer;
uint16_t Frequency_1Hz = 100;
uint16_t Frequency_2Hz = 50;
uint16_t Frequency_4Hz = 25;

void EXTI15_10_IRQHandler(void)
{
    SET_BIT(EXTI->PR, EXTI_PR_PR13);                  // Выход с обработчика прерываний
    if (READ_BIT(GPIOC->IDR, GPIO_IDR_ID13) == RESET) // Если кнопка нажата, то обнуляется таймер
    {
    }
    else
    {
        counter_timer = 0;
        counter++;
    }
    if (counter > 2)
    {
        counter = 0;
    }
}

void TIM3_IRQHandler(void)
{
    if (READ_BIT(TIM3->SR, TIM_SR_UIF))
    {
        CLEAR_BIT(TIM3->SR, TIM_SR_UIF);
        counter_timer++;
        switch (counter)
        {
        case 0:
            Flickering_LED(Frequency_1Hz);
            break;
        case 1:
            Flickering_LED(Frequency_2Hz);
            break;
        case 2:
            Flickering_LED(Frequency_4Hz);
            break;
        }
    }
}
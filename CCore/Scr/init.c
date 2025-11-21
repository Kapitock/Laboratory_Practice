#include "../Inc/init.h"

uint32_t counter_timer = 0;

void GPIO_Init(void)
{
    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN);

    SET_BIT(GPIOC->MODER, GPIO_MODER_MODER12_0 | GPIO_MODER_MODER10_0 | GPIO_MODER_MODER11_0
                            | GPIO_MODER_MODER5_0 | GPIO_MODER_MODER6_0 | GPIO_MODER_MODER8_0);
    SET_BIT(GPIOC->OSPEEDR, GPIO_OSPEEDER_OSPEEDR12_0 | GPIO_OSPEEDER_OSPEEDR10_0 | GPIO_OSPEEDER_OSPEEDR11_0
                            | GPIO_OSPEEDER_OSPEEDR5_0 | GPIO_OSPEEDER_OSPEEDR6_0 | GPIO_OSPEEDER_OSPEEDR8_0);
    SET_BIT(GPIOC->BSRR, GPIO_BSRR_BR12 | GPIO_BSRR_BR10 | GPIO_BSRR_BR11
                            | GPIO_BSRR_BR5 | GPIO_BSRR_BR6 | GPIO_BSRR_BR8);
}

void RCC_Init(void)
{
    /*Предварительная очистка регистров RCC */
    MODIFY_REG(RCC->CR, RCC_CR_HSITRIM, 0x80UL);                    // Очистка битов HSITRIM и установка 1000 0000
    CLEAR_REG(RCC->CFGR);                                           // Очистка регистра CFGR
    while (READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != RESET);             // Проверка очистки регистра CR
    CLEAR_BIT(RCC->CR, RCC_CR_PLLON);                               // Очистка бита PLLON в регистре CR
    while (READ_BIT(RCC->CR, RCC_CR_PLLRDY) != RESET);              // Проверка очистки бита PLLON
    CLEAR_BIT(RCC->CR, RCC_CR_HSEON | RCC_CR_CSSON);                // Очистка битов HSEON, CSSON в регистре CR
    while (READ_BIT(RCC->CR, RCC_CR_HSERDY) != RESET);              // Проверка очистки битов HSEON, CSSON
    CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);                              // Очистка бита HSEBYP в регистре CR

    /*Настройка главного регистра RCC */
    SET_BIT(RCC->CR, RCC_CR_HSION);                                 // Запускаем HSI
    while (READ_BIT(RCC->CR, RCC_CR_HSIRDY) == RESET);              // Ждём пока он запустится

    /*Настройка регистра PLLCFGR*/
    CLEAR_REG(RCC->PLLCFGR);                                        // Очищаем регистр PLLCFGR
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC_HSI);                  // Источник тактирования HSE
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLM_3);                      // Деление источника тактирования на 8
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLN_6 | RCC_PLLCFGR_PLLN_5); // Настрока умножения на 96
    CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLP_0);                    // Делитель для выхода PLL(PLLCLK) на 4
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLQ_2);                      // Делитель для USB на 4

    /*Настройка регистра CFGR*/
    SET_BIT(RCC->CFGR, RCC_CFGR_SW_PLL);                            // Источник системного тактирования -> выход PLL
    CLEAR_BIT(RCC->CFGR, RCC_CFGR_HPRE_DIV1);                       // Делитель AHB1 -> 0
    SET_BIT(RCC->CFGR, RCC_CFGR_PPRE1_DIV2);                        // Делитель APB1 -> 2 (48 МГц)
    SET_BIT(RCC->CFGR, RCC_CFGR_PPRE2_DIV1);                        // Делитель APB2 -> 1 (96 МГц)
    CLEAR_BIT(RCC->CFGR, RCC_CFGR_MCO2);                            // Выход MCO2 -> Sysclk
    SET_BIT(RCC->CFGR, RCC_CFGR_MCO2PRE_2 | RCC_CFGR_MCO2PRE_1);    // Делитель для MCO2 -> 4

    /*Настрйока частоты FLASH-памяти*/
    SET_BIT(FLASH->ACR, FLASH_ACR_LATENCY_3WS);

    /*Включение блока PLL*/
    SET_BIT(RCC->CR, RCC_CR_PLLON);
    while (READ_BIT(RCC->CR, RCC_CR_PLLRDY) == RESET);
}

void TIMER_Init(void)
{
    /*Включение тактирования таймера*/
    SET_BIT(RCC->APB1ENR, RCC_APB1ENR_TIM3EN);

    CLEAR_REG(TIM3->CR1);               // Очистка регистра CR1
    SET_BIT(TIM3->CR1, TIM_CR1_ARPE);   //     

    CLEAR_REG(TIM3->PSC);           // Очистка регистра PSC от мусора
    SET_BIT(TIM3->PSC, 47999UL);    // Делитель частоты тактирования для таймера (чF_psc = x + 1)
    CLEAR_REG(TIM3->ARR);           // Очистка регистра ARR от мусора
    SET_BIT(TIM3->ARR, 19UL);       // Установка времени прерывания таймера (время удвоено, по факту таймер прерывания срабатывает раз в 10 мс) 
    //(F_arr = x + 1)

    SET_BIT(TIM3->EGR, TIM_EGR_UG); // Принудительное обнуления события UG

    SET_BIT(TIM3->DIER, TIM_DIER_UIE);  // Разрешение прерывания по событию UIE
    NVIC_SetPriority(TIM3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0)); // Выбор приоретета прерывания
    NVIC_EnableIRQ(TIM3_IRQn);

    SET_BIT(TIM3->CR1, TIM_CR1_CEN);    // Включение таймера
}

void IQR_Init(void)
{
    /*Включение тактирование периферии SYSCFG*/
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);

    /*Обозначение снятие внешеного сигнала с линии PC3*/
    SET_BIT(SYSCFG->EXTICR[3], SYSCFG_EXTICR4_EXTI13_PC);

    /*Настройка регистров EXTI*/
    SET_BIT(EXTI->IMR, EXTI_IMR_IM13);   // Включение маскирование
    CLEAR_BIT(EXTI->EMR, EXTI_EMR_EM13); // Отключение генерации события
    SET_BIT(EXTI->RTSR, EXTI_RTSR_TR13); // Настройка отслеживания по спаду (кнопка была отпущена)
    SET_BIT(EXTI->FTSR, EXTI_FTSR_TR13); // Настройка отслеживания по фронту (кнопка была нажата)

    /*Настройка регистров NVIC*/
    NVIC_SetPriority(EXTI15_10_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0)); // Выбор приоретета прерывания
    NVIC_EnableIRQ(EXTI15_10_IRQn);                                                          // Разрешение прерывания
}

void Flickering_LED(uint8_t Frequency)
{
    if (counter_timer >= 0 && counter_timer < Frequency)
    {
        SET_BIT(GPIOC->BSRR, GPIO_BSRR_BS12 | GPIO_BSRR_BR10 | GPIO_BSRR_BR11 | GPIO_BSRR_BR5 | GPIO_BSRR_BR6 | GPIO_BSRR_BR8);
    }
    else if (counter_timer >= Frequency && counter_timer < 2 * Frequency)
    {
        SET_BIT(GPIOC->BSRR, GPIO_BSRR_BR12 | GPIO_BSRR_BS10 | GPIO_BSRR_BR11 | GPIO_BSRR_BR5 | GPIO_BSRR_BR6 | GPIO_BSRR_BR8);
    }
    else if (counter_timer >= 2 * Frequency && counter_timer < 3 * Frequency)
    {
        SET_BIT(GPIOC->BSRR, GPIO_BSRR_BR12 | GPIO_BSRR_BR10 | GPIO_BSRR_BS11 | GPIO_BSRR_BR5 | GPIO_BSRR_BR6 | GPIO_BSRR_BR8);
    }
    else if (counter_timer >= 3 * Frequency && counter_timer < 4 * Frequency)
    {
        SET_BIT(GPIOC->BSRR, GPIO_BSRR_BR12 | GPIO_BSRR_BR10 | GPIO_BSRR_BR11 | GPIO_BSRR_BS5 | GPIO_BSRR_BR6 | GPIO_BSRR_BR8);
    }
    else if (counter_timer >= 4 * Frequency && counter_timer < 5 * Frequency)
    {
        SET_BIT(GPIOC->BSRR, GPIO_BSRR_BR12 | GPIO_BSRR_BR10 | GPIO_BSRR_BR11 | GPIO_BSRR_BR5 | GPIO_BSRR_BS6 | GPIO_BSRR_BR8);
    }
    else if (counter_timer >= 5 * Frequency && counter_timer < 6 * Frequency)
    {
        SET_BIT(GPIOC->BSRR, GPIO_BSRR_BR12 | GPIO_BSRR_BR10 | GPIO_BSRR_BR11 | GPIO_BSRR_BR5 | GPIO_BSRR_BR6 | GPIO_BSRR_BS8);
    }
    else if (counter_timer >= 6 * Frequency)
    {
        counter_timer = 0;
    }
}
#include "../Inc/init.h"

void RCC_Init(void)
{
    /* Предварительная очистка регистров RCC */
    MODIFY_REG(RCC->CR, RCC_CR_HSITRIM, 0x80UL);                                    // Очистка битов HSITRIM и установка 1000 0000
    CLEAR_REG(RCC->CFGR);                                                           // Очистка регистра CFGR
    while (READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != RESET);                             // Проверка очистки регистра CR
    CLEAR_BIT(RCC->CR, RCC_CR_PLLON);                                               // Очистка бита PLLON в регистре CR
    while (READ_BIT(RCC->CR, RCC_CR_PLLRDY) != RESET);                              // Проверка очистки бита PLLON
    CLEAR_BIT(RCC->CR, RCC_CR_HSEON | RCC_CR_CSSON);                                // Очистка битов HSEON, CSSON в регистре CR
    while (READ_BIT(RCC->CR, RCC_CR_HSERDY) != RESET);                              // Проверка очистки битов HSEON, CSSON
    CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);                                              // Очистка бита HSEBYP в регистре CR
    /* Настройка главного регистра RCC */
    SET_BIT(RCC->CR, RCC_CR_HSION);                                                 // Запускаем внешний кварцевый резонатор
    while (READ_BIT(RCC->CR, RCC_CR_HSIRDY) == RESET);                              // Ждём пока он запустится

    CLEAR_REG(RCC->PLLCFGR);
    CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC_HSI);                                // Источник тактирования HSE
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLM_3);                                      // Деление источника тактирования на 8
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLN_6 | RCC_PLLCFGR_PLLN_5);                 // Настрока умножения на 96
    CLEAR_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLP_0);                                    // Делитель для выхода PLL(PLLCLK) на 4 
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLQ_2);                                      // Делитель для USB на 15 

    SET_BIT(RCC->CFGR, RCC_CFGR_SW_PLL);                                            // Источник системного тактирования -> выход PLL
    CLEAR_BIT(RCC->CFGR, RCC_CFGR_HPRE_DIV1);                                       // Делитель AHB1 -> 0
    SET_BIT(RCC->CFGR, RCC_CFGR_PPRE1_DIV2);                                        // Делитель APB1 -> 2 (48 МГц)
    SET_BIT(RCC->CFGR, RCC_CFGR_PPRE2_DIV1);                                        // Делитель APB2 -> 1 (96 МГц)
    CLEAR_BIT(RCC->CFGR, RCC_CFGR_MCO2);                                            // Выход MCO2 -> Sysclk
    SET_BIT(RCC->CFGR, RCC_CFGR_MCO2PRE_2 | RCC_CFGR_MCO2PRE_1);                    // Делитель для MCO2 -> 4

    SET_BIT(FLASH->ACR, FLASH_ACR_LATENCY_3WS);

    SET_BIT(RCC->CR, RCC_CR_PLLON);
    while(READ_BIT(RCC->CR, RCC_CR_PLLRDY) == RESET);
}

void IQR_Init(void)
{
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_SYSCFGEN);

    SET_BIT(SYSCFG->EXTICR[3], SYSCFG_EXTICR4_EXTI13_PC);

    SET_BIT(EXTI->IMR, EXTI_IMR_IM13);
    SET_BIT(EXTI->RTSR, EXTI_RTSR_TR13);
    CLEAR_BIT(EXTI->FTSR, EXTI_FTSR_TR13);

    NVIC_SetPriority(EXTI15_10_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 0, 0));
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}

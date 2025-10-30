#include "../Inc/init.h"

void RCC_Init(void)
{
    /* Предварительная очистка регистров RCC */
    MODIFY_REG(RCC->CR, RCC_CR_HSITRIM, 0x80UL);
    CLEAR_REG(RCC->CFGR);
    while (READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != RESET);
    CLEAR_BIT(RCC->CR, RCC_CR_PLLON);
    while (READ_BIT(RCC->CR, RCC_CR_PLLRDY) != RESET);
    CLEAR_BIT(RCC->CR, RCC_CR_HSEON | RCC_CR_CSSON);
    while (READ_BIT(RCC->CR, RCC_CR_HSERDY) != RESET);
    CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);
    /* Настройка главного регистра RCC */
    SET_BIT(RCC->CR, RCC_CR_HSEON);                                                 // Запускаем внешний кварцевый резонатор
    while (READ_BIT(RCC->CR, RCC_CR_HSERDY) == RESET);                              // Ждём пока он запустится
    SET_BIT(RCC->CR, RCC_CR_CSSON);
    SET_BIT(RCC->CR, RCC_CR_HSEBYP);
    CLEAR_BIT(RCC->CR, RCC_CR_HSION);

    CLEAR_REG(RCC->PLLCFGR);
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLSRC_HSE);                                  // Источник тактирования HSE
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLM_2);                                      // Деление источника тактирования на 4
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLN_8 | RCC_PLLCFGR_PLLN_6 
                        | RCC_PLLCFGR_PLLN_5 | RCC_PLLCFGR_PLLN_3);                 // Настрока умножения на 360
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLP_0);                                      // Делитель для выхода PLL(PLLCLK) на 4 
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLLQ_0 | RCC_PLLCFGR_PLLQ_1 
                        | RCC_PLLCFGR_PLLQ_2 | RCC_PLLCFGR_PLLQ_3);                 // Делитель для USB на 15 

    SET_BIT(RCC->CFGR, RCC_CFGR_SW_PLL);                                            // Источник системного тактирования -> выход PLL
    CLEAR_BIT(RCC->CFGR, RCC_CFGR_HPRE_DIV1);                                       // Делитель AHB1 -> 0
    SET_BIT(RCC->CFGR, RCC_CFGR_PPRE1_DIV4);                                        // Делитель APB1 -> 4 (45 МГц)
    SET_BIT(RCC->CFGR, RCC_CFGR_PPRE2_DIV2);                                        // Делитель APB2 -> 2 (90 МГц)
    CLEAR_BIT(RCC->CFGR, RCC_CFGR_MCO2);                                            // Выход MCO2 -> Sysclk
    SET_BIT(RCC->CFGR, RCC_CFGR_MCO2PRE_2 | RCC_CFGR_MCO2PRE_1);                    // Делитель для MCO2 -> 4

    SET_BIT(FLASH->ACR, FLASH_ACR_LATENCY_5WS);

    SET_BIT(RCC->CR, RCC_CR_PLLON);
    while(READ_BIT(RCC->CR, RCC_CR_PLLRDY) == RESET);
}
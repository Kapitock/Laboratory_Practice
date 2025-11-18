#include "../../CMSIS/Devices/STM32F4xx/Inc/stm32f4xx.h"
#include "../../CMSIS/Devices/STM32F4xx/Inc/STM32F411xE/stm32f411xe.h"
#include <stdbool.h>

void GPIO_Init(void);
void RCC_Init(void);
void TIMER_Init(void);
void IQR_Init(void);
void Flickering_LED(uint8_t Frequency);

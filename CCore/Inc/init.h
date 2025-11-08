#include "../../CMSIS/Devices/STM32F4xx/Inc/stm32f4xx.h"
#include "../../CMSIS/Devices/STM32F4xx/Inc/STM32F411xE/stm32f411xe.h"
#include <stdbool.h>

#define Freauency_First_Mode_0_4Hz      2500
#define Freauency_First_Mode_1_9Hz      526
#define Freauency_First_Mode_2_6Hz      385
#define Freauency_Second_Mode_0_3Hz     3333
#define Freauency_Second_Mode_1_6Hz     625
#define Freauency_Second_Mode_2_3Hz     435

void GPIO_Init(void);
void RCC_Init(void);
void IQR_Init(void);
void SysTick_Init(void);
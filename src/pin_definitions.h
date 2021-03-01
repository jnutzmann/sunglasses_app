/*
 * pin_definitions.h
 *
 *  Created on: Feb 28, 2021
 *      Author: jnutzmann
 */

#ifndef PIN_DEFINITIONS_H_
#define PIN_DEFINITIONS_H_

#include "stm32f3_hal/stm32f3xx_hal.h"


#define LED_RED_Pin GPIO_PIN_13
#define LED_RED_GPIO_Port GPIOC
#define SOIL0_MOIST_Pin GPIO_PIN_0
#define SOIL0_MOIST_GPIO_Port GPIOA
#define SOIL0_TEMP_Pin GPIO_PIN_1
#define SOIL0_TEMP_GPIO_Port GPIOA
#define SOIL1_MOIST_Pin GPIO_PIN_2
#define SOIL1_MOIST_GPIO_Port GPIOA
#define SOIL1_TEMP_Pin GPIO_PIN_3
#define SOIL1_TEMP_GPIO_Port GPIOA
#define LED_BLUE_Pin GPIO_PIN_4
#define LED_BLUE_GPIO_Port GPIOA
#define VIN_ADC_Pin GPIO_PIN_0
#define VIN_ADC_GPIO_Port GPIOB
#define LED0_SS_Pin GPIO_PIN_1
#define LED0_SS_GPIO_Port GPIOB
#define LED1_SS_Pin GPIO_PIN_2
#define LED1_SS_GPIO_Port GPIOB
#define MAT0_EN_Pin GPIO_PIN_12
#define MAT0_EN_GPIO_Port GPIOB
#define MAT1_EN_Pin GPIO_PIN_13
#define MAT1_EN_GPIO_Port GPIOB
#define SOIL0_EN_Pin GPIO_PIN_14
#define SOIL0_EN_GPIO_Port GPIOB
#define SOIL1_EN_Pin GPIO_PIN_15
#define SOIL1_EN_GPIO_Port GPIOB
#define LED0_PWM_A_Pin GPIO_PIN_8
#define LED0_PWM_A_GPIO_Port GPIOA
#define LED0_PWM_B_Pin GPIO_PIN_9
#define LED0_PWM_B_GPIO_Port GPIOA
#define LED1_PWM_A_Pin GPIO_PIN_10
#define LED1_PWM_A_GPIO_Port GPIOA
#define LED1_PWM_B_Pin GPIO_PIN_11
#define LED1_PWM_B_GPIO_Port GPIOA
#define MOIST0_EXCITE_Pin GPIO_PIN_5
#define MOIST0_EXCITE_GPIO_Port GPIOB
#define MOIST1_EXCITE_Pin GPIO_PIN_9
#define MOIST1_EXCITE_GPIO_Port GPIOB


#endif /* PIN_DEFINITIONS_H_ */

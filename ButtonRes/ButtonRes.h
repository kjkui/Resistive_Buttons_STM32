/*
 Библиотека для работы с резистивными кнопками.

 Переменные, которые имеют в названии _ означают приватные и не выходят за исполняемый файл .c


 Функция Button_Handler обрабатывает значение АЦП и по формуле возвращает нажатую кнопку.
 Преобразование АЦП нужно вызвать в цикле main.c
 TODO: Начинать преобразование АЦП внутри функции
 В этой функции так же есть проверка на количество кнопок чтобы функция не смогла вернуть кнопку которой не существует
 if (_buttonNumber <= BUTTON_COUNT) {
 return ((ButtonState) _buttonNumber);
 }
 Если же напряжение меньше чем шаговое напряжение (STEP_VOLTAGE) то возвращает 1-ю кнопку

 Функция Button_Callback уже возвращает кнопку пользователю и может быть обработана для дальнейших действий.
 */

#ifndef BUTTONRES_H_
#define BUTTONRES_H_

#include "stm32f4xx_hal.h"     // подключаем хеадер HAL
#include <stdio.h>
#include <string.h>

#define BUTTON_RES_DEBUG 0

#if BUTTON_RES_DEBUG
extern UART_HandleTypeDef huart2;
extern uint8_t str[100];       // для текстовой строки в USART при отладке
#endif /* BUTTON_RES_DEBUG */

#define ADC_RESOLUTION 4095 // 12-bit ADC
#define VREF 3.3 // Опорное напряжение

#define BUTTON_COUNT 4 // Количество кнопок

// xxx: А зачем мне эта?
#define RESISTOR_VALUE 220 // Сопротивление
#define ADC_CHANNEL 0 // PA0

#define STEP_VOLTAGE (float)(VREF / (BUTTON_COUNT + 1))

// Определяем состояние кнопок
// TODO: Отказаться от использования enum в пользу простой работы с библиотекой
typedef enum {
	NO_BUTTON, BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_4
} ButtonState;

// Глобальные переменные
extern ButtonState currentButton; // Устанавливаем изначальное значение NO_BUTTON переменной currentButton
extern float adcValue; // Текущее значение АЦП

ButtonState Button_Callback();

#endif /* BUTTONRES_H_ */

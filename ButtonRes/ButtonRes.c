/*
 Библиотека для работы с резистивными кнопками.

 Переменные, которые имеют в названии _ означают приватные и не выходят за исполняемый файл .c


 Функция Button_Handler обрабатывает значение АЦП и по формуле возвращает нажатую кнопку.
 Преобразование АЦП нужно вызвать в цикле main.c
 В этой функции так же есть проверка на количество кнопок чтобы функция не смогла вернуть кнопку которой не существует
 if (_buttonNumber <= BUTTON_COUNT) {
 return ((ButtonState) _buttonNumber);
 }
 Если же напряжение меньше чем шаговое напряжение (STEP_VOLTAGE) то возвращает 1-ю кнопку

 Функция Button_Callback уже возвращает кнопку пользователю и может быть обработана для дальнейших действий.
 */

#include "ButtonRes.h"

// Глобальные переменные
ButtonState currentButton = NO_BUTTON; // Устанавливаем изначальное значение NO_BUTTON переменной currentButton
float adcValue = 0; // Текущее значение АЦП

// Приватные переменные
float _voltage = 0;
int _buttonNumber = 0;

ButtonState Button_Handler() {
#if BUTTON_RES_DEBUG
		sprintf((char*) str, "adcValue = %f\r\n\n", adcValue);
		HAL_UART_Transmit(&huart2, (uint8_t*) str, strlen((char*) str), HAL_MAX_DELAY);
	#endif

	_voltage = adcValue * VREF / ADC_RESOLUTION;

#if BUTTON_RES_DEBUG
		sprintf((char*) str, "voltage = %f\r\n\n", _voltage);
		HAL_UART_Transmit(&huart2, (uint8_t*) str, strlen((char*) str), HAL_MAX_DELAY);
	#endif

	if (_voltage < STEP_VOLTAGE) {
		return BUTTON_1;
	}

	_buttonNumber = (int) ((_voltage - STEP_VOLTAGE ) / STEP_VOLTAGE ) + 2;
	if (_buttonNumber <= BUTTON_COUNT) {
		return ((ButtonState) _buttonNumber);
	}

	return currentButton;
}

ButtonState Button_Callback() {
	ButtonState button = Button_Handler();

	if (button != currentButton) {
		currentButton = button; // update current button state

#if BUTTON_RES_DEBUG
			sprintf((char*) str, "Button %d pressed\r\n\n", button);
			HAL_UART_Transmit(&huart2, (uint8_t*) str, strlen((char*) str), HAL_MAX_DELAY);
		#endif

		return button;
	}

	return currentButton;
}

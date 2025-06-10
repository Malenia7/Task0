#include "bsp_ch579_uart2.h"
#include "usart.h"
#include "stdio.h"

void ch579_init(void) {
	HAL_UART_Transmit(&huart5, (uint8_t *)"+++a", 4, HAL_MAX_DELAY);
	HAL_Delay(200);
	HAL_UART_Transmit(&huart5, (uint8_t *)"AT+UART=115200,8,0,1\r\n", 22, HAL_MAX_DELAY);
	HAL_Delay(200);
	HAL_UART_Transmit(&huart5, (uint8_t *)"AT+NAME=CH579\r\n", 15, HAL_MAX_DELAY);
	HAL_Delay(200);
	HAL_UART_Transmit(&huart5, (uint8_t *)"AT+RESET\r\n", 10, HAL_MAX_DELAY);
	HAL_Delay(200);
	
	HAL_UART_Transmit(&huart5, (uint8_t *)"+++a", 4, HAL_MAX_DELAY);
	HAL_Delay(200);
	HAL_UART_Transmit(&huart5, (uint8_t *)"AT+ADPTIM=5\r\n", 13, HAL_MAX_DELAY);
	HAL_Delay(200);
	HAL_UART_Transmit(&huart5, (uint8_t *)"AT+MODE=S\r\n", 11, HAL_MAX_DELAY);
	HAL_Delay(200);
	
	printf("---------------------ok\n");
	
}




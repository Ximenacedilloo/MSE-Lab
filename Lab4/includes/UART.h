#ifndef UART_DRIVER_H
#define UART_DRIVER_H

/**
 * @file uart_driver.h
 * @brief UART Driver for USART2 — STM32F411RE
 *
 * Pin mapping (Nucleo-64):
 *   PA2  →  USART2_TX  (AF7)
 *   PA3  →  USART2_RX  (AF7)
 *
 * @author Carlos Villarreal
 * @date   May 14, 2026
 */

#include <stdint.h>
#include "stm32f4xx.h"
#include "GPIO.h"

#define UART_AF7    7U
#define UART_TX_PIN 2U
#define UART_RX_PIN 3U

typedef enum {
    UART_OK            = 0,
    UART_ERROR_NULL    = 1,
    UART_ERROR_TIMEOUT = 2
} UART_Status_t;

void    UART_Init(uint32_t baud_rate);  /* FR-1 */
void    UART_SendByte(uint8_t byte);    /* FR-2 */
uint8_t UART_ReceiveByte(void);         /* FR-3 */
void    UART_SendString(const char *str); /* FR-4 */
uint8_t UART_IsTxReady(void);           /* FR-5 */
uint8_t UART_IsRxReady(void);           /* FR-5 */

#endif /* UART_DRIVER_H */
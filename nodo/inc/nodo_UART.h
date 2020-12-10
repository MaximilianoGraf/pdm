/*
 * nodo_UART.h
 *
 *  Created on: 8 dic. 2020
 *      Author: max
 */
#ifndef EJERCICIOSPM_NODO_INC_NODO_UART_H_
#define EJERCICIOSPM_NODO_INC_NODO_UART_H_

#include "sapi.h"

void nodoUartInit(uartMap_t uart, uint32_t speed);// Inicializa la UART.
void nodoUartWriteStr(uartMap_t uart, const char * text); // Envía un texto con información del estado actual por la UART para informar al usuario.
void nodoUartPrintAdcSample(uartMap_t uart, uint16_t sample);// Envía un texto con información de la muestra por la UART para informar al usuario.

#endif /* EJERCICIOSPM_NODO_INC_NODO_UART_H_ */

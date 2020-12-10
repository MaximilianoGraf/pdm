/*
 * nodo_UART.c
 *
 *  Created on: 8 dic. 2020
 *      Author: max
 */
#include "nodo_UART.h"

/**
 * C++ version 0.4 char* style "itoa":
 * Written by Lukás Chmela
 * Released under GPLv3.

 */
static char* itoa(int value, char* result, int base) {
   // check that the base if valid
   if (base < 2 || base > 36) { *result = '\0'; return result; }

   char* ptr = result, *ptr1 = result, tmp_char;
   int tmp_value;

   do {
      tmp_value = value;
      value /= base;
      *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
   } while ( value );

   // Apply negative sign
   if (tmp_value < 0) *ptr++ = '-';
   *ptr-- = '\0';
   while(ptr1 < ptr) {
      tmp_char = *ptr;
      *ptr--= *ptr1;
      *ptr1++ = tmp_char;
   }
   return result;
}

void nodoUartInit(uartMap_t uart, const uint32_t speed)
{
	uartInit(uart, speed);
}

void nodoUartWriteStr(uartMap_t uart, const char * text)
{
	uartWriteString(uart, text);
}

void nodoUartPrintAdcSample(uartMap_t uart, const uint16_t sample)
{
	char uart_buff[10];

	/* Envío la primer parte del mensaje a la Uart */
	nodoUartWriteStr(UART_USB, "ADC value: " );

	/* Conversión de muestra entera a ascii con base decimal */
	itoa( sample, uart_buff, 10 ); /* 10 significa decimal */

	/* Enviar muestra y Enter */
	nodoUartWriteStr( UART_USB, uart_buff );
	nodoUartWriteStr( UART_USB, "\r\n" );
}

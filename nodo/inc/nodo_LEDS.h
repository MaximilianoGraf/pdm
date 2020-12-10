/*
 * nodo_LEDS.h
 *
 *  Created on: 8 dic. 2020
 *      Author: max
 */
#ifndef EJERCICIOSPM_SEMAPHORE_INC_LED_H_
#define EJERCICIOSPM_SEMAPHORE_INC_LED_H_

#include "sapi.h"

#define LED_ON 1
#define LED_OFF 0

typedef enum
{
	LUZ_ROJA     = LED2,
	LUZ_AZUL 	 = LEDB,
	LUZ_VERDE    = LEDG,
	LUZ_CANT	 = 3
}led_e;

bool_t nodoLedToggle(led_e led);
bool_t nodoLedInit();

#endif /* EJERCICIOSPM_SEMAPHORE_INC_LED_H_ */

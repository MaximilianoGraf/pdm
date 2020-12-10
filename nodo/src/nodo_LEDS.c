/*
 * nodo_LEDS.c
 *
 *  Created on: 8 dic. 2020
 *      Author: max
 */
#include "nodo_LEDS.h"

static bool_t nodoLedOnOff(led_e led, bool_t value)
{
	bool_t ret;

	if (!(ret = gpioWrite(led, value)))
	{
		printf("Error al utilizar el led %d", led);
		printf("Revisar configuraciones ");
	}

	return ret;
}

bool_t nodoLedToggle(led_e led)
{
	bool_t ret;
	return gpioToggle(led);
}

bool_t nodoLedInit()
{
	bool_t ret1,ret2,ret3;
	ret1 = nodoLedOnOff(LUZ_ROJA, LED_OFF);
	ret2 = nodoLedOnOff(LUZ_AZUL, LED_OFF);
	ret3 = nodoLedOnOff(LUZ_VERDE, LED_OFF);

	if (ret1 && ret2 && ret3)
		return TRUE;
	else
		return FALSE;
}

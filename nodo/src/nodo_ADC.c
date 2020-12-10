/*
 * nodo_ADC.c
 *
 *  Created on: 8 dic. 2020
 *      Author: max
 */
#include "nodo_ADC.h"

void nodoAdcInit(adcInit_t config)
{
	adcInit( config );
}

uint16_t nodoAdcRead(adcMap_t channel)
{
	return adcRead( channel );
}

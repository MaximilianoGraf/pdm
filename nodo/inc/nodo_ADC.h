/*
 * nodo_ADC.h
 *
 *  Created on: 8 dic. 2020
 *      Author: max
 */
#ifndef EJERCICIOSPM_NODO_INC_NODO_ADC_H_
#define EJERCICIOSPM_NODO_INC_NODO_ADC_H_
#include "sapi.h"

void nodoAdcInit(adcInit_t config);//configurar el ADC a utilizar
uint16_t nodoAdcRead(adcMap_t channel);//obtener el valor leído desde el conversor A/D;


#endif /* EJERCICIOSPM_NODO_INC_NODO_ADC_H_ */

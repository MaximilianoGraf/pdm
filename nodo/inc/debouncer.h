/*
 * debouncer.h
 *
 *  Created on: Nov 18, 2020
 *      Author: max
 */
#ifndef EJERCICIOSPM_SEMAPHORE_INC_ANTIREBOTE_H_
#define EJERCICIOSPM_SEMAPHORE_INC_ANTIREBOTE_H_

#include "sapi.h"

#define DEBOUNCE_DELAY_MS 40

typedef struct
{
	gpioMap_t tecla;
	delay_t *delay;
	int delay_time;
	void (*tecPressed)();
	void (*tecReleased)();
}trigger_t;

void buttonDebouncerInit();
void buttonDebouncerUpdate( trigger_t trigger );


#endif /* EJERCICIOSPM_SEMAPHORE_INC_ANTIREBOTE_H_ */

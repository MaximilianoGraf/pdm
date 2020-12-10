/*
 * nodo.h
 *
 *  Created on: 8 dic. 2020
 *      Author: max
 */

#ifndef EJERCICIOSPM_NODO_INC_NODO_H_
#define EJERCICIOSPM_NODO_INC_NODO_H_

typedef enum
{
	OPERATIVE,
	MAINTENANCE,
	INIT
}nodo_state_t;

void nodoSetMode(nodo_state_t mode);
void nodoInit(nodo_state_t initial_state);
void nodoMef();

#endif /* EJERCICIOSPM_NODO_INC_NODO_H_ */

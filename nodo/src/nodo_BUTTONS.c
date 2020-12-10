/*
 * nodo_BUTTONS.c
 *
 *  Created on: 8 dic. 2020
 *      Author: max
 */
#include "nodo.h"
#include "debouncer.h"

static delay_t delay_button1;
static delay_t delay_button2;
static delay_t delay_button3;

static void button1pressed()
{
	nodoSetMode(OPERATIVE);
}

static void button2pressed()
{
	nodoSetMode(MAINTENANCE);
}

static void button3pressed()
{
	nodoSetMode(INIT);
}

static void buttonReleased()
{
	//nothing to do
}

static const trigger_t trigger_button1 = {TEC1, &delay_button1, DEBOUNCE_DELAY_MS, &button1pressed, &buttonReleased};
static const trigger_t trigger_button2 = {TEC2, &delay_button2, DEBOUNCE_DELAY_MS, &button2pressed, &buttonReleased};
static const trigger_t trigger_button3 = {TEC3, &delay_button3, DEBOUNCE_DELAY_MS, &button3pressed, &buttonReleased};

void nodoButtonsRead()
{
	buttonDebouncerUpdate(trigger_button1);
	buttonDebouncerUpdate(trigger_button2);
	buttonDebouncerUpdate(trigger_button3);
}

void nodoButtonsInit()
{
	buttonDebouncerInit();
}


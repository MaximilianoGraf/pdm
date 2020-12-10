#include "nodo.h"

#include "nodo_LEDS.h"
#include "nodo_ADC.h"
#include "nodo_UART.h"
#include "nodo_BUTTONS.h"

#define INITIAL_DELAY_MS 50
#define DELAY_TIME_MS 1000

typedef struct
{
	adcInit_t adc_mode;
	adcMap_t adc_channel;
	uartMap_t uart;
	uint32_t uart_speed;
}nodo_config_t;

static const nodo_config_t nodo_config = {
		.adc_mode = ADC_ENABLE,
		.adc_channel = CH1,
		.uart = UART_USB,
		.uart_speed = 115200
};

typedef struct
{
	delay_t delay_nodo;
	nodo_state_t new_mode;
	bool_t flag_mode_has_changed;
	bool_t semaphore_is_taken;
}nodo_control_t;

static nodo_control_t nodo_control = {
		.new_mode = INIT,
		.flag_mode_has_changed = true,
		.semaphore_is_taken = false
};

void nodoInit(const nodo_state_t initial_state)
{
	delayInit( &nodo_control.delay_nodo, INITIAL_DELAY_MS);
	nodo_control.new_mode = initial_state;
	nodoUartInit(nodo_config.uart, nodo_config.uart_speed);
	nodoAdcInit(nodo_config.adc_mode);
	nodoLedInit();
	nodoButtonsInit();
}

static void operativeMode()
{
	uint16_t sample = 0;

	if (nodo_control.flag_mode_has_changed)
	{
		nodoUartWriteStr( nodo_config.uart, "Se ingresa a modo operative \r\n" );
		nodo_control.flag_mode_has_changed = false;
	}

	if (delayRead(&nodo_control.delay_nodo))
	{
		/* Leo la Entrada Analogica AI0 - ADC0 CH1 */
		sample = nodoAdcRead(nodo_config.adc_channel);
		nodoUartPrintAdcSample(nodo_config.uart, sample);

		nodoLedToggle(LUZ_VERDE);
		delayWrite(&nodo_control.delay_nodo, DELAY_TIME_MS);
	}
}

static void initMode()
{
	if (nodo_control.flag_mode_has_changed)
	{
		nodoUartWriteStr( nodo_config.uart, "Se ingresa a modo init \r\n" );
		nodo_control.flag_mode_has_changed = false;
	}
	if (delayRead(&nodo_control.delay_nodo))
	{
		nodoLedToggle(LUZ_AZUL);
		delayWrite(&nodo_control.delay_nodo, DELAY_TIME_MS);
	}
}

static void maintenanceMode()
{
	if (nodo_control.flag_mode_has_changed)
	{
		nodoUartWriteStr( nodo_config.uart, "Se ingresa a modo maintenance \r\n" );
		nodo_control.flag_mode_has_changed = false;
	}

	if (delayRead(&nodo_control.delay_nodo))
	{
		nodoLedToggle(LUZ_ROJA);
		delayWrite(&nodo_control.delay_nodo, DELAY_TIME_MS);
	}
}

void nodoMef()
{
	static nodo_state_t actual_mode = OPERATIVE;

	nodoButtonsRead();

	if (actual_mode != nodo_control.new_mode)
	{
		delayWrite(&nodo_control.delay_nodo, INITIAL_DELAY_MS);
		nodoLedInit();
		actual_mode = nodo_control.new_mode;
		nodo_control.flag_mode_has_changed = true;
	}

	switch (nodo_control.new_mode)
	{
	case OPERATIVE:
		operativeMode();
		break;
	case MAINTENANCE:
		maintenanceMode();
		break;
	case INIT:
		initMode();
		break;
	default:
		break;
	}
}

static bool_t nodoTakeSem()
{
	if (nodo_control.semaphore_is_taken == false)
	{
		nodo_control.semaphore_is_taken = true;
		return true;
	}
	else
		return false;
}

static bool_t nodoReleaseSem()
{
	if (nodo_control.semaphore_is_taken == true)
	{
		nodo_control.semaphore_is_taken = false;
		return true;
	}
	else
		return false;
}

void nodoSetMode(nodo_state_t mode)
{
	if (nodoTakeSem())
	{
		nodo_control.new_mode = mode;
		nodoReleaseSem();
	}
}

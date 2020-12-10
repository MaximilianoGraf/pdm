#include "debouncer.h"

typedef enum{
   STATE_BUTTON_UP,
   STATE_BUTTON_DOWN,
   STATE_BUTTON_FALLING,
   STATE_BUTTON_RISING
} fsmButtonState_t;

fsmButtonState_t fsmButtonState;

static void buttonError()
{
   fsmButtonState = STATE_BUTTON_UP;
}

void buttonDebouncerInit()
{
   fsmButtonState = STATE_BUTTON_UP;  // Set initial state
}


// FSM Update Sate Function
void buttonDebouncerUpdate( trigger_t trigger )
{
   static bool_t flagFalling = FALSE;
   static bool_t flagRising = FALSE;
   
   switch( fsmButtonState ){

      case STATE_BUTTON_UP: 
         /* CHECK TRANSITION CONDITIONS */
         if( !gpioRead(trigger.tecla) ){
            fsmButtonState = STATE_BUTTON_FALLING;
         }
      break;

      case STATE_BUTTON_DOWN:
         /* CHECK TRANSITION CONDITIONS */
         if( gpioRead(trigger.tecla) ){
            fsmButtonState = STATE_BUTTON_RISING;
         }
      break;

      case STATE_BUTTON_FALLING:      
         /* ENTRY */
         if( flagFalling == FALSE ){
            flagFalling = TRUE;
            delayWrite(trigger.delay, trigger.delay_time);
         }      
         /* CHECK TRANSITION CONDITIONS */
         if( delayRead(trigger.delay) ){
            if( !gpioRead(trigger.tecla) ){
               fsmButtonState = STATE_BUTTON_DOWN;
               trigger.tecPressed();
            } else{
               fsmButtonState = STATE_BUTTON_UP;
            }
         }

         /* LEAVE */
         if( fsmButtonState != STATE_BUTTON_FALLING )
         {
            flagFalling = FALSE;
         }
      break;

      case STATE_BUTTON_RISING:      
         /* ENTRY */
         if( flagRising == FALSE )
         {
            flagRising = TRUE;
            delayWrite(trigger.delay, trigger.delay_time);
         }    
         /* CHECK TRANSITION CONDITIONS */
         
         if( delayRead(trigger.delay))
         {
            if( gpioRead(trigger.tecla) )
            {
               fsmButtonState = STATE_BUTTON_UP;
               trigger.tecReleased();
            }
            else
            {
               fsmButtonState = STATE_BUTTON_DOWN;
            }
         }
         
         /* LEAVE */
         if( fsmButtonState != STATE_BUTTON_RISING )
         {
            flagRising = FALSE;
         }
      break;

      default:
    	  buttonError();
      break;
   }
}

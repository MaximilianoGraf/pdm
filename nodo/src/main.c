#include "nodo.h"
#include "sapi.h"

int main(void)
{
   // ----- Setup -----------------------------------
   boardInit();
   nodoInit(INIT);

   // ----- Repeat for ever -------------------------
   while(true)
   {
	   nodoMef();
   }
   return 0;
}

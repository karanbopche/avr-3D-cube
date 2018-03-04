#include "cube.h"

int main()
{
	InitDisplay();
	SetTimer();
	while(1)
	{
		Display();
	}
	return 0;
}

ISR(TIMER1_COMPB_vect)
{
	NewFrame();
	TCNT1 = 0;
}

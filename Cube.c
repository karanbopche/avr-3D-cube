#include "Cube.h"

Sequence_t Sequence;

uint8_t Cube[8] = {136, 136, 136, 136, 136, 136, 136, 136};
// location of current Frame in sequence......
uint8_t Location;

// to cycle between columns of cube.......
uint16_t Address = 0xffff;

void InitDisplay()
{
	// initialize the display port and control port for Cube...........
	// set data direction to output....
	DDR_DISPLAY_PORT |= 0x0f;
	DDR_CONTROL_PORT1 = 0xff;
	DDR_CONTROL_PORT2 = 0xff;
	// set pin voltage levels...
	DISPLAY_PORT = 0x00;
	CONTROL_PORT1 = 0xff;
	CONTROL_PORT2 = 0xff;
	// pointer to the sequence.........
	Sequence.NewSequence = BlinkSequence;
	Sequence.LoadFrame = Memory;
	Sequence.NewSequence();
	Sequence.Loop = 8;
}
void SetTimer()
{
	sei();
	TIMSK |= (1<<TIMER_INTERRUPT);
	TIMER_COMP = 15000;
	TCNT1 = 0;
	TCCR1B |= (1<<CS11);
}
// engine to drive the Cube........
void Display()
{
	uchar i;
	for(i=0;i<16;i++)
	{
		// low each address pin one by one.........
		Address &= ~(1<<i);
		CONTROL_PORT1 = Address;
		CONTROL_PORT2 = (Address>>8);
		if(i<8)
			DISPLAY_PORT = Cube[i];
		else
			DISPLAY_PORT = (Cube[i-8]>>4);
		_delay_ms(1);
		// Clear address port......
		DISPLAY_PORT = 0x00;
		Address = 0xFFFF;
	}
}

// load Frame of sequence from memory to Cube........
void Memory()
{
	uchar i;
	ClearCube();
	for(i=0;i<8;i++)
	{
		Cube[i] = pgm_read_byte(&Sequence.Sequence[Location]);
		Location++;
	}
}

void NewFrame()
{
	Sequence.LoadFrame();
	// repeat the sequence.......
	if(Location >= Sequence.SizeOfSequence)
	{
		Location = 0;
		// if loop time completed then load new sequence.....
		Sequence.Loop--;
		if(Sequence.Loop<1)
		{
			Sequence.Loop = 8;				// default loops...
			ClearCube();
			Location = 0;			// reset location
			TIMER_COMP = 15000;		// Time........
			Sequence.NewSequence();
			Sequence.LoadFrame = Memory;		// By default load Frames form memory.....
		}
	}
}

void ClearCube()
{
	uchar i;
	for(i=0;i<8;i++)
		Cube[i] = 0;
}

// All the sequence functions..............
void BlinkSequence()
{
	//set the size of sequence array......
	Sequence.SizeOfSequence = sizeof(Blink);
	// Set current sequence array pointer.....
	Sequence.Sequence = (uint8_t*) Blink;
	// Set next sequence function pointer.....
	Sequence.NewSequence = WallSequence;
}
void WallSequence()
{
	Sequence.SizeOfSequence = sizeof(Wall);
	Sequence.Sequence = (uint8_t*) Wall;
	Sequence.NewSequence = Wall1Sequence;
}
void Wall1Sequence()
{
	Sequence.SizeOfSequence = sizeof(Wall1);
	Sequence.Sequence = (uint8_t*) Wall1;
	Sequence.NewSequence = Wall2Sequence;
}
void Wall2Sequence()
{
	Sequence.SizeOfSequence = sizeof(Wall2);
	Sequence.Sequence = (uint8_t*) Wall2;
	Sequence.NewSequence = Wall3Sequence;
}
void Wall3Sequence()
{
	Sequence.SizeOfSequence = sizeof(Wall3);
	Sequence.Sequence = (uint8_t*) Wall3;
	Sequence.NewSequence = RollSequence;
}
void RollSequence()
{
	Sequence.SizeOfSequence = sizeof(Roll);
	Sequence.Sequence = (uint8_t*) Roll;
	Sequence.NewSequence = RainSequence;
}
void RainSequence()
{
	Sequence.SizeOfSequence = sizeof(Rain);
	Sequence.Loop = 4;
	TIMER_COMP = 55000;
	Sequence.Sequence = (uint8_t*) Rain;
	Sequence.NewSequence = IncSequence;
}

void IncSequence()
{
	Sequence.SizeOfSequence = 128;
	// this sequence uses Function to generate the Frames.......
	Sequence.LoadFrame = IncFrames;
	TIMER_COMP = 55000;
	Sequence.NewSequence = BlinkSequence;
}
// Function to Generate IncSequence Frames.......
void IncFrames()
{
	uchar i;
	for(i=0;i<8;i++)
		Cube[i] |= (1<<Location);
	Location++;
}

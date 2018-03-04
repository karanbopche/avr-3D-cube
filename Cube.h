#ifndef _CUBE_H_
#define _CUBE_H_

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <stdint.h>

typedef unsigned int uint;
typedef unsigned char uchar;

typedef struct {
	// next sequence function pointer......
	void (*NewSequence)(void);
	// Load Frame from Memory or from funtion......
	void (*LoadFrame)(void);
	// Current Sequence pointer..................
	uint8_t *Sequence;
	// size of current sequence......
	uint8_t SizeOfSequence;
	// counter for looping through sequence........
	uint8_t Loop;
} Sequence_t;

// definations of Hardware..............
#define DDR_DISPLAY_PORT	DDRC
#define DDR_CONTROL_PORT1	DDRB
#define DDR_CONTROL_PORT2	DDRD
#define DISPLAY_PORT		PORTC
#define CONTROL_PORT1		PORTB
#define CONTROL_PORT2  		PORTD
#define TIMER_INTERRUPT		OCIE1B
#define TIMER_COMP			OCR1B

//Function prototypes...........
void InitDisplay();
void SetTimer();
void Display();
void ClearCube();
void SetLoop(uint8_t loop);
void NewFrame();
void Memory();
// sequence functions.......
void BlinkSequence();
void WallSequence();
void Wall1Sequence();
void Wall2Sequence();
void Wall3Sequence();
void RollSequence();
void RainSequence();
void IncSequence();
void IncFrames();

// Static Array of sequence.......
static const uint8_t Blink[16] PROGMEM = 
{
	255, 255, 255, 255, 255, 255, 255, 255,
	0, 0, 0, 0, 0, 0, 0, 0
}; 
static const uint8_t Wall[48] PROGMEM = 
{
	17, 17, 17, 17, 17, 17, 17, 17, // First wall.......
	34, 34, 34, 34, 34, 34, 34, 34,  
	68, 68, 68, 68, 68, 68, 68, 68,
	136, 136, 136, 136, 136, 136, 136, 136,
	68, 68, 68, 68, 68, 68, 68, 68,
	34, 34, 34, 34, 34, 34, 34, 34
};
static const uint8_t Wall1[56] PROGMEM = 
{
	255, 0, 0, 0, 255, 0, 0, 0,
	255, 255, 0, 0, 255, 255, 0, 0,
	255, 255, 255, 0, 255, 255, 255, 0,
	255, 255, 255, 255, 255, 255, 255, 255,
	255, 255, 255, 0, 255, 255, 255, 0,
	255, 255, 0, 0, 255, 255, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0
};
static const uint8_t Wall2[48] PROGMEM = 
{
	15, 15, 15, 15, 0, 0 ,0, 0,
	0, 0, 0, 0, 15, 15, 15, 15,
	240, 240, 240, 240, 0, 0, 0, 0,
	0, 0, 0, 0, 240, 240, 240, 240,
	240, 240, 240, 240, 0, 0, 0, 0,
	0, 0, 0, 0, 15, 15, 15, 15
};
static const uint8_t Wall3[48] PROGMEM = 
{
	255, 15, 15, 15, 255, 0, 0, 0, 
	0, 255, 0, 0, 15, 255, 15, 15, 
	240, 240, 255, 240,  0, 0, 255, 0,
	0, 0, 0, 255, 240, 240, 240, 255, 
	240, 240, 255, 240,  0, 0, 255, 0,
	0, 255, 0, 0, 15, 255, 15, 15, 
};
static const uint8_t Roll[48] PROGMEM = 
{
	15, 0, 0, 0, 0, 0, 0, 240,
	0, 15, 0, 0, 0, 0, 240, 0,
	0, 0, 15, 0, 0, 240, 0, 0,
	0, 0, 0, 15, 240, 0, 0, 0,
	240, 0, 0, 0, 0, 0, 0, 15,
	0, 0, 0, 240, 15, 0, 0, 0
};
static const uint8_t Rain[80] PROGMEM = 
{
	15, 15, 15, 15, 0, 0 ,0, 0,
	0, 0, 0, 0, 15, 15, 15, 15,
	240, 240, 240, 240, 0, 0, 0, 0,
	0, 0, 0, 0, 240, 240, 240, 240, 
	16, 0, 16, 128, 224, 240, 224, 112, 
	32, 0, 32, 64, 193, 240, 193, 56, 
	65, 0, 65, 40, 130, 240, 130, 20, 
	131, 32, 131, 28, 4, 208, 4, 2, 
	7, 208, 7, 14, 8, 2, 8, 1, 
	15, 2, 15, 15, 0, 13, 0, 0, 
};
#endif

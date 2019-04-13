#include "Info.h"

#ifndef _GAME
#define _GAME

#define NUM_ENTITYS 2

typedef enum _COLOR
{
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	YELLOW,
	WHITE
} COLOR;

typedef enum _OBJECTS
{
	NONE,
	FOOD,
	BLOCK
} OBJECTS;

typedef struct _ENTITY
{
	POSITION pos;
	POSITION pre;
	COLOR color;
} ENTITY, *PENTITY, ENTITYS[NUM_ENTITYS];

typedef MOVEMENT MOVEMENTS[NUM_ENTITYS];
typedef POSITION *PPOSITION;


#define KEY_ENTER 0x0d

#endif

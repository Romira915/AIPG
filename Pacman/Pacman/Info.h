#ifndef _INFO
#define _INFO

#define MAP_WIDTH 19
#define MAP_HEIGHT 22

//#define NUM_FOOD 156

typedef enum _MOVEMENT
{
	STAY,
	UP,
	LEFT,
	RIGHT,
	DOWN
} MOVEMENT;

typedef struct _POSITION
{
	int x;
	int y;
} POSITION;

typedef unsigned char MAPDATA[MAP_HEIGHT][MAP_WIDTH];

#endif

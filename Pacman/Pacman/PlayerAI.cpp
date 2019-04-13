#include <stdio.h>
#include <stdlib.h>
#include "Info.h"

#define U 0
#define D 1
#define L 2
#define R 3
#define NO 4

bool Enemy_pos(int dir, POSITION p, POSITION e) {
	switch (dir)
	{
	case U: {
		if (p.y - 1 == e.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	} break;
	case D: {
		if (p.y + 1 == e.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	} break;
	case L: {
		if (p.x - 1 == e.x)
		{
			return true;
		}
		else
		{
			return false;
		}
	} break;
	case R: {
		if (p.x + 1 == e.x)
		{
			return true;
		}
		else
		{
			return false;
		}
	} break;
	default: exit(-1);
		break;
	}
}

MOVEMENT playerAI(MAPDATA map, POSITION p, POSITION e, int turn)
{
	return LEFT;
}

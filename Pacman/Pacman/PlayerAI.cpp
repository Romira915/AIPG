#include <stdio.h>
#include <stdlib.h>
#include "Info.h"

#define U 10
#define D 11
#define L 12
#define R 13
#define NO 14
#define ROAD 0
#define FOOD 1
#define WALL 2

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

MOVEMENT Food_Search(MAPDATA map, POSITION p) {
	if (map[p.y - 1][p.x] == FOOD)
	{
		return UP;
	}
	if (map[p.y + 1][p.x] == FOOD)
	{
		return DOWN;
	}
	if (map[p.y][p.x + 1] == FOOD)
	{
		return RIGHT;
	}
	if (map[p.y][p.x - 1] == FOOD)
	{
		return LEFT;
	}

	return STAY;
}

MOVEMENT Road_Search(MAPDATA map, POSITION p) {

}

MOVEMENT playerAI(MAPDATA map, POSITION p, POSITION e, int turn)
{
	return LEFT;
}

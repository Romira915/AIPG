#include <stdio.h>
#include <stdlib.h>
#include "Info.h"

#include <queue>
#include <cmath>
using namespace std;

#define ROAD 0
#define FOOD 1
#define WALL 2

class Direction
{
public:
	Direction();
	~Direction();

	void Init(MOVEMENT);
	void All_true();
	void All_false();

	bool up, left, right, down;
	queue<MOVEMENT> node;

private:

};

Direction::Direction()
{
	All_true();
}

Direction::~Direction()
{
}

void Direction::Init(MOVEMENT dir_off = STAY)
{
	All_true();
	if (dir_off != STAY)
	{
		switch (dir_off)
		{
		case UP: {up = false; }break;
		case LEFT: {left = false; }break;
		case RIGHT: {right = false; }break;
		case DOWN: {down = false; }break;
		default:
			break;
		}
	}
	MOVEMENT rn;
	while (up || left || right || down)
	{
		rn = MOVEMENT(rand() % 4 + 1);
		switch (rn)
		{
		case UP: {
			if (up)
			{
				node.push(UP);
				up = false;
			}
		}break;
		case LEFT: {
			if (left)
			{
				node.push(LEFT);
				left = false;
			}
		}break;
		case RIGHT: {
			if (right)
			{
				node.push(RIGHT);
				right = false;
			}
		}break;
		case DOWN: {
			if (down)
			{
				node.push(DOWN);
				down = false;
			}
		}break;
		default:printf("test");
			break;
		}
	}

	All_true();
}

void Direction::All_true()
{
	up = true;
	left = true;
	right = true;
	down = true;
}

void Direction::All_false()
{
	up = false;
	left = false;
	right = false;
	down = false;
}



MOVEMENT Enemy_pos(POSITION p, POSITION e) {
	if (p.x == e.x && p.y - 1 == e.y)
	{
		return UP;
	}
	if (p.x - 1 == e.x && p.y == e.y)
	{
		return LEFT;
	}
	if (p.x + 1 == e.x && p.y == e.y)
	{
		return RIGHT;
	}
	if (p.x == e.x && p.y + 1 == e.y)
	{
		return DOWN;
	}

	return STAY;
}

int Enemy_Distance(POSITION p, POSITION e, int dist = 1) {
	return 0;
}

MOVEMENT Map_Search(int target, Direction dir, MAPDATA map, POSITION p, int range = 1) {
	while (!dir.node.empty())
	{
		MOVEMENT tmp;
		tmp = dir.node.front();
		dir.node.pop();

		switch (tmp)
		{
		case UP: {
			if (map[p.y - range][p.x] == target)
			{
				return UP;
			}
		}break;
		case LEFT: {
			if (map[p.y][p.x - range] == target)
			{
				return LEFT;
			}
		}break;
		case RIGHT: {
			if (map[p.y][p.x + range] == target)
			{
				return RIGHT;
			}
		}break;
		case DOWN: {
			if (map[p.y + range][p.x] == target)
			{
				return DOWN;
			}
		}break;
		default:
			break;
		}
	}

	return STAY;
}

MOVEMENT playerAI(MAPDATA map, POSITION p, POSITION e, int turn)
{
	Direction dir;

	dir.Init(Enemy_pos(p, e));
	if (Enemy_pos(p, e) == STAY)
	{
		return STAY;
	}
	else
	{
		if (Map_Search(FOOD, dir, map, p) != STAY)
		{
			return Map_Search(FOOD, dir, map, p);
		}
		else
		{
			return Map_Search(ROAD, dir, map, p);
		}
	}
}

#include <stdio.h>
#include "Info.h"

#define _START 5
#define _GOAL 250

#define _ABS(x) ((x) < 0 ? (x) * -1 : (x))

int _manhattanDist(int x1, int y1, int x2, int y2)
{
	int dx, dy;

	dx = _ABS(x1 - x2);
	dy = _ABS(y1 - y2);

	return dx + dy;
}

POSITION _getPosition(int x, int y)
{
	POSITION pos;

	pos.x = x;
	pos.y = y;

	return pos;
}

void _getPositionAround(int x, int y, POSITION pos[4])
{
	pos[0] = _getPosition(x, y - 1);
	pos[1] = _getPosition(x - 1, y);
	pos[2] = _getPosition(x + 1, y);
	pos[3] = _getPosition(x, y + 1);
}

int _calcPath(int cost, MAPDATA map, POSITION tar)
{
	POSITION pos[4];

	int num;
	int x, y;
	int i, j, k;

	for (i = 0; i < MAP_HEIGHT; i++)
	{
		for (j = 0; j < MAP_WIDTH; j++)
		{
			num = cost + _manhattanDist(j, i, tar.x, tar.y);

			if (map[i][j] == num)
			{
				_getPositionAround(j, i, pos);

				for (k = 0; k < 4; k++)
				{
					x = pos[k].x;
					y = pos[k].y;

					if (map[y][x] == _GOAL)
						return k;

					switch(map[y][x])
					{
					case 0:
					case 1:
						map[y][x] = (cost + 1) + _manhattanDist(x, y, tar.x, tar.y);
						break;

					case 2:
					default:
						break;
					}
				}
			}
		}
	}

	return _calcPath(cost + 1, map, tar);
}

MOVEMENT redAI(MAPDATA map, POSITION p, POSITION e, int turn)
{
	map[p.y][p.x] = _START;
	map[e.y][e.x] = _GOAL;

	if (map[p.y][p.x] == _GOAL)
		return STAY;

	map[p.y][p.x] += _manhattanDist(p.x, p.y, e.x, e.y);

	switch (_calcPath(_START, map, e))
	{
	case 0: return DOWN; break;
	case 1: return RIGHT; break;
	case 2: return LEFT; break;
	case 3: return UP; break;

	default:
		break;
	}

	return STAY;
}

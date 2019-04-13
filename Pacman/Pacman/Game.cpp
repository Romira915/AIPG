#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Windows.h>

#include "Game.h"

MOVEMENT playerAI(MAPDATA map, POSITION p, POSITION e, int turn);
MOVEMENT redAI(MAPDATA map, POSITION p, POSITION e, int turn);

MOVEMENT (*entityAI[])(MAPDATA map, POSITION p, POSITION e, int turn) = {
	playerAI,
	redAI,
};

// 初期マップデータ
#if 0
MAPDATA mapStd = {
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2 },
	{ 2, 1, 2, 2, 1, 2, 2, 2, 1, 2, 1, 2, 2, 2, 1, 2, 2, 1, 2 },
	{ 2, 1, 2, 2, 1, 2, 2, 2, 1, 2, 1, 2, 2, 2, 1, 2, 2, 1, 2 },
	{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2 },
	{ 2, 1, 2, 2, 1, 2, 1, 2, 2, 2, 2, 2, 1, 2, 1, 2, 2, 1, 2 },
	{ 2, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 2 },
	{ 2, 2, 2, 2, 1, 2, 2, 2, 0, 2, 0, 2, 2, 2, 1, 2, 2, 2, 2 },
	{ 0, 0, 0, 2, 1, 2, 0, 0, 0, 0, 0, 0, 0, 2, 1, 2, 0, 0, 0 },
	{ 2, 2, 2, 2, 1, 2, 0, 2, 2, 0, 2, 2, 0, 2, 1, 2, 2, 2, 2 },
	{ 0, 0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 2, 0, 0, 1, 0, 0, 0, 0 },
	{ 2, 2, 2, 2, 1, 2, 0, 2, 2, 2, 2, 2, 0, 2, 1, 2, 2, 2, 2 },
	{ 0, 0, 0, 2, 1, 2, 0, 0, 0, 0, 0, 0, 0, 2, 1, 2, 0, 0, 0 },
	{ 2, 2, 2, 2, 1, 2, 0, 2, 2, 2, 2, 2, 0, 2, 1, 2, 2, 2, 2 },
	{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2 },
	{ 2, 1, 2, 2, 1, 2, 2, 2, 1, 2, 1, 2, 2, 2, 1, 2, 2, 1, 2 },
	{ 2, 1, 1, 2, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 2, 1, 1, 2 },
	{ 2, 2, 1, 2, 1, 2, 1, 2, 2, 2, 2, 2, 1, 2, 1, 2, 1, 2, 2 },
	{ 2, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 2 },
	{ 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2 },
	{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2 },
	{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
};
#endif

#define NUM_MAP 3

MAPDATA mapStd[NUM_MAP] = {
	// １面目
	{
		{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2 },
		{ 2, 1, 2, 2, 1, 2, 2, 2, 1, 2, 1, 2, 2, 2, 1, 2, 2, 1, 2 },
		{ 2, 1, 2, 2, 1, 2, 2, 2, 1, 2, 1, 2, 2, 2, 1, 2, 2, 1, 2 },
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2 },
		{ 2, 1, 2, 2, 1, 2, 1, 2, 2, 2, 2, 2, 1, 2, 1, 2, 2, 1, 2 },
		{ 2, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 2 },
		{ 2, 1, 2, 2, 1, 2, 2, 2, 0, 2, 0, 2, 2, 2, 1, 2, 2, 1, 2 },
		{ 2, 1, 2, 2, 1, 2, 0, 0, 0, 0, 0, 0, 0, 2, 1, 2, 2, 1, 2 },
		{ 2, 1, 2, 2, 1, 2, 0, 2, 2, 2, 2, 2, 0, 2, 1, 2, 2, 1, 2 },
		{ 2, 1, 1, 1, 1, 0, 0, 2, 2, 2, 2, 2, 0, 0, 1, 1, 1, 1, 2 },
		{ 2, 1, 2, 2, 1, 2, 0, 2, 2, 2, 2, 2, 0, 2, 1, 2, 2, 1, 2 },
		{ 2, 1, 2, 2, 1, 2, 0, 0, 0, 0, 0, 0, 0, 2, 1, 2, 2, 1, 2 },
		{ 2, 1, 2, 2, 1, 2, 0, 2, 2, 2, 2, 2, 0, 2, 1, 2, 2, 1, 2 },
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2 },
		{ 2, 1, 2, 2, 1, 2, 2, 2, 1, 2, 1, 2, 2, 2, 1, 2, 2, 1, 2 },
		{ 2, 1, 1, 2, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 2, 1, 1, 2 },
		{ 2, 2, 1, 2, 1, 2, 1, 2, 2, 2, 2, 2, 1, 2, 1, 2, 1, 2, 2 },
		{ 2, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 2 },
		{ 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2 },
		{ 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2 },
		{ 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	},
	// ２面目
	{
		{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
		{ 2,1,1,1,1,1,2,1,1,1,1,1,2,1,1,1,1,1,2 },
		{ 2,1,2,2,2,1,2,1,2,2,2,1,2,1,2,2,2,1,2 },
		{ 2,1,2,1,1,1,2,1,2,1,1,1,1,1,1,1,2,1,2 },
		{ 2,1,2,1,2,1,2,1,2,1,2,1,2,2,2,1,2,1,2 },
		{ 2,1,2,1,2,1,2,1,2,1,2,1,1,1,2,1,2,1,2 },
		{ 2,1,2,1,2,1,2,1,2,1,2,2,2,1,2,1,2,1,2 },
		{ 2,1,2,1,2,1,2,1,1,1,1,1,1,1,2,1,2,1,2 },
		{ 2,1,2,1,2,1,2,2,2,1,2,2,2,1,2,1,2,1,2 },
		{ 2,1,2,1,2,1,1,1,2,1,1,1,2,1,2,1,2,1,2 },
		{ 2,1,2,1,1,1,2,1,2,1,2,1,2,1,1,1,1,1,2 },
		{ 2,1,2,1,2,2,2,1,2,1,2,1,2,2,2,1,2,2,2 },
		{ 2,1,2,1,1,1,1,1,1,1,2,1,1,1,2,1,1,1,2 },
		{ 2,1,2,2,2,1,2,2,2,1,2,2,2,1,2,2,2,1,2 },
		{ 2,1,1,1,2,1,1,1,2,1,2,1,1,1,1,1,1,1,2 },
		{ 2,1,2,1,2,2,2,1,2,1,2,1,2,1,2,2,2,1,2 },
		{ 2,1,2,1,1,1,1,1,1,1,1,1,2,1,1,1,2,1,2 },
		{ 2,1,2,1,2,2,2,1,2,2,2,1,2,2,2,1,2,1,2 },
		{ 2,1,2,1,1,1,2,1,1,1,2,1,1,1,1,1,2,1,2 },
		{ 2,1,2,2,2,1,2,2,2,1,2,1,2,2,2,1,2,1,2 },
		{ 2,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,2 },
		{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
	},
	// ３面目
	{
		{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
		{ 2,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,2 },
		{ 2,1,2,2,2,1,2,2,2,1,2,1,2,1,2,2,2,1,2 },
		{ 2,1,1,1,2,1,1,1,1,1,2,1,2,1,1,1,2,1,2 },
		{ 2,1,2,1,2,2,2,1,2,1,2,1,2,2,2,1,2,1,2 },
		{ 2,1,2,1,1,1,1,1,2,1,2,1,1,1,1,1,2,1,2 },
		{ 2,1,2,2,2,1,2,2,2,1,2,2,2,2,2,2,2,1,2 },
		{ 2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2 },
		{ 2,2,2,1,2,2,2,2,2,1,2,2,2,1,2,2,2,1,2 },
		{ 2,1,1,1,2,1,1,1,2,1,1,1,2,1,2,1,1,1,2 },
		{ 2,1,2,1,1,1,2,1,1,1,2,1,2,1,1,1,2,1,2 },
		{ 2,1,2,2,2,1,2,2,2,1,2,1,2,2,2,1,2,1,2 },
		{ 2,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,2,1,2 },
		{ 2,1,2,2,2,1,2,2,2,2,2,2,2,1,2,1,2,1,2 },
		{ 2,1,2,1,1,1,2,1,1,1,1,1,1,1,2,1,2,1,2 },
		{ 2,1,2,1,2,1,2,1,2,2,2,1,2,2,2,1,2,1,2 },
		{ 2,1,1,1,2,1,1,1,1,1,2,1,1,1,1,1,2,1,2 },
		{ 2,1,2,2,2,2,2,1,2,1,2,2,2,2,2,2,2,1,2 },
		{ 2,1,2,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,2 },
		{ 2,1,2,1,2,1,2,2,2,1,2,1,2,1,2,2,2,1,2 },
		{ 2,1,1,1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,2 },
		{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2 },
	},
};

POSITION yellowInit[NUM_MAP] = {
	{ 9, 16 },	// １面目スタート地点
	{ 17, 20 },	// ２面目スタート地点
	{ 1, 20 },	// ３面目スタート地点
};
POSITION redInit[NUM_MAP] = {
	{ 9, 8 },	// １面目スタート地点
	{ 1, 1 },	// ２面目スタート地点
	{ 17, 1 },	// ３面目スタート地点
};

int num_food = 0;

// コンソール処理

void setColor(BOOL light, COLOR color, int shift)
{
	HANDLE hConsoleOutput;
	CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
	WORD wAttributes;

	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOutput, &consoleScreenBufferInfo);
	wAttributes = 15 << (4 - shift) & consoleScreenBufferInfo.wAttributes;

	wAttributes = light ? wAttributes | 8 << shift : wAttributes;
	wAttributes = wAttributes | color << shift;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

void setTextColor(BOOL light, COLOR color)
{
	setColor(light, color, 0);
}

void setBackgroundColor(BOOL light, COLOR color)
{
	setColor(light, color, 4);
}

void setDefaultColor()
{
	setTextColor(FALSE, WHITE);
	setBackgroundColor(FALSE, BLACK);
}

void setCursorVisible(BOOL flag)
{
	HANDLE hConsoleOutput;
	CONSOLE_CURSOR_INFO consoleCursorInfo;

	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleCursorInfo(hConsoleOutput, &consoleCursorInfo);

	consoleCursorInfo.bVisible = flag;
	SetConsoleCursorInfo(hConsoleOutput, &consoleCursorInfo);
}

void setCursorPosition(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;

	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	dwCursorPosition.X = x * 2;
	dwCursorPosition.Y = y;

	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

void putObject(int x, int y, char *obj, BOOL light, COLOR color)
{
	setCursorPosition(x, y);
	setTextColor(light, color);
	printf("%s", obj);
}

void updateLocation(int x, int y, MAPDATA mapData)
{
	switch (mapData[y][x])
	{
	case NONE:
		putObject(x, y, "　", FALSE, WHITE);
		break;

	case FOOD:
		putObject(x, y, "・", FALSE, YELLOW);
		break;

	case BLOCK:
		putObject(x, y, "■", FALSE, BLUE);
		break;
	}
}

void updateEntitySymbol(ENTITY entity)
{
	putObject(entity.pos.x, entity.pos.y, "●", TRUE, entity.color);
}

void updateFoodsCount(int *foods)
{
	setCursorPosition(20, 2);
	setDefaultColor();
	printf("FOODS [%3d/%3d] = %d   ", foods[0], foods[1], (int)(30.0 * foods[0] / foods[1] + 0.5));
}



// ゲーム処理

void initMapData(MAPDATA mapData, int *foods, int map)
{
	int i, j;

	memcpy(mapData, mapStd[map], sizeof(MAPDATA));

	num_food = 0;
	foods[0] = 0;
	foods[1] = 0;
	for (i = 0; i < MAP_HEIGHT; i++) {
		for (j = 0; j < MAP_WIDTH; j++) {
			if (mapData[i][j] == 1) {
				foods[1]++;
				num_food++;
			}
		}
	}
}

void initEntity(PENTITY entity, int x, int y, COLOR color)
{
	entity->pos.x = x;
	entity->pos.y = y;
	entity->pre = entity->pos;
	entity->color = color;
}

void writeMap(ENTITYS entity, MAPDATA mapData, int *foods)
{
	int i, j;

	for (i = 0; i < MAP_HEIGHT; i++)
		for (j = 0; j < MAP_WIDTH; j++)
			updateLocation(j, i, mapData);

	for (i = 0; i < NUM_ENTITYS; i++)
		updateEntitySymbol(entity[i]);

	updateFoodsCount(foods);
}

BOOL checkMovable(PPOSITION pos, MAPDATA mapData)
{
	if (pos->y == 10)
	{
		if (pos->x == -1)
			pos->x = MAP_WIDTH - 1;

		if (pos->x == MAP_WIDTH)
			pos->x = 0;
	}

	if (pos->x < 0 || pos->x >= MAP_WIDTH)
		return FALSE;

	if (pos->y < 0 || pos->y >= MAP_HEIGHT)
		return FALSE;

	if (mapData[pos->y][pos->x] == BLOCK)
		return FALSE;

	return TRUE;
}

void moveReception(MOVEMENTS move, ENTITYS entity, MAPDATA mapData, int turn)
{
	MAPDATA mapBuff;
	POSITION pos[NUM_ENTITYS];
	int i, j;

	for (i = 0; i < NUM_ENTITYS; i++)
	{
		for (j = 0; j < NUM_ENTITYS; j++)
			pos[j] = entity[j].pos;

		memcpy(mapBuff, mapData, sizeof(MAPDATA));
		move[i] = (entityAI[i])(mapBuff, pos[0], pos[1], turn);
	}
}

void moveEntitys(MOVEMENTS move, ENTITYS entity, MAPDATA mapData)
{
	int i;

	for (i = 0; i < NUM_ENTITYS; i++)
	{
		entity[i].pre = entity[i].pos;

		switch (move[i])
		{
		case STAY: break;
		case UP: (entity[i].pos.y)--; break;
		case LEFT: (entity[i].pos.x)--; break;
		case RIGHT: (entity[i].pos.x)++; break;
		case DOWN: (entity[i].pos.y)++; break;
		}

		if (!checkMovable(&(entity[i].pos), mapData))
			entity[i].pos = entity[i].pre;
	}
}

BOOL comparePosition(POSITION pos1, POSITION pos2)
{
	BOOL flagX;
	BOOL flagY;

	flagX = pos1.x == pos2.x;
	flagY = pos1.y == pos2.y;

	if (flagX && flagY)
		return TRUE;

	return FALSE;
}

BOOL checkAlive(ENTITYS entity, MAPDATA mapData)
{
	int i;

	for (i = 1; i < NUM_ENTITYS; i++)
	{
		if (comparePosition(entity[0].pos, entity[i].pos))
			return FALSE;

		if (comparePosition(entity[0].pos, entity[i].pre))
		{
			if (comparePosition(entity[0].pre, entity[i].pos))
			{
				entity[i].pos = entity[i].pre;
				return FALSE;
			}
		}
	}

	return TRUE;
}

BOOL tick(ENTITYS entity, MAPDATA mapData, int *foods, int *turn)
{
	MOVEMENTS move;
	BOOL flag = FALSE;

	int i;
	int x, y;

	moveReception(move, entity, mapData, *turn);
	moveEntitys(move, entity, mapData);

	if (checkAlive(entity, mapData))
	{
		x = entity[0].pos.x;
		y = entity[0].pos.y;

		if (mapData[y][x] == FOOD)
		{
			mapData[y][x] = NONE;
			foods[0]++;
		}

		flag = TRUE;
	}

	for (i = 0; i < NUM_ENTITYS; i++)
		updateLocation(entity[i].pre.x, entity[i].pre.y, mapData);

	for (i = 0; i < NUM_ENTITYS; i++)
		updateEntitySymbol(entity[i]);
	
	if (foods[0] == num_food || (*turn)++ >= 1000)
	{
		flag = FALSE;
	}

	updateFoodsCount(foods);
	Sleep(2);

	return flag;
}



// メイン

int main(void)
{
	MAPDATA mapData;
	ENTITYS entity;

	int totalFoods[2] = {0, 0};
	int foods[2];
	int turn = 0;

	// ランダムシードの固定
	srand(0);

	// カーソルの消去
	setCursorVisible(FALSE);

	for (int map = 0; map < NUM_MAP; map++) {
		// 初期化
		initMapData(mapData, foods, map);
		initEntity(&entity[0], yellowInit[map].x, yellowInit[map].y, YELLOW);
		initEntity(&entity[1], redInit[map].x, redInit[map].y, RED);

		// マップ表示
		writeMap(entity, mapData, foods);

		turn = 0;
		totalFoods[1] += foods[1];
		// ゲームループ
		while (tick(entity, mapData, foods, &turn));
		totalFoods[0] += foods[0];

		Sleep(2000);
	}

	// 終了
	//rewind(stdin);
	// マップ表示
	foods[0] = totalFoods[0];
	foods[1] = totalFoods[1];
	writeMap(entity, mapData, foods);

	printf("HIT ENTER KEY");
	while (_getch() != KEY_ENTER);
	return 0;
}

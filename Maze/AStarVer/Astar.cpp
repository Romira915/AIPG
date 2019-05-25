#include "Astar.h"
#include <cstdlib>

Astar::Astar()
{
	printf("このインスタンスは無効です");
	exit(-1);
}

Astar::Astar(int h,int w,int** input_maze)
{
	height = h;
	width = w;
	maze = input_maze;
	Init();
}

Astar::~Astar()
{
}

void Astar::Init()
{
	while (!nodeQ.empty()) { nodeQ.pop(); }
	x = STARTXY;
	y = STARTXY;
	goal_x = 2 * width - 1;
	goal_y = 2 * height - 1;

	nodeQ.push(Pos(x, y, Manhattan_dist(x, y, goal_x, goal_y), 0));
	x = goal_x;
	y = goal_y;
}

inline int Astar::Manhattan_dist(int x, int y, int dx, int dy) const
{
	return abs(dx - x) + abs(dy - y);
}

Astar::Pos::Pos() {
	x = 0;
	y = 0;
	score = 0;
	cost = 0;
}

inline Astar::Pos::Pos(int xin, int yin) {
	x = xin;
	y = yin;
	score = -1;
	cost = -1;
}

inline Astar::Pos::Pos(int xin, int yin, int scorein, int costin)
{
	x = xin;
	y = yin;
	score = scorein;
	cost = costin;
}

Astar::Pos::~Pos() {

}

inline bool Astar::Pos::operator>(const Pos& p) const {
	if (this->score != p.score)
	{
		return this->score > p.score;
	}
	else
	{
		return this->cost > p.cost;
	}
}

Astar::Pos Astar::Pos::operator=(const Pos& p)
{
	this->x = p.x;
	this->y = p.y;
	this->score = p.score;
	this->cost = p.cost;
	return *this;
}

inline int Astar::Pos::Get_x() const
{
	return x;
}

inline int Astar::Pos::Get_y() const
{
	return y;
}

inline int Astar::Pos::Get_cost() const
{
	return cost;
}

inline int Astar::Pos::Get_score() const
{
	return score;
}

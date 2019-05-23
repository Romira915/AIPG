#include "Astar.h"

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
	init();
}

Astar::~Astar()
{
}

void Astar::init()
{
	while (!nodeQ.empty()) { nodeQ.pop(); }
	x = STARTXY;
	y = STARTXY;
}

Astar::Pos::Pos() {
	x = 0;
	y = 0;
	score = 0;
	cost = 0;
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

#pragma once

#include <queue>
#include <vector>

class Astar
{
public:
	Astar();
	~Astar();

private:
	class Pos
	{
	public:
		Pos();
		Pos(int, int, int, int);
		~Pos();

		bool operator>(const Pos&) const;

	private:
		int x, y;
		int cost, score;
	};

	std::priority_queue< Pos, std::vector<Pos>, std::greater<Pos >> nodeQ;
};

Astar::Astar()
{
}

Astar::~Astar()
{
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

inline bool Astar::Pos::operator>(const Pos& p)const {
	if (this->score != p.score)
	{
		return this->score > p.score;
	}
	else
	{
		return this->cost > p.cost;
	}
}

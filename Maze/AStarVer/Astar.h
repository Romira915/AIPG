#pragma once

#include <queue>
#include <vector>

#define STARTXY 1
#define ROAD 0
#define VISITED 500
#define SHORTEST 1000

class Astar
{
public:
	Astar();
	Astar(int, int, int**);
	~Astar();

private:
	class Pos
	{
	public:
		Pos();
		Pos(int, int, int, int);
		~Pos();

		bool operator>(const Pos&) const;
		inline int Get_x() const;
		inline int Get_y() const;
		inline int Get_cost() const;
		inline int Get_score() const;

	private:
		int x, y;
		int cost, score;
	};

	void init();

	std::priority_queue< Pos, std::vector<Pos>, std::greater<Pos >> nodeQ;
	int** maze;
	int height, width;
	int x, y;
};


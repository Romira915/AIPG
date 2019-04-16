#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <cstdlib>
#include <cstdio>

//#include "BFS.h"
//#include "Pos.h"

using namespace std;

#define STARTXY 1
#define ROAD 0
#define VISITED 500
#define SHORTEST 1000

class Pos
{
public:
	Pos();
	Pos(int, int);
	~Pos();

	int x, y;
	bool operator<(Pos a) const;
	Pos operator=(Pos a);
	bool operator==(Pos a);
};

class BFS
{
public:
	BFS();
	~BFS();

	void Search(const char** filename);

private:
	void ReadMaze(const char* filename);
	void WriteMaze(const char* filename);
	void init();
	bool Add_quese();
	Pos pos;
	Pos goal;
	int w, h;
	int** maze;
	queue<Pos> nodeQ;
	map<pair<int, int>, pair<int, int> > path;
	Pos queueNow;
	vector<Pos> tmp;
	vector<Pos>::iterator itr;

	int size;
};

Pos::Pos()
{
}

Pos::Pos(int x1, int y1)
{
	x = x1;
	y = y1;
}


Pos::~Pos()
{
}

bool Pos::operator<(const Pos a) const
{
	return x < a.x;
}

Pos Pos::operator=(Pos a)
{
	x = a.x;
	y = a.y;
	return *this;
}

bool Pos::operator==(Pos a)
{
	if (x == a.x && y == a.y)
	{
		return true;
	}
	else
	{
		return false;
	}
	return false;
}

BFS::BFS()
{
	w = 0;
	h = 0;
	maze = NULL;

	size = 100;
}


BFS::~BFS()
{
}

void BFS::ReadMaze(const char* filename)
{
	FILE* fp;
	int x, y;
	if (0 != fopen_s(&fp, filename, "r")) {
		fprintf(stderr, "指定された迷路の入力ファイルを開くことができませんでした．\n");
		exit(-1);
	}

	fscanf_s(fp, "%d,%d\n", &w, &h);

	maze = new int*[2 * h + 1];
	for (int i = 0; i < 2 * h + 1; i++)
	{
		maze[i] = new int[2 * w + 1];
	}

	goal.x = 2 * w - 1;
	goal.y = 2 * h - 1;

	for (y = 0; y < 2 * h + 1; y++) {
		for (x = 0; x < 2 * w + 1; x++) {
			fscanf_s(fp, "%d%*[^-0-9]", &(maze[y][x]));
		}
	}
	fclose(fp);
}

void BFS::WriteMaze(const char* filename)
{
	FILE* fp;
	int x, y;
	if (0 != fopen_s(&fp, filename, "w")) {
		fprintf(stderr, "指定された迷路の出力ファイルを開くことができませんでした．\n");
		exit(-1);
	}

	fprintf_s(fp, "%d,%d\n", w, h);
	for (y = 0; y < 2 * h + 1; y++) {
		for (x = 0; x < 2 * w + 1; x++) {
			fprintf_s(fp, "%d", maze[y][x]);
			if (x < 2 * w) {
				fprintf_s(fp, ",");
			}
			else {
				fprintf_s(fp, "\n");
			}
		}
	}
	fclose(fp);


	for (int i = 0; i < 2 * h + 1; i++)
	{
		delete[] maze[i];
	}
	delete[] maze;
	maze = NULL;

}

void BFS::init()
{
	pos.x = STARTXY;
	pos.y = STARTXY;
	maze[STARTXY][STARTXY] = VISITED;
	nodeQ.push(pos);
	pos = goal;
}

bool BFS::Add_quese()
{
	if (!nodeQ.empty())
	{
		queueNow = nodeQ.front();
		nodeQ.pop();
		if (maze[queueNow.y - 1][queueNow.x] == ROAD || (queueNow.y - 1 == goal.y && queueNow.x == goal.x)) {
			nodeQ.push(Pos{ queueNow.x, queueNow.y - 1 });
			maze[queueNow.y - 1][queueNow.x] = VISITED;
			path[make_pair(queueNow.x, queueNow.y - 1)] = make_pair(queueNow.x, queueNow.y);
		}
		if (maze[queueNow.y][queueNow.x + 1] == ROAD || (queueNow.y == goal.y && queueNow.x + 1 == goal.x)) {
			nodeQ.push(Pos{ queueNow.x + 1, queueNow.y });
			maze[queueNow.y][queueNow.x + 1] = VISITED;
			path[make_pair(queueNow.x + 1, queueNow.y)] = make_pair(queueNow.x, queueNow.y);

		}
		if (maze[queueNow.y + 1][queueNow.x] == ROAD || (queueNow.y + 1 == goal.y && queueNow.x == goal.x)) {
			nodeQ.push(Pos{ queueNow.x, queueNow.y + 1 });
			maze[queueNow.y + 1][queueNow.x] = VISITED;
			path[make_pair(queueNow.x, queueNow.y + 1)] = make_pair(queueNow.x, queueNow.y);

		}
		if (maze[queueNow.y][queueNow.x - 1] == ROAD || (queueNow.y == goal.y && queueNow.x - 1 == goal.x)) {
			nodeQ.push(Pos{ queueNow.x - 1, queueNow.y });
			maze[queueNow.y][queueNow.x - 1] = VISITED;
			path[make_pair(queueNow.x - 1, queueNow.y)] = make_pair(queueNow.x, queueNow.y);


		}

		if (queueNow == goal)
		{
			maze[queueNow.y][queueNow.x] = VISITED;

			return false;
		}


		return true;
	}
	else
	{
		return false;
	}
}

void BFS::Search(const char** filename)
{
	ReadMaze(filename[0]);

	init();

	printf("幅優先探索中・・・\n");
	while (Add_quese()) {
	}

	while (!(pos == Pos{ STARTXY,STARTXY }))
	{
		maze[path[make_pair(pos.x, pos.y)].second][path[make_pair(pos.x, pos.y)].first] = SHORTEST;
		pos = { path[make_pair(pos.x,pos.y)].first,path[make_pair(pos.x,pos.y)].second };
	}

	printf("探索完了\n");

	WriteMaze(filename[1]);
}



int main(int argc, char** argv) {
	const char* (test[])[2] = {
		{"maze8060A.csv", "maze8060A-out.csv" },
		{"maze8060B.csv", "maze8060B-out.csv" },
		{"maze8060C.csv", "maze8060C-out.csv" },
		{"maze8060D.csv", "maze8060D-out.csv" },
		{"maze8060E.csv", "maze8060E-out.csv" },
		{"maze8060F.csv", "maze8060F-out.csv" },
	}; // test is array[] of array[3] of pointer of char

	if (argc == 1)
	{
		BFS bfs[6];

		for (int i = 0; i < 6; i++)
		{
			bfs[i].Search(test[i]);
		}
	}
	else
	{
		const char* filename[] = { argv[1],argv[2] };
		BFS bfs;
		bfs.Search(filename);
	}
	
}
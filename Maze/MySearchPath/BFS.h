#ifndef BFS_H
#define BFS_H

#include <queue>
#include "Pos.h"
#include <map>
#include <vector>

using namespace std;

#define STARTXY 1
#define ROAD 0
#define VISITED 500
#define SHORTEST 1000

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

#endif // !BFS_H

#include <iostream>
#include <queue>
#include <map>
#include "BFS.h"
#include "Pos.h"

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
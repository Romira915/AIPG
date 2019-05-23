#include <stdlib.h>
#include <stdio.h>


#define LEN 256

int maze[LEN][LEN];

void readMaze(char* filename, int *w, int *h, int maze[LEN][LEN]) {
	FILE *fp;
	int x, y;
	if (0 != fopen_s(&fp, filename, "r")) {
		fprintf(stderr, "指定された迷路の入力ファイルを開くことができませんでした．\n");
		exit(-1);
	}

	fscanf_s(fp, "%d,%d\n", w, h);
	for (y = 0; y < 2 * *h + 1; y++) {
		for (x = 0; x < 2 * *w + 1; x++) {
			fscanf_s(fp, "%d%*[^-0-9]", &(maze[y][x]));
		}
	}
	fclose(fp);
}

void writeMaze(char* filename, int w, int h, int maze[LEN][LEN]) {
	FILE *fp;
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
}

int main(int argc, char** argv) {
	int i;
	const char *(test[])[3] = {
		{ "dummy", "maze8060A.csv", "maze8060A-out.csv" },
		{ "dummy", "maze8060B.csv", "maze8060B-out.csv" },
		{ "dummy", "maze8060C.csv", "maze8060C-out.csv" },
		{ "dummy", "maze8060D.csv", "maze8060D-out.csv" },
		{ "dummy", "maze8060E.csv", "maze8060E-out.csv" },
		{ "dummy", "maze8060F.csv", "maze8060F-out.csv" },
	};

	if (argc == 1) {
		for (i = 0; i < 6; i++) {
			printf("%sの迷路をテスト\n", test[i][1]);
			if (main0(3, test[i]) == 0) {
				printf("ゴールまでの経路が見つかりました．しかし，ゴミはあるかもしれません．\n\n");
			} else {
				printf("ゴールまでの経路が見つかりませんでした．\n\n");
			}
		}
		printf("HIT ENTER KEY");
		while (getchar() != '\n');
		return 0;
	} else {
		return main0(argc, argv);
	}
}
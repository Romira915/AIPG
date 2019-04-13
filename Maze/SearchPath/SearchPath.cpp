#include <stdlib.h>
#include <stdio.h>

#include "List.h"

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

// シンプルなバージョン：なるべく右下へ行けるなら右下へ
int main0(int argc, char** argv) {
	int w, h;
	int x, y;

	if (argc < 3) {
		fprintf(stderr, "迷路の入出力ファイル名を指定してください．\n");
		exit(-1);
	}

	// 迷路読込
	readMaze(argv[1], &w, &h, maze);

	// maze[1][1] から maze[2*h-1][2*w-1] までのルートを探す
	x = 1;	//座標の初期化
	y = 1;

	while (x != 2 * w - 1 || y != 2 * h - 1){
		if (maze[y][x + 1] == 0) {		// 右にまだ行ってない？
			maze[y][x] = 1000;
			x = x + 1;
		}
		else if (maze[y + 1][x] == 0) {	// 下にまだ行ってない？
			maze[y][x] = 1000;
			y = y + 1;
		}
		else if (maze[y][x - 1] == 0) {	// 左にまだ行ってない？
			maze[y][x] = 1000;
			x = x - 1;
		}
		else if (maze[y - 1][x] == 0) {	// 上にまだ行ってない？
			maze[y][x] = 1000;
			y = y - 1;
		}
		else if (maze[y][x + 1] == 1000) { // 行き止まりなので右に引き返す
			maze[y][x] = 1;
			x = x + 1;
		}
		else if (maze[y + 1][x] == 1000) { // 行き止まりなので下に引き返す
			maze[y][x] = 1;
			y = y + 1;
		}
		else if (maze[y][x - 1] == 1000) { // 行き止まりなので左に引き返す
			maze[y][x] = 1;
			x = x - 1;
		}
		else if (maze[y - 1][x] == 1000) { // 行き止まりなので上に引き返す
			maze[y][x] = 1;
			y = y - 1;
		}
		else { // ここまできた時点でバグなので，迷路を書き出して終了
			writeMaze(argv[2], w, h, maze);
			return -1;
		}
	}
	maze[2 * h - 1][2 * w - 1] = 1000; // ゴール

	// 答えを濃い色に
	// 上記のプログラムはすでに答えを濃い色(1000)にしている

	// 迷路書出
	writeMaze(argv[2], w, h, maze);
	return 0;
}

int main(int argc, char** argv) {
	int i;
	char *(test[])[3] = {
		{ "dummy", "maze8060A.csv", "maze8060A-out.csv" },
		{ "dummy", "maze8060B.csv", "maze8060B-out.csv" },
		{ "dummy", "maze8060C.csv", "maze8060C-out.csv" },
		{ "dummy", "maze8060D.csv", "maze8060D-out.csv" },
		{ "dummy", "maze8060E.csv", "maze8060E-out.csv" },
		{ "dummy", "maze8060F.csv", "maze8060F-out.csv" },
	}; // test is array[] of array[3] of pointer of char

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
#include <stdlib.h>
#include <stdio.h>

#include "List.h"

#define LEN 256

int maze[LEN][LEN];

void readMaze(char* filename, int *w, int *h, int maze[LEN][LEN]) {
	FILE *fp;
	int x, y;
	if (0 != fopen_s(&fp, filename, "r")) {
		fprintf(stderr, "�w�肳�ꂽ���H�̓��̓t�@�C�����J�����Ƃ��ł��܂���ł����D\n");
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
		fprintf(stderr, "�w�肳�ꂽ���H�̏o�̓t�@�C�����J�����Ƃ��ł��܂���ł����D\n");
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

// �V���v���ȃo�[�W�����F�Ȃ�ׂ��E���֍s����Ȃ�E����
int main0(int argc, char** argv) {
	int w, h;
	int x, y;

	if (argc < 3) {
		fprintf(stderr, "���H�̓��o�̓t�@�C�������w�肵�Ă��������D\n");
		exit(-1);
	}

	// ���H�Ǎ�
	readMaze(argv[1], &w, &h, maze);

	// maze[1][1] ���� maze[2*h-1][2*w-1] �܂ł̃��[�g��T��
	x = 1;	//���W�̏�����
	y = 1;

	while (x != 2 * w - 1 || y != 2 * h - 1){
		if (maze[y][x + 1] == 0) {		// �E�ɂ܂��s���ĂȂ��H
			maze[y][x] = 1000;
			x = x + 1;
		}
		else if (maze[y + 1][x] == 0) {	// ���ɂ܂��s���ĂȂ��H
			maze[y][x] = 1000;
			y = y + 1;
		}
		else if (maze[y][x - 1] == 0) {	// ���ɂ܂��s���ĂȂ��H
			maze[y][x] = 1000;
			x = x - 1;
		}
		else if (maze[y - 1][x] == 0) {	// ��ɂ܂��s���ĂȂ��H
			maze[y][x] = 1000;
			y = y - 1;
		}
		else if (maze[y][x + 1] == 1000) { // �s���~�܂�Ȃ̂ŉE�Ɉ����Ԃ�
			maze[y][x] = 1;
			x = x + 1;
		}
		else if (maze[y + 1][x] == 1000) { // �s���~�܂�Ȃ̂ŉ��Ɉ����Ԃ�
			maze[y][x] = 1;
			y = y + 1;
		}
		else if (maze[y][x - 1] == 1000) { // �s���~�܂�Ȃ̂ō��Ɉ����Ԃ�
			maze[y][x] = 1;
			x = x - 1;
		}
		else if (maze[y - 1][x] == 1000) { // �s���~�܂�Ȃ̂ŏ�Ɉ����Ԃ�
			maze[y][x] = 1;
			y = y - 1;
		}
		else { // �����܂ł������_�Ńo�O�Ȃ̂ŁC���H�������o���ďI��
			writeMaze(argv[2], w, h, maze);
			return -1;
		}
	}
	maze[2 * h - 1][2 * w - 1] = 1000; // �S�[��

	// ������Z���F��
	// ��L�̃v���O�����͂��łɓ�����Z���F(1000)�ɂ��Ă���

	// ���H���o
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
			printf("%s�̖��H���e�X�g\n", test[i][1]);
			if (main0(3, test[i]) == 0) {
				printf("�S�[���܂ł̌o�H��������܂����D�������C�S�~�͂��邩������܂���D\n\n");
			} else {
				printf("�S�[���܂ł̌o�H��������܂���ł����D\n\n");
			}
		}
		printf("HIT ENTER KEY");
		while (getchar() != '\n');
		return 0;
	} else {
		return main0(argc, argv);
	}
}
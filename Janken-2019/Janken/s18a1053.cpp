#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"

//勝負する
Te syoubu(int g, int c, int p) {
	if (g > c && g > p) return Pa;
	else if (c > g && c > p) return Gu;
	else if (p > c && p > g) return Choki;
	else if (g == c && g == p) return (Te)(rand() % 3);
	else if (g == c) return (rand() % 2) ? Pa : Gu;
	else if (g == p) return (rand() % 2) ? Pa : Choki;
	else if (p == c) return (rand() % 2) ? Choki : Gu;
	else return (Te)(rand() % 3);
}

//五次元マルコフ戦略
Te markov2(int previous_rival_hand, int previous_rival_win_or_lose, int previous2_rival_hand, int previous2_rival_win_or_lose, int SearchData2[375][3][3][3][3]) {
	//num[二つ前の相手の手(Gu,Choki,Pa)][その時の相手の勝敗(draw,win,lose)][ひとつ前の相手の手(Gu,Choki,Pa)]
	int num[3][3][3][3][3] = {};
	//２７通りの状態ががあった分だけそれぞれ加算
	for (int i = 0; i < 375; i++) {
		for (int j = 0; j < 3; j++) {
			for (int l = 0; l < 3; l++) {
				for (int n = 0; n < 3; n++) {
					for (int k = 0; k < 3; k++) {
						for (int z = 0; z < 3; z++) {
							if (SearchData2[i][j][l][n][k] == z) { //l = {Gu, Choki, Pa}
								num[j][l][n][k][z]++;
							}
						}
					}
				}
			}
		}
	}
	//ひとつ前のライバルの手とその時のライバルの勝敗を見る。
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int l = 0; l < 3; l++) {
				for (int n = 0; n < 3; n++) {
					if (previous_rival_hand == i && previous_rival_win_or_lose == j && previous2_rival_hand == l && previous2_rival_win_or_lose == n) {
						//勝負に出る。
						return syoubu(num[i][j][l][n][0], num[i][j][l][n][1], num[i][j][l][n][2]);
					}
				}
			}
		}
	}
	return (Te)(rand() % 3);
}

//Dataの作成 SearchData2[二つ前の相手の手][二つ前の相手の勝敗][三つ前の相手の手][三つ前の相手の勝敗][対戦番号i]
void WriteTheData2(int battle_number, Te myhistory[], Te rivalhistory[], int SearchData[375][3][3][3][3]) {
	for (int i = 2; i <= battle_number; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				for (int l = 0; l < 3; l++) {
					for (int n = 0; n < 3; n++) {
						if ((rivalhistory[i - 2] == j) && (((myhistory[i - 2] - rivalhistory[i - 2]) + 3) % 3) == k && (rivalhistory[i - 3] == l) && (((myhistory[i - 3] - rivalhistory[i - 3]) + 3) % 3) == n) { //j = { Gu, Choki, Pa } k = { Draw, Win, Lose }
							SearchData[i - 2][j][k][l][n] = rivalhistory[i - 1];
						}
					}
				}
			}
		}
	}
}

//Search_Data2の初期化
void init_Search_Data2(int SearchData2[375][3][3][3][3]) {
	for (int i = 0; i < 375; i++) {
		for (int j = 0; j < 3; j++) {
			for (int l = 0; l < 3; l++) {
				for (int n = 0; n < 3; n++) {
					for (int k = 0; k < 3; k++) {
						SearchData2[i][j][l][n][k] = -1;
					}
				}
			}

		}
	}
}

//counterの初期化
void init_counter(int* counter) {
	*counter = 0;
}

// Te は Gu=0, Choki=1, Pa=2 という値を持つ enum 型
// 第一引数 i は１試合の中で現在何回目を示す．0からMAXKAISU-1までの値．
// 第二引数 myhistory は自分の手の履歴を示す．添字は0からMAXKAISU-1まで使えるが，0からi-1までの履歴しか信用出来ない．
// 第三引数 rivalhistory は相手の手の履歴を示す．添字は0からMAXKAISU-1まで使えるが，0からi-1までの履歴しか信用出来ない．
Te s18a1053(int i, Te myhistory[], Te rivalhistory[]) {
	static int counter = 0; //カウンター：0 ~ 354まで数える

	static int SearchData2[375][3][3][3][3]; //SearchData[二つ前の相手の手][二つ前の相手の勝敗][三つ前の相手の手][三つ前の相手の勝敗][対戦番号i]

	//ひとつ前
	int previous_my_hand = myhistory[i - 1]; //ひとつ前の自分の手：0 = Gu, 1 = Choki, 2 = Pa.
	int previous_rival_hand = rivalhistory[i - 1]; //ひとつ前の相手の手：0 = Gu, 1 = Choki, 2 = Pa.
	int previous_rival_win_or_lose = ((previous_my_hand - previous_rival_hand) + 3) % 3; //ひとつ前の相手にとっての勝敗：0 = draw, 1 = win, 2 = lose.
	//二つ前
	int previous2_my_hand = myhistory[i - 2]; //二つ前の自分の手：0 = Gu, 1 = Choki, 2 = Pa.
	int previous2_rival_hand = rivalhistory[i - 2]; //二つ前の相手の手：0 = Gu, 1 = Choki, 2 = Pa.
	int previous2_rival_win_or_lose = ((previous2_my_hand - previous2_rival_hand) + 3) % 3; //二つ前の相手にとっての勝敗：0 = draw, 1 = win, 2 = lose.

	if (!(counter % 75) && !(counter == 0)) {
		//ひとつ前
		previous_my_hand = myhistory[72];
		previous_rival_hand = rivalhistory[72];
		previous_rival_win_or_lose = ((previous_my_hand - previous_rival_hand) + 3) % 3;

		//二つ前
		previous2_my_hand = myhistory[71];
		previous2_rival_hand = rivalhistory[71];
		previous2_rival_win_or_lose = ((previous2_my_hand - previous2_rival_hand) + 3) % 3;
	}
	if (counter == 76 || counter == 151 || counter == 226 || counter == 301 || counter == 376) {
		//ひとつ前
		previous_my_hand = myhistory[73];
		previous_rival_hand = rivalhistory[73];
		previous_rival_win_or_lose = ((previous_my_hand - previous_rival_hand) + 3) % 3;

		//二つ前
		previous2_my_hand = myhistory[72];
		previous2_rival_hand = rivalhistory[72];
		previous2_rival_win_or_lose = ((previous2_my_hand - previous2_rival_hand) + 3) % 3;
	}
	if (counter == 375) {
		init_counter(&counter);
	}
	if (counter == 0) {
		//init_Search_Data(SearchData);
		init_Search_Data2(SearchData2);
	}

	WriteTheData2(i, myhistory, rivalhistory, SearchData2);

	++counter;

	return markov2(previous_rival_hand, previous_rival_win_or_lose, previous2_rival_hand, previous2_rival_win_or_lose, SearchData2);
}
//参考資料：https://www.jstage.jst.go.jp/article/jacc/54/0/54_0_145/_pdf
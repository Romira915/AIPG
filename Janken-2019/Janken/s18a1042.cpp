//TODO このソースコードを参考に，自分の学籍番号.cppというファイルを作り，改造する．
#include "stdafx.h"
#include "cstdlib"
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <random>
#include <direct.h>

extern int MAXKAISU;
extern int NUMMATCH;

class Combination_Data
{
public:
	Combination_Data();
	~Combination_Data();

	void Update();
	void Set_data(int, Te*, Te*);
	void Save_data();

	Te Next_probability();
	Te Next_markov();
	Te Next_mymarkov();
	Te Next_markov2();
	Te Next_markov3();
	Te Next_markov3_5();
	Te Next_markov4();
	Te Judg_markov();

	double WinRate(int);
	double LossRate(int);

	bool FirstBattle();
	bool IsOnlyCpu();
	bool IsWin4Pre();

	Te MyLatestHand();
	Te RivalLatestHand();
	Te Win(Te);
	Te Lose(Te);
	int Get_win();
	int Get_lose();
	// 引き分け:0 負け:1 勝ち:2
	int WinorLose(Te, Te);
	Te rnd();
	int Get_count();

	void debug();

	bool IsWin4PreFlag;

private:
	int Add_data();
	void Init_data();
	int winning_counter();
	int Losing_counter();
	int markov_counter();

	const int MAXKAISU_intern;
	const int NUMMATCH_intern;

	int t;
	Te* myhistory;
	Te* rivalhistory;

	//相手の前々回と前回の手の組み合わせ
	int rivalcomb_history[3][3];
	//自分の前々回と相手の前回の手の組み合わせ
	int mycomb_history[3][3];
	// マルコフ戦略用データ [前の状態][勝敗][次の状態]
	int markov_history[3][3][3];
	int markov_myhistory[3][3][3];
	int markov_history2[3][3][3][3][3];
	int markov_history3[3][3][3][3][3][3][3];
	int markov_history3_5[3][3][3][3][3][3][3][3];
	int markov_history4[3][3][3][3][3][3][3][3][3];

	int* allmyhistory;
	int* allrivalhistory;

	int won_count;
	int losed_count;
	int markov_accuracy;
	int mymarkov_accuracy;
	int markov_accuracy2;
	int markov_accuracy3;
	int markov_accuracy4;
	Te markov_prediction;
	Te mymarkov_prediction;
	Te markov_prediction2;
	Te markov_prediction3;
	Te markov_prediction4;

	int count;

	int savecount;
	std::ofstream logf;
	std::ofstream logf2;
	std::string filename;
	std::string filename2;
	const std::string testr[3] = { "Gu","Choki","Pa" };
	const std::string winlose[3] = { "引き分け","勝ち","負け" };

	std::random_device r;
	std::uniform_int_distribution<> rand3;
};

Combination_Data::Combination_Data() : rand3(0, 2), MAXKAISU_intern(MAXKAISU), NUMMATCH_intern(NUMMATCH), markov_prediction(Te(0)), mymarkov_prediction(Te(0))
{
	count = -1;
	savecount = 0;

	allmyhistory = new int[MAXKAISU_intern * NUMMATCH_intern];
	allrivalhistory = new int[MAXKAISU_intern * NUMMATCH_intern];

	filename = "log\\log.csv";
	filename2 = "log\\log2.csv";
	_mkdir("log");
	logf.open(filename);
	logf2.open(filename2);
	if (!logf)
	{
		std::cout << "Can't open " << '"' << filename << '"' << '\n';
		std::exit(-1);
	}
	if (!logf2)
	{
		std::cout << "Can't open " << '"' << filename2 << '"' << '\n';
		std::exit(-1);
	}

	Init_data();
}

Combination_Data::~Combination_Data()
{
	logf.close();
	logf2.close();

	delete[] allmyhistory;
	delete[]  allrivalhistory;
}

// 各種データを更新　呼び出し時に必ず1回実行
void Combination_Data::Update()
{
	Init_data();
	Add_data();
	winning_counter();
	Losing_counter();
	markov_counter();
}

// データをクラスに与える
void Combination_Data::Set_data(int u, Te* my, Te* rival)
{
	t = u;
	myhistory = my;
	rivalhistory = rival;
}

// アルゴリズムのログをlogディレクトリに出力
void Combination_Data::Save_data()
{
	if (count == MAXKAISU_intern * NUMMATCH_intern - 1)
	{
		if (savecount > 146)
		{
			logf << savecount - 146 << "戦目\n";
			std::cout << "↑ " << savecount - 146 << "戦目\n";
			for (int i = 0; i < 3; i++)
			{
				logf << testr[i] << "\n,";
				for (int m = 0; m < 3; m++)
				{
					logf << testr[m] << ',';
				}
				logf << '\n';
				for (int j = 0; j < 3; j++)
				{
					logf << winlose[j] << ',';
					for (int k = 0; k < 3; k++)
					{
						logf << markov_history[i][j][k] << ",";
					}
					logf << '\n';
				}
				logf << "\n";
			}
			logf << '\n';


			logf2 << savecount - 146 << "戦目\n";
			logf2 << "now-3,勝敗,now-2,勝敗,now-1,勝敗,now,count" << '\n';
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					for (int k = 0; k < 3; k++)
					{
						for (int l = 0; l < 3; l++)
						{
							for (int m = 0; m < 3; m++)
							{
								for (int n = 0; n < 3; n++)
								{
									for (int o = 0; o < 3; o++)
									{
										if (markov_history3[i][j][k][l][m][n][o] > 0)
										{
											logf2 << testr[i] << ','
												<< winlose[j] << ','
												<< testr[k] << ','
												<< winlose[l] << ','
												<< testr[m] << ','
												<< winlose[n] << ','
												<< testr[o] << ','
												<< markov_history3[i][j][k][l][m][n][o]
												<< '\n';
										}
									}
								}
							}
						}
					}
				}
			}
		}
		savecount++;
	}

}

// 簡単な予測アルゴリズム 戻り値 相手の次の手の予測
Te Combination_Data::Next_probability()
{
	int max = 0;
	Te prob;
	for (int i = 0; i < 3; i++)
	{
		if (mycomb_history[myhistory[t - 1]][i] >= max) {
			max = mycomb_history[myhistory[t - 1]][i];
			prob = Te(i);
		}
	}
	return prob;
}

// マルコフ戦略による予測アルゴリズム 戻り値 相手の次の手の予測
Te Combination_Data::Next_markov()
{
	int max = -1;
	Te next;
	int subscript[2];

	for (int i = count - 1, j = 0; i >= 0 && j < 2; i--)
	{
		if (allrivalhistory[i] != -1 && allmyhistory[i] != -1)
		{
			subscript[j] = WinorLose(Te(allmyhistory[i]), Te(allrivalhistory[i]));
			subscript[j + 1] = allrivalhistory[i];
			j += 2;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (count >= 1)
		{
			if (markov_history[subscript[1]][subscript[0]][i] >= max)
			{
				max = markov_history[subscript[1]][subscript[0]][i];
				next = Te(i);
			}

			/*if (markov_history3[allrivalhistory[count - 3]][WinorLose(Te(allmyhistory[count - 3]), Te(allrivalhistory[count - 3]))][allrivalhistory[count - 2]][WinorLose(Te(allmyhistory[count - 2]), Te(allrivalhistory[count - 2]))][allrivalhistory[count - 1]][WinorLose(Te(allmyhistory[count - 1]), Te(allrivalhistory[count - 1]))][i] >= max)
			{
				max = markov_history3[allrivalhistory[count - 3]][WinorLose(Te(allmyhistory[count - 3]), Te(allrivalhistory[count - 3]))][allrivalhistory[count - 2]][WinorLose(Te(allmyhistory[count - 2]), Te(allrivalhistory[count - 2]))][allrivalhistory[count - 1]][WinorLose(Te(allmyhistory[count - 1]), Te(allrivalhistory[count - 1]))][i];
				next = Te(i);
			}*/
		}
		else
		{
			next = rnd();
		}
		/*else if (markov_history3[rivalhistory[t - 3]][WinorLose(Te(myhistory[t - 3]), Te(rivalhistory[t - 3]))][rivalhistory[t - 2]][WinorLose(Te(myhistory[t - 2]), Te(rivalhistory[t - 2]))][rivalhistory[t - 1]][WinorLose(Te(myhistory[t - 1]), Te(rivalhistory[t - 1]))][i] >= max)
		{
			max = markov_history3[rivalhistory[t - 3]][WinorLose(Te(myhistory[t - 3]), Te(rivalhistory[t - 3]))][rivalhistory[t - 2]][WinorLose(Te(myhistory[t - 2]), Te(rivalhistory[t - 2]))][rivalhistory[t - 1]][WinorLose(Te(myhistory[t - 1]), Te(rivalhistory[t - 1]))][i];
			next = Te(i);
		}*/
	}
	return next;
}

// マルコフ戦略を自分に対して予測 自分の次の手の予測
Te Combination_Data::Next_mymarkov()
{
	int max = -1;
	Te next;
	int subscript[2];

	for (int i = count - 1, j = 0; i >= 0 && j < 2; i--)
	{
		if (allrivalhistory[i] != -1 && allmyhistory[i] != -1)
		{
			subscript[j] = WinorLose(Te(allmyhistory[i]), Te(allrivalhistory[i]));
			subscript[j + 1] = allrivalhistory[i];
			j += 2;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (count >= 2)
		{
			if (markov_myhistory[subscript[1]][subscript[0]][i] >= max)
			{
				max = markov_myhistory[subscript[1]][subscript[0]][i];
				next = Te(i);
			}

			/*if (markov_history3[allrivalhistory[count - 3]][WinorLose(Te(allmyhistory[count - 3]), Te(allrivalhistory[count - 3]))][allrivalhistory[count - 2]][WinorLose(Te(allmyhistory[count - 2]), Te(allrivalhistory[count - 2]))][allrivalhistory[count - 1]][WinorLose(Te(allmyhistory[count - 1]), Te(allrivalhistory[count - 1]))][i] >= max)
			{
				max = markov_history3[allrivalhistory[count - 3]][WinorLose(Te(allmyhistory[count - 3]), Te(allrivalhistory[count - 3]))][allrivalhistory[count - 2]][WinorLose(Te(allmyhistory[count - 2]), Te(allrivalhistory[count - 2]))][allrivalhistory[count - 1]][WinorLose(Te(allmyhistory[count - 1]), Te(allrivalhistory[count - 1]))][i];
				next = Te(i);
			}*/
		}
		else
		{
			next = rnd();
		}
		/*else if (markov_history3[rivalhistory[t - 3]][WinorLose(Te(myhistory[t - 3]), Te(rivalhistory[t - 3]))][rivalhistory[t - 2]][WinorLose(Te(myhistory[t - 2]), Te(rivalhistory[t - 2]))][rivalhistory[t - 1]][WinorLose(Te(myhistory[t - 1]), Te(rivalhistory[t - 1]))][i] >= max)
		{
			max = markov_history3[rivalhistory[t - 3]][WinorLose(Te(myhistory[t - 3]), Te(rivalhistory[t - 3]))][rivalhistory[t - 2]][WinorLose(Te(myhistory[t - 2]), Te(rivalhistory[t - 2]))][rivalhistory[t - 1]][WinorLose(Te(myhistory[t - 1]), Te(rivalhistory[t - 1]))][i];
			next = Te(i);
		}*/
	}
	return next;
}

Te Combination_Data::Next_markov2()
{
	int max = -1;
	Te next;
	int subscript[4];

	for (int i = count - 1, j = 0; i >= 0 && j < 4; i--)
	{
		if (allrivalhistory[i] != -1 && allmyhistory[i] != -1)
		{
			subscript[j] = WinorLose(Te(allmyhistory[i]), Te(allrivalhistory[i]));
			subscript[j + 1] = allrivalhistory[i];
			j += 2;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (count >= 2)
		{
			if (markov_history2[subscript[3]][subscript[2]][subscript[1]][subscript[0]][i] >= max)
			{
				max = markov_history2[subscript[3]][subscript[2]][subscript[1]][subscript[0]][i];
				next = Te(i);
			}

			/*if (markov_history3[allrivalhistory[count - 3]][WinorLose(Te(allmyhistory[count - 3]), Te(allrivalhistory[count - 3]))][allrivalhistory[count - 2]][WinorLose(Te(allmyhistory[count - 2]), Te(allrivalhistory[count - 2]))][allrivalhistory[count - 1]][WinorLose(Te(allmyhistory[count - 1]), Te(allrivalhistory[count - 1]))][i] >= max)
			{
				max = markov_history3[allrivalhistory[count - 3]][WinorLose(Te(allmyhistory[count - 3]), Te(allrivalhistory[count - 3]))][allrivalhistory[count - 2]][WinorLose(Te(allmyhistory[count - 2]), Te(allrivalhistory[count - 2]))][allrivalhistory[count - 1]][WinorLose(Te(allmyhistory[count - 1]), Te(allrivalhistory[count - 1]))][i];
				next = Te(i);
			}*/
		}
		else
		{
			next = rnd();
		}
		/*else if (markov_history3[rivalhistory[t - 3]][WinorLose(Te(myhistory[t - 3]), Te(rivalhistory[t - 3]))][rivalhistory[t - 2]][WinorLose(Te(myhistory[t - 2]), Te(rivalhistory[t - 2]))][rivalhistory[t - 1]][WinorLose(Te(myhistory[t - 1]), Te(rivalhistory[t - 1]))][i] >= max)
		{
			max = markov_history3[rivalhistory[t - 3]][WinorLose(Te(myhistory[t - 3]), Te(rivalhistory[t - 3]))][rivalhistory[t - 2]][WinorLose(Te(myhistory[t - 2]), Te(rivalhistory[t - 2]))][rivalhistory[t - 1]][WinorLose(Te(myhistory[t - 1]), Te(rivalhistory[t - 1]))][i];
			next = Te(i);
		}*/
	}
	return next;
}

Te Combination_Data::Next_markov3()
{
	int max = -1;
	Te next;
	int subscript[6];

	for (int i = count - 1, j = 0; i >= 0 && j < 6; i--)
	{
		if (allrivalhistory[i] != -1 && allmyhistory[i] != -1)
		{
			subscript[j] = WinorLose(Te(allmyhistory[i]), Te(allrivalhistory[i]));
			subscript[j + 1] = allrivalhistory[i];
			j += 2;
		}
	}


	for (int i = 0; i < 3; i++)
	{
		if (count >= 3)
		{
			if (markov_history3[subscript[5]][subscript[4]][subscript[3]][subscript[2]][subscript[1]][subscript[0]][i] >= max)
			{
				max = markov_history3[subscript[5]][subscript[4]][subscript[3]][subscript[2]][subscript[1]][subscript[0]][i];
				next = Te(i);
			}

			/*if (markov_history3[allrivalhistory[count - 3]][WinorLose(Te(allmyhistory[count - 3]), Te(allrivalhistory[count - 3]))][allrivalhistory[count - 2]][WinorLose(Te(allmyhistory[count - 2]), Te(allrivalhistory[count - 2]))][allrivalhistory[count - 1]][WinorLose(Te(allmyhistory[count - 1]), Te(allrivalhistory[count - 1]))][i] >= max)
			{
				max = markov_history3[allrivalhistory[count - 3]][WinorLose(Te(allmyhistory[count - 3]), Te(allrivalhistory[count - 3]))][allrivalhistory[count - 2]][WinorLose(Te(allmyhistory[count - 2]), Te(allrivalhistory[count - 2]))][allrivalhistory[count - 1]][WinorLose(Te(allmyhistory[count - 1]), Te(allrivalhistory[count - 1]))][i];
				next = Te(i);
			}*/
		}
		else
		{
			next = rnd();
		}
		/*else if (markov_history3[rivalhistory[t - 3]][WinorLose(Te(myhistory[t - 3]), Te(rivalhistory[t - 3]))][rivalhistory[t - 2]][WinorLose(Te(myhistory[t - 2]), Te(rivalhistory[t - 2]))][rivalhistory[t - 1]][WinorLose(Te(myhistory[t - 1]), Te(rivalhistory[t - 1]))][i] >= max)
		{
			max = markov_history3[rivalhistory[t - 3]][WinorLose(Te(myhistory[t - 3]), Te(rivalhistory[t - 3]))][rivalhistory[t - 2]][WinorLose(Te(myhistory[t - 2]), Te(rivalhistory[t - 2]))][rivalhistory[t - 1]][WinorLose(Te(myhistory[t - 1]), Te(rivalhistory[t - 1]))][i];
			next = Te(i);
		}*/
	}
	return next;
}

Te Combination_Data::Next_markov3_5()
{
	int max = -1;
	Te next;
	int subscript[7];

	for (int i = count - 1, j = 0; i >= 0 && j < 7; i--)
	{
		if (allrivalhistory[i] != -1 && allmyhistory[i] != -1)
		{
			subscript[j] = WinorLose(Te(allmyhistory[i]), Te(allrivalhistory[i]));
			if (j + 1 < 7)
			{
				subscript[j + 1] = allrivalhistory[i];
			}
			j += 2;
		}
	}


	for (int i = 0; i < 3; i++)
	{
		if (count >= 4)
		{
			if (markov_history3_5[subscript[6]][subscript[5]][subscript[4]][subscript[3]][subscript[2]][subscript[1]][subscript[0]][i] >= max)
			{
				max = markov_history3_5[subscript[6]][subscript[5]][subscript[4]][subscript[3]][subscript[2]][subscript[1]][subscript[0]][i];
				next = Te(i);
			}

			/*if (markov_history3[allrivalhistory[count - 3]][WinorLose(Te(allmyhistory[count - 3]), Te(allrivalhistory[count - 3]))][allrivalhistory[count - 2]][WinorLose(Te(allmyhistory[count - 2]), Te(allrivalhistory[count - 2]))][allrivalhistory[count - 1]][WinorLose(Te(allmyhistory[count - 1]), Te(allrivalhistory[count - 1]))][i] >= max)
			{
				max = markov_history3[allrivalhistory[count - 3]][WinorLose(Te(allmyhistory[count - 3]), Te(allrivalhistory[count - 3]))][allrivalhistory[count - 2]][WinorLose(Te(allmyhistory[count - 2]), Te(allrivalhistory[count - 2]))][allrivalhistory[count - 1]][WinorLose(Te(allmyhistory[count - 1]), Te(allrivalhistory[count - 1]))][i];
				next = Te(i);
			}*/
		}
		else
		{
			next = rnd();
		}
		/*else if (markov_history3[rivalhistory[t - 3]][WinorLose(Te(myhistory[t - 3]), Te(rivalhistory[t - 3]))][rivalhistory[t - 2]][WinorLose(Te(myhistory[t - 2]), Te(rivalhistory[t - 2]))][rivalhistory[t - 1]][WinorLose(Te(myhistory[t - 1]), Te(rivalhistory[t - 1]))][i] >= max)
		{
			max = markov_history3[rivalhistory[t - 3]][WinorLose(Te(myhistory[t - 3]), Te(rivalhistory[t - 3]))][rivalhistory[t - 2]][WinorLose(Te(myhistory[t - 2]), Te(rivalhistory[t - 2]))][rivalhistory[t - 1]][WinorLose(Te(myhistory[t - 1]), Te(rivalhistory[t - 1]))][i];
			next = Te(i);
		}*/
	}
	return next;
}

Te Combination_Data::Next_markov4()
{
	int max = -1;
	Te next;
	int subscript[8];

	for (int i = count - 1, j = 0; i >= 0 && j < 8; i--)
	{
		if (allrivalhistory[i] != -1 && allmyhistory[i] != -1)
		{
			subscript[j] = WinorLose(Te(allmyhistory[i]), Te(allrivalhistory[i]));
			subscript[j + 1] = allrivalhistory[i];
			j += 2;
		}
	}


	for (int i = 0; i < 3; i++)
	{
		if (count >= 4)
		{
			if (markov_history4[subscript[7]][subscript[6]][subscript[5]][subscript[4]][subscript[3]][subscript[2]][subscript[1]][subscript[0]][i] >= max)
			{
				max = markov_history4[subscript[7]][subscript[6]][subscript[5]][subscript[4]][subscript[3]][subscript[2]][subscript[1]][subscript[0]][i];
				next = Te(i);
			}

			/*if (markov_history3[allrivalhistory[count - 3]][WinorLose(Te(allmyhistory[count - 3]), Te(allrivalhistory[count - 3]))][allrivalhistory[count - 2]][WinorLose(Te(allmyhistory[count - 2]), Te(allrivalhistory[count - 2]))][allrivalhistory[count - 1]][WinorLose(Te(allmyhistory[count - 1]), Te(allrivalhistory[count - 1]))][i] >= max)
			{
				max = markov_history3[allrivalhistory[count - 3]][WinorLose(Te(allmyhistory[count - 3]), Te(allrivalhistory[count - 3]))][allrivalhistory[count - 2]][WinorLose(Te(allmyhistory[count - 2]), Te(allrivalhistory[count - 2]))][allrivalhistory[count - 1]][WinorLose(Te(allmyhistory[count - 1]), Te(allrivalhistory[count - 1]))][i];
				next = Te(i);
			}*/
		}
		else
		{
			next = rnd();
		}
		/*else if (markov_history3[rivalhistory[t - 3]][WinorLose(Te(myhistory[t - 3]), Te(rivalhistory[t - 3]))][rivalhistory[t - 2]][WinorLose(Te(myhistory[t - 2]), Te(rivalhistory[t - 2]))][rivalhistory[t - 1]][WinorLose(Te(myhistory[t - 1]), Te(rivalhistory[t - 1]))][i] >= max)
		{
			max = markov_history3[rivalhistory[t - 3]][WinorLose(Te(myhistory[t - 3]), Te(rivalhistory[t - 3]))][rivalhistory[t - 2]][WinorLose(Te(myhistory[t - 2]), Te(rivalhistory[t - 2]))][rivalhistory[t - 1]][WinorLose(Te(myhistory[t - 1]), Te(rivalhistory[t - 1]))][i];
			next = Te(i);
		}*/
	}
	return next;
}

// markovによる精度を比較し高いアルゴリズムを利用する
// 戻り値 相手の次の手の予測に勝てる手
Te Combination_Data::Judg_markov()
{
	int accuracy[] = {
		markov_accuracy,
		mymarkov_accuracy,
		markov_accuracy2,
		markov_accuracy3,
		markov_accuracy4
	};
	Te(Combination_Data:: * markov_func[])() = {
		&Combination_Data::Next_markov,
		&Combination_Data::Next_mymarkov,
		&Combination_Data::Next_markov2,
		&Combination_Data::Next_markov3,
		&Combination_Data::Next_markov4
	};
	int max[] = { -1,0 };

	for (int i = 0; i < sizeof(accuracy) / sizeof(accuracy[0]); i++)
	{
		if (accuracy[i] >= max[0])
		{
			max[0] = accuracy[i];
			max[1] = i;
		}
	}

	if (max[1] != 1)
	{
		return Win((this->*markov_func[max[1]])());
	}
	else
	{
		return Lose((this->*markov_func[max[1]])());
	}
}

// 戻り値 現在の勝率 引数：計測開始ターン
double Combination_Data::WinRate(int start)
{
	if (count >= start)
	{
		return (double)won_count / (count + 1);
	}
	return 1;
}

// 戻り値 現在の敗率 引数：計測開始ターン
double Combination_Data::LossRate(int start)
{
	if (count >= start)
	{
		return (double)losed_count / (count + 1);
	}
	return 0;
}

// 戻り値 0戦目0回目ならtrue
bool Combination_Data::FirstBattle()
{
	return count == 0;
}

// 戻り値 OnlyCpuと判定した場合true
bool Combination_Data::IsOnlyCpu()
{
	if (count >= 2)
	{
		for (int i = 1; i < count; i++)
		{
			if (allrivalhistory[i] != -1 && allrivalhistory[i - 1] != -1)
			{
				if (allrivalhistory[i] != allrivalhistory[i - 1]) {
					return false;
				}
			}
		}
	}
	return true;
}

// 戻り値 Win4Preと判定した場合true
bool Combination_Data::IsWin4Pre()
{
	if (count >= 2 && t >= 2)
	{
		for (int i = 1; i < t; i++)
		{
			if (WinorLose(Te(myhistory[i - 1]), Te(rivalhistory[i])) != 1)
			{
				IsWin4PreFlag = false;
				return false;
			}
		}
	}

	IsWin4PreFlag = true;
	return true;
}

// 戻り値 自分が最後に出した手
Te Combination_Data::MyLatestHand()
{
	for (int i = count - 1; i >= 0; i--)
	{
		if (allmyhistory[i] != -1) {
			return Te(allmyhistory[i]);
		}
	}
}

// 戻り値 相手が最後に出した手
Te Combination_Data::RivalLatestHand()
{
	for (int i = count - 1; i >= 0; i--)
	{
		if (allrivalhistory[i] != -1) {
			return Te(allrivalhistory[i]);
		}
	}
}

// 戻り値 引数に勝てる手
Te Combination_Data::Win(Te te)
{
	return Te((te + 2) % 3);
}

// 戻り値 引数に負ける手
Te Combination_Data::Lose(Te te)
{
	return Te((te + 1) % 3);
}

int Combination_Data::Get_win()
{
	return won_count;
}

int Combination_Data::Get_lose()
{
	return losed_count;
}

// 戻り値 引き分け:0 負け:1 勝ち:2
int Combination_Data::WinorLose(Te my, Te rival)
{
	return (my - rival + 3) % 3;
}

// 戻り値 ランダムな手
Te Combination_Data::rnd()
{
	return Te(rand3(r));
}

int Combination_Data::Get_count()
{
	return count;
}

// デバッグ用
void Combination_Data::debug()
{
	//if (count == 374)
	//{
	//	for (int i = 0; i < 374; i++)
	//	{
	//		std::cout << allrivalhistory[i] << ' ';
	//	}
	//	std::cout << '\n';
	//}

	std::cout << count << ':'
		<< markov_accuracy << ' '
		<< mymarkov_accuracy << ' '
		<< markov_accuracy2 << ' '
		<< markov_accuracy3 << ' '
		<< markov_accuracy4 << '\n';
}

int Combination_Data::Add_data()
{
	count++;
	if (t >= 1)
	{
		allmyhistory[count - 1] = myhistory[t - 1];
		allrivalhistory[count - 1] = rivalhistory[t - 1];
	}
	if (t >= 2)
	{
		rivalcomb_history[rivalhistory[t - 2]][rivalhistory[t - 1]]++;
		mycomb_history[myhistory[t - 2]][rivalhistory[t - 1]]++;
		markov_history[rivalhistory[t - 2]][WinorLose(myhistory[t - 2], rivalhistory[t - 2])][rivalhistory[t - 1]]++;
		markov_myhistory[myhistory[t - 2]][WinorLose(myhistory[t - 2], rivalhistory[t - 2])][myhistory[t - 1]]++;
	}
	if (t >= 3)
	{
		markov_history2[rivalhistory[t - 3]][WinorLose(myhistory[t - 3], rivalhistory[t - 3])][rivalhistory[t - 2]][WinorLose(myhistory[t - 2], rivalhistory[t - 2])][rivalhistory[t - 1]]++;
	}
	if (t >= 4)
	{
		markov_history3[rivalhistory[t - 4]][WinorLose(myhistory[t - 4], rivalhistory[t - 4])][rivalhistory[t - 3]][WinorLose(myhistory[t - 3], rivalhistory[t - 3])][rivalhistory[t - 2]][WinorLose(myhistory[t - 2], rivalhistory[t - 2])][rivalhistory[t - 1]]++;
	}
	if (t >= 5)
	{
		markov_history3_5[WinorLose(myhistory[t - 5], rivalhistory[t - 5])][rivalhistory[t - 4]][WinorLose(myhistory[t - 4], rivalhistory[t - 4])][rivalhistory[t - 3]][WinorLose(myhistory[t - 3], rivalhistory[t - 3])][rivalhistory[t - 2]][WinorLose(myhistory[t - 2], rivalhistory[t - 2])][rivalhistory[t - 1]]++;
		markov_history4[rivalhistory[t - 5]][WinorLose(myhistory[t - 5], rivalhistory[t - 5])][rivalhistory[t - 4]][WinorLose(myhistory[t - 4], rivalhistory[t - 4])][rivalhistory[t - 3]][WinorLose(myhistory[t - 3], rivalhistory[t - 3])][rivalhistory[t - 2]][WinorLose(myhistory[t - 2], rivalhistory[t - 2])][rivalhistory[t - 1]]++;
	}

	return 0;
}

void Combination_Data::Init_data()
{
	if (count == MAXKAISU_intern * NUMMATCH_intern - 1)
	{
		count = -1;
	}
	if (count == -1)
	{
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++)
			{
				rivalcomb_history[i][j] = 0;
				mycomb_history[i][j] = 0;
				for (int k = 0; k < 3; k++)
				{
					markov_history[i][j][k] = 0;
					markov_myhistory[i][j][k] = 0;
					for (int l = 0; l < 3; l++)
					{
						for (int m = 0; m < 3; m++)
						{
							markov_history2[i][j][k][l][m] = 0;
							for (int n = 0; n < 3; n++)
							{
								for (int o = 0; o < 3; o++)
								{
									markov_history3[i][j][k][l][m][n][o] = 0;
									for (int p = 0; p < 3; p++)
									{
										markov_history3_5[i][j][k][l][m][n][o][p] = 0;
										for (int q = 0; q < 3; q++)
										{
											markov_history4[i][j][k][l][m][n][o][p][q] = 0;
										}
									}
								}
							}
						}
					}
				}
			}
		}
		for (int i = 0; i < MAXKAISU_intern * NUMMATCH_intern; i++)
		{
			allmyhistory[i] = -1;
			allrivalhistory[i] = -1;
		}

		won_count = 0;
		losed_count = 0;
		markov_accuracy = 0;
		mymarkov_accuracy = 0;
		markov_accuracy2 = 0;
		markov_accuracy3 = 0;
		markov_accuracy4 = 0;
		IsWin4PreFlag = false;
	}
}

int Combination_Data::winning_counter()
{
	if (t >= 1)
	{
		if (WinorLose(myhistory[t - 1], rivalhistory[t - 1]) == 2)
		{
			won_count++;
		}
	}
	return won_count;
}

int Combination_Data::Losing_counter()
{
	if (t >= 1)
	{
		if (WinorLose(myhistory[t - 1], rivalhistory[t - 1]) == 1)
		{
			losed_count++;
		}
	}
	return losed_count;
}

int Combination_Data::markov_counter()
{
	if (count >= 4)
	{
		if (markov_prediction == Te(allrivalhistory[count - 1]))
		{
			markov_accuracy++;
		}
		if (mymarkov_prediction == Te(allrivalhistory[count - 1]))
		{
			mymarkov_accuracy++;
		}
		if (markov_prediction2 == Te(allrivalhistory[count - 1]))
		{
			markov_accuracy2++;
		}
		if (markov_prediction3 == Te(allrivalhistory[count - 1]))
		{
			markov_accuracy3++;
		}
		if (markov_prediction4 == Te(allrivalhistory[count - 1]))
		{
			markov_accuracy4++;
		}

		markov_prediction = Next_markov();
		mymarkov_prediction = Win(Next_mymarkov());
		markov_prediction2 = Next_markov2();
		markov_prediction3 = Next_markov3();
		markov_prediction4 = Next_markov4();
	}

	return 0;
}



// Te は Gu=0, Choki=1, Pa=2 という値を持つ enum 型
// 第一引数 i は１試合の中で現在何回目を示す．0からMAXKAISU-1までの値．
// 第二引数 myhistory は自分の手の履歴を示す．添字は0からMAXKAISU-1まで使えるが，0からi-1までの履歴しか信用出来ない．
// 第三引数 rivalhistory は相手の手の履歴を示す．添字は0からMAXKAISU-1まで使えるが，0からi-1までの履歴しか信用出来ない．
Te s18a1042(int i, Te myhistory[], Te rivalhistory[]) {
	static Combination_Data cmb;
	cmb.Set_data(i, myhistory, rivalhistory);
	cmb.Update();
	//cmb.debug();
	cmb.Save_data();
	if (cmb.FirstBattle())
	{
		return Te(cmb.rnd());
	}
	if (cmb.IsOnlyCpu() && cmb.IsWin4PreFlag == false)
	{
		return cmb.Win(cmb.RivalLatestHand());
	}
	if (cmb.IsWin4Pre())
	{
		return cmb.Lose(cmb.MyLatestHand());
	}

	return cmb.Win(cmb.Next_markov3());
	return cmb.rnd();
	return cmb.Judg_markov();
	return cmb.Win(cmb.Next_markov4());
	return cmb.Win(cmb.Next_markov3_5());
	return cmb.Win(cmb.Next_markov());
	return cmb.Win(cmb.Next_markov2());
	return cmb.Lose(cmb.Next_mymarkov());
}
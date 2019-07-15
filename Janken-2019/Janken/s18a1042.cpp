//TODO このソースコードを参考に，自分の学籍番号.cppというファイルを作り，改造する．
#include "stdafx.h"
#include "cstdlib"
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <random>
#include <direct.h>
#include <vector>

extern int MAXKAISU;
extern int NUMMATCH;

class Markov
{
public:
	Markov();
	~Markov();

	void Add(int, int, int, int, int, int, int);
	void Init();
	Te Next(int, int, int, int, int, int, int, int) const;
	Te Next(Markov*, int, int, int, int, int, int, int, int) const;
	int markov_data[3][3][3][3][3][3][3];

private:
};

Markov::Markov()
{
	Init();
}

Markov::~Markov()
{
}

void Markov::Add(int prev3, int vict3, int prev2, int vict2, int prev1, int vict1, int stdd)
{
	markov_data[prev3][vict3][prev2][vict2][prev1][vict1][stdd]++;
}

void Markov::Init()
{
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
								markov_data[i][j][k][l][m][n][o] = 0;
							}
						}
					}
				}
			}
		}
	}
}

Te Markov::Next(int count, int t, int prev3, int vict3, int prev2, int vict2, int prev1, int vict1) const
{
	int max = -1;
	Te next;

	for (int i = 0; i < 3; i++)
	{
		if (count >= 3 && t >= 3)
		{
			if (markov_data[prev3][vict3][prev2][vict2][prev1][vict1][i] >= max)
			{
				max = markov_data[prev3][vict3][prev2][vict2][prev1][vict1][i];
				next = Te(i);
			}
		}
		else
		{
			next = Te(rand() % 3);
		}

	}
	return next;
}

Te Markov::Next(Markov* m, int count, int t, int prev3, int vict3, int prev2, int vict2, int prev1, int vict1) const
{
	int max = -1;
	Te next;

	for (int i = 0; i < 3; i++)
	{
		if (count >= 3 && t >= 3)
		{
			if (this->markov_data[prev3][vict3][prev2][vict2][prev1][vict1][i] +
				m->markov_data[prev3][vict3][prev2][vict2][prev1][vict1][i] >= max)
			{
				max = this->markov_data[prev3][vict3][prev2][vict2][prev1][vict1][i] +
					m->markov_data[prev3][vict3][prev2][vict2][prev1][vict1][i];
				next = Te(i);
			}
		}
		else
		{
			next = Te(rand() % 3);
		}
	}
	return next;
}

class Combination_Data
{
public:
	Combination_Data();
	~Combination_Data();

	void Update();
	void Set_data(int, Te*, Te*);
	void Save_data();
	void Set_Mgradient(int m1 = 10, int mym = 10, int m2 = 10, int m3 = 10, int m4 = 10, int mym2 = 10, int prem = 10, int pastdm = 10);

	Te Next_probability();
	Te Next_markov();
	Te Next_mymarkov();
	Te Next_markov2();
	Te Next_markov3();
	Te Next_markov3_5();
	Te Next_markov4();
	Te Next_mymarkov2();
	Te Next_premarkov(int p);
	Te Judg_markov();
	Te Judg_mRetsubs(int);

	Te markovclass();

	inline double WinRate(int) const;
	inline double LossRate(int) const;

	bool FirstBattle() const;
	bool IsOnlyCpu() const;
	bool IsWin4Pre();

	Te MyLatestHand() const;
	Te RivalLatestHand() const;
	Te Win(Te) const;
	Te Lose(Te) const;
	int Get_win() const;
	int Get_lose() const;
	// 引き分け:0 負け:1 勝ち:2
	int WinorLose(Te, Te) const;
	const Te rnd();
	int Get_count() const;

	void debug();

	bool IsWin4PreFlag;

private:
	int Add_data();
	void Init_data();
	int winning_counter();
	int Losing_counter();
	int markov_counter();

	void Set_premarkov();

	const int MAXKAISU_intern;
	const int NUMMATCH_intern;

	int t;
	Te* myhistory;
	Te* rivalhistory;

	// MAX 147
	static const int NUMPREDATA = 147;

	//相手の前々回と前回の手の組み合わせ
	int rivalcomb_history[3][3];
	//自分の前々回と相手の前回の手の組み合わせ
	int mycomb_history[3][3];
	// マルコフ戦略用データ ...[][前の状態][勝敗][次の状態]
	int markov_history[3][3][3];
	int markov_myhistory[3][3][3];
	int markov_history2[3][3][3][3][3];
	int markov_history3[3][3][3][3][3][3][3];
	int markov_history3_5[3][3][3][3][3][3][3][3];
	int markov_history4[3][3][3][3][3][3][3][3][3];
	int markov_myhistory2[3][3][3][3][3];
	int premarkov[NUMPREDATA][3][3][3][3][3][3][3][3][3];
	Markov markov3;
	std::vector<Markov> markov_Pastdata;

	int savejudg;

	int* allmyhistory;
	int* allrivalhistory;

	int won_count;
	int losed_count;
	int markov_accuracy;
	int mymarkov_accuracy;
	int markov_accuracy2;
	int markov_accuracy3;
	int markov_accuracy4;
	int mymarkov_accuracy2;
	int preM_accuracy[NUMPREDATA];
	std::vector<int> pastdM_accuracy;
	Te markov_prediction;
	Te mymarkov_prediction;
	Te markov_prediction2;
	Te markov_prediction3;
	Te markov_prediction4;
	Te mymarkov_prediction2;
	Te preM_prediction[NUMPREDATA];
	std::vector<Te> pastdM_prediction;

	static const int markovnum = 8;
	int markov_gradient[markovnum];

	int count;
	int allcount;

	int savecount;
	std::ofstream logf;
	std::ofstream logf2;
	std::ifstream markovf[NUMPREDATA];
	std::string filename;
	std::string filename2;
	std::string markovFN[NUMPREDATA];
	const std::string testr[3] = { "Gu","Choki","Pa" };
	const std::string winlose[3] = { "引き分け","勝ち","負け" };

	std::random_device r;
	std::uniform_int_distribution<> rand3;

};

Combination_Data::Combination_Data() : rand3(0, 2), MAXKAISU_intern(MAXKAISU), NUMMATCH_intern(NUMMATCH), markov_prediction(Te(0)), mymarkov_prediction(Te(0))
{
	count = -1;
	allcount = -1;
	savecount = 0;

	allmyhistory = new int[MAXKAISU_intern * NUMMATCH_intern];
	allrivalhistory = new int[MAXKAISU_intern * NUMMATCH_intern];
	markov_Pastdata.reserve(300);
	pastdM_accuracy.reserve(300);
	pastdM_prediction.reserve(300);

	filename = "log\\log.csv";
	filename2 = "log\\log2.csv";
	_mkdir("log");
	logf.open(filename);
	logf2.open(filename2);
	for (int i = 0; i < NUMPREDATA; i++)
	{
		markovFN[i] = "markov/markov" + std::to_string(i) + ".bin";
		markovf[i].open(markovFN[i], std::ios::binary);
	}
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
	Set_premarkov();
	Set_Mgradient();
}

Combination_Data::~Combination_Data()
{
	logf.close();
	logf2.close();
	for (int i = 0; i < NUMPREDATA; i++)
	{
		markovf[i].close();
	}

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

void Combination_Data::Set_Mgradient(int m1, int mym, int m2, int m3, int m4, int mym2, int prem, int pastdm)
{
	markov_gradient[0] = m1;
	markov_gradient[1] = mym;
	markov_gradient[2] = m2;
	markov_gradient[3] = m3;
	markov_gradient[4] = m4;
	markov_gradient[5] = mym2;
	markov_gradient[6] = prem;
	markov_gradient[7] = pastdm;
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
		if (count >= 1 && t >= 1)
		{
			if (markov_history[subscript[1]][subscript[0]][i] >= max)
			{
				max = markov_history[subscript[1]][subscript[0]][i];
				next = Te(i);
			}
		}
		else
		{
			next = rnd();
		}
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
		if (count >= 1 && t >= 1)
		{
			if (markov_myhistory[subscript[1]][subscript[0]][i] >= max)
			{
				max = markov_myhistory[subscript[1]][subscript[0]][i];
				next = Te(i);
			}
		}
		else
		{
			next = rnd();
		}
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
		if (count >= 2 && t >= 2)
		{
			if (markov_history2[subscript[3]][subscript[2]][subscript[1]][subscript[0]][i] >= max)
			{
				max = markov_history2[subscript[3]][subscript[2]][subscript[1]][subscript[0]][i];
				next = Te(i);
			}
		}
		else
		{
			next = rnd();
		}
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
		if (count >= 3 && t >= 3)
		{
			if (markov_history3[subscript[5]][subscript[4]][subscript[3]][subscript[2]][subscript[1]][subscript[0]][i] >= max)
			{
				max = markov_history3[subscript[5]][subscript[4]][subscript[3]][subscript[2]][subscript[1]][subscript[0]][i];
				next = Te(i);
			}
		}
		else
		{
			next = rnd();
		}
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
		if (count >= 4 && t >= 4)
		{
			if (markov_history3_5[subscript[6]][subscript[5]][subscript[4]][subscript[3]][subscript[2]][subscript[1]][subscript[0]][i] >= max)
			{
				max = markov_history3_5[subscript[6]][subscript[5]][subscript[4]][subscript[3]][subscript[2]][subscript[1]][subscript[0]][i];
				next = Te(i);
			}
		}
		else
		{
			next = rnd();
		}
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
		if (count >= 4 && t >= 4)
		{
			if (markov_history4[subscript[7]][subscript[6]][subscript[5]][subscript[4]][subscript[3]][subscript[2]][subscript[1]][subscript[0]][i] >= max)
			{
				max = markov_history4[subscript[7]][subscript[6]][subscript[5]][subscript[4]][subscript[3]][subscript[2]][subscript[1]][subscript[0]][i];
				next = Te(i);
			}
		}
		else
		{
			next = rnd();
		}
	}
	return next;
}

Te Combination_Data::Next_mymarkov2()
{
	int max = -1;
	Te next;
	int subscript[4];

	for (int i = count - 1, j = 0; i >= 0 && j < 4; i--)
	{
		if (allrivalhistory[i] != -1 && allmyhistory[i] != -1)
		{
			subscript[j] = WinorLose(Te(allmyhistory[i]), Te(allrivalhistory[i]));
			subscript[j + 1] = allmyhistory[i];
			j += 2;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (count >= 2 && t >= 2)
		{
			if (markov_history2[subscript[3]][subscript[2]][subscript[1]][subscript[0]][i] >= max)
			{
				max = markov_history2[subscript[3]][subscript[2]][subscript[1]][subscript[0]][i];
				next = Te(i);
			}
		}
		else
		{
			next = rnd();
		}
	}
	return next;
}

Te Combination_Data::Next_premarkov(int p)
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
		if (count >= 4 && t >= 4)
		{
			if (premarkov[p][subscript[7]][subscript[6]][subscript[5]][subscript[4]][subscript[3]][subscript[2]][subscript[1]][subscript[0]][i] >= max)
			{
				max = premarkov[p][subscript[7]][subscript[6]][subscript[5]][subscript[4]][subscript[3]][subscript[2]][subscript[1]][subscript[0]][i];
				next = Te(i);
			}
		}
		else
		{
			next = rnd();
		}

	}
	return next;
}

// markovによる精度を比較し高いアルゴリズムを利用する
// 戻り値 相手の次の手の予測に勝てる手
Te Combination_Data::Judg_markov()
{
	std::vector<int> accuracy = {
		markov_accuracy,
		mymarkov_accuracy,
		markov_accuracy2,
		markov_accuracy3,
		markov_accuracy4,
		mymarkov_accuracy2
	};
	accuracy.resize((markovnum - 2) + NUMPREDATA + pastdM_accuracy.size());
	for (int i = markovnum - 2; i < (markovnum - 2) + NUMPREDATA; i++)
	{
		accuracy[i] = preM_accuracy[i - (markovnum - 2)];
	}
	for (int i = (markovnum - 2) + NUMPREDATA; i < (markovnum - 2) + NUMPREDATA + pastdM_accuracy.size(); i++)
	{
		accuracy[i] = pastdM_prediction[i - ((markovnum - 2) + NUMPREDATA)];
	}
	Te(Combination_Data:: * markov_func[])() = {
		&Combination_Data::Next_markov,
		&Combination_Data::Next_mymarkov,
		&Combination_Data::Next_markov2,
		&Combination_Data::Next_markov3,
		&Combination_Data::Next_markov4,
		&Combination_Data::Next_mymarkov2,
	};
	Te(Combination_Data:: * premarkov_func)(int p) = &Combination_Data::Next_premarkov;
	int max[] = { -1,0 };

	for (int i = 0; i < accuracy.size(); i++)
	{
		if (accuracy[i] >= max[0])
		{
			max[0] = accuracy[i];
			max[1] = i;
		}
	}

	if (max[1] == 1 || max[1] == 5)
	{
		return Lose((this->*markov_func[max[1]])());
	}
	else if (max[1] >= 0 && max[1] <= 4)
	{
		return Win((this->*markov_func[max[1]])());
	}
	else if (max[1] < (markovnum - 2) + NUMPREDATA)
	{
		return Win((this->*premarkov_func)(max[1] - (markovnum - 2)));
	}
	else
	{
		if (count >= 3)
		{
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
			return Win(markov_Pastdata[max[1] - ((markovnum - 2) + NUMPREDATA)].Next(&markov3, count, t, subscript[5], subscript[4], subscript[3], subscript[2], subscript[1], subscript[0]));
		}
		else
		{
			return rnd();
		}
	}
}

Te Combination_Data::Judg_mRetsubs(int start)
{
	int accuracy[5 + NUMPREDATA] = {
		markov_accuracy,
		mymarkov_accuracy,
		markov_accuracy2,
		markov_accuracy3,
		markov_accuracy4
	};
	for (int i = 5; i < 5 + NUMPREDATA; i++)
	{
		accuracy[i] = preM_accuracy[i - 5];
	}
	Te(Combination_Data:: * markov_func[])() = {
		&Combination_Data::Next_markov,
		&Combination_Data::Next_mymarkov,
		&Combination_Data::Next_markov2,
		&Combination_Data::Next_markov3,
		&Combination_Data::Next_markov4
	};
	Te(Combination_Data:: * premarkov_func)(int p) = &Combination_Data::Next_premarkov;
	int max[] = { -1,0 };


	if (count >= start)
	{
		if (savejudg == 1)
		{
			return Lose((this->*markov_func[savejudg])());
		}
		else if (savejudg >= 0 && savejudg <= 4)
		{
			return Win((this->*markov_func[savejudg])());
		}
		else
		{
			return Win((this->*premarkov_func)(savejudg - 5));
		}
	}

	for (int i = 0; i < sizeof(accuracy) / sizeof(accuracy[0]); i++)
	{
		if (accuracy[i] >= max[0])
		{
			max[0] = accuracy[i];
			max[1] = i;
		}
	}

	savejudg = max[1];

	if (max[1] == 1)
	{
		return Lose((this->*markov_func[max[1]])());
	}
	else if (max[1] >= 0 && max[1] <= 4)
	{
		return Win((this->*markov_func[max[1]])());
	}
	else
	{
		return Win((this->*premarkov_func)(max[1] - 5));
	}
}

Te Combination_Data::markovclass()
{
	if (count >= 3)
	{
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
		return Win(markov3.Next(count, t, subscript[5], subscript[4], subscript[3], subscript[2], subscript[1], subscript[0]));
	}
	else
	{
		return rnd();
	}
}

// 戻り値 現在の勝率 引数：計測開始ターン
inline double Combination_Data::WinRate(int start) const
{
	if (count >= start)
	{
		return (double)won_count / (count + 1);
	}
	return 1;
}

// 戻り値 現在の敗率 引数：計測開始ターン
inline double Combination_Data::LossRate(int start) const
{
	if (count >= start)
	{
		return (double)losed_count / (count + 1);
	}
	return 0;
}

// 戻り値 0戦目0回目ならtrue
bool Combination_Data::FirstBattle() const
{
	return count == 0;
}

// 戻り値 OnlyCpuと判定した場合true
bool Combination_Data::IsOnlyCpu() const
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
Te Combination_Data::MyLatestHand() const
{
	for (int i = count - 1; i >= 0; i--)
	{
		if (allmyhistory[i] != -1) {
			return Te(allmyhistory[i]);
		}
	}
}

// 戻り値 相手が最後に出した手
Te Combination_Data::RivalLatestHand() const
{
	for (int i = count - 1; i >= 0; i--)
	{
		if (allrivalhistory[i] != -1) {
			return Te(allrivalhistory[i]);
		}
	}
}

// 戻り値 引数に勝てる手
Te Combination_Data::Win(Te te) const
{
	return Te((te + 2) % 3);
}

// 戻り値 引数に負ける手
Te Combination_Data::Lose(Te te) const
{
	return Te((te + 1) % 3);
}

int Combination_Data::Get_win() const
{
	return won_count;
}

int Combination_Data::Get_lose() const
{
	return losed_count;
}

// 戻り値 引き分け:0 負け:1 勝ち:2
int Combination_Data::WinorLose(Te my, Te rival) const
{
	return (my - rival + 3) % 3;
}

// 戻り値 ランダムな手
const Te Combination_Data::rnd()
{
	return Te(rand3(r));
}

int Combination_Data::Get_count() const
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

	/*std::cout << count << ':'
		<< markov_accuracy << ' '
		<< mymarkov_accuracy << ' '
		<< markov_accuracy2 << ' '
		<< markov_accuracy3 << ' '
		<< markov_accuracy4 << '\n';*/
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
		markov_myhistory2[myhistory[t - 3]][WinorLose(myhistory[t - 3], rivalhistory[t - 3])][myhistory[t - 2]][WinorLose(myhistory[t - 2], rivalhistory[t - 2])][myhistory[t - 1]]++;
	}
	if (t >= 4)
	{
		markov_history3[rivalhistory[t - 4]][WinorLose(myhistory[t - 4], rivalhistory[t - 4])][rivalhistory[t - 3]][WinorLose(myhistory[t - 3], rivalhistory[t - 3])][rivalhistory[t - 2]][WinorLose(myhistory[t - 2], rivalhistory[t - 2])][rivalhistory[t - 1]]++;
		markov3.Add(rivalhistory[t - 4], WinorLose(myhistory[t - 4], rivalhistory[t - 4]), rivalhistory[t - 3], WinorLose(myhistory[t - 3], rivalhistory[t - 3]), rivalhistory[t - 2], WinorLose(myhistory[t - 2], rivalhistory[t - 2]), rivalhistory[t - 1]);
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
							markov_myhistory2[i][j][k][l][m] = 0;
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
		if (allcount != -1)
		{
			markov_Pastdata.push_back(markov3);
			pastdM_accuracy.push_back(0);
			pastdM_prediction.push_back(Gu);
			markov3.Init();
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
		mymarkov_accuracy2 = 0;
		for (int i = 0; i < NUMPREDATA; i++)
		{
			preM_accuracy[i] = 0;
		}
		for (int i = 0; i < pastdM_accuracy.size(); i++)
		{
			pastdM_accuracy[i] = 0;
		}
		IsWin4PreFlag = false;
		allcount++;
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
	if (count >= 3)
	{
		if (markov_prediction == Te(allrivalhistory[count - 1]))
		{
			markov_accuracy += markov_gradient[0];
		}
		if (mymarkov_prediction == Te(allrivalhistory[count - 1]))
		{
			mymarkov_accuracy += markov_gradient[1];
		}
		if (markov_prediction2 == Te(allrivalhistory[count - 1]))
		{
			markov_accuracy2 += markov_gradient[2];
		}
		if (markov_prediction3 == Te(allrivalhistory[count - 1]))
		{
			markov_accuracy3 += markov_gradient[3];
		}
		if (markov_prediction4 == Te(allrivalhistory[count - 1]))
		{
			markov_accuracy4 += markov_gradient[4];
		}
		if (mymarkov_accuracy2 == Te(allrivalhistory[count - 1]))
		{
			mymarkov_accuracy2 += markov_gradient[5];
		}
		for (int i = 0; i < NUMPREDATA; i++)
		{
			if (preM_prediction[i] == Te(allrivalhistory[count - 1]))
			{
				preM_accuracy[i] += markov_gradient[6];
			}
		}
		for (int i = 0; i < pastdM_prediction.size(); i++)
		{
			if (pastdM_prediction[i] == Te(allrivalhistory[count - 1]))
			{
				pastdM_accuracy[i] += markov_gradient[7];
			}
		}


		markov_prediction = Next_markov();
		mymarkov_prediction = Win(Next_mymarkov());
		markov_prediction2 = Next_markov2();
		markov_prediction3 = Next_markov3();
		markov_prediction4 = Next_markov4();
		mymarkov_accuracy2 = Win(Next_mymarkov2());
		for (int i = 0; i < NUMPREDATA; i++)
		{
			preM_prediction[i] = Next_premarkov(i);
		}

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
		for (int i = 0; i < pastdM_prediction.size(); i++)
		{
			pastdM_prediction[i] = markov_Pastdata[i].Next(count, t, subscript[5], subscript[4], subscript[3], subscript[2], subscript[1], subscript[0]);
		}
	}

	return 0;
}

void Combination_Data::Set_premarkov()
{
	for (int mfn = 0; mfn < NUMPREDATA; mfn++)
	{
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
									for (int p = 0; p < 3; p++)
									{
										for (int q = 0; q < 3; q++)
										{
											markovf[mfn].read((char*)& premarkov[mfn][i][j][k][l][m][n][o][p][q], sizeof(premarkov[mfn][i][j][k][l][m][n][o][p][q]));
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}



// Te は Gu=0, Choki=1, Pa=2 という値を持つ enum 型
// 第一引数 i は１試合の中で現在何回目を示す．0からMAXKAISU-1までの値．
// 第二引数 myhistory は自分の手の履歴を示す．添字は0からMAXKAISU-1まで使えるが，0からi-1までの履歴しか信用出来ない．
// 第三引数 rivalhistory は相手の手の履歴を示す．添字は0からMAXKAISU-1まで使えるが，0からi-1までの履歴しか信用出来ない．
Te s18a1042(int i, Te myhistory[], Te rivalhistory[]) {
	static Combination_Data cmb;
	cmb.Set_data(i, myhistory, rivalhistory);
	cmb.Update();
	cmb.Set_Mgradient(10, 10, 10, 17, 14, 10, 15, 15);
	cmb.debug();
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

	return cmb.Judg_markov();
}
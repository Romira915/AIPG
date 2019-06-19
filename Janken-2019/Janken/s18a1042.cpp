//TODO このソースコードを参考に，自分の学籍番号.cppというファイルを作り，改造する．
#include "stdafx.h"
#include "cstdlib"
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <random>

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
	double WinRate(int);
	double LossRate(int);

	bool FirstBattle();
	bool IsOnlyCpu();
	bool IsWin4Pre();
	Te MyLatestHand();
	Te RivalLatestHand();
	Te Win(Te);
	Te Lose(Te);
	// 引き分け:0 負け:1 勝ち:2
	int WinorLose(Te, Te);
	Te rnd();

	void debug();

	bool IsWin4PreFlag;

private:
	int Add_data();
	void Init_data();
	int winning_counter();
	int Losing_counter();

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

	int *allmyhistory;
	int *allrivalhistory;

	int won_count;
	int losed_count;

	int count;

	int savecount;
	std::ofstream logf;
	std::string filename;
	const std::string testr[3] = { "Gu","Choki","Pa" };
	const std::string winlose[3] = { "引き分け","勝ち","負け" };

	std::random_device r;
	std::uniform_int_distribution<> rand3;
};

Combination_Data::Combination_Data() : rand3(0, 2), MAXKAISU_intern(MAXKAISU), NUMMATCH_intern(NUMMATCH)
{
	count = -1;
	savecount = 0;

	allmyhistory = new int[MAXKAISU_intern * NUMMATCH_intern];
	allrivalhistory = new int[MAXKAISU_intern * NUMMATCH_intern];

	filename = "log\\log.csv";
	logf.open(filename);
	if (!logf)
	{
		std::cout << "Can't open " << '"' << filename << '"' << '\n';
		std::exit(-1);
	}

	Init_data();
}

Combination_Data::~Combination_Data()
{
	logf.close();

	delete[] allmyhistory;
	delete[]  allrivalhistory;
}

void Combination_Data::Update()
{
	Init_data();
	Add_data();
	winning_counter();
	Losing_counter();
}

void Combination_Data::Set_data(int u, Te* my, Te* rival)
{
	t = u;
	myhistory = my;
	rivalhistory = rival;
}

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
		}
		savecount++;
	}
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

Te Combination_Data::Next_markov()
{
	double markov_probability[3][3][3] = { 0 };
	double max = 0;
	Te next;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				markov_probability[i][j][k] = double(markov_history[i][j][k]) / (count + 1);
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (count != 0 && t == 0)
		{
			if (markov_probability[allrivalhistory[count - 1]][WinorLose(Te(allmyhistory[count - 1]), Te(allrivalhistory[count - 1]))][i] >= max) {
				max = markov_probability[allrivalhistory[count - 1]][WinorLose(Te(allmyhistory[count - 1]), Te(allrivalhistory[count - 1]))][i];
				next = Te(i);
			}
		}
		else if (markov_probability[rivalhistory[t - 1]][WinorLose(myhistory[t - 1], rivalhistory[t - 1])][i] >= max) {
			max = markov_probability[rivalhistory[t - 1]][WinorLose(myhistory[t - 1], rivalhistory[t - 1])][i];
			next = Te(i);
		}
	}

	return next;
}

Te Combination_Data::Next_mymarkov()
{
	double markov_probability[3][3][3] = { 0 };
	double max = 0;
	Te next;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				markov_probability[i][j][k] = double(markov_myhistory[i][j][k]) / (count + 1);
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		if (count != 0 && t == 0)
		{
			if (markov_probability[allmyhistory[count - 1]][WinorLose(Te(allmyhistory[count - 1]), Te(allrivalhistory[count - 1]))][i] >= max) {
				max = markov_probability[allmyhistory[count - 1]][WinorLose(Te(allmyhistory[count - 1]), Te(allrivalhistory[count - 1]))][i];
				next = Te(i);
			}
		}
		else if (markov_probability[myhistory[t - 1]][WinorLose(myhistory[t - 1], rivalhistory[t - 1])][i] >= max) {
			max = markov_probability[myhistory[t - 1]][WinorLose(myhistory[t - 1], rivalhistory[t - 1])][i];
			next = Te(i);
		}
	}

	return next;
}

double Combination_Data::WinRate(int start)
{
	if (count >= start)
	{
		return (double)won_count / (count + 1);
	}
	return 1;
}

double Combination_Data::LossRate(int start)
{
	if (count >= start)
	{
		return (double)losed_count / (count + 1);
	}
	return 0;
}

bool Combination_Data::FirstBattle()
{
	return count == 0;
}

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

bool Combination_Data::IsWin4Pre()
{
	if (count >= 2 && t >= 2)
	{
		for (int i = 1; i < count; i++)
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

Te Combination_Data::MyLatestHand()
{
	for (int i = count - 1; i >= 0; i--)
	{
		if (allmyhistory[i] != -1) {
			return Te(allmyhistory[i]);
		}
	}
}

Te Combination_Data::RivalLatestHand()
{
	for (int i = count - 1; i >= 0; i--)
	{
		if (allrivalhistory[i] != -1) {
			return Te(allrivalhistory[i]);
		}
	}
}

Te Combination_Data::Win(Te te)
{
	return Te((te + 2) % 3);
}

Te Combination_Data::Lose(Te te)
{
	return Te((te + 1) % 3);
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

// 引き分け:0 負け:1 勝ち:2
int Combination_Data::WinorLose(Te my, Te rival)
{
	return (my - rival + 3) % 3;
}

Te Combination_Data::rnd()
{
	return Te(rand3(r));
}

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

	return cmb.WinRate(40) > 0 ? cmb.Win(cmb.Next_markov()) : cmb.Lose(cmb.Next_mymarkov());
	//return cmb.LossRate(75) > 0.376 ? Te(rand() % 3) : Te((cmb.Next_probability() + 2) % 3);
	return cmb.LossRate(40) > 0.375 ? cmb.rnd() : cmb.Win(cmb.Next_markov());
	return cmb.LossRate(40) > 0.375 ? cmb.rnd() : cmb.Lose(cmb.Next_mymarkov());
}
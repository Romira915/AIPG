//TODO ���̃\�[�X�R�[�h���Q�l�ɁC�����̊w�Дԍ�.cpp�Ƃ����t�@�C�������C��������D
#include "stdafx.h"
#include "cstdlib"
#include <iostream>
#include <fstream>

#include <cmath>

class Combination_Data
{
public:
	Combination_Data();
	~Combination_Data();

	void Update();
	void Set_data(int, Te*, Te*);
	Te Next_probability();
	Te Next_markov();
	double LossRate(int);

	bool FirstBattle();
	bool IsOnlyCpu();
	bool IsWin4Pre();
	Te MyLatestHand();
	Te RivalLatestHand();
	Te Win(Te);
	Te Lose(Te);
	// ��������:0 ����:1 ����:2
	Te WinorLose(Te, Te);

	void debug();

	bool IsWin4PreFlag;

private:
	int Add_data();
	void Reset_data();
	int Losing_counter();

	static const int MAXGAME = 75;
	static const int NUMMATCH = 5;

	int t;
	Te* myhistory;
	Te* rivalhistory;

	//����̑O�X��ƑO��̎�̑g�ݍ��킹
	int rivalcomb_history[3][3];
	//�����̑O�X��Ƒ���̑O��̎�̑g�ݍ��킹
	int mycomb_history[3][3];
	// �}���R�t�헪�p�f�[�^ [�O�̏��][���s][���̏��]
	int markov_history[3][3][3];

	int losed_count;

	int count;
	int allmyhistory[MAXGAME * NUMMATCH];
	int allrivalhistory[MAXGAME * NUMMATCH];
};

Combination_Data::Combination_Data()
{
	count = -1;

	Reset_data();
}

Combination_Data::~Combination_Data()
{
}

void Combination_Data::Update()
{
	Reset_data();
	Add_data();
	Losing_counter();
}

void Combination_Data::Set_data(int u, Te* my, Te* rival)
{
	t = u;
	myhistory = my;
	rivalhistory = rival;
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
	}
	/*if (t == MAXGAME)
	{
		kaisu++;
		if (kaisu == NUMMATCH + 1)
		{

			losed_count = 0;
			count = -1;
			kaisu = 0;
		}
	}*/

	return 0;
}

void Combination_Data::Reset_data()
{
	if (count == MAXGAME * NUMMATCH - 1)
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
				}
			}
		}
		for (int i = 0; i < MAXGAME * NUMMATCH; i++)
		{
			allmyhistory[i] = -1;
			allrivalhistory[i] = -1;
		}

		losed_count = 0;
		IsWin4PreFlag = false;
	}
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
			if (WinorLose(Te(myhistory[i - 1]), Te(rivalhistory[i])) != Te(1))
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

// ��������:0 ����:1 ����:2
Te Combination_Data::WinorLose(Te my, Te rival)
{
	return Te((my - rival + 3) % 3);
}

void Combination_Data::debug()
{
	//std::cout << "count " << count << "  t " << t << '\n';
	if (count == 374)
	{
		for (int i = 0; i < 374; i++)
		{
			std::cout << allrivalhistory[i] << ' ';
		}
		std::cout << '\n';
	}
}

bool All_Win(int count, const Te* myhistory, const Te* rivalhistory) {
	for (int i = 1; i < count; i++)
	{
		if ((myhistory[i] - rivalhistory[i] + 3) % 3 != 2)
		{
			return false;
		}
	}

	return true;
}

bool Win4Pre_or(int count, Te* myhistory, Te* rivalhistory) {
	for (int i = 1; i < count; i++)
	{
		if ((myhistory[i - 1] + 2) % 3 != rivalhistory[i] % 3)
		{
			return false;
		}
	}

	return true;
}

// Te �� Gu=0, Choki=1, Pa=2 �Ƃ����l������ enum �^
// ������ i �͂P�����̒��Ō��݉���ڂ������D0����MAXKAISU-1�܂ł̒l�D
// ������ myhistory �͎����̎�̗����������D�Y����0����MAXKAISU-1�܂Ŏg���邪�C0����i-1�܂ł̗��������M�p�o���Ȃ��D
// ��O���� rivalhistory �͑���̎�̗����������D�Y����0����MAXKAISU-1�܂Ŏg���邪�C0����i-1�܂ł̗��������M�p�o���Ȃ��D
Te s18a1042(int i, Te myhistory[], Te rivalhistory[]) {
	static Combination_Data cmb;
	cmb.Set_data(i, myhistory, rivalhistory);
	cmb.Update();
	//cmb.debug();
	//std::ofstream f("log.txt", std::ios::app);
	if (cmb.FirstBattle())
	{
		return Te(rand() % 3);
	}
	if (cmb.IsOnlyCpu() && cmb.IsWin4PreFlag == false)
	{
		return cmb.Win(cmb.RivalLatestHand());
	}
	if (cmb.IsWin4Pre())
	{
		return cmb.Lose(cmb.MyLatestHand());
	}

	//return cmb.LossRate(75) > 0.376 ? Te(rand() % 3) : Te((cmb.Next_probability() + 2) % 3);
	//return cmb.LossRate(40) > 0.375 ? Te((cmb.Next_probability() + 2) % 3) : Te((cmb.Next_markov() + 2) % 3);
	return cmb.LossRate(40) > 0.375 ? Te(rand() % 3) : cmb.Win(cmb.Next_markov());
}
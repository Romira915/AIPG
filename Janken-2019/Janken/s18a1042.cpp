//TODO ���̃\�[�X�R�[�h���Q�l�ɁC�����̊w�Дԍ�.cpp�Ƃ����t�@�C�������C��������D
#include "stdafx.h"
#include "cstdlib"
#include <iostream>

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

	void debug();

private:
	int Add_data();
	int Losing_counter();
	// ��������:0 ����:1 ����:2
	Te WinorLose(Te, Te);

	static const int MAXGAME = 75 - 1;
	static const int NUMMATCH = 5 - 1;

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
	Te allmyhistroy[(MAXGAME + 1) * (NUMMATCH + 1)];
	Te allrivalhistory[(MAXGAME + 1) * (NUMMATCH + 1)];
	int kaisu;
};

Combination_Data::Combination_Data()
{
	losed_count = 0;
	count = 0;
	kaisu = 0;
}

Combination_Data::~Combination_Data()
{
}

void Combination_Data::Update()
{
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
	if (t >= 2)
	{
		rivalcomb_history[rivalhistory[t - 2]][rivalhistory[t - 1]]++;
		mycomb_history[myhistory[t - 2]][rivalhistory[t - 1]]++;
		markov_history[rivalhistory[t - 2]][WinorLose(myhistory[t - 2], rivalhistory[t - 2])][rivalhistory[t - 1]]++;
	}
	if (t == MAXGAME)
	{
		kaisu++;
		if (kaisu == NUMMATCH + 1)
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
			for (int i = 0; i < (MAXGAME + 1) * (NUMMATCH + 1); i++)
			{
				allmyhistroy[i] = Te(0);
				allrivalhistory[i] = Te(0);
			}
			losed_count = 0;
			count = 0;
			kaisu = 0;
		}
	}
	count++;

	return 0;
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
		if (markov_probability[rivalhistory[t - 1]][WinorLose(myhistory[t - 1], rivalhistory[t - 1])][i] >= max) {
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

Te Combination_Data::WinorLose(Te my, Te rival)
{
	return Te((my - rival + 3) % 3);
}

void Combination_Data::debug()
{
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
	cmb.debug();
	if (i == 0)
	{
		return Te(rand() % 3);
	}
	if (i >= 1 && All_Win(i, myhistory, rivalhistory))
	{
		return Te((rivalhistory[i - 1] + 2) % 3);
	}
	if (i >= 2 && Win4Pre_or(i, myhistory, rivalhistory))
	{
		return Te((myhistory[i - 1] + 1) % 3);
	}

	//return cmb.LossRate(75) > 0.376 ? Te(rand() % 3) : Te((cmb.Next_probability() + 2) % 3);
	return cmb.LossRate(40) > 0.387 ? Te(rand() % 3) : Te((cmb.Next_markov() + 2) % 3);
}
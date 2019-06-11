//TODO ���̃\�[�X�R�[�h���Q�l�ɁC�����̊w�Дԍ�.cpp�Ƃ����t�@�C�������C��������D
#include "stdafx.h"
#include "cstdio"
#include "cstdlib"

#include <cmath>

class Combination_Data
{
public:
	Combination_Data();
	~Combination_Data();

	void Update();
	void Set_data(int, Te*, Te*);
	Te Next_probability();
	double LossRate(int);

	void debug();

private:
	int Add_data();
	int Losing_count();

	static const int MAXGAME = 75 - 1;
	static const int NUMMATCH = 5 - 1;

	int t;
	Te* myhistory;
	Te* rivalhistory;

	int*** comb;
	//����̑O�X��ƑO��̎�̑g�ݍ��킹
	int rivalcomb_history[3][3];
	//�����̑O�X��Ƒ���̑O��̎�̑g�ݍ��킹
	int mycomb_history[3][3];

	int losed_count;

	int count;
	int kaisu;
	double prob[3][3];
};

Combination_Data::Combination_Data()
{
	comb = new int** [(MAXGAME - 2) * NUMMATCH];
	for (int i = 0; i < (MAXGAME - 2) * NUMMATCH; i++)
	{
		comb[i] = new int* [3];
	}
	for (int i = 0; i < (MAXGAME - 2) * NUMMATCH; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			comb[i][j] = new int[3];
		}
	}

	for (int i = 0; i < (MAXGAME - 2) * NUMMATCH; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				comb[i][j][k] = 0;
			}
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{

		}
	}
	losed_count = 0;
	count = 0;
	kaisu = 0;
}

Combination_Data::~Combination_Data()
{
	for (int i = 0; i < (MAXGAME - 2) * NUMMATCH; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			delete[] comb[i][j];
		}
	}
	for (int i = 0; i < (MAXGAME - 2) * NUMMATCH; i++)
	{
		delete[] comb[i];
	}
	delete[] comb;
}

void Combination_Data::Update()
{
	Add_data();
	Losing_count();
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
	if (t >= 2)
	{
		rivalcomb_history[rivalhistory[t - 2]][rivalhistory[t - 1]]++;

		mycomb_history[myhistory[t - 2]][rivalhistory[t - 1]]++;

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
				}
			}
			count = 0;
			kaisu = 0;
		}
	}

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

double Combination_Data::LossRate(int start)
{
	if (count >= start)
	{
		return (double)losed_count / (count + 1);
	}
	return 1.0;
}

int Combination_Data::Losing_count()
{
	if (t >= 1)
	{
		if ((myhistory[t - 1] - rivalhistory[t - 1] + 3) % 3 == 1)
		{
			losed_count++;
		}
	}
	return losed_count;
}

void Combination_Data::debug()
{
	printf("count:%d kaisu:%d\n", count, kaisu);
}


double* softmax(const double* x, int i) {
	double* y = new double[i];
	double sum = 0, max = 0;

	for (int j = 0; j < i; j++)
	{
		if (x[j] >= max)
		{
			max = x[j];
		}
	}
	for (int j = 0; j < i; j++)
	{
		sum += exp(x[j] - max);
	}
	for (int j = 0; j < i; j++)
	{
		y[j] = exp(x[j] - max) / exp(sum);
	}

	return y;
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

	return cmb.LossRate(75 * 2) > 0.70 ? Te(rand() % 3) : cmb.Next_probability();
}

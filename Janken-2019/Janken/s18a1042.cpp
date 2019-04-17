//TODO このソースコードを参考に，自分の学籍番号.cppというファイルを作り，改造する．
#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"

#include <cmath>

class Combination_Data
{
public:
	Combination_Data();
	~Combination_Data();

	int Add_data(int t, const Te rivalhistory[]);
	int Next_probability();


private:
	static const int MAXGAME = 75;
	static const int NUMMATCH = 5;
	int*** comb;
	int sum_comb[3][3];
	int count;
	int kaisu;
	double prob[3][3];
};

Combination_Data::Combination_Data()
{
	comb = new int**[(MAXGAME - 2) * NUMMATCH];
	for (int i = 0; i < (MAXGAME - 2) * NUMMATCH; i++)
	{
		comb[i] = new int*[3];
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
	count = 0;
	kaisu = 1;
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

int Combination_Data::Add_data(int t, const Te rivalhistory[])
{
	if (t >= 2)
	{
		comb[(t - 2) * kaisu][rivalhistory[t - 2]][rivalhistory[t - 1]]++;
		sum_comb[rivalhistory[t - 2]][rivalhistory[t - 1]]++;
		count++;
	}
	if (t = MAXGAME)
	{
		kaisu++;
		if (kaisu == 6)
		{
			kaisu = 1;
		}
	}
	if (count == MAXGAME * NUMMATCH)
	{
		count = 0;
	}

	return 0;
}

int Combination_Data::Next_probability()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			prob[i][j] = sum_comb[i][j] / count;
		}
	}
	return 0;
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

double* Te_probability(int count, const Te rivalhistory[]) {
	double te_prob[3];

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < count - 1; j++)
		{
			if (rivalhistory[j] == i)
			{
				te_prob[i]++;
			}
		}
	}
	for (int i = 0; i < 3; i++)
	{
		te_prob[i] = te_prob[i] / count;
	}

	return te_prob;
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

// Te は Gu=0, Choki=1, Pa=2 という値を持つ enum 型
// 第一引数 i は１試合の中で現在何回目を示す．0からMAXKAISU-1までの値．
// 第二引数 myhistory は自分の手の履歴を示す．添字は0からMAXKAISU-1まで使えるが，0からi-1までの履歴しか信用出来ない．
// 第三引数 rivalhistory は相手の手の履歴を示す．添字は0からMAXKAISU-1まで使えるが，0からi-1までの履歴しか信用出来ない．
Te s18a1042(int i, Te myhistory[], Te rivalhistory[]) {
	static Combination_Data cmb;
	cmb.Add_data(i, rivalhistory);
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

	return Te(rand() % 3);
}

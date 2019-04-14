//TODO ���̃\�[�X�R�[�h���Q�l�ɁC�����̊w�Дԍ�.cpp�Ƃ����t�@�C�������C��������D
#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"

#include <cmath>

double softmax(Te target, const double* te_prob) {
	double te_denial[3];
	double sum = 0, max = 0;

	for (int i = 0; i < 3; i++)
	{
		te_denial[i] = 100 - te_prob[i];
		sum += te_denial[i];
		if (te_denial[i] >= max)
		{
			max = te_denial[i];
		}
	}

	return (exp(te_denial[target] - max)) / (exp(sum - max));
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

// Te �� Gu=0, Choki=1, Pa=2 �Ƃ����l������ enum �^
// ������ i �͂P�����̒��Ō��݉���ڂ������D0����MAXKAISU-1�܂ł̒l�D
// ������ myhistory �͎����̎�̗����������D�Y����0����MAXKAISU-1�܂Ŏg���邪�C0����i-1�܂ł̗��������M�p�o���Ȃ��D
// ��O���� rivalhistory �͑���̎�̗����������D�Y����0����MAXKAISU-1�܂Ŏg���邪�C0����i-1�܂ł̗��������M�p�o���Ȃ��D
Te s18a1042(int i, Te myhistory[], Te rivalhistory[]) {
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

	double *te_prob = Te_probability(i, rivalhistory);
	double next_Te[3];
	int next_Te_int[3];
	for (int i = 0; i < 3; i++)
	{
		next_Te[i] = softmax(Te(i), te_prob);
		next_Te_int[i] = int(next_Te[i] * 10000);
	}

	int te = rand() % 10000 + 1;
	if (1 <= te && te < next_Te_int[0])
	{
		return Gu;
	}
	else if (next_Te_int[0] <= te && te < next_Te_int[0] + next_Te_int[1])
	{
		return Choki;
	}
	else if (next_Te_int[0] + next_Te_int[1] <= te && te < next_Te_int[0] + next_Te_int[1] + next_Te_int[3])
	{
		return Pa;
	}
	else
	{
		return Te(rand() % 3);
	}
}

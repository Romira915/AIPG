//TODO このソースコードを参考に，自分の学籍番号.cppというファイルを作り，改造する．
#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"

// Te は Gu=0, Choki=1, Pa=2 という値を持つ enum 型
// 第一引数 i は１試合の中で現在何回目を示す．0からMAXKAISU-1までの値．
// 第二引数 myhistory は自分の手の履歴を示す．添字は0からMAXKAISU-1まで使えるが，0からi-1までの履歴しか信用出来ない．
// 第三引数 rivalhistory は相手の手の履歴を示す．添字は0からMAXKAISU-1まで使えるが，0からi-1までの履歴しか信用出来ない．
Te s00a0000(int i, Te myhistory[], Te rivalhistory[]) {
	switch (i) {
	case 0:
		return Gu;
	case 1:
		return Choki;
	case 2:
		return Pa;
	default:
		return (Te)((rivalhistory[i-1]+2)%3);
	}
}

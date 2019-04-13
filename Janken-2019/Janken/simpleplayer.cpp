#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"

Te simpleGu(int i, Te myhistory[], Te rivalhistory[]) {
	return Gu;
}

Te simpleChoki(int i, Te myhistory[], Te rivalhistory[]) {
	return Choki;
}

Te simplePa(int i, Te myhistory[], Te rivalhistory[]) {
	return Pa;
}

Te simpleRand(int i, Te myhistory[], Te rivalhistory[]) {
	return (Te)(rand()%3);
}

Te simpleWin4Pre(int i, Te myhistory[], Te rivalhistory[]) {
	if (i==0) {
		return (Te)(rand()%3);
	} else {
		return (Te)((rivalhistory[i-1]+2)%3);
	}
}

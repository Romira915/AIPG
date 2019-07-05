// janken.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

// TODO １試合（１セット）のじゃんけん回数を変更したい場合はこの値を変更する．
// 最後の評価で変更する可能性あり
int MAXKAISU = 75;

// TODO 同じ相手との試合回数（何セットマッチ）を変更したい場合はこの値を変更する．
// 最後の評価で変更する可能性あり
int NUMMATCH = 5;

// TODO プレイヤーを追加するには以下のs00a0000と同じよう３箇所追加すること．
extern Te s18a1042(int i, Te myhistory[], Te rivalhistory[]);
extern Te yamazawa(int i, Te myhistory[], Te rivalhistory[]);
extern Te simpleWin4Pre(int i, Te myhistory[], Te rivalhistory[]);
extern Te simpleRand(int i, Te myhistory[], Te rivalhistory[]);
extern Te simpleGu(int i, Te myhistory[], Te rivalhistory[]);
extern Te simpleChoki(int i, Te myhistory[], Te rivalhistory[]);
extern Te simplePa(int i, Te myhistory[], Te rivalhistory[]);

// 歴代の強い人
extern Te s18a1053(int i, Te myhistory[], Te rivalhistory[]);
extern Te s09a1007(int i, Te myhistory[], Te rivalhistory[]);
extern Te s12a2036(int i, Te myhistory[], Te rivalhistory[]);
extern Te s12a2070(int i, Te myhistory[], Te rivalhistory[]);
extern Te s12a1057(int i, Te myhistory[], Te rivalhistory[]);
extern Te s12a1069(int i, Te myhistory[], Te rivalhistory[]);
extern Te s13a1051(int i, Te myhistory[], Te rivalhistory[]);
extern Te s14a2026(int i, Te myhistory[], Te rivalhistory[]);
extern Te s14a2043(int i, Te myhistory[], Te rivalhistory[]);
extern Te s14a1003(int i, Te myhistory[], Te rivalhistory[]);
extern Te s14a1022(int i, Te myhistory[], Te rivalhistory[]);
extern Te s16a1041(int i, Te myhistory[], Te rivalhistory[]);

//昨年度の人
// 1限目のクラス
extern Te s16a1305(int i, Te myhistory[], Te rivalhistory[]);
extern Te s16a2302(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1001(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1003(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1006(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1007(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1008(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1009(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1010(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1011(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1012(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1013(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1016(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1017(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1019(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1020(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1021(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1024(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1025(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1027(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1028(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1029(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1032(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1034(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1035(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1037(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1038(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1039(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1040(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1043(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1044(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1046(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1047(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1048(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1049(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1050(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1051(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1052(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1053(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1055(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1056(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1057(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1058(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1059(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1060(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1061(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1062(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1063(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1064(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1065(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1066(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1068(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1070(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1072(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1073(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1074(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1075(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1076(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1077(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1078(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1079(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a1080(int i, Te myhistory[], Te rivalhistory[]);

// 2限目のクラス
extern Te s13a2029(int i, Te myhistory[], Te rivalhistory[]);
extern Te s16a1301(int i, Te myhistory[], Te rivalhistory[]);
extern Te s16a1303(int i, Te myhistory[], Te rivalhistory[]);
extern Te s16a2301(int i, Te myhistory[], Te rivalhistory[]);
extern Te s16a2304(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2001(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2002(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2003(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2004(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2005(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2006(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2007(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2008(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2009(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2010(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2011(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2012(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2014(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2015(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2017(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2018(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2019(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2020(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2022(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2023(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2024(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2025(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2026(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2027(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2028(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2029(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2030(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2031(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2032(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2033(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2034(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2035(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2036(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2037(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2038(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2039(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2040(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2041(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2042(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2043(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2044(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2046(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2047(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2048(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2050(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2052(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2053(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2055(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2056(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2057(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2058(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2060(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2062(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2063(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2065(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2066(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2069(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2070(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2071(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2076(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2077(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2078(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2079(int i, Te myhistory[], Te rivalhistory[]);
extern Te s17a2301(int i, Te myhistory[], Te rivalhistory[]);

static Te(*player[])(int i, Te myhistory[], Te rivalhistory[]) = {
	s18a1042,
	yamazawa,
	simpleWin4Pre,
	//	simpleRand,
	simpleGu,
	simpleChoki,
	simplePa,

	// 歴代の強い人
	s18a1053,
	s09a1007,
	s12a2036,
	s12a2070,
	s12a1057,
	s12a1069,
	s13a1051,
	s14a2026,
	s14a2043,
	s14a1003,
	s14a1022,
	s16a1041,

	// 昨年度の人
	// 1限目のクラス
	s16a1305,
	s16a2302,
	s17a1001,
	s17a1003,
	s17a1006,
	s17a1007,
	s17a1008,
	s17a1009,
	s17a1010,
	s17a1011,
	s17a1012,
	s17a1013,
	s17a1016,
	s17a1017,
	s17a1019,
	s17a1020,
	s17a1021,
	s17a1024,
	s17a1025,
	s17a1027,
	s17a1028,
	s17a1029,
	s17a1032,
	s17a1034,
	s17a1035,
	s17a1037,
	s17a1038,
	s17a1039,
	s17a1040,
	s17a1043,
	s17a1044,
	s17a1046,
	s17a1047,
	s17a1048,
	s17a1049,
	s17a1050,
	s17a1051,
	s17a1052,
	s17a1053,
	s17a1055,
	s17a1056,
	s17a1057,
	s17a1058,
	s17a1059,
	s17a1060,
	s17a1061,
	s17a1062,
	s17a1063,
	s17a1064,
	s17a1065,
	s17a1066,
	s17a1068,
	s17a1070,
	s17a1072,
	s17a1073,
	s17a1074,
	s17a1075,
	s17a1076,
	s17a1077,
	s17a1078,
	s17a1079,
	s17a1080,

	// 2限目のクラス
	s13a2029,
	s16a1301,
	s16a1303,
	s16a2301,
	s16a2304,
	s17a2001,
	s17a2002,
	s17a2003,
	s17a2004,
	s17a2005,
	s17a2006,
	s17a2007,
	s17a2008,
	s17a2009,
	s17a2010,
	s17a2011,
	s17a2012,
	s17a2014,
	s17a2015,
	s17a2017,
	s17a2018,
	s17a2019,
	s17a2020,
	s17a2022,
	s17a2023,
	s17a2024,
	s17a2025,
	s17a2026,
	s17a2027,
	s17a2028,
	s17a2029,
	s17a2030,
	s17a2031,
	s17a2032,
	s17a2033,
	s17a2034,
	s17a2035,
	s17a2036,
	s17a2037,
	s17a2038,
	s17a2039,
	s17a2040,
	s17a2041,
	s17a2042,
	s17a2043,
	s17a2044,
	s17a2046,
	s17a2047,
	s17a2048,
	s17a2050,
	s17a2052,
	s17a2053,
	s17a2055,
	s17a2056,
	s17a2057,
	s17a2058,
	s17a2060,
	s17a2062,
	s17a2063,
	s17a2065,
	s17a2066,
	s17a2069,
	s17a2070,
	s17a2071,
	s17a2076,
	s17a2077,
	s17a2078,
	s17a2079,
	s17a2301,
};

static char *playername[] = {
	"s18a1042",
	"yamazawa",
	"Win4Pre",
	//	"Rand",
	"Gu",
	"Choki",
	"Pa",

	// 歴代の強い人
	"s18a1053",
	"s09a1007",
	"s12a2036",
	"s12a2070",
	"s12a1057",
	"s12a1069",
	"s13a1051",
	"s14a2026",
	"s14a2043",
	"s14a1003",
	"s14a1022",
	"s16a1041",

	// 昨年度の人
	// 1限目のクラス
	"s16a1305",
	"s16a2302",
	"s17a1001",
	"s17a1003",
	"s17a1006",
	"s17a1007",
	"s17a1008",
	"s17a1009",
	"s17a1010",
	"s17a1011",
	"s17a1012",
	"s17a1013",
	"s17a1016",
	"s17a1017",
	"s17a1019",
	"s17a1020",
	"s17a1021",
	"s17a1024",
	"s17a1025",
	"s17a1027",
	"s17a1028",
	"s17a1029",
	"s17a1032",
	"s17a1034",
	"s17a1035",
	"s17a1037",
	"s17a1038",
	"s17a1039",
	"s17a1040",
	"s17a1043",
	"s17a1044",
	"s17a1046",
	"s17a1047",
	"s17a1048",
	"s17a1049",
	"s17a1050",
	"s17a1051",
	"s17a1052",
	"s17a1053",
	"s17a1055",
	"s17a1056",
	"s17a1057",
	"s17a1058",
	"s17a1059",
	"s17a1060",
	"s17a1061",
	"s17a1062",
	"s17a1063",
	"s17a1064",
	"s17a1065",
	"s17a1066",
	"s17a1068",
	"s17a1070",
	"s17a1072",
	"s17a1073",
	"s17a1074",
	"s17a1075",
	"s17a1076",
	"s17a1077",
	"s17a1078",
	"s17a1079",
	"s17a1080",

	// 2限目のクラス
	"s13a2029",
	"s16a1301",
	"s16a1303",
	"s16a2301",
	"s16a2304",
	"s17a2001",
	"s17a2002",
	"s17a2003",
	"s17a2004",
	"s17a2005",
	"s17a2006",
	"s17a2007",
	"s17a2008",
	"s17a2009",
	"s17a2010",
	"s17a2011",
	"s17a2012",
	"s17a2014",
	"s17a2015",
	"s17a2017",
	"s17a2018",
	"s17a2019",
	"s17a2020",
	"s17a2022",
	"s17a2023",
	"s17a2024",
	"s17a2025",
	"s17a2026",
	"s17a2027",
	"s17a2028",
	"s17a2029",
	"s17a2030",
	"s17a2031",
	"s17a2032",
	"s17a2033",
	"s17a2034",
	"s17a2035",
	"s17a2036",
	"s17a2037",
	"s17a2038",
	"s17a2039",
	"s17a2040",
	"s17a2041",
	"s17a2042",
	"s17a2043",
	"s17a2044",
	"s17a2046",
	"s17a2047",
	"s17a2048",
	"s17a2050",
	"s17a2052",
	"s17a2053",
	"s17a2055",
	"s17a2056",
	"s17a2057",
	"s17a2058",
	"s17a2060",
	"s17a2062",
	"s17a2063",
	"s17a2065",
	"s17a2066",
	"s17a2069",
	"s17a2070",
	"s17a2071",
	"s17a2076",
	"s17a2077",
	"s17a2078",
	"s17a2079",
	"s17a2301",
};

char strTe[] = { 'G', 'C', 'P' };

int checkTe(Te t) {
	return (Gu <= t && t <= Pa);
}

int _tmain(int argc, _TCHAR* argv[])
{
	int numofplayer = sizeof(player) / sizeof(player[0]);
	Te(*player1)(int i, Te myhistory[], Te rivalhistory[]);
	Te(*player2)(int i, Te myhistory[], Te rivalhistory[]);
	Te *history1 = (Te*)malloc(sizeof(Te) * MAXKAISU);
	Te *history2 = (Te*)malloc(sizeof(Te) * MAXKAISU);
	Te *history1copy = (Te*)malloc(sizeof(Te) * MAXKAISU);
	Te *history2copy = (Te*)malloc(sizeof(Te) * MAXKAISU);
	int *history3 = (int*)malloc(sizeof(int) * MAXKAISU);
	int *point = (int*)malloc(sizeof(int) * numofplayer);
	int *result = (int*)malloc(sizeof(int) * numofplayer * numofplayer);
	int i, j, k, l, m, win1, win2, draw, pwin1, pwin2, pdraw;
	FILE *fp1, *fp2, *fperr;

	/* initialize */
	srand((unsigned int)time(NULL));
	for (i = 0; i < numofplayer; i++) {
		point[i] = 0; /* clear point */
	}
	if (0 != fopen_s(&fp1, "jresult-detail.csv", "w")) {
		fprintf(stderr, "Cannot open jresult.csv\n");
		return -1;
	}
	if (0 != fopen_s(&fp2, "jresult.csv", "w")) {
		fprintf(stderr, "Cannot open jresult.csv\n");
		return -1;
	}
	if (0 != fopen_s(&fperr, "jerror.txt", "w")) {
		fprintf(stderr, "Cannot open jerror.txt\n");
		return -1;
	}

	/* make a league */
	for (i = 0; i < numofplayer; i++) {
		printf("%s vs *\n", playername[i]);
		for (j = 0; j < numofplayer; j++) {
			/* initialize a match */
			player1 = player[i];
			player2 = player[j];
			result[i*numofplayer + j] = 0;
			if (i == j) continue;
			win1 = win2 = draw = 0;

			/* make (5) matches */
			for (l = 0; l < NUMMATCH; l++) {
				for (k = 0; k < MAXKAISU; k++) {
					history1[k] = Gu;
					history2[k] = Gu;
				}
				pwin1 = win1;
				pwin2 = win2;
				pdraw = draw;

				/* make a match */
				for (k = 0; k < MAXKAISU; k++) {
					for (m = 0; m < k; m++) {
						history1copy[m] = history1[m];
						history2copy[m] = history2[m];
					}
					Te t1 = (*player1)(k, history1copy, history2copy);
					if (!checkTe(t1)) {
						fprintf(stderr, "%s has inccorect Te:%d\n", playername[i], t1);
						fprintf(fperr, "%s has inccorect Te:%d\n", playername[i], t1);
					}
					for (m = 0; m < k; m++) {
						history1copy[m] = history1[m];
						history2copy[m] = history2[m];
					}
					Te t2 = (*player2)(k, history2copy, history1copy);
					if (!checkTe(t2)) {
						fprintf(stderr, "%s has inccorect Te:%d\n", playername[j], t2);
						fprintf(fperr, "%s has inccorect Te:%d\n", playername[j], t2);
					}
					if ((!checkTe(t1) && !checkTe(t2)) || t1 == t2) {
						draw++; /* even */
						history3[k] = 0;
					} else if (!checkTe(t2) || (checkTe(t1) && (t1 == t2 - 1 || (t1 == Pa && t2 == Gu)))) {
						win1++; /* player1 wins */
						history3[k] = 1;
					} else {
						win2++; /* player2 wins */
						history3[k] = 2;
					}
					history1[k] = (Te)((t1 % 3 + 3) % 3);
					history2[k] = (Te)((t2 % 3 + 3) % 3);
				}

				/* output a result of the match */
				//printf("%s vs %s\n", playername[i], playername[j]);
				fprintf(fp1, "%s,vs,%s", playername[i], playername[j]);
				fprintf(fp1, "\n");
				/* player1 */
				//printf("%2d ", win1-pwin1);
				fprintf(fp1, "%d,", win1 - pwin1);
				for (k = 0; k < MAXKAISU; k++) {
					//printf("%c", strTe[history1[k]]);
					fprintf(fp1, "%c,", strTe[history1[k]]);
				}
				//printf("\n");
				fprintf(fp1, "\n");
				/* player2 */
				//printf("%2d ", win2-pwin2);
				fprintf(fp1, "%d,", win2 - pwin2);
				for (k = 0; k < MAXKAISU; k++) {
					//printf("%c", strTe[history2[k]]);
					fprintf(fp1, "%c,", strTe[history2[k]]);
				}
				//printf("\n");
				fprintf(fp1, "\n");
				/* result and num of even */
				//printf("%2d ", draw-pdraw);
				fprintf(fp1, "%d,", draw - pdraw);
				for (k = 0; k < MAXKAISU; k++) {
					//printf("%d", history3[k]);
					fprintf(fp1, "%d,", history3[k]);
				}
				//printf("\n");
				fprintf(fp1, "\n");
				//printf("\n");
				fprintf(fp1, "\n");
			}

			result[i*numofplayer + j] = win1 - win2;
			point[i] += win1 - win2;
			point[j] += win2 - win1;
		}
	}

	/* show results */
	// printf("  Name  : Sum ,Detail\n");
	fprintf(fp2, "Name,Points,Sum");
	for (i = 0; i < numofplayer; i++) {
		fprintf(fp2, ",%s", playername[i]);
	}
	fprintf(fp2, "\n");
	for (i = 0; i < numofplayer; i++) {
		// printf("%8s:%+5d ", playername[i], point[i]);
		fprintf(fp2, "%s,\"=IF(C%d>=0,C%d/C$3*15+25,25-C%d/C$4*15)\",%d", playername[i], i + 2, i + 2, i + 2, point[i]);
		for (j = 0; j < numofplayer; j++) {
			// printf(",%+4d", result[i*numofplayer + j]);
			fprintf(fp2, ",%d", result[i*numofplayer + j]);
		}
		//printf("\n");
		fprintf(fp2, "\n");
	}

	free(history1);
	free(history2);
	free(point);
	free(result);
	fclose(fp1);
	fclose(fp2);
	fclose(fperr);
	printf("Hit Enter Key\n");
	getchar();
	return 0;
}


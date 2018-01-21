#include "stdafx.h"
#include <math.h>

int main()
{
	// 次の値の偏差値を求めよ
	const int N = 100;
	int value[N] = {
		74, 83, 60,  3, 23,  9, 90, 28, 46, 88,
		10, 26, 42, 98,  1, 58, 20, 36, 82, 77,
		34, 63, 41,  7,  4, 88, 10, 61,  3, 92,
		 7, 94, 55, 38, 26,  7, 61,  2, 87, 30,
		33, 67, 17, 71, 80, 73, 56, 56,	38, 38,
		21, 81, 66,  1, 79, 89, 58, 11, 34, 48,
		32, 36, 48, 21, 37, 40, 96, 23, 35, 94,
		83, 54, 43, 54, 22, 13,  9, 17, 38, 32,
		66, 96, 78, 36, 66, 67, 72, 12, 35, 36,
		52, 86, 84, 90, 98, 55, 10, 80,  8, 53,
	};

	int std_score[N];// 偏差値を格納する

	// 平均、分散を求める
	double mean = 0.0;
	double standard_deviation = 0.0;
	for (int i = 0; i < N; i++) {
		double score = (double)value[i];
		mean += score;
		standard_deviation += score * score;
	}
	mean /= (double)N;
	standard_deviation = sqrt(standard_deviation / (double)N - mean * mean);

	// 偏差値を求める
	#pragma omp parallel for
	for (int i = 0; i < N; i++) {
		std_score[i] = (int)(10.0 * ((double)value[i] - mean) / standard_deviation) + 50;
	}

	// 表示
	printf_s("mean:%lf\n", mean);
	printf_s("standard deviation:%lf\n", standard_deviation);

	for (int i = 0; i < N; i++) {
		printf_s("%d:%d\n", i, std_score[i]);
	}

    return 0;
}


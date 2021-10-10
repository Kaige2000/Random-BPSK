#pragma once
#include <stdio.h>
#include <malloc.h>
#include "myFunctions.h"


//N位移位寄存器
void SR(int p[], int N, int fn) {
	for (int i = N - 1; i > 0; i--) {
		p[i] = p[i - 1];
	}
	p[0] = fn;
}

//获取fn
int get_fn(int B[]) {
	int fn = 0;
	/*不再以数组的形式计算
	int G[10] = {0,0,1,0,0,0,0,0,0,1};*/
	fn = (B[2] + B[9]) % 2;
	//printf("%d", fn);
	return fn;
}

//生成长度为N的伪噪声序列
int* FN_Sequence(int N) {
	static int* Fn;  // 数组指针

	// 动态分配内存空间
	Fn = (int*)malloc(N * sizeof(int));

	//初始值
	int B[10] = { 0,0,0,0,0,0,0,0,0,1 };
	Print_array(B, 10);
	int fn;

	for (int i = 0; i < N; i++) {
		fn = get_fn(B);
		printf("第%d个fn是%d\n\n", i+1, fn);
		
		SR(B, 10, fn);
		Print_array(B, 10);

		Fn[i] = 2* fn - 1 ;
	}
	return Fn;
}

//把FN序列写入txt文件
int FN2txt(int N) {
	FILE* fp;//文件指针
	fp = fopen(".\\data\\FNdata.txt", "w");

	int* p;
	p = FN_Sequence(N);

	for (int i = 0; i < N; i++){
	    fprintf(fp, "%d\n", *(p + i));
	}
	fclose(fp);
}

//计算第m点对应的自相关函数值
int AutoCorrelation(int FN_Sequence[], int m, int N){
	int r = 0;
	for (int i = m; i < N; i++){
		r += FN_Sequence[i] * FN_Sequence[i - m];
	}
	return  r;
}

//得到全部自相关对应的函数值并写入文件
void AutoCorrelation_Y(int N) {
	static int* Fn_;  // 数组指针
	Fn_ = FN_Sequence(N);
	FN2txt(N);

	static int* FN_Y;
	FN_Y = (int*)malloc(N * sizeof(int));

	FILE* fp;//文件指针
	fp = fopen(".\\data\\FN_Y.txt", "w");

	for (int i = 0; i < N; i++) {
		FN_Y[i ]=AutoCorrelation(Fn_,i, N);
		fprintf(fp, "%d\n", FN_Y[i]);
	}
}
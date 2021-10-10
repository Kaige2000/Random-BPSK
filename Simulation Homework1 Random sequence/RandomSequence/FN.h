#pragma once
#include <stdio.h>
#include <malloc.h>
#include "myFunctions.h"


//Nλ��λ�Ĵ���
void SR(int p[], int N, int fn) {
	for (int i = N - 1; i > 0; i--) {
		p[i] = p[i - 1];
	}
	p[0] = fn;
}

//��ȡfn
int get_fn(int B[]) {
	int fn = 0;
	/*�������������ʽ����
	int G[10] = {0,0,1,0,0,0,0,0,0,1};*/
	fn = (B[2] + B[9]) % 2;
	//printf("%d", fn);
	return fn;
}

//���ɳ���ΪN��α��������
int* FN_Sequence(int N) {
	static int* Fn;  // ����ָ��

	// ��̬�����ڴ�ռ�
	Fn = (int*)malloc(N * sizeof(int));

	//��ʼֵ
	int B[10] = { 0,0,0,0,0,0,0,0,0,1 };
	Print_array(B, 10);
	int fn;

	for (int i = 0; i < N; i++) {
		fn = get_fn(B);
		printf("��%d��fn��%d\n\n", i+1, fn);
		
		SR(B, 10, fn);
		Print_array(B, 10);

		Fn[i] = 2* fn - 1 ;
	}
	return Fn;
}

//��FN����д��txt�ļ�
int FN2txt(int N) {
	FILE* fp;//�ļ�ָ��
	fp = fopen(".\\data\\FNdata.txt", "w");

	int* p;
	p = FN_Sequence(N);

	for (int i = 0; i < N; i++){
	    fprintf(fp, "%d\n", *(p + i));
	}
	fclose(fp);
}

//�����m���Ӧ������غ���ֵ
int AutoCorrelation(int FN_Sequence[], int m, int N){
	int r = 0;
	for (int i = m; i < N; i++){
		r += FN_Sequence[i] * FN_Sequence[i - m];
	}
	return  r;
}

//�õ�ȫ������ض�Ӧ�ĺ���ֵ��д���ļ�
void AutoCorrelation_Y(int N) {
	static int* Fn_;  // ����ָ��
	Fn_ = FN_Sequence(N);
	FN2txt(N);

	static int* FN_Y;
	FN_Y = (int*)malloc(N * sizeof(int));

	FILE* fp;//�ļ�ָ��
	fp = fopen(".\\data\\FN_Y.txt", "w");

	for (int i = 0; i < N; i++) {
		FN_Y[i ]=AutoCorrelation(Fn_,i, N);
		fprintf(fp, "%d\n", FN_Y[i]);
	}
}
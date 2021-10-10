#pragma once
#include <malloc.h>
#include <math.h>
#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS 
#pragma warning(disable : 4996)

//���ɳ���ΪN���ڣ�0��1��֮����ȷֲ����������(W-L�㷨)
float * get_UDS(float x, float y, float z,int N) {
	//printf("�������鳤�ȣ�");
	//scanf("%d", &N);

	static float* UDS;  // ����ָ��

	// ��̬�����ڴ�ռ�
	UDS = (float*)malloc(N * sizeof(float));
	if (!UDS) {
		printf("��������ʧ�ܣ�\n");
	}
	//ʹ��w-l�㷨����
	int i; //ÿһ��������±�
	for (i = 0; i < N; i++)
	{
		UDS[i] = fmod((x / 30269 + y / 30307 + z / 30323), 1);//��1ȡģ
		//printf("%f\n", UDS[i]);
		x = fmod(171 * x, 30269);
		y = fmod(170 * y, 30307);
		z = fmod(172 * z, 30323);
	}
	return UDS;
}

//�Ѿ������������txt�ļ�
void UDS2txt(int N) {
	FILE* fp;//�ļ�ָ��
	fp = fopen("USDdata.txt", "w");

	float* p1;
	p1 = get_UDS(1,2,3,N);

	for (int i = 0; i < N; i++)
	{
		fprintf(fp, "%f\n", *(p1 + i));}
	fclose(fp);
}
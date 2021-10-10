#pragma once
#include <malloc.h>
#include <math.h>
#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS 
#pragma warning(disable : 4996)

//生成长度为N的在（0，1）之间均匀分布的随机变量(W-L算法)
float * get_UDS(float x, float y, float z,int N) {
	//printf("输入数组长度：");
	//scanf("%d", &N);

	static float* UDS;  // 数组指针

	// 动态分配内存空间
	UDS = (float*)malloc(N * sizeof(float));
	if (!UDS) {
		printf("创建数组失败！\n");
	}
	//使用w-l算法迭代
	int i; //每一个数组的下标
	for (i = 0; i < N; i++)
	{
		UDS[i] = fmod((x / 30269 + y / 30307 + z / 30323), 1);//对1取模
		//printf("%f\n", UDS[i]);
		x = fmod(171 * x, 30269);
		y = fmod(170 * y, 30307);
		z = fmod(172 * z, 30323);
	}
	return UDS;
}

//把均匀随机数存入txt文件
void UDS2txt(int N) {
	FILE* fp;//文件指针
	fp = fopen("USDdata.txt", "w");

	float* p1;
	p1 = get_UDS(1,2,3,N);

	for (int i = 0; i < N; i++)
	{
		fprintf(fp, "%f\n", *(p1 + i));}
	fclose(fp);
}
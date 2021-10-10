#pragma once
#include <stdio.h>
#include <malloc.h>
#include "myFunctions.h"
#include <stdlib.h>
#include "GD.h"

//生成长度为N的离散信源
int* get_DS(int N) {
	static int* DS;  // 数组指针

	// 动态分配内存空间
	DS = (int*)malloc(N * sizeof(int));
	if (!DS) {
		printf("创建数组失败！\n");
	}
	for (int i = 0; i < N; i++) {
		DS[i] = rand() % 2;
	}
	return DS;
}

//进行BPSK调制
int* BPSK_DS(int DS[],int N) {
	for (int i = 0; i < N; i++) {
		if (DS[i] < 0.5) {
			DS[i] = -1;//这里调制门限设置为0.5，以应对C语言float精度问题
		}
	}
	return DS;
}

//模拟信道，1为高斯信道，2为衰落信道
float *Channel(float coding[], float N[], int length,int style) {
	float* receive_coding;
	receive_coding = (float*)malloc(length * sizeof(float));

	if (!receive_coding) {
		printf("创建数组失败！\n");
		exit(1);
	}
	for (int i = 0; i < length; i++) {
		if (style == 1) {
			receive_coding[i] = coding[i] + N[i];
			//printf("%f\n", receive_coding[i]);
		}		
		if (style == 2) {
			receive_coding[i] = coding[i] * N[i];
			//printf("%f\n", receive_coding[i]);
		}
	}
	return receive_coding;
}

//重写衰落信道
float *Rayleigh_Channel(int coding[],float r[],int length){
	float* receive_coding1;
	receive_coding1 = (float*)malloc(length * sizeof(float));

	if (!receive_coding1) {
		printf("创建数组失败！\n");
		exit(1);
	}

	for (int i = 0; i < length; i++) {
        receive_coding1[i] = coding[i] * r[i] * 1/sqrt(2) ;
		}
	return receive_coding1;
}


//高斯噪声修正函数
float *GN_adjust(float GN[], int N, float SNR_dB) {
	float Eb = 1;//能量为1
	float SNR;
	SNR = pow(10, SNR_dB / 10); //分贝单位换算

	float N0 = Eb / SNR; //获取噪声功率
	printf("噪声功率为%f\n",N0);
	float sigma = sqrt(0.5 * N0); //获取高斯噪声方差

	for (int i = 0; i < N; i++) {
		*(GN + i) = *(GN + i) * sigma;// sigma * N(0,1)~N(0,sigma^2)
	}
	return GN;
}

//判决
int* judge(float receive_coding[], int N) {
	static int* result;  // 数组指针

	// 动态分配内存空间
	result = (int*)malloc(N * sizeof(int));
	if (!result) {
		printf("创建数组失败！\n");
		exit(1);
	}

	for (int i = 0; i < N; i++) {
		if (receive_coding[i] > 0) {
			result[i] = 1;
		}
		if (receive_coding[i] <= 0) {
			result[i] = 0;}
	}
	return result;
}

//计算误码率
float BER(int S[], int R[], int N) {
	int error = 0;
	for (int i = 0; i < N; i++) {
		if (S[i] != R[i]){
			error += 1;
		}
	}
	return (float)error / (float)N;
}

//BPSK仿真主程序，对长度为N的信源做仿真
float BPSK_main(int N,int SNR_dB) {

	//产生离散信源并存入数组
	int* S;
	S = get_DS(N);
	static int* SS;  
	SS = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < N; i++) {
		SS[i] = *(S + i);
	}

	//调制
	int* send_coding;
	send_coding = BPSK_DS(S, N);

	//产生服从标准正态分布的高斯噪声
	float* GN_standard;
	GN_standard = US_GRS(N);

	//产生服从瑞利分布的衰减系数
	float* Rayleigh;
	Rayleigh = Rayleigh_RS(N);


	//根据信噪比对高斯噪声进行修正
	float* GN;
	GN = GN_adjust(GN_standard, N, SNR_dB);

	//经过衰落信道
	float* receive_coding1;
	receive_coding1 = Rayleigh_Channel(send_coding, Rayleigh, N);

	//经过高斯信道
	float* receive_coding;
	receive_coding = Channel(receive_coding1, GN, N ,1);

	//判决
	int* result;
	result = judge(receive_coding,N);

	//获取误码率
	float ber;
	ber = BER(SS, result, N);
	printf("误码率为%f\n\n", ber);
	return ber;
}
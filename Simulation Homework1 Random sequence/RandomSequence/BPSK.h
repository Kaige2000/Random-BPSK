#pragma once
#include <stdio.h>
#include <malloc.h>
#include "myFunctions.h"
#include <stdlib.h>
#include "GD.h"

//���ɳ���ΪN����ɢ��Դ
int* get_DS(int N) {
	static int* DS;  // ����ָ��

	// ��̬�����ڴ�ռ�
	DS = (int*)malloc(N * sizeof(int));
	if (!DS) {
		printf("��������ʧ�ܣ�\n");
	}
	for (int i = 0; i < N; i++) {
		DS[i] = rand() % 2;
	}
	return DS;
}

//����BPSK����
int* BPSK_DS(int DS[],int N) {
	for (int i = 0; i < N; i++) {
		if (DS[i] < 0.5) {
			DS[i] = -1;//���������������Ϊ0.5����Ӧ��C����float��������
		}
	}
	return DS;
}

//ģ���ŵ���1Ϊ��˹�ŵ���2Ϊ˥���ŵ�
float *Channel(float coding[], float N[], int length,int style) {
	float* receive_coding;
	receive_coding = (float*)malloc(length * sizeof(float));

	if (!receive_coding) {
		printf("��������ʧ�ܣ�\n");
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

//��д˥���ŵ�
float *Rayleigh_Channel(int coding[],float r[],int length){
	float* receive_coding1;
	receive_coding1 = (float*)malloc(length * sizeof(float));

	if (!receive_coding1) {
		printf("��������ʧ�ܣ�\n");
		exit(1);
	}

	for (int i = 0; i < length; i++) {
        receive_coding1[i] = coding[i] * r[i] * 1/sqrt(2) ;
		}
	return receive_coding1;
}


//��˹������������
float *GN_adjust(float GN[], int N, float SNR_dB) {
	float Eb = 1;//����Ϊ1
	float SNR;
	SNR = pow(10, SNR_dB / 10); //�ֱ���λ����

	float N0 = Eb / SNR; //��ȡ��������
	printf("��������Ϊ%f\n",N0);
	float sigma = sqrt(0.5 * N0); //��ȡ��˹��������

	for (int i = 0; i < N; i++) {
		*(GN + i) = *(GN + i) * sigma;// sigma * N(0,1)~N(0,sigma^2)
	}
	return GN;
}

//�о�
int* judge(float receive_coding[], int N) {
	static int* result;  // ����ָ��

	// ��̬�����ڴ�ռ�
	result = (int*)malloc(N * sizeof(int));
	if (!result) {
		printf("��������ʧ�ܣ�\n");
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

//����������
float BER(int S[], int R[], int N) {
	int error = 0;
	for (int i = 0; i < N; i++) {
		if (S[i] != R[i]){
			error += 1;
		}
	}
	return (float)error / (float)N;
}

//BPSK���������򣬶Գ���ΪN����Դ������
float BPSK_main(int N,int SNR_dB) {

	//������ɢ��Դ����������
	int* S;
	S = get_DS(N);
	static int* SS;  
	SS = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < N; i++) {
		SS[i] = *(S + i);
	}

	//����
	int* send_coding;
	send_coding = BPSK_DS(S, N);

	//�������ӱ�׼��̬�ֲ��ĸ�˹����
	float* GN_standard;
	GN_standard = US_GRS(N);

	//�������������ֲ���˥��ϵ��
	float* Rayleigh;
	Rayleigh = Rayleigh_RS(N);


	//��������ȶԸ�˹������������
	float* GN;
	GN = GN_adjust(GN_standard, N, SNR_dB);

	//����˥���ŵ�
	float* receive_coding1;
	receive_coding1 = Rayleigh_Channel(send_coding, Rayleigh, N);

	//������˹�ŵ�
	float* receive_coding;
	receive_coding = Channel(receive_coding1, GN, N ,1);

	//�о�
	int* result;
	result = judge(receive_coding,N);

	//��ȡ������
	float ber;
	ber = BER(SS, result, N);
	printf("������Ϊ%f\n\n", ber);
	return ber;
}
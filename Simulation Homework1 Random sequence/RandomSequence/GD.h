#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "UD.h"
#include<math.h>
#define PI 3.1415926


//ʹ�þ�����ͷ�����N����ֵΪ0������Ϊ1��˹�����
float *US_GRS(int N) {

    static float* GRS1;  // ����ָ��
    static float* UD1;  // ����ָ��

// ��̬�����ڴ�ռ�
    GRS1 = (float*)malloc(N * sizeof(float));
    UD1 = (float*)malloc(12*N * sizeof(float));
    if (!GRS1) {
        printf("��������ʧ�ܣ�\n");
    }
    //ʹ��w-l�㷨����


    //����12N����0,1)֮��������
    float* p;
    p = get_UDS(1,2,3,12*N);
    for (int i = 0; i < 12 * N; i++) {
        UD1[i] =  *(p + i);
        //printf("%f\n", UD1[i]);

    }

    int i; //ÿһ��������±�
    //ÿ12���������ͣ������µ������
    for (i = 0; i < 12 * N; i = i + 12){
        GRS1[i / 12] = -6;//ʹ��ֵΪ0
        for (int j = i; j < i + 12; j++){
            GRS1[i/12] += UD1[j];
        }
        //printf("%f ", GRS1[i / 12]);
        //printf("\n");
    }
    return GRS1;
}
//����txt�ļ�
void USGRS2txt(int N) {
    FILE* fp;//�ļ�ָ��
    fp = fopen("USGRSdata.txt", "w");

    float*p;
    p = US_GRS(N);

    for (int i = 0; i < N; i++)
    {
        fprintf(fp, "%f\n", *(p + i));
    }
    fclose(fp);
}

//ʹ��Box-Muller�㷨���ɷ��ӱ�׼�ֲ��ĸ�˹�����
float *BM_GRS(int N) {

    static float* GRS2;  // ����ָ��
    static float* UD1;  // ����ָ��
    static float* UD2;  // ����ָ��
    //static float* X;  // ����ָ��
    //static float* Y;  // ����ָ��
    static float* XY;  // ����ָ�룬�±�ΪżX���±�Ϊ��Y

// ��̬�����ڴ�ռ�
    GRS2 = (float*)malloc(N * sizeof(float));
    UD1 = (float*)malloc( N * sizeof(float));
    UD2 = (float*)malloc(N * sizeof(float));
    //X = (float*)malloc(N * sizeof(float));
    //Y = (float*)malloc(N * sizeof(float));
     XY = (float*)malloc( N * sizeof(float));


    if (!GRS2) {
        printf("��������ʧ�ܣ�\n");
    }
    //ʹ��w-l�㷨����


    //�ֱ�����N�������������UD1��UD2��
    float* p1;
    float* p2;
    p1 = get_UDS(1, 2, 3, N);
    p2 = get_UDS(4, 5, 6, N);
    for (int i = 0; i < N; i++) {
        UD1[i] = (*(p1 + i));
        UD2[i] = (*(p2 + i));
    }

    int i; //ÿһ��������±�
    for (i = 0; i <  N; i = i + 2) {
        //ʹ��һ�����鷵�أ�
        XY[i] = sqrt(-2 * log(UD1[i])) * cos((2 * PI * UD2[i]));       
        XY[i + 1] = sqrt(-2 * log(UD2[i])) * sin((2 * PI * UD1[i]));
        printf("%f\t", XY[i]);
        printf("%f\n", XY[i+1]);
    }
    return XY;
}
//����txt�ļ�
void BMGRS2txt(int N) {
    FILE* fpX;//�ļ�ָ��
    FILE* fpY;//�ļ�ָ��
    fpX = fopen("BMGRSdataX.txt", "w");
    fpY = fopen("BMGRSdataY.txt", "w");

    float* p;
    p = BM_GRS(N);

    for (int i = 0; i <N; i = i + 2)
    {
        fprintf(fpX, "%f\n", *(p + i));
        fprintf(fpY, "%f\n", *(p + i + 1));

    }
    fclose(fpX);
    fclose(fpY);
}

//ʹ��polar method�����ɸ�˹�����
float *PM_GRS(int N) {
    static float* UD1_for_PM;  
    static float* UD2_for_PM;  
    static float* V1;
    static float* V2;
 
    static float* XY_for_PM;  // ����ָ�룬�±�ΪżX���±�Ϊ��Y

    // ��̬�����ڴ�ռ�
    UD1_for_PM = (float*)malloc(N * sizeof(float));
    UD2_for_PM = (float*)malloc(N * sizeof(float));
    V1 = (float*)malloc(N * sizeof(float));
    V2 = (float*)malloc(N * sizeof(float));

    XY_for_PM = (float*)malloc(N * sizeof(float));

    //�ֱ�����N�������������UD1��UD2��
    float* p1;
    float* p2;
    p1 = get_UDS(1, 2, 3, N);
    p2 = get_UDS(4, 5, 6, N);


    int j = 1;
    for (int i = 0; i < N; i++) {
        UD1_for_PM[i] = (*(p1 + i));
        UD2_for_PM[i] = (*(p2 + i));  

        V1[i] = 2 * UD1_for_PM[i] - 1;
        V2[i] = 2 * UD2_for_PM[i] - 1;
        printf("%f\n", V1[i]);
        printf("%f\n", V2[i]);

        float S;
        S= sqrt(V1[i] * V1[i] + V2[i] * V2[i]);
        printf("SΪ%f\n", S);
        if (S >= 1) {
            printf("����\n\n");
            continue;  
        }


        float AS;
        AS= sqrt(-2 * log(S) / S);
        printf("ASΪ%f\n", AS);

        XY_for_PM[j] = AS * V1[i];

        printf("�������%f\n\n", XY_for_PM[j]);

        XY_for_PM[j+1] = AS * V2[i];
        j = j + 2;
    }
    XY_for_PM[0] = j;//�׵�ַ�洢���������
    return XY_for_PM;
}
//����txt�ļ�
void PMGRS2txt(int N) {
    FILE* fpX;//�ļ�ָ��
    FILE* fpY;//�ļ�ָ��
    fpX = fopen(".\\data\\PMGRSdataX.txt", "w");
    fpY = fopen(".\\data\\PMGRSdataY.txt", "w");

    float* p;
    p = PM_GRS(N);
    int N_real = *p;//ʵ�����ɵĸ�˹���������

    for (int i = 1; i < N_real; i = i + 2)
    {
        fprintf(fpX, "%f\n", *(p + i));
        fprintf(fpY, "%f\n", *(p + i + 1));
    }
    printf("�ܹ�������%d�γ��ԣ���%d�η�������",N,(int)*p / 2);
    fclose(fpX);
    fclose(fpY);
}

//��дP-M�㷨
void PM(int N) {
    float* U1_for_P;
    float* U2_for_P;
    static float* PM;  
    PM = (float*)malloc(N * sizeof(float));

    U1_for_P = get_UDS(1,2,3,N);
    U2_for_P = get_UDS(4,5,6,N);

    int j = 0;

    float S = 0;
    float AS = 0;
    for (int i = 0; i < N; i++) {
        *(U1_for_P + i) = 2 * (*(U1_for_P + i)) - 1;
        *(U2_for_P + i) = 2 * (*(U2_for_P + i)) - 1;

        S = sqrt((*(U1_for_P + i)) * (*(U1_for_P + i))+ (*(U2_for_P + i)) * (*(U2_for_P + i)));
        if (S > 1) {
            continue;
        }
        AS = sqrt(-2 * log(S) / S);
        PM[j] = AS * (*(U1_for_P + i));
        j = j + 1;
    }
    PM[0] = j;

    FILE* fp;//�ļ�ָ��
    fp = fopen(".\\data\\PMGRSdata.txt", "w");

    for (int i = 1; i < j; i ++){
        fprintf(fp, "%f\n", PM[i]);

    }
    printf("�ܹ�������%d�γ��ԣ���%d�η�������", N, j);
    fclose(fp);
}



//����N�����������ֲ��������(sigma = 1)
float* Rayleigh_RS(int N) {

    static float* Rayleigh_RS;  // ����ָ��
    static float* UD_for_R;  // ����ָ��

// ��̬�����ڴ�ռ�
    Rayleigh_RS = (float*)malloc(N * sizeof(float));
    UD_for_R = (float*)malloc(N * sizeof(float));

    if (!Rayleigh_RS) {
        printf("��������ʧ�ܣ�\n");
    }

    //�ֱ�����N��(0,1)֮��������
    UD_for_R = get_UDS(1, 2, 3, N);

    for (int i = 0; i < N; i++) {
        Rayleigh_RS[i] = sqrt(-2*log(UD_for_R[i]));
       // printf("%f",Rayleigh_RS[i]);
    }
    return Rayleigh_RS;
}

//����txt�ļ�
void Rayleigh_RS2txt(int N) {
    FILE* fp_Rayleigh;//�ļ�ָ��

    fp_Rayleigh = fopen("RayleighdataX.txt", "w");


    float* p;
    p = Rayleigh_RS(N);

    for (int i = 0; i < N; i = i + 1)
    {
        fprintf(fp_Rayleigh, "%f\n", *(p + i));
    }
    fclose(fp_Rayleigh);
}
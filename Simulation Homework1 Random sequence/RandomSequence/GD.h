#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "UD.h"
#include<math.h>
#define PI 3.1415926


//使用均匀求和法生成N个均值为0，方差为1高斯随机数
float *US_GRS(int N) {

    static float* GRS1;  // 数组指针
    static float* UD1;  // 数组指针

// 动态分配内存空间
    GRS1 = (float*)malloc(N * sizeof(float));
    UD1 = (float*)malloc(12*N * sizeof(float));
    if (!GRS1) {
        printf("创建数组失败！\n");
    }
    //使用w-l算法迭代


    //生成12N个（0,1)之间的随机数
    float* p;
    p = get_UDS(1,2,3,12*N);
    for (int i = 0; i < 12 * N; i++) {
        UD1[i] =  *(p + i);
        //printf("%f\n", UD1[i]);

    }

    int i; //每一个数组的下标
    //每12个随机数求和，生成新的随机数
    for (i = 0; i < 12 * N; i = i + 12){
        GRS1[i / 12] = -6;//使均值为0
        for (int j = i; j < i + 12; j++){
            GRS1[i/12] += UD1[j];
        }
        //printf("%f ", GRS1[i / 12]);
        //printf("\n");
    }
    return GRS1;
}
//存入txt文件
void USGRS2txt(int N) {
    FILE* fp;//文件指针
    fp = fopen("USGRSdata.txt", "w");

    float*p;
    p = US_GRS(N);

    for (int i = 0; i < N; i++)
    {
        fprintf(fp, "%f\n", *(p + i));
    }
    fclose(fp);
}

//使用Box-Muller算法生成服从标准分布的高斯随机数
float *BM_GRS(int N) {

    static float* GRS2;  // 数组指针
    static float* UD1;  // 数组指针
    static float* UD2;  // 数组指针
    //static float* X;  // 数组指针
    //static float* Y;  // 数组指针
    static float* XY;  // 数组指针，下标为偶X，下标为奇Y

// 动态分配内存空间
    GRS2 = (float*)malloc(N * sizeof(float));
    UD1 = (float*)malloc( N * sizeof(float));
    UD2 = (float*)malloc(N * sizeof(float));
    //X = (float*)malloc(N * sizeof(float));
    //Y = (float*)malloc(N * sizeof(float));
     XY = (float*)malloc( N * sizeof(float));


    if (!GRS2) {
        printf("创建数组失败！\n");
    }
    //使用w-l算法迭代


    //分别生成N个随机数并存入UD1，UD2中
    float* p1;
    float* p2;
    p1 = get_UDS(1, 2, 3, N);
    p2 = get_UDS(4, 5, 6, N);
    for (int i = 0; i < N; i++) {
        UD1[i] = (*(p1 + i));
        UD2[i] = (*(p2 + i));
    }

    int i; //每一个数组的下标
    for (i = 0; i <  N; i = i + 2) {
        //使用一个数组返回？
        XY[i] = sqrt(-2 * log(UD1[i])) * cos((2 * PI * UD2[i]));       
        XY[i + 1] = sqrt(-2 * log(UD2[i])) * sin((2 * PI * UD1[i]));
        printf("%f\t", XY[i]);
        printf("%f\n", XY[i+1]);
    }
    return XY;
}
//存入txt文件
void BMGRS2txt(int N) {
    FILE* fpX;//文件指针
    FILE* fpY;//文件指针
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

//使用polar method法生成高斯随机数
float *PM_GRS(int N) {
    static float* UD1_for_PM;  
    static float* UD2_for_PM;  
    static float* V1;
    static float* V2;
 
    static float* XY_for_PM;  // 数组指针，下标为偶X，下标为奇Y

    // 动态分配内存空间
    UD1_for_PM = (float*)malloc(N * sizeof(float));
    UD2_for_PM = (float*)malloc(N * sizeof(float));
    V1 = (float*)malloc(N * sizeof(float));
    V2 = (float*)malloc(N * sizeof(float));

    XY_for_PM = (float*)malloc(N * sizeof(float));

    //分别生成N个随机数并存入UD1，UD2中
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
        printf("S为%f\n", S);
        if (S >= 1) {
            printf("跳过\n\n");
            continue;  
        }


        float AS;
        AS= sqrt(-2 * log(S) / S);
        printf("AS为%f\n", AS);

        XY_for_PM[j] = AS * V1[i];

        printf("随机数是%f\n\n", XY_for_PM[j]);

        XY_for_PM[j+1] = AS * V2[i];
        j = j + 2;
    }
    XY_for_PM[0] = j;//首地址存储随机数个数
    return XY_for_PM;
}
//存入txt文件
void PMGRS2txt(int N) {
    FILE* fpX;//文件指针
    FILE* fpY;//文件指针
    fpX = fopen(".\\data\\PMGRSdataX.txt", "w");
    fpY = fopen(".\\data\\PMGRSdataY.txt", "w");

    float* p;
    p = PM_GRS(N);
    int N_real = *p;//实际生成的高斯随机数个数

    for (int i = 1; i < N_real; i = i + 2)
    {
        fprintf(fpX, "%f\n", *(p + i));
        fprintf(fpY, "%f\n", *(p + i + 1));
    }
    printf("总共进行了%d次尝试，有%d次符合条件",N,(int)*p / 2);
    fclose(fpX);
    fclose(fpY);
}

//重写P-M算法
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

    FILE* fp;//文件指针
    fp = fopen(".\\data\\PMGRSdata.txt", "w");

    for (int i = 1; i < j; i ++){
        fprintf(fp, "%f\n", PM[i]);

    }
    printf("总共进行了%d次尝试，有%d次符合条件", N, j);
    fclose(fp);
}



//生成N个服从瑞利分布的随机数(sigma = 1)
float* Rayleigh_RS(int N) {

    static float* Rayleigh_RS;  // 数组指针
    static float* UD_for_R;  // 数组指针

// 动态分配内存空间
    Rayleigh_RS = (float*)malloc(N * sizeof(float));
    UD_for_R = (float*)malloc(N * sizeof(float));

    if (!Rayleigh_RS) {
        printf("创建数组失败！\n");
    }

    //分别生成N个(0,1)之间的随机数
    UD_for_R = get_UDS(1, 2, 3, N);

    for (int i = 0; i < N; i++) {
        Rayleigh_RS[i] = sqrt(-2*log(UD_for_R[i]));
       // printf("%f",Rayleigh_RS[i]);
    }
    return Rayleigh_RS;
}

//存入txt文件
void Rayleigh_RS2txt(int N) {
    FILE* fp_Rayleigh;//文件指针

    fp_Rayleigh = fopen("RayleighdataX.txt", "w");


    float* p;
    p = Rayleigh_RS(N);

    for (int i = 0; i < N; i = i + 1)
    {
        fprintf(fp_Rayleigh, "%f\n", *(p + i));
    }
    fclose(fp_Rayleigh);
}
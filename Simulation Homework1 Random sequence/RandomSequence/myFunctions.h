#pragma once
#include <stdio.h>
#include<math.h>
#define _CRT_SECURE_NO_WARNINGS 
#pragma warning(disable : 4996)
# define PI 3.1415926535

//������
void hello(void)
{
    printf("hello world\n");
}

//�ж��������Ƿ��ʣ�����ֵΪ1����
int ifPrime(int a, int b)
{
    int t;
    if (a < b)
    {
        t = a; a = b; b = t;
    }
    while (a % b)
    {
        t = b;
        b = a % b;
        a = t;
    }
    return b;
}

//��ӡ����
void Print_array(int a[], int size)
{

    for (int i = 0; i < size ; i++)
    {
        printf("%d\t", a[i]);
    }
    printf("\n");
}

//������һ�������(��׼�㷨)  
int NextRandomSequsence(a, c, m,seed)
{
    seed = (a * seed + c) % m;
    return seed;
}
/*
//������һ�������(W-L�㷨)�����ϣ�
int W_LRandomSequsence(x, y, z)
{
    int u;
    u = (mod(x, 30269) + mod(y, 30307) + mod(z, 30323));
    printf("%d\n", u);
    //printf("%d");
    x = mod(171 * x, 30269);
    y = mod(170 * y, 30307);
    z = mod(172 * z, 30323);
    return u, x, y, z;
}
*/

//ȡģ���������ϣ�ʹ��math.h���е�fmod�����
int mod(a, b)
{
    int c;
    if (b > a)
    {
        c = a;
        a = b;
        b = c;
    }
    return a % b;
}

//ֱ������N���������W-L�㷨����д���ļ���c�����޷�ʹ��Ĭ�ϲ��������ú����
void N_WLRandomSequsence()
{ 

    FILE* fp;//�ļ�ָ��
    fp = fopen("data.txt", "w");  //�ļ����������Զ����ɡ���w��д����r����
    
    //�жϡ��ļ�ָ���Ƿ��
    if (fp == NULL) 
    {
        printf("File cannot open! ");
        exit(0);
    }

    //�趨��ʼֵ������u���ڴ�����ɵ�����
    double x = 1;
    double y = 2;
    double z = 3;
    //double* u;
    double u[10000];

    // ��̬���飬�������ɿɱ䳤�ȵ����������
    //printf("������ϣ���õ��ľ������鳤�ȣ�");
    //scanf_s("%d", &N);  
    //u = (int*)calloc(N+1, sizeof(int));

    //ʹ��w-l�㷨����
    int i; //ÿһ��������±�
    for (i = 0; i < 10000; i++)
    {
        u[i] = fmod((x/30269 + y/30307 + z/30323),1);//��1ȡģ��
        printf("%f\n", u[i]);
        fprintf(fp, "%f\n", u[i]);//д��ָ��fp��д��Ķ������Ǹղŵ��û������d,ע�������fp��dû������
        x = fmod(171 * x, 30269);
        y = fmod(170 * y, 30307);
        z = fmod(172 * z, 30323);
    }
    fclose(fp);
}

//���ɸ�˹�����(������ͷ�)
void SUM_GRSequsence()
{
    FILE* fin = fopen("data.txt", "r");
    float a[10000];//ȡ��10000������
    int i;
    for (i = 0; i < 10000; i++) {
        fscanf(fin, "%f", &a[i]);
        //printf("%f\n", a[i]);
    }
    fclose(fin);
    /*��ȡ���*/

    printf("\n");

    //����1000�����Ӹ�˹�ֲ����������
    float b[850] = { 0 };//����Ϊ0

    for (i = 0; i < 9600; i = i + 12)
    {
        //printf("%f\n", a[i]);
        for (int j = i; j < i + 12; j++)
        {
            b[i / 12] += a[j];
        }
        //printf("%f\n", b[i / 12]);
        //printf("\n");
    }

    //for (i = 0; i < 800 ;i++)
    //	printf("%f\n", b[i]-6);

    FILE* fp;//�ļ�ָ��
    fp = fopen("Gdata1.txt", "w");  //�ļ����������Զ����ɡ���w��д����r����
    for (i = 0; i < 800; i++)
    {
        fprintf(fp, "%f\n", b[i] - 6);
    }
    fclose(fp);
}

//���ɸ�˹�������box-muller�㷨��
void BM_GRSequsence()
{
    FILE* fin = fopen("data.txt", "r");
    /*�����ļ���Ϊfile.txt*/
    float a[10000];//ȡ��10000������
    int i;
    for (i = 0; i < 10000; i++)
    {
        fscanf(fin, "%f", &a[i]);
        //printf("%f\n", a[i]);
    }
    fclose(fin);
    /*��ȡ���*/
    printf("\n");

    float X[1000], Y[1000];
    float U1[1000], U2[1000];
    FILE* fp1;//�ļ�ָ��
    FILE* fp2;//�ļ�ָ��


    for (i = 0; i < 1000; i++)
    {
        U1[i] = a[i + 1000];
        U2[i] = a[i + 2000];
        X[i] = cos(2 * PI * U2[i]) * sqrt(-2 * log(U1[i]));
        Y[i] = cos(2 * PI * U1[i]) * sqrt(-2 * log(U2[i]));
        printf("%f\n", X[i]);
    }

    fp1 = fopen("Gdata2_X.txt", "w");
    fp2 = fopen("Gdata2_Y.txt", "w");

    for (i = 0; i < 1000; i++)
    {
        fprintf(fp1, "%f\n", X[i]);
        fprintf(fp2, "%f\n", Y[i]);
    }

    fclose(fp1);
    fclose(fp2);
}

//���ɸ�˹�������polar method����
void PM_GRSequsence()
{
    FILE* fin = fopen("data.txt", "r");
    float a[10000];//ȡ��10000������
    int i;
    for (i = 0; i < 10000; i++)
    {
        fscanf(fin, "%f", &a[i]);
    }
    fclose(fin);
    printf("\n");

    float X[1000] = { 0 }, Y[1000] = { 0 };
    float V1[1000], V2[1000];
    float U1[1000], U2[1000];
    float AS[1000];
    int j = 0;

    for (i = 0; i < 1000; i++)
    {
        U1[i] = a[i + 1000];
        U2[i] = a[i + 2000];
        V1[i] = 2 * U1[i] - 1;
        V2[i] = 2 * U2[i] - 1;
        float S = sqrt(V1[i] * V1[i] + V2[i] * V2[i]);
        if (S > 1) {
            continue;
        }
        AS[i] = sqrt(-2 * log(S) / S);
        X[j] = AS[i] * V1[i];
        Y[j] = AS[i] * V2[i];
        j += 1;
    }

    FILE* fp1;//�ļ�ָ��
    FILE* fp2;//�ļ�ָ��
    fp1 = fopen("Gdata3_X.txt", "w");
    fp2 = fopen("Gdata3_Y.txt", "w");


    for (i = 0; i < 1000; i++)
    {
        if (X[i] != 0) {
            fprintf(fp1, "%f\n", X[i]);
        }
        if (Y[i] != 0) {
            fprintf(fp2, "%f\n", Y[i]);
        }
    }
    fclose(fp1);
    fclose(fp2);
}
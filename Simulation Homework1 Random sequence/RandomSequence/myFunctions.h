#pragma once
#include <stdio.h>
#include<math.h>
#define _CRT_SECURE_NO_WARNINGS 
#pragma warning(disable : 4996)
# define PI 3.1415926535

//测试用
void hello(void)
{
    printf("hello world\n");
}

//判断输入数是否互质，返回值为1则互质
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

//打印数组
void Print_array(int a[], int size)
{

    for (int i = 0; i < size ; i++)
    {
        printf("%d\t", a[i]);
    }
    printf("\n");
}

//生成下一个随机数(标准算法)  
int NextRandomSequsence(a, c, m,seed)
{
    seed = (a * seed + c) % m;
    return seed;
}
/*
//生成下一个随机数(W-L算法)（作废）
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

//取模函数（作废，使用math.h包中的fmod替代）
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

//直接生成N个随机数（W-L算法）并写入文件，c语言无法使用默认参数，可用宏代替
void N_WLRandomSequsence()
{ 

    FILE* fp;//文件指针
    fp = fopen("data.txt", "w");  //文件不存在则自动生成。“w”写，“r”读
    
    //判断、文件指针是否空
    if (fp == NULL) 
    {
        printf("File cannot open! ");
        exit(0);
    }

    //设定初始值，数组u用于存放生成的数据
    double x = 1;
    double y = 2;
    double z = 3;
    //double* u;
    double u[10000];

    // 动态数组，用于生成可变长度的随机数数组
    //printf("请输入希望得到的均匀数组长度：");
    //scanf_s("%d", &N);  
    //u = (int*)calloc(N+1, sizeof(int));

    //使用w-l算法迭代
    int i; //每一个数组的下标
    for (i = 0; i < 10000; i++)
    {
        u[i] = fmod((x/30269 + y/30307 + z/30323),1);//对1取模？
        printf("%f\n", u[i]);
        fprintf(fp, "%f\n", u[i]);//写入指针fp，写入的东西就是刚才的用户输入的d,注意这里的fp和d没有引号
        x = fmod(171 * x, 30269);
        y = fmod(170 * y, 30307);
        z = fmod(172 * z, 30323);
    }
    fclose(fp);
}

//生成高斯随机数(均匀求和法)
void SUM_GRSequsence()
{
    FILE* fin = fopen("data.txt", "r");
    float a[10000];//取出10000个数据
    int i;
    for (i = 0; i < 10000; i++) {
        fscanf(fin, "%f", &a[i]);
        //printf("%f\n", a[i]);
    }
    fclose(fin);
    /*读取完毕*/

    printf("\n");

    //生成1000个服从高斯分布的随机变量
    float b[850] = { 0 };//设置为0

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

    FILE* fp;//文件指针
    fp = fopen("Gdata1.txt", "w");  //文件不存在则自动生成。“w”写，“r”读
    for (i = 0; i < 800; i++)
    {
        fprintf(fp, "%f\n", b[i] - 6);
    }
    fclose(fp);
}

//生成高斯随机数（box-muller算法）
void BM_GRSequsence()
{
    FILE* fin = fopen("data.txt", "r");
    /*假设文件名为file.txt*/
    float a[10000];//取出10000个数据
    int i;
    for (i = 0; i < 10000; i++)
    {
        fscanf(fin, "%f", &a[i]);
        //printf("%f\n", a[i]);
    }
    fclose(fin);
    /*读取完毕*/
    printf("\n");

    float X[1000], Y[1000];
    float U1[1000], U2[1000];
    FILE* fp1;//文件指针
    FILE* fp2;//文件指针


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

//生成高斯随机数（polar method法）
void PM_GRSequsence()
{
    FILE* fin = fopen("data.txt", "r");
    float a[10000];//取出10000个数据
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

    FILE* fp1;//文件指针
    FILE* fp2;//文件指针
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
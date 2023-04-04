#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include "sort.h"

#define MAXK 1e5

void showFunction() {
	printf("\n\n\n<<<Function Menu>>>\n");
	printf("   1. 插入排序算法\n");
	printf("   2. 归并排序\n");
	//printf("   3. 归并排序\n");
	printf("   3. 快速排序\n");
	//printf("   5. 快速排序（非递归版）\n");
	//printf("   6. 快速排序（枢轴存放）\n");
	printf("   4. 计数排序\n");
	printf("   5. 基数计数排序\n");
	printf("   6. 颜色排序(只有012三种数据)\n");
	printf("   7. 退出\n");
	printf("   请输入相应操作：");

}

//产生随机数据，并保存到文件中
void Random_Save(int num, char Typename[]) {
	if (num == 0) {
		return;
	}
	FILE* fp;
	srand((unsigned int)time(NULL));
	//int* p = (int*)malloc(num * sizeof(int));
	int temp = 0;
	if ((fp = fopen(Typename, "w")) == NULL) {
			printf("创建文件失败！\n");
			exit(0);
	}
	for (int i = 0; i < num; i++)
	{
		if (strcmp(Typename, "任意整数.txt") == 0) {
			//assert(p);
			//*(p + i) = rand() % 1000;
			temp = rand() % 1000;
		}
		else if (strcmp(Typename, "只有012的数据.txt") == 0) {
			//assert(p);
			//*(p + i) = rand() % 3;
			temp = rand() % 3;
		}
		//assert(p);
		fprintf(fp, "%d\t", temp);
	}
	//写入结束标志，方便读取数据
	fputs("\nover\n", fp);
	printf("\n数据已保存！\n");
	//free(p);
	fclose(fp);
}

//从文件中读取数据
int* Open(int num,char Typename[]) {
	FILE* fp;
	int* p = (int*)malloc(num * sizeof(int));
	if ((fp = fopen(Typename, "r")) == NULL) {
		printf("打开文件失败！\n");
		return NULL;
	}
	while(!feof(fp))
	{
		for (int i = 0; i < num; i++) {
			assert(p);
			fscanf_s(fp, "%d", &p[i]);
		}
		return p;
	}
	return NULL;

}

void showTest() {
	printf("\n\n\n<<<Test Menu>>>\n");
	printf("   1. 任意整数的数据\n");
	printf("   2. 只有012的数据\n");
	printf("   请输入相应操作：");
}

//输出数组元素
void Print(int* a, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

//取数字且防止乱输入
int judge_int(void)
{
	int len, num = 0, arg = 1;
	char word[10] = "\0";
	int m, j = 1, k = 0;
	while (j)
	{
		scanf_s("\t\t\t\t\t%s", word, 10);
		len = strlen(word);
		for (m = 0; m < len; m++)
		{
			//出错处理，接受数字
			if (word[m] < '0' || word[m]>'9')
			{
				printf("请输入整数：");
				break;
			}
			else
			{
				if (m == len - 1)
					j = 0;
			}
		}
	}
	j = len - 1;
	//把字符换成整型
	for (m = 0; m < len; m++)
	{
		for (int i = 0; i <= j; i++)
			arg *= 10;
		num += (word[m] - '0') * arg;
		arg = 1;
		j--;
	}
	num = num / 10;
	return num;
}

//找出数组最大值
int Max(int* a, int size) {
	if (a == NULL) {
		return 0;
	}
	int max = a[0];
	for (int i = 0; i < size; i++) {
		if (a[i] > max)
			max = a[i];
	}
	return max;
}

clock_t start, stop;

double duration;

int main() {
	int choice, num = 0, mid = 0, max = 0;
	char Type[20] = "任意整数.txt";
	int* p = NULL, * temp = NULL;
	do
	{
		showFunction();
		choice = judge_int();
		system("cls");
		switch (choice)
		{
		case 1: 
		{
			printf("<<<插入排序>>>：\n");
			showTest();
			choice = judge_int();
			//获取测试数据量
			printf("请输入要测试的数据量：\n");
			num = judge_int();
			if (choice == 2) {
				strcpy(Type, "只有012的数据.txt");
			}
			else
			{
				strcpy(Type, "任意整数.txt");
			}
			Random_Save(num, Type);
			p = Open(num, Type);
			//计算排序时间，反复执行除以平均值
			if(num < 10000)
			{
				start = clock();
				for (int i = 0; i < MAXK; i++)
					insertSort(p, num);
				stop = clock();
				duration = ((double)(stop - start)) / CLK_TCK / MAXK;
				//输出排序后的数组
				printf("插入排序用时：%2.3e seconds\n", duration);
				Print(p, num);
			}
			else
			{
				start = clock();
				insertSort(p, num);
				stop = clock();
				duration = ((double)(stop - start)) / CLK_TCK ;
				//输出排序后的数组
				printf("插入排序用时：%2.3e seconds\n", duration);
				
			}
			free(p);
			p = NULL;
			break;
		}
		case 2:
		{
			printf("<<<归并排序排序>>>：\n");
			showTest();
			choice = judge_int();
			printf("请输入要测试的数据量：\n");
			num = judge_int();
			//获取数据数量的同时，确定temp要开辟空间的大小
			num = num + 1;
			mid = (num - 2) / 2;
			temp = (int*)malloc(num * sizeof(int));
			if (choice == 2) {
				strcpy(Type, "只有012的数据.txt");
			}
			else
			{
				strcpy(Type, "任意整数.txt");
			}
			Random_Save(num - 1, Type);
			p = Open(num - 1, Type);
			//计算排序时间
			if (num < 10001) {
				start = clock();
				for (int i = 0; i < MAXK; i++)
					MergeArray(p, 0, mid, num - 2, temp);
				stop = clock();
				duration = ((double)(stop - start)) / CLK_TCK / MAXK;
				printf("（数组合并）归并排序用时：%2.3e seconds\n", duration);
				Print(p, num - 1);

				p = Open(num - 1, Type);
				start = clock();
				for (int i = 0; i < MAXK; i++)
					MergeSort(p, 0, num - 2, temp);
				stop = clock();
				duration = ((double)(stop - start)) / CLK_TCK / MAXK;
				printf("归并排序用时：%2.3e seconds\n", duration);
				Print(p, num - 1);
			}
			else
			{
				start = clock();
				MergeArray(p, 0, mid, num - 2, temp);
				stop = clock();
				duration = ((double)(stop - start)) / CLK_TCK ;
				printf("（数组合并）归并排序用时：%2.3e seconds\n", duration);

				p = Open(num - 1, Type);
				start = clock();
				MergeSort(p, 0, num - 2, temp);
				stop = clock();
				duration = ((double)(stop - start)) / CLK_TCK ;
				printf("归并排序用时：%2.3e seconds\n", duration);
			}
			free(temp);
			free(p);
			p = NULL;
			break;
		}
		case 3:
		{
			printf("<<<快速排序>>>：\n");
			showTest();
			choice = judge_int();
			printf("请输入要测试的数据量：\n");
			num = judge_int();
			mid = (num-1) / 2;
			if (choice == 2) {
				strcpy(Type, "只有012的数据.txt");
			}
			else
			{
				strcpy(Type, "任意整数.txt");
			}
			Random_Save(num, Type);
			p = Open(num, Type);
			if (num < 10000) {
				start = clock();
				for (int i = 0; i < MAXK; i++)
					QuickSort_Recursion(p, 0, num - 1);
				stop = clock();
				duration = ((double)(stop - start)) / CLK_TCK / MAXK;
				printf("递归版快速排序用时：%2.3e seconds\n", duration);
				Print(p, num);

				p = Open(num, Type);
				start = clock();
				for (int i = 0; i < MAXK; i++)
					QuickSort(p, num - 1);
				stop = clock();
				duration = ((double)(stop - start)) / CLK_TCK / MAXK;
				printf("非递归版快速排序用时：%2.3e seconds\n", duration);
				Print(p, num);

				p = Open(num, Type);
				start = clock();
				for (int i = 0; i < MAXK; i++)
					QuickSort_Recursion(p, 0, num - 1);
				stop = clock();
				duration = ((double)(stop - start)) / CLK_TCK / MAXK;
				printf("选第一个元素为枢轴版快速排序用时：%2.3e seconds\n", duration);
				Print(p, num);

				p = Open(num, Type);
				start = clock();
				for (int i = 0; i < MAXK; i++)
					QuickSort_Random(p, 0, num - 1);
				stop = clock();
				duration = ((double)(stop - start)) / CLK_TCK / MAXK;
				printf("随机枢轴版快速排序用时：%2.3e seconds\n", duration);
				Print(p, num);

				p = Open(num, Type);
				start = clock();
				for (int i = 0; i < MAXK; i++)
					QuickSort_Three(p, 0, num , mid);
				stop = clock();
				duration = ((double)(stop - start)) / CLK_TCK / MAXK;
				printf("三数枢轴版快速排序用时：%2.3e seconds\n", duration);
				Print(p, num);
			}
			else
			{
				start = clock();
				QuickSort_Recursion(p, 0, num - 1);
				stop = clock();
				duration = ((double)(stop - start)) / CLK_TCK;
				printf("递归版快速排序用时：%2.3e seconds\n", duration);

				p = Open(num, Type);
				start = clock();
				QuickSort(p, num - 1);
				stop = clock();
				duration = ((double)(stop - start)) / CLK_TCK;
				printf("非递归版快速排序用时：%2.3e seconds\n", duration);
				
				p = Open(num, Type);
				start = clock();
				QuickSort_Recursion(p, 0, num - 1);
				stop = clock();
				duration = ((double)(stop - start)) / CLK_TCK;
				printf("选第一个元素为枢轴版快速排序用时：%2.3e seconds\n", duration);
				
				p = Open(num, Type);
				start = clock();
				QuickSort_Random(p, 0, num - 1);
				stop = clock();
				duration = ((double)(stop - start)) / CLK_TCK ;
				printf("随机枢轴版快速排序用时：%2.3e seconds\n", duration);
				
				p = Open(num, Type);
				start = clock();
				QuickSort_Three(p, 0, num , mid);
				stop = clock();
				duration = ((double)(stop - start)) / CLK_TCK;
				printf("三数枢轴版快速排序用时：%2.3e seconds\n", duration);
			}
			free(p);
			p = NULL;
			break;
		}
	    case 4:
		{
			printf("<<<计数排序>>>：\n");
			showTest();
			choice = judge_int();
			printf("请输入要测试的数据量：\n");
			num = judge_int();
			if (choice == 2) {
				strcpy(Type, "只有012的数据.txt");
			}
			else
			{
				strcpy(Type, "任意整数.txt");
			}
			Random_Save(num, Type);
			p = Open(num, Type);
			max = Max(p, num);
			if (num < 100000) {
				start = clock();
				for (int i = 0; i < MAXK; i++)
					CountSort(p, num, max);
				stop = clock();
				duration = ((double)(stop - start)) / CLK_TCK / MAXK;
				printf("计数排序用时：%2.3e seconds\n", duration);
				Print(p, num);
			}
			else
			{
				start = clock();
				CountSort(p, num, max);
				stop = clock();
				duration = ((double)(stop - start)) / CLK_TCK;
				printf("计数排序用时：%2.3e seconds\n", duration);

			}
			free(p);
			p = NULL;
			break;
		}
		case 5:
		{
			printf("<<<基数计数排序>>>：\n");
			showTest();
			choice = judge_int();
			printf("请输入要测试的数据量：\n");
			num = judge_int();
			if (choice == 2) {
				strcpy(Type, "只有012的数据.txt");
			}
			else
			{
				strcpy(Type, "任意整数.txt");
			}
			Random_Save(num, Type);
			p = Open(num, Type);
			if (num < 10000) {
				start = clock();
				for (int i = 0; i < MAXK; i++)
					RadixCountSort(p, num);
				stop = clock();
				duration = ((double)(stop - start)) / CLK_TCK / MAXK;
				printf("基数计数排序用时：%2.3e seconds\n", duration);
				Print(p, num);
			}
			else
			{
				start = clock();
				RadixCountSort(p, num);
				stop = clock();
				duration = ((double)(stop - start)) / CLK_TCK ;
				printf("基数计数排序用时：%2.3e seconds\n", duration);
			}
			free(p);
			p = NULL;
			break;
		}
		case 6:
		{
			printf("<<<颜色排序>>>：\n");
			showTest();
			choice = judge_int();
			printf("请输入要测试的数据量：\n");
			num = judge_int();
			if (choice == 2) {
				strcpy(Type, "只有012的数据.txt");
			}
			else
			{
				strcpy(Type, "任意整数.txt");
			}
			Random_Save(num, Type);
			p = Open(num, Type);
			if (num < 100000) {
				start = clock();
				for (int i = 0; i < MAXK; i++)
					ColorSort(p, num);
				stop = clock();
				duration = ((double)(stop - start)) / CLK_TCK / MAXK;
				printf("颜色排序用时：%2.3e seconds\n", duration);
				Print(p, num);
			}
			else
			{
				start = clock();
				ColorSort(p, num);
				stop = clock();
				duration = ((double)(stop - start)) / CLK_TCK / MAXK;
				printf("颜色排序用时：%2.3e seconds\n", duration);
			}
			free(p);
			p = NULL;
			break;
		}
		case 7:
		{
			if (p != NULL) {
				free(p);
			}
			
			break;
		}
		default:
		{
			
			printf("请重新输入数字！（1-7）\n");
			break;
		}
		}
	} while (choice != 7);
	
}
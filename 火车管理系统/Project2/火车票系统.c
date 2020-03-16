#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"train_book.h"
#include "linklist.h"


void showmenu();

int main() {
	int ret = 0;
	int choice = 0;
	int train_num;
	showmenu();

	do {
		printf("输入你的选择：");
		scanf("%d", &choice);
		while (getchar() != '\n')
			continue;
		switch (choice)
		{
		case 1:
			input();
			break;
		case 2:
			showinf();
			break;
		case 3:
			searchinf();
			break;
		case 4:
			booktrain();
			break;
		case 5:
			cancelbook();
			break;
		case 6:
			exit(0);
			break;
		//处理错误是输入
		default:
			continue;
		}
		system("cls");
		showmenu();
	} while (1);
}

void showmenu() {
	printf("==================================\n");
	printf("1 录入信息\n");
	printf("2 显示所有火车信息\n");
	printf("3 查询信息\n");
	printf("4 订票预约\n");
	printf("5 取消预约\n");
	printf("6 退出系统\n");
	printf("==================================\n");
}
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
		printf("�������ѡ��");
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
		//�������������
		default:
			continue;
		}
		system("cls");
		showmenu();
	} while (1);
}

void showmenu() {
	printf("==================================\n");
	printf("1 ¼����Ϣ\n");
	printf("2 ��ʾ���л���Ϣ\n");
	printf("3 ��ѯ��Ϣ\n");
	printf("4 ��ƱԤԼ\n");
	printf("5 ȡ��ԤԼ\n");
	printf("6 �˳�ϵͳ\n");
	printf("==================================\n");
}
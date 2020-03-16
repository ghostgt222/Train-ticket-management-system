#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"train_book.h"
#include "linklist.h"
#define SIZE sizeof(struct Train)
#define Filename "火车信息.txt"
/*
typedef struct Train {
	int train_num;           //车次
	char de_time[20];        //出发时间
	char de_sta[20];         //始发站
	char al_sta[50];             //沿途站点
	char fi_sta[20];             //终点站
	int sta_num;             //座位数
	int book_status;          //预约状态
	struct train *next;
}Train;
*/
int input() {
	int status = 0;
	int choice = 0;
	List *list;
	Train *cur;
	list = List_creat();
	system("cls");
	printf("\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("1. * * * * * * * * * * * * * 录入出入车次信息 * * * * * * * * * * * * * * * * * *\n");
	printf("2.* * * * * * * * * * * * * * * 返回菜单 * * * * * * * * * * * * * * * * * * * *\n");
	printf("请输入你的选择：");
	while (1) {
		scanf_s("%d", &choice);
		while (getchar() != '\n')
			continue;
		if (choice == 1)break;
		else if (choice == 2)break;
		else {
			printf("输入错误，请重新输入：");
			continue;
		}
	}
	while (choice == 1) {
		system("cls");
		printf("* * * * * * * * * * * * * * *请输入车次信息 * * * * * * * * * * * * * * * * * * * \n");
		printf("    车次   出发时间   始发站   沿途站点                  终点站    座位数\n");
		printf("\n");
		printf("例： 01     7:00     南京站   镇江站、无锡站、苏州站    上海站         80\n");
		while (1) {
			cur = (Train *)malloc(SIZE);
			if (cur == NULL) {
				printf("func input(Train **train) malloc err\n");
				return -1;
			}
			//输入数据并处理错误输入
			do {
				int status2;
				//处理错误输入
				while ((status2 = scanf_s("%d%s%s%s%s%d", &cur->train_num, cur->de_time, 20, cur->de_sta, 20, cur->al_sta, 50,
					cur->fi_sta, 20, &cur->sta_num)) != 6) {
					printf("输入错误，请重新输入：\n");
					while (getchar() != '\n')
						continue;
				}
				//判断时间是否错误输入
				char *find, *find2;
				find = strchr(cur->de_time, ':');
				find2 = strstr(cur->de_time, "：");
				if (find == NULL && find2 == NULL) {
					printf("输入错误，请输入正确时间，重新输入：\n");
					continue;
				}
				//将中文符号"："转化为英文符号":"
				if (find2 != NULL) {
					find = strchr(find2, '0');
					*find2 = ':';
					strcpy(find2 + 1, find);
				}
				//判断站名是否输入错误
				if ((find = strstr(cur->de_sta, "站")) == NULL) {
					printf("输入错误，请输入正确的站台名，重新输入：\n");
					continue;
				}
				if ((find = strstr(cur->fi_sta, "站")) == NULL) {
					printf("输入错误，请输入正确的站台名，重新输入：\n");
					continue;
				}

				if ((find = strstr(cur->al_sta, "站")) == NULL) {
					printf("输入错误，请输入正确的站台名，重新输入：\n");
					continue;
				}
				status = 1;
			} while (status != 1);
			List_insert(list, cur, 0);		//插入链表
			printf("是否继续输入(1 继续输入 2 返回菜单)：\n");
			choice = 0;
			while (scanf("%d", &choice) != 1 && (choice != 1 || choice != 2)) {
				while (getchar() != '\n')
					continue;
			}
			if (choice == 1)
				break;
			else
				save(list);
			break;
		}
	}
	List_destroy(list);		//销毁链表
	return 0;
}

int showinf() {
	system("cls");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n");
	List* list = List_creat();
	Train *cur = NULL;
	int ret = load(list);		//加载文件信息
	int length = List_length(list);		//获取链表长度
	int n = 0;		//第n个节点
	if (ret != 0) {
		return -1;
	}
	while (cur = List_get(list, n), n < length) {
		printf("车次：%2d\n出发时间：%s \n始发站：%s  \n沿途站点：%s  \n终点站：%s  \n座位数：%3d\n\n\n",
			cur->train_num, cur->de_time, cur->de_sta, cur->al_sta, cur->fi_sta, cur->sta_num);
		n++;
	}
	List_destroy(list);		//销毁链表
	system("pause");
	return 0;
}

int searchinf() {
	int choice = 0;
	List *list = List_creat();		//创建链表
	system("cls");
	int ret = load(list);		//加载数据
	if (ret != 0) {
		return -1;
	}
	printf("\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("* * * * * * * * * * * * * 1. 根据时间查询 * * * * * * * * * * * * * * * * * * *\n");
	printf("* * * * * * * * * * * * * 2. 根据终点站查询 * * * * * * * * * * * * * * * * * *\n");
	fputs("输入你的选择：", stdout);
	choice = 0;
	while (scanf("%d", &choice) != 1 && (choice != 1 || choice != 2)) {
		while (getchar() != '\n')
			continue;
		printf("输入错误，请重新输入：");
	}
	//选择搜索方式
	if (choice == 1)
		search_time(list);
	else
		search_sta(list);
	List_destroy(list);		//销毁链表
	return 0;
}

int search_sta(List *list) {
	int count = 0;
	int n = 0;		//第n个节点
	int length = List_length(list);		//获取链表长度
	Train *cur = NULL;
	char station[20] = { 0 };
	printf("请输入终点站：");
	//处理错误输入
	while (1) {
		scanf("%s", station);
		while (getchar() != '\n')
			continue;
		char *find = strstr(station, "站");
		if (find == NULL) {
			printf("输入错误，请输入正确的站台名，重新输入：\n");
			continue;
		}
		else
			break;
	}
	system("cls");
	printf("\n* * * * * * * * * * * * * * * * * * * * * * * * * * \n");
	fputs("有以下车次：\n", stdout);
	while (cur = List_get(list, n), n < length) {
		int judge = strcmp(station, cur->fi_sta);		//比对节点信息和输入信息
		if (judge == 0) {
			printf("车次：%2d\n出发时间：%s \n始发站：%s  \n沿途站点：%s  \n终点站：%s  \n座位数：%3d\n\n\n",
				&cur->train_num, cur->de_time, cur->de_sta, cur->al_sta, cur->fi_sta, &cur->sta_num);
			count++;
		}
		n++;
	}
	if (count == 0) {
		fputs("（无车次）\n", stdout);
	}
	system("pause");
	return 0;
}

int search_time(List *list) {
	int count = 0;		//符合条件的信息个数
	int n = 0;		//第n个节点
	int length = List_length(list);		//获取链表长度
	Train *cur = NULL;
	char time[20] = { 0 };
	printf("请输入出发时间：");
	//输入时间并处理错误信息
	while (1) {
		scanf("%s", time);
		while (getchar() != '\n')
			continue;
		char *find, *find2;
		find = strchr(time, ':');
		find2 = strstr(time, "：");
		if (find == NULL && find2 == NULL) {
			printf("输入错误，请输入正确时间，重新输入：\n");
			continue;
		}
		if (find2 != NULL) {
			find = strchr(find2, '0');
			*find2 = ':';
			strcpy(find2 + 1, find);
		}
		break;
	}
	system("cls");
	printf("\n* * * * * * * * * * * * * * * * * * * * * * * * * * \n");
	fputs("有以下车次：\n", stdout);
	while (cur = List_get(list, n), n < length) {
		int judge = strcmp(time, cur->de_time);
		if (judge == 0) {
			printf("车次：%2d\n出发时间：%s \n始发站：%s  \n沿途站点：%s  \n终点站：%s  \n座位数：%3d\n\n\n",
				cur->train_num, cur->de_time, cur->de_sta, cur->al_sta, cur->fi_sta, cur->sta_num);
			count++;
		}
		n++;
	}
	if (count == 0) {
		fputs("（无车次）\n", stdout);
	}
	system("pause");
	return 0;
}

int booktrain() {
	system("cls");
	List *list = List_creat();
	Train *cur;
	int n = 0;		//第n个节点
	int ret = load(list);
	if (ret != 0) {
		return -1;
	}
	int length = List_length(list);		//获取链表长度
	int num, status = 0;
	printf("请输入要预定的车次：");
	while (1) {
		int n = scanf("%d", &num);
		while (getchar() != '\n')
			continue;
		if (n != 1) {
			printf("输入错误，请重新输入：");
			continue;
		}
		break;
	}
	while (cur = List_get(list, n), n < length) {
		if (cur->train_num == num) {
			if (cur->book_status == 1) {
				status = -1;
				break;
			}
			cur->book_status = 1;
			status = 1;
			break;
		}
		n++;
	}
	if (status == 1) {
		fputs("预定成功。\n\n", stdout);
	}
	else if (status == -1) {
		fputs("此车次已经预定过了。\n\n", stdout);
	}
	else {
		fputs("没有此车次。\n\n", stdout);
	}
	FILE *fp;
	//把文件清空
	fp = fopen(Filename, "w");
	fclose(fp);
	save(list);
	List_destroy(list);		//销毁链表
	system("pause");
	return 0;
}

int cancelbook() {
	system("cls");
	List* list = List_creat();
	int n = 0;		//第n个节点
	int ret = load(list);
	if (ret != 0) {
		return -1;
	}
	int length = List_length(list);		//获取链表长度
	Train *cur;
	printf("有以下车次已被预定：\n");
	while (cur = List_get(list, n), n < length) {
		if (cur->book_status == 1) {
			printf("车次：%2d\n出发时间：%s \n始发站：%s  \n沿途站点：%s  \n终点站：%s  \n座位数：%3d\n\n\n",
				cur->train_num, cur->de_time, cur->de_sta, cur->al_sta, cur->fi_sta, cur->sta_num);
		}
		n++;
	}
	printf("您要取消哪辆,请输入车次：\n");
	int choice;
	scanf("%d", &choice);
	int status = 0;
	n = 0;		//初始化到头节点
	while (cur = List_get(list, n), n < length) {
		if (cur->train_num == choice) {
			cur->book_status = 0;
			status = 1;
			break;
		}
		n++;
	}
	if (status == 1) {
		fputs("取消预约成功。\n", stdout);
	}
	else {
		system("pause");
		fputs("取消预约失败。\n", stdout);
	}
	FILE *fp;
	//清空文件
	fp = fopen(Filename, "w");
	fclose(fp);
	save(list);
	List_destroy(list);		//销毁链表
	system("pause");
	return 0;
}

int save(List *list) {
	int n = 0;
	int length = List_length(list);		//获取链表长度
	Train *cur;
	int status = 0;
	FILE *fp;
	if (list == NULL) {
		fputs("无数据存储。\n", stdout);
		system("pause");
		return -1;
	}
	fp = fopen(Filename, "a+");
	if (fp == NULL) {
		printf("文件打开失败。\n");
		return -1;
	}
	while (cur = List_get(list, n), n < length) {
		fwrite(cur, SIZE, 1, fp);
		n++;
	}
	fclose(fp);
	system("cls");
	printf("\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n");
	printf("\n* * * * * * * * * * * * * * * * 保存成功 * * * * * * * * * * * * * * * * * * \n");
	return 0;
}

int load(List* list) {
	Train *cur;
	FILE *fp;
	fp = fopen(Filename, "r");
	if (fp == NULL) {
		fputs("文件加载失败。\n\n", stdout);
		system("pause");
		return -1;
	}
	getc(fp);
	if (feof(fp)) {
		fputs("数据库为空\n\n", stdout);
		system("pause");
		return -1;
	}
	rewind(fp);
	while (getc(fp), feof(fp) == 0) {
		fseek(fp, -1L, SEEK_CUR);
		if ((cur = (Train *)malloc(SIZE)) == NULL) {
			printf("func load(List* list) malloc err\n");
			return -1;
		}
		memset(cur, 0, SIZE);
		fread(cur, SIZE, 1, fp);
		List_insert(list, cur, 0);
	}
	fclose(fp);
	return 0;
}




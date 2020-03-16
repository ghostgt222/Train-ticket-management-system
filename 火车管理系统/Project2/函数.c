#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"train_book.h"
#include "linklist.h"
#define SIZE sizeof(struct Train)
#define Filename "����Ϣ.txt"
/*
typedef struct Train {
	int train_num;           //����
	char de_time[20];        //����ʱ��
	char de_sta[20];         //ʼ��վ
	char al_sta[50];             //��;վ��
	char fi_sta[20];             //�յ�վ
	int sta_num;             //��λ��
	int book_status;          //ԤԼ״̬
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
	printf("1. * * * * * * * * * * * * * ¼����복����Ϣ * * * * * * * * * * * * * * * * * *\n");
	printf("2.* * * * * * * * * * * * * * * ���ز˵� * * * * * * * * * * * * * * * * * * * *\n");
	printf("���������ѡ��");
	while (1) {
		scanf_s("%d", &choice);
		while (getchar() != '\n')
			continue;
		if (choice == 1)break;
		else if (choice == 2)break;
		else {
			printf("����������������룺");
			continue;
		}
	}
	while (choice == 1) {
		system("cls");
		printf("* * * * * * * * * * * * * * *�����복����Ϣ * * * * * * * * * * * * * * * * * * * \n");
		printf("    ����   ����ʱ��   ʼ��վ   ��;վ��                  �յ�վ    ��λ��\n");
		printf("\n");
		printf("���� 01     7:00     �Ͼ�վ   ��վ������վ������վ    �Ϻ�վ         80\n");
		while (1) {
			cur = (Train *)malloc(SIZE);
			if (cur == NULL) {
				printf("func input(Train **train) malloc err\n");
				return -1;
			}
			//�������ݲ������������
			do {
				int status2;
				//�����������
				while ((status2 = scanf_s("%d%s%s%s%s%d", &cur->train_num, cur->de_time, 20, cur->de_sta, 20, cur->al_sta, 50,
					cur->fi_sta, 20, &cur->sta_num)) != 6) {
					printf("����������������룺\n");
					while (getchar() != '\n')
						continue;
				}
				//�ж�ʱ���Ƿ��������
				char *find, *find2;
				find = strchr(cur->de_time, ':');
				find2 = strstr(cur->de_time, "��");
				if (find == NULL && find2 == NULL) {
					printf("���������������ȷʱ�䣬�������룺\n");
					continue;
				}
				//�����ķ���"��"ת��ΪӢ�ķ���":"
				if (find2 != NULL) {
					find = strchr(find2, '0');
					*find2 = ':';
					strcpy(find2 + 1, find);
				}
				//�ж�վ���Ƿ��������
				if ((find = strstr(cur->de_sta, "վ")) == NULL) {
					printf("���������������ȷ��վ̨�����������룺\n");
					continue;
				}
				if ((find = strstr(cur->fi_sta, "վ")) == NULL) {
					printf("���������������ȷ��վ̨�����������룺\n");
					continue;
				}

				if ((find = strstr(cur->al_sta, "վ")) == NULL) {
					printf("���������������ȷ��վ̨�����������룺\n");
					continue;
				}
				status = 1;
			} while (status != 1);
			List_insert(list, cur, 0);		//��������
			printf("�Ƿ��������(1 �������� 2 ���ز˵�)��\n");
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
	List_destroy(list);		//��������
	return 0;
}

int showinf() {
	system("cls");
	printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n");
	List* list = List_creat();
	Train *cur = NULL;
	int ret = load(list);		//�����ļ���Ϣ
	int length = List_length(list);		//��ȡ������
	int n = 0;		//��n���ڵ�
	if (ret != 0) {
		return -1;
	}
	while (cur = List_get(list, n), n < length) {
		printf("���Σ�%2d\n����ʱ�䣺%s \nʼ��վ��%s  \n��;վ�㣺%s  \n�յ�վ��%s  \n��λ����%3d\n\n\n",
			cur->train_num, cur->de_time, cur->de_sta, cur->al_sta, cur->fi_sta, cur->sta_num);
		n++;
	}
	List_destroy(list);		//��������
	system("pause");
	return 0;
}

int searchinf() {
	int choice = 0;
	List *list = List_creat();		//��������
	system("cls");
	int ret = load(list);		//��������
	if (ret != 0) {
		return -1;
	}
	printf("\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("* * * * * * * * * * * * * 1. ����ʱ���ѯ * * * * * * * * * * * * * * * * * * *\n");
	printf("* * * * * * * * * * * * * 2. �����յ�վ��ѯ * * * * * * * * * * * * * * * * * *\n");
	fputs("�������ѡ��", stdout);
	choice = 0;
	while (scanf("%d", &choice) != 1 && (choice != 1 || choice != 2)) {
		while (getchar() != '\n')
			continue;
		printf("����������������룺");
	}
	//ѡ��������ʽ
	if (choice == 1)
		search_time(list);
	else
		search_sta(list);
	List_destroy(list);		//��������
	return 0;
}

int search_sta(List *list) {
	int count = 0;
	int n = 0;		//��n���ڵ�
	int length = List_length(list);		//��ȡ������
	Train *cur = NULL;
	char station[20] = { 0 };
	printf("�������յ�վ��");
	//�����������
	while (1) {
		scanf("%s", station);
		while (getchar() != '\n')
			continue;
		char *find = strstr(station, "վ");
		if (find == NULL) {
			printf("���������������ȷ��վ̨�����������룺\n");
			continue;
		}
		else
			break;
	}
	system("cls");
	printf("\n* * * * * * * * * * * * * * * * * * * * * * * * * * \n");
	fputs("�����³��Σ�\n", stdout);
	while (cur = List_get(list, n), n < length) {
		int judge = strcmp(station, cur->fi_sta);		//�ȶԽڵ���Ϣ��������Ϣ
		if (judge == 0) {
			printf("���Σ�%2d\n����ʱ�䣺%s \nʼ��վ��%s  \n��;վ�㣺%s  \n�յ�վ��%s  \n��λ����%3d\n\n\n",
				&cur->train_num, cur->de_time, cur->de_sta, cur->al_sta, cur->fi_sta, &cur->sta_num);
			count++;
		}
		n++;
	}
	if (count == 0) {
		fputs("���޳��Σ�\n", stdout);
	}
	system("pause");
	return 0;
}

int search_time(List *list) {
	int count = 0;		//������������Ϣ����
	int n = 0;		//��n���ڵ�
	int length = List_length(list);		//��ȡ������
	Train *cur = NULL;
	char time[20] = { 0 };
	printf("���������ʱ�䣺");
	//����ʱ�䲢���������Ϣ
	while (1) {
		scanf("%s", time);
		while (getchar() != '\n')
			continue;
		char *find, *find2;
		find = strchr(time, ':');
		find2 = strstr(time, "��");
		if (find == NULL && find2 == NULL) {
			printf("���������������ȷʱ�䣬�������룺\n");
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
	fputs("�����³��Σ�\n", stdout);
	while (cur = List_get(list, n), n < length) {
		int judge = strcmp(time, cur->de_time);
		if (judge == 0) {
			printf("���Σ�%2d\n����ʱ�䣺%s \nʼ��վ��%s  \n��;վ�㣺%s  \n�յ�վ��%s  \n��λ����%3d\n\n\n",
				cur->train_num, cur->de_time, cur->de_sta, cur->al_sta, cur->fi_sta, cur->sta_num);
			count++;
		}
		n++;
	}
	if (count == 0) {
		fputs("���޳��Σ�\n", stdout);
	}
	system("pause");
	return 0;
}

int booktrain() {
	system("cls");
	List *list = List_creat();
	Train *cur;
	int n = 0;		//��n���ڵ�
	int ret = load(list);
	if (ret != 0) {
		return -1;
	}
	int length = List_length(list);		//��ȡ������
	int num, status = 0;
	printf("������ҪԤ���ĳ��Σ�");
	while (1) {
		int n = scanf("%d", &num);
		while (getchar() != '\n')
			continue;
		if (n != 1) {
			printf("����������������룺");
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
		fputs("Ԥ���ɹ���\n\n", stdout);
	}
	else if (status == -1) {
		fputs("�˳����Ѿ�Ԥ�����ˡ�\n\n", stdout);
	}
	else {
		fputs("û�д˳��Ρ�\n\n", stdout);
	}
	FILE *fp;
	//���ļ����
	fp = fopen(Filename, "w");
	fclose(fp);
	save(list);
	List_destroy(list);		//��������
	system("pause");
	return 0;
}

int cancelbook() {
	system("cls");
	List* list = List_creat();
	int n = 0;		//��n���ڵ�
	int ret = load(list);
	if (ret != 0) {
		return -1;
	}
	int length = List_length(list);		//��ȡ������
	Train *cur;
	printf("�����³����ѱ�Ԥ����\n");
	while (cur = List_get(list, n), n < length) {
		if (cur->book_status == 1) {
			printf("���Σ�%2d\n����ʱ�䣺%s \nʼ��վ��%s  \n��;վ�㣺%s  \n�յ�վ��%s  \n��λ����%3d\n\n\n",
				cur->train_num, cur->de_time, cur->de_sta, cur->al_sta, cur->fi_sta, cur->sta_num);
		}
		n++;
	}
	printf("��Ҫȡ������,�����복�Σ�\n");
	int choice;
	scanf("%d", &choice);
	int status = 0;
	n = 0;		//��ʼ����ͷ�ڵ�
	while (cur = List_get(list, n), n < length) {
		if (cur->train_num == choice) {
			cur->book_status = 0;
			status = 1;
			break;
		}
		n++;
	}
	if (status == 1) {
		fputs("ȡ��ԤԼ�ɹ���\n", stdout);
	}
	else {
		system("pause");
		fputs("ȡ��ԤԼʧ�ܡ�\n", stdout);
	}
	FILE *fp;
	//����ļ�
	fp = fopen(Filename, "w");
	fclose(fp);
	save(list);
	List_destroy(list);		//��������
	system("pause");
	return 0;
}

int save(List *list) {
	int n = 0;
	int length = List_length(list);		//��ȡ������
	Train *cur;
	int status = 0;
	FILE *fp;
	if (list == NULL) {
		fputs("�����ݴ洢��\n", stdout);
		system("pause");
		return -1;
	}
	fp = fopen(Filename, "a+");
	if (fp == NULL) {
		printf("�ļ���ʧ�ܡ�\n");
		return -1;
	}
	while (cur = List_get(list, n), n < length) {
		fwrite(cur, SIZE, 1, fp);
		n++;
	}
	fclose(fp);
	system("cls");
	printf("\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n");
	printf("\n* * * * * * * * * * * * * * * * ����ɹ� * * * * * * * * * * * * * * * * * * \n");
	return 0;
}

int load(List* list) {
	Train *cur;
	FILE *fp;
	fp = fopen(Filename, "r");
	if (fp == NULL) {
		fputs("�ļ�����ʧ�ܡ�\n\n", stdout);
		system("pause");
		return -1;
	}
	getc(fp);
	if (feof(fp)) {
		fputs("���ݿ�Ϊ��\n\n", stdout);
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




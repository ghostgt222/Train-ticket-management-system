#ifndef _TRAIN_BOOK_H
#define _TRAIN_BOOK_H
#include "linklist.h"
typedef struct Train {
	ListNode *next;		//ͨ������
	int train_num;           //����
	char de_time[20];        //����ʱ��
	char de_sta[20];         //ʼ��վ
	char al_sta[50];             //��;վ��
	char fi_sta[20];             //�յ�վ
	int sta_num;             //��λ��
	int book_status;          //ԤԼ״̬
}Train;


int input();     //¼��
int showinf();     //��ʾ��Ϣ
int searchinf();   //��ѯ
int search_sta(List *list);  //�����յ�վ��ѯ
int search_time(List *list);     //����ʱ���ѯ
int booktrain();          //Ԥ��
int cancelbook();          //ȡ��ԤԼ
int save(List *list);		//����
int load(List *list);		//����
//int sort(List *list);		//��������

#endif // !_TRAIN_BOOK_H




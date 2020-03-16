#ifndef _TRAIN_BOOK_H
#define _TRAIN_BOOK_H
#include "linklist.h"
typedef struct Train {
	ListNode *next;		//通用链表
	int train_num;           //车次
	char de_time[20];        //出发时间
	char de_sta[20];         //始发站
	char al_sta[50];             //沿途站点
	char fi_sta[20];             //终点站
	int sta_num;             //座位数
	int book_status;          //预约状态
}Train;


int input();     //录入
int showinf();     //显示信息
int searchinf();   //查询
int search_sta(List *list);  //根据终点站查询
int search_time(List *list);     //根据时间查询
int booktrain();          //预订
int cancelbook();          //取消预约
int save(List *list);		//保存
int load(List *list);		//加载
//int sort(List *list);		//链表排序

#endif // !_TRAIN_BOOK_H




#pragma once
typedef void List;


typedef struct ListNode {
	struct ListNode *next;
}ListNode;

List* List_creat();		//创建链表
void List_destroy(List *list);		//销毁链表
void List_clear(List* list);		//清空链表
int List_length(List* list);		//链表长度
int List_insert(List* list, ListNode* node, int pos);		//节点插入
ListNode* List_get(List* list, int pos);		//获取节点信息
ListNode* List_delete(List* list, int pos);		//删除节点
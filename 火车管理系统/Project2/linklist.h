#pragma once
typedef void List;


typedef struct ListNode {
	struct ListNode *next;
}ListNode;

List* List_creat();		//��������
void List_destroy(List *list);		//��������
void List_clear(List* list);		//�������
int List_length(List* list);		//������
int List_insert(List* list, ListNode* node, int pos);		//�ڵ����
ListNode* List_get(List* list, int pos);		//��ȡ�ڵ���Ϣ
ListNode* List_delete(List* list, int pos);		//ɾ���ڵ�
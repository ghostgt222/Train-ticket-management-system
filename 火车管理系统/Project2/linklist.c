#include <stdio.h>
#include<string.h>
#include "linklist.h"


typedef struct tag_linklist {
	ListNode head;
	int length;
}tag_linklist;

List* List_creat() {
	tag_linklist* list = NULL;
	list = (tag_linklist*)malloc(sizeof(tag_linklist));
	memset(list, 0, sizeof(tag_linklist));
	list->length = 0;
	list->head.next = NULL;
	return list;
}
void List_destroy(List *list) {
	if (list != NULL) {
		free(list);
		list = NULL;
	}
}
void List_clear(List* list) {
	tag_linklist* tlist = NULL;
	if (list == NULL) {
		return;
	}
	tlist = (tag_linklist*)list;
	tlist->length = 0;
	tlist->head.next = NULL;
	return;
}
int List_length(List* list) {
	tag_linklist* tlist = NULL;
	if (list == NULL) {
		return;
	}
	tlist = (tag_linklist*)list;
	return tlist->length;
}
int List_insert(List* list, ListNode* node, int pos) {
	tag_linklist* tlist = NULL;
	if (list == NULL) {
		return -1;
	}
	if (node == NULL) {
		return -2;
	}
	tlist = (tag_linklist*)list;
	ListNode* current = &(tlist->head);
	for (int i = 0; i < pos && current->next != NULL; i++) {
		current = current->next;
	}
	node->next = current->next;
	current->next = node;
	tlist->length++;
	return 0;
}
ListNode* List_get(List* list, int pos) {
	tag_linklist* tlist = NULL;
	if (list == NULL) {
		return -1;
	}
	tlist = (tag_linklist*)list;
	ListNode* current = &(tlist->head);
	for (int i = 0; i < pos + 1 && current->next != NULL; i++) {
		current = current->next;
	}
	return  current;
}
ListNode* List_delete(List* list, int pos) {
	tag_linklist* tlist = NULL;
	if (list == NULL) {
		return -1;
	}
	tlist = (tag_linklist*)list;
	ListNode* pre = &(tlist->head);
	ListNode* current = NULL;
	for (int i = 0; i < pos && pre->next!=NULL; i++) {
		pre = pre->next;
	}
	current = pre->next;
	pre->next = current->next;
	tlist->length--;
	return current;
}
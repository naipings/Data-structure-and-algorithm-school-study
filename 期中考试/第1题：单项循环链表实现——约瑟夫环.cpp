#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef int LDataType;
typedef bool Status;

//循环链表的表示与实现
typedef struct ListNode {
	LDataType data;
	struct ListNode* next;
}ListNode, *LinkList;

//初始化一个空单循环链表
void initList(LinkList *list)
{
	(*list) = (LinkList)malloc(sizeof(LinkList));
	(*list)->next = (*list);	
}

//创建单循环链表
Status listCreate(LinkList* list, LDataType n)
{
	if ( (*list) == NULL ) {
		return false;
	}
	ListNode *s, *r;
	r = *list;
	int cnt = 1;
	while ( n-- ) {
		s = (ListNode *)malloc(sizeof(ListNode));
		
		s->data = cnt;
		cnt++;
		r->next = s;
		r = s;
	}
	r->next = (*list)->next; //让尾结点指向头结点（这里是首元结点）
	
	return true;
}

//打印
Status listPrint(LinkList list, int n)
{
	if ( (list) == NULL ) {
		return false;
	}
	LinkList p, r;
	int m;
	p = list;
	r = list->next;
	printf("请输入出列方式：");
	scanf("%d", &m);
	while( n-- ) {
		for ( int i=1; i<m; i++ ) {
			p = r;
			r = r->next;
		}
		printf("%d-->", r->data);
		p->next = r->next;
		free(r);
		r = p->next;
	}

	return true;
		
}

int main()
{
	srand(time(0));
	
	int n;
	LinkList list;
	initList(&list);
	printf("请输入人数大小：");
	scanf("%d", &n);
	listCreate(&list, n);	
	listPrint(list, n);
	
	return 0;
}

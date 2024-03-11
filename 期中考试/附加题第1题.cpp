#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef bool Status;

typedef struct nodel{
	int value;
	struct nodel *next;
} Node;

typedef struct _list {
	Node* head;
	////Node* tail;
} List;

//创建链表（添加链表结点）
void add_list(List* pList, int number)
{
	Node *p = (Node*)malloc(sizeof(Node));
	p->value = number;
	p->next = NULL;
			
	Node *last = pList->head;
	if ( last != NULL ) {
		while ( last->next != NULL ) {
			last = last->next;
		}
		last->next = p;
	} else {
		pList->head = p;
	}
}

//遍历链表
void prt_node(List* pList)
{
	Node *p;
	for ( p=pList->head; p; p=p->next ) {
		printf("%d\t", p->value);
	}
	printf("\n");	
}

//销毁链表
void delete_list(Node *head)
{
	if ( head->next != NULL ) {
//	if ( head->next ) { //也可以直接这么写 
		delete_list(head->next); 
	}
	free(head);
}

//快速排序（带头结点）（从小到大）
void quickSort(List* pList)
{
	Node *p = pList->head;
	Node *q = pList->head;
	int temp = 0;
    if( (p->next == NULL) || (p->next->next == NULL) ) {
        return;
    }
    
    for ( ; p; p=p->next ) {
    	for ( ; q; q=q->next ) {
    		if ( q->value > p->value ) {
    			temp = p->value;
    			p->value = q->value;
    			q->value = temp;		
			}
		}
		q = pList->head;
	}
}

//删除数据
void delete_node(List* plist, int number)
{
	Node *p;
	Node *q;
	for ( q=NULL, p=plist->head; p; q=p, p=p->next ) {
		if ( p->value == number ) {
			//下面这个if-else语句用于考虑q的边界条件
			if ( q != NULL ) {
				q->next = p->next;
			} else {
				plist->head = p->next;
			}
			free(p);
			break;
		}
	}	
}

//链表拆分
Status splitList(List* pList1, List* pList2, List* pList3)
{
	Node *p = pList1->head;
	Node *q;
	if ( p->next == NULL ) {
        return false;
    }
    
    for ( ; p; p=p->next ) {
    	if ( p->value >= 0 ) {
    		add_list(pList3, p->value);
		} else {
			add_list(pList2, p->value);
		}
	}
	
	for ( ; p; p=p->next ) {
		if ( p->value > 0 ) {
			continue;
		} else {
			q = p;
			break;
			
		}
	}

	return true;
}

int main(int argc, char const* argv[])
{
	srand(time(0));
	List list;
	list.head = NULL;
	List list2;
	list2.head = NULL;
	List list3;
	list3.head = NULL;
	
	//添加结点（直至输入-1时停止添加链表结点）
	int number;
//	do {
//		scanf("%d", &number);
//		if ( number != -1 ) {
//			add_list(&list, number);
//		}
//	} while ( number != -1 );
	
	for ( int i=0; i<9; i++ ) {
		number = -50 + rand()%100;
		add_list(&list, number);
	}
	prt_node(&list); //打印

	//快速排序（从小到大），并打印排序结果
	quickSort(&list);	
	prt_node(&list);
	
	//链表拆分
	splitList(&list, &list2, &list3);
	prt_node(&list);
	prt_node(&list2);
	prt_node(&list3);

	//销毁链表
	delete_list(list.head);
	delete_list(list2.head);
	delete_list(list3.head);
	
	return 0;
}
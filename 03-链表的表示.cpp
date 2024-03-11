//链表的表示
//#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <Stdlib.h>
#include <time.h>
//#include <assert.h>

typedef struct _node {
	int value;
	struct _node *next;
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

//查找
void search_node(List* pList, int number)
{
	Node *p;
	int flag = 0;
	for ( p=pList->head; p; p=p->next ) {
		if ( p->value == number ) {
			printf("find number:%d\n", p->value);
			flag = 1;
			break;
		}
	}
	
	if ( flag == 0 ) {
		printf("没找到!\n");
	}	
}

//插入
//指定结点的后插
void InsertNextNode(List* pList, int pos, int number)
{
	Node *p;
	p = pList->head;
	if ( p == NULL ) {
		return;
	}
	
	Node *s = (Node*)malloc(sizeof(Node));
	s->value = number;
	
	for ( ; p; p=p->next ) {
		if ( p->value == pos ) {
			s->next = p->next;
			p->next = s;
			break;
		}
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
			if ( q !=NULL ) {
				q->next = p->next;
			} else {
				plist->head = p->next;
			}
			free(p);
			break;
		}
	}	
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

//链表归并

//链表应用

//插入排序（不带头结点）
void insertSort(List* pList)
{
	Node *p = pList->head;
    if( (p->next == NULL) || (p->next->next == NULL) ) {
        return;
    }
	
    Node *head, *p1, *prep1, *p2, *prep2, *temp;
    head = p;
    prep1 = head->next;
    p1 = prep1->next;
    //prep1和p1是否需要手动后移
    bool flag;
 
    while ( p1 != NULL ) {   
        flag = true;
        temp = p1; 
        //由于是单向链表，所以只能从头部开始检索
        for( prep2=head, p2=prep2->next; p2!=p1; prep2=prep2->next, p2=p2->next ) {   
            //发现第一个较大值
            if ( p2->value > p1->value ) {   
                p1 = p1->next;
                prep1->next = p1; 
                prep2->next = temp;
                temp->next = p2; 
                flag = false;
                break;
            }   
        }   
        //手动后移prep1和p1
        if( flag ) {   
            prep1 = prep1->next;
            p1 = p1->next;
        }   
    }   
}

//冒泡排序（不带头结点）
void bubbleSort(List* pList)
{
	Node *p = pList->head;
    if( (p->next == NULL) || (p->next->next == NULL) ) {
        return;
    }
	
    Node *head, *pre, *cur, *next, *end, *temp;
    head = p;
    end = NULL;
    //从链表头开始将较大值往后沉
    while ( head->next != end ) { 
        for( pre=head, cur=pre->next, next=cur->next; next!=end; pre=pre->next, cur=cur->next, next=next->next ) {
            //相邻的节点比较
            if( cur->value > next->value ) {
                cur->next = next->next;
                pre->next = next;
                next->next = cur;
                temp = next;
                next = cur;
                cur = temp;
            }
        }
        end = cur;
    }
}

//快速排序（带头结点）
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
//				printf("temp=%d\n", temp);			
			}
		}
		q = pList->head;
	}
}

int main(int argc, char const* argv[])
{
	srand(time(0));
	List list;
	list.head = NULL;
	
	//添加结点（直至输入-1时停止添加链表结点）
	int number;
//	do {
//		scanf("%d", &number);
//		if ( number != -1 ) {
//			add_list(&list, number);
//		}
//	} while ( number != -1 );
	
	for ( int i=0; i<9; i++ ) {
		number = -50 + rand()%150;
		add_list(&list, number);
	}
	
	prt_node(&list);
	
//	printf("请输入要查找的数据：");
//	scanf("%d", &number);
//	search_node(&list, number);
//	
//	int pos = 0;
//	printf("请输入要插入的位置与数据：");
//	scanf("%d %d", &pos, &number);
//	InsertNextNode(&list, pos, number);
//	prt_node(&list);
//	
//	printf("请输入要删除的数据：");
//	scanf("%d", &number);
//	delete_node(&list, number);
//	prt_node(&list);
//	
//
//	insertSort(&list);
//	bubbleSort(&list);
	quickSort(&list);	
	prt_node(&list);

	delete_list(list.head);
	
	return 0;
}
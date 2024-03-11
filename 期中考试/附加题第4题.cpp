#include<stdio.h>
#include <stdlib.h>
#include <time.h>

typedef bool Status;
typedef int ElemType;

typedef struct Node{
	ElemType data;
	struct Node * next; 
	struct Node * former; 
}numset;

typedef struct List{
	numset* head;
	numset* end;
	numset* now; 
	int size;
}list;

void read(list* p){
	ElemType n;
	numset* position=NULL;//存一下当前节点A1的位置，当处理到了下一个节点A2，就可以把这个位置赋给A2的前驱指针。现在没有任何结点，位置指针指向空。
	
	do {
		printf("请输入数字（=-1就终止）：");
		scanf("%d", &n);
		
		if ( n == -1 ) {
			return;
		}
		
		p->now=(numset*)malloc(sizeof(numset));
        p->now->data=n;
 
		p->now->former=position;//把前驱节点挂到之前保存的位置上
				
		if(!p->head){
			p->head=p->now;//如果头结点指针指向空，则把头指针挂在刚输入的结点
		}
		
		p->end=p->now;//把尾指针挂在最新输入的结点
 
		p->size++;
 
		position=p->now;//存一下当前节点A1的位置，当处理到了下一个节点A2，就可以把这个位置赋给A2的前驱指针
		p->now=p->now->next;
		
	} while( n != -1 );
	
}

Status put(list* p)
{		
	while ( p->end ) {
		printf("%d ", p->end->data);
		free(p->end);
		p->end=p->end->former;		
	}
	return true;
}

int main()
{
	list pset;//相当于 numset* pset;
 
	pset.head=NULL;
	pset.end=NULL;
	pset.now=NULL;
	pset.size=0;//初始化链表。相当于pset=NULL;
 
	read(&pset);
 
	put(&pset);
 
	return 0;
}
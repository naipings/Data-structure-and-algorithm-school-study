#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXSIZE 10

//定义节点的数据结构
typedef struct node {
	int data; 
	struct node* next;
}node;
//节点的第一位元素用来存储有多少个元素

//创建节点的函数
node* initlist(int data)
{
	node* head = (node*)malloc(sizeof(node));
	head->data=data;
	head->next = NULL;
	return head;
}

//链表的遍历
void printlist(node* head)
{
	node* flag = head;
	do
	{
		printf("%d\t", flag->data);
		flag = flag->next;
	} while (flag->next != NULL);
	printf("%d\n", flag->data);
}

//头插法
void head_insert(node* head,int data)
{
	node* second = (node*)malloc(sizeof(node));
	second->data=data;
	if (head->next == NULL) {
		second->next = NULL;
	}
	else {
		second->next = head->next;
	}
	head->next = second;
}

//尾插法
void last_insert(node* head,int data)
{
	node* last = (node*)malloc(sizeof(node));
	last->data=data;
	last->next = NULL;
	node* flag = head;
	while (flag->next != NULL) {
		flag = flag->next;
	}
	flag->next = last;
}

//删除
void delete_node(node* head, int number)
{
	node* flag = head;
	while (number - 1 > 0) {
		flag = flag->next;
		number--;
	}
	node* delete_flag = flag->next;
	flag->next = (flag->next)->next;
	free(delete_flag);
}

// 找到链表中最大的数据元素并返回该节点
node* findMaxElement(node *head)
{
    node *p = head;
    node *maxNode = p;
    int maxData = p->data;

    while (p != NULL) {
        if (p->data > maxData) {
            maxNode = p;
            maxData = p->data;
        }
        p = p->next;
    }

    return maxNode;
}

int main()
{
	srand(time(0));
	//创建一个链表，里面有正有负 
	node* head = initlist(3);
	
	for ( int i=0; i<MAXSIZE; i++ ) {
		int number = -20 + rand()%40;
		if ( i % 2 == 0 ) {
			head_insert(head, number);
		} else {
			last_insert(head, number);
		}
	}
	printf("链表表示为：\n");
	printlist(head);
	
	printf("链表中最大的元素表示为：\n");
	node* maxnode= findMaxElement(head);
	printf("%d\n",maxnode->data);

	return 0;
}

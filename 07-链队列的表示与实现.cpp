//链队列的表示与实现
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef int QDataType; //队列存储数据类型

typedef struct QueueNode {
	QDataType data;
	struct QueueNode *next;
} QueueNode;

typedef struct Queue {
	QueueNode *head;
	QueueNode *tail;
} Queue;

//初始化
bool QueueInit(Queue* pq)
{
	if ( pq == NULL ) {  //防止pq为空指针
		return false;
	}
	pq->head = pq->tail = NULL;
	
	return true;
}

//销毁队列
void QueueDestory(Queue* pq)
{
	if ( pq == NULL ) {
		return;
	}
	
	QueueNode* cur = pq->head;
	while ( cur ) {
		QueueNode* next = cur->next;
		free(cur);
		cur = next;
	}
	pq->tail = pq->head = NULL;
	
}

//入队
bool QueuePush(Queue* pq, QDataType x)
{
	if ( pq == NULL ) {
		return false;
	}
	
	QueueNode* p = (QueueNode*)malloc(sizeof(QueueNode));
	if ( p == NULL ) {
		printf("ERROR1");
		exit(-1);
	}
	p->data = x;
	p->next = NULL;
	
	if ( pq->tail == NULL ) { //判断是否为空队列
//		if ( pq->head == NULL ) {
//			return false;
//		}
		pq->head = pq->tail = p;
	} else {
		pq->tail->next = p;
		pq->tail = p;
	
	}
	
	return true;
}

//出队
void QueuePop(Queue* pq)
{
	if ( pq->head == NULL ) {
		return;
	}
	if ( pq->head == NULL || pq->tail == NULL ) {
		return;
	}
	
	QDataType x = pq->head->data;
	printf("出队元素为：%d\n", x);	
	
	if ( pq->head->next == NULL ) {
		free(pq->head);
		pq->head = pq->tail = NULL;
	} else {
		QueueNode* p = pq->head->next;
		free(pq->head);
		pq->head = p;
	}
	
}

//取出队首元素
QDataType QueueFront(Queue* pq)
{
	if ( pq == NULL ) {
		printf("ERROR2");
		exit(-1);
	}
	if ( pq->head == NULL ) {
		printf("ERROR3");
		exit(-1);
	}
	
	return pq->head->data;
	
}

//遍历队列
bool QueueView(Queue* pq)
{
	if ( pq == NULL ) {
		return false;
	}
	if ( pq->head == NULL || pq->tail == NULL ) {
		return false;
	}
	
	QueueNode* p = pq->head;
	
	while ( p ) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("\n");
	
	return true;
}

//求队列长度
int QueueSize(Queue *pq)
{
	if ( pq == NULL ) {
		return false;
	}
	QueueNode* cur = pq->head;
	int count = 0;
	while ( cur ) {
		cur = cur->next;
		count++;
	}
	return count;
}

//判断队列是否为空
bool QueueEmpty(Queue *pq)
{
	if ( pq == NULL ) {
		return false;
	}
	return pq->head == NULL;
}

int main(int argc, char const *argv[])
{
	srand(time(0));
	bool flag = false;
	
	Queue q;
	flag = QueueInit(&q);
	printf("flag=%d\n", flag);
	
	printf("-------------------------------------------------------------\n");
	
	//一个元素的队列测试
	printf("一个元素的队列测试：\n");
	
	for ( int i=0; i<1; i++ ) {
		flag = QueuePush(&q, -30 + rand()%70);
		printf("flag=%d\n", flag);
	}
	flag = QueueView(&q);
	printf("flag=%d\n", flag);
	
	int numberFront = QueueFront(&q);
	printf("number=%d\n", numberFront);
	
	for ( int i=0; i<1; i++ ) {
		QueuePop(&q);
	}
	flag = QueueView(&q);
	printf("flag=%d\n", flag);
	
	printf("-------------------------------------------------------------\n");

	//多个元素的队列测试
	printf("多个元素的队列测试：\n");
		
	for ( int i=0; i<9; i++ ) {
		QueuePush(&q, -30 + rand()%70);
	}
	QueueView(&q);
	printf("\n");
	
	printf("继续入队：\n");
	for ( int i=0; i<3; i++ ) {
		QueuePush(&q, -30 + rand()%70);
	}
	QueueView(&q);
	printf("\n");
	
	numberFront = QueueFront(&q);
	printf("numberFront=%d\n", numberFront);
	
	for ( int i=0; i<3; i++ ) {
		QueuePop(&q);
		numberFront = QueueFront(&q);
		printf("numberFront=%d\n", numberFront);
	}
	QueueView(&q);
	
	QueueDestory(&q);
	
	return 0;
}

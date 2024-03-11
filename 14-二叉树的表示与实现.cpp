//二叉树的表示与实现
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef bool Status;
typedef int TElemType;

//二叉树的链式存储
typedef struct BiTNode {
	TElemType data;
	struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

//定义栈
#define STACK_INIT_SIZE 100 //存储空间初始分配量
#define STACKINCREMENT 10 //存储空间分配增量
typedef struct {
	BiTNode *base; //在栈构造之前和销毁之后，base的值为NULL
	BiTNode *top; //栈顶指针
	int stacksize; //当前已分配的存储空间，以元素为单位
} SqStack;

//定义队列
typedef struct QueueNode {
	BiTNode data;
	struct QueueNode *next;
} QueueNode;

typedef struct Queue {
	QueueNode *head;
	QueueNode *tail;
} Queue;


//二叉树创建
Status createTree(BiTree *bt) //传入一个BiTree的指针地址
{
	TElemType data;
	scanf("%d", &data);
	
	if ( data == -1 ) { //-1代表终端结点值（即：此结点下子树不存在数据，也就是不再递归创建）
		(*bt) = NULL;
		return false;
	}
	else {
		(*bt) = (BiTree )malloc(sizeof(BiTNode));
		(*bt)->data = data;
		printf("请输入%d的左孩子结点：", data);
		createTree(&((*bt)->lchild));
		printf("请输入%d的右孩子结点：", data);
		createTree(&((*bt)->rchild));
	}
	
	return true;
}

//二叉树销毁
Status destroyTree(BiTree bt)
{
	BiTree pl, pr;
	if ( bt == NULL ) {
		return false;
	}
	else {
		pl = (bt)->lchild; //保存左孩子的地址
		pr = (bt)->rchild; //保存右孩子的地址
		(bt)->lchild = NULL;
		(bt)->rchild = NULL;
		free(bt); //释放根结点
		(bt) = NULL;
		//递归销毁
		destroyTree(pl);
		destroyTree(pr);
	}
	return true;
}

//遍历二叉树：（D表示根，L表示左子树，R表示右子树）
//递归实现：
//先序遍历（D L R）
void preOrder(BiTree bt)
{
	if ( bt == NULL ) {
		return;
	}
	else {
		printf("%d ", bt->data);
		preOrder(bt->lchild);
		preOrder(bt->rchild);
	}
}

//中序遍历（L D R）
void inOrder(BiTree bt)
{
	if ( bt == NULL ) {
		return;
	}
	else {
		inOrder(bt->lchild);
		printf("%d ", bt->data);
		inOrder(bt->rchild);
	}
}

//后序遍历（L R D）
void postOrder(BiTree bt)
{
	if ( bt == NULL ) {
		return;
	}
	else {
		postOrder(bt->lchild);
		postOrder(bt->rchild);
		printf("%d ", bt->data);
	}
}

//非递归实现后序遍历（结合栈实现）
//栈初始化
Status InitStack(SqStack &s)
{
	s.base = (BiTNode *)malloc(STACK_INIT_SIZE*sizeof(BiTNode));
	if ( !s.base ) {
		printf("Error!");
		exit(-1);
	}
	//printf("s.base=%d\n", s.base);
	s.top = s.base;
	s.stacksize = STACK_INIT_SIZE;
	
	return true;
}

//销毁栈
Status DestoryStack(SqStack &s)
{
	if ( s.base == NULL ) { //栈结构不存在，程序异常退出
		exit(1);
	}
	free(s.base);
	s.base = NULL;
	return true;
}

//判断是否为空栈
//true————空栈；false————非空栈
Status StackEmpty(SqStack &s)
{
	if ( s.base == NULL ) {
	exit(1);
	}
	bool ret = false;
	ret = s.top - s.base ? false : true;
	
	return ret;
}

//取出栈顶元素
Status GetTop(SqStack &s, BiTNode &e)
{
	if ( s.top - s.base == 0 ) {
		return false;
	}
	e = *(s.top-1);
	
	return true;
}

//入栈
Status Push(SqStack &s, BiTNode e)
{
	//插入元素e为新的栈顶元素
	if ( s.top - s.base >= s.stacksize ) { //栈满，追加存储空间
		s.base = (BiTNode *)realloc(s.base, (s.stacksize + STACKINCREMENT)*sizeof(BiTNode));
		s.top = s.base + s.stacksize;
		s.stacksize += STACKINCREMENT;	
	}
	* s.top++ = e;
	return true;
}

//出栈
Status Pop(SqStack &s, BiTNode &e)
{
	//若栈不空，则删除s的栈顶元素，用e返回其值，并返回true；否则返回false
	if ( s.top - s.base == 0 ) {
		return false;
	}
	e = * --s.top;
	
	return true;
}

//比较两个节点是否相等
Status Equal(BiTNode *e1, BiTNode *e2)
{
	if ( e1==NULL || e2==NULL ) {
		return false;
	}
	if ( e1->data==e2->data && e1->lchild==e2->lchild && e1->rchild==e2->rchild ) {
		return true;
	}
	else {
		return false;
	}
}

void postOrder2(BiTree bt)
{
	if ( bt == NULL ) {
		return;
	}
	else {
		SqStack s;
		InitStack(s); //初始化栈
		BiTree p = bt;
		BiTree pre = NULL; //临时变量，记录上一个访问的结点（根据后序遍历特点，访问根结点时，就意味着右子树已经访问完毕，故此时，上一个结点必定是右子树根结点）
		BiTNode e, cur; //二叉树结点，用于存储从栈中取出的结点
		Push(s, *p);
		while ( !StackEmpty(s) ) {
			GetTop(s, e);
			if ( (e.lchild==NULL && e.rchild==NULL) || (pre!=NULL && (Equal(pre, e.lchild) || Equal(pre, e.rchild))) ) {
				Pop(s, cur);
				printf("%d ", cur.data);
				pre = &cur;
			} else {
				if ( e.rchild != NULL ) {
					Push(s, (*e.rchild));
				}
				if ( e.lchild != NULL ) {
					Push(s, (*e.lchild));
				}
			}
		}
		printf("\n");
		DestoryStack(s);		
	}
}


//二叉树的层次遍历（结合队列实现）
//队列初始化
Status QueueInit(Queue &pq)
{
	pq.head = pq.tail = NULL;
	
	return true;
}

//销毁队列
Status QueueDestory(Queue &pq)
{
	if ( pq.head == NULL ) {
		return false;
	}
	QueueNode* cur = pq.head;
	while ( cur ) {
		QueueNode* next = cur->next;
		free(cur);
		cur = next;
	}
	pq.tail = pq.head = NULL;
	return true;
}

//判断队列是否为空
Status isQueueEmpty(Queue &pq)
{
	return pq.head == NULL;
}

//入队
Status QueuePush(Queue &pq, BiTNode x)
{
	QueueNode* p = (QueueNode *)malloc(sizeof(QueueNode));
	if ( p == NULL ) {
		printf("ERROR1");
		exit(-1);
	}
	p->data = x;
	p->next = NULL;
	
	if ( pq.tail == NULL ) { //判断是否为空队列
		pq.head = pq.tail = p;
	} else {
		pq.tail->next = p;
		pq.tail = p;
	}
	
	return true;
}

//出队
Status QueuePop(Queue &pq, BiTNode &e)
{
	if ( pq.head == NULL ) {
		return false;
	}
	if ( pq.head == NULL || pq.tail == NULL ) {
		return false;
	}

	e = pq.head->data;

	if ( pq.head->next == NULL ) {
		free(pq.head);
		pq.head = pq.tail = NULL;
	} else {
		QueueNode* p = pq.head->next;
		free(pq.head);
		pq.head = p;
	}
	return true;
}

void levelOrder(BiTree bt)
{
	Queue pq;
	QueueInit(pq);
		
	BiTNode tempq;
	
	QueuePush(pq, *bt); //根结点入队
	while ( !isQueueEmpty(pq) ) {
		QueuePop(pq, tempq);
		printf("%d ", tempq.data);
		if ( tempq.lchild != NULL ) {
			QueuePush(pq, (*tempq.lchild));
		}
		if ( tempq.rchild != NULL ) {
			QueuePush(pq, (*tempq.rchild));
		}
	}
	printf("\n");
	QueueDestory(pq);
	
}

int main()
{
	BiTree *bt = (BiTree *)malloc(sizeof(BiTree));
	bool flag = false;
	flag = createTree(bt);
	printf("createTree() flag=%d\n", flag);
	
	printf("\n前序遍历结果：      ");
	preOrder((*bt));
	printf("\n中序遍历结果：      ");
	inOrder((*bt));
	printf("\n后序遍历结果：      ");
	postOrder((*bt));
	printf("\n非递归后序遍历结果：");
	postOrder2((*bt));
	
	printf("\n\n层次遍历结果：      ");
	levelOrder((*bt));

	flag = destroyTree(*bt);				     
	printf("\ndestroyTree() flag=%d\n", flag);
	
	return 0;
}
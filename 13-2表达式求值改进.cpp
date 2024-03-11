//表达式求值：中序表达式转后序表达式，利用顺序栈实现
//改进版1：可以计算10位及以上整数
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
#define MAXSIZE 10
typedef struct BTNode{//树节点
    char *key;
    struct BTNode *lchild;
    struct BTNode *rchild;
}BTNode;

#define STACK_INIT_SIZE 100 //存储空间初始分配量
#define STACKINCREMENT 10 //存储空间分配增量
typedef double SElemType;
typedef struct {
	SElemType *base; //在栈构造之前和销毁之后，base的值为NULL
	SElemType *top; //栈顶指针
	int stacksize; //当前已分配的存储空间，以元素为单位
} SqStack;

static char s0[100];

BTNode *createBTree( char f[])//实现中缀表达式构建二叉树
{
    char Stackoperate[MAXSIZE];int topo =-1;
    BTNode *StackBTNode[MAXSIZE];int topb =-1;
    BTNode *node;
    char *p=f;
    
    while(*p!='\0')//遍历输出顺序表的字符
    {
        if(*p=='+'||*p=='-'||*p=='*'||*p=='/')
        {
            if((topo!=-1)&&(*p=='+'||*p=='-'))//优先级判断
            {
            	node = (BTNode*)malloc(sizeof(BTNode));
            	node->key = (char *)malloc(sizeof(char));
              	node->key[0]=Stackoperate[topo--];
              	node->rchild=StackBTNode[topb--];
              	node->lchild=StackBTNode[topb--];

              	StackBTNode[++topb]=node;
	        	Stackoperate[++topo]=*p;
            }
            else {
                Stackoperate[++topo]=*p;
            }
            ++p;
//            printf("*p=%c\n", *p);
        }
        else if ( isdigit(*p) ){
        	node=(BTNode*)malloc(sizeof(BTNode));
        	node->key = (char *)malloc(MAXSIZE*sizeof(char));
        	node->key[0] = *p;
        	int i = 1;   	
        	while ( isdigit(*(p+i)) ) {
        		node->key[i] = *(p+i);
        		i++;
			}
			node->key[i] = '_';
//			printf("key=%s\n", node->key);
            node->lchild=node->rchild=NULL;
            StackBTNode[++topb]=node;
            p=p+i;
//            printf("*p=%c\n", *p);
        }    
    }
    while(topo!=-1)
    {
        node=(BTNode*)malloc(sizeof(BTNode));
        node->key = (char *)malloc(sizeof(char));
        node->key[0]=Stackoperate[topo--];
        node->rchild=StackBTNode[topb--];
        node->lchild=StackBTNode[topb--];

        StackBTNode[++topb]=node;
    }
    return StackBTNode[topb];
}

void postioder(BTNode *root)
{
	static int cnt = 0;
    if(root!=NULL) {
    	postioder(root->lchild);
    	postioder(root->rchild);
    	int num = 0;
    	if ( root->key[0] != '+' && root->key[0] != '-' && root->key[0] != '*' && root->key[0] != '/' ) {
    		while ( root->key[num] != '_' ) {
    			s0[cnt++] = root->key[num++];
			}
			s0[cnt++] = '_';
			printf("s0=%s, cnt=%d\n", s0, cnt);
		} else {
			s0[cnt++] = root->key[0];
			printf("s0=%s, key=%c\n", s0, root->key[0]);
		}

//		printf("cnt=%d\n", cnt);
//		printf("%s\n", s0);	
    }
}

//顺序栈计算表达式的值
//初始化
bool InitStack(SqStack &s)
{
	s.base = (SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
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
bool DestoryStack(SqStack &s)
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
bool StackEmpty(SqStack &s)
{
	if ( s.base == NULL ) {
	exit(1);
	}
	bool ret = false;
	ret = s.top - s.base ? false : true;
	
	return ret;
}

//入栈
bool Push(SqStack &s, SElemType e)
{
	//插入元素e为新的栈顶元素
	if ( s.top - s.base >= s.stacksize ) { //栈满，追加存储空间
		s.base = (SElemType *)realloc(s.base, (s.stacksize + STACKINCREMENT)*sizeof(SElemType));
		s.top = s.base + s.stacksize;
		s.stacksize += STACKINCREMENT;	
	}
	* s.top++ = e;
//	printf("e=%f\n", e);
	return true;
}

//出栈
bool Pop(SqStack &s, SElemType &e)
{
	//若栈不空，则删除s的栈顶元素，用e返回其值，并返回true；否则返回false
	if ( s.top - s.base == 0 ) {
		return false;
	}
	e = * --s.top;
	
	return true;
}

//后缀表达式求值
bool calcul(char str[],int length)
{
	SqStack s;
	InitStack(s); //初始化栈
	double e = 0;
	for( int i=0; i<length; i++ ) {
		double num = 0;
		if( isdigit(str[i]) ) {
			while ( str[i] != '_' ) {
				num = num*10 + ((int)str[i] - 48) * 1.0;
				i++;
			}
			
			printf("%f\n", num);
			Push(s,num); //扫描到数字就入栈
		} else { //扫描到运算符
			if( StackEmpty(s) ) {
				return false; //表达式为空无法计算失败
			}
			SElemType topElem1, topElem2; //用来保存弹出栈的栈顶元素
			Pop(s, topElem1); //栈顶元素出栈
			Pop(s, topElem2); //栈顶元素出栈
			if( str[i]=='+' ) {
				e = topElem1 + topElem2;
				Push(s, e);
			}
			if( str[i]=='-' ) {
				e = topElem2 - topElem1;
				Push(s, e);
			}
			if( str[i]=='*' ) {
				e = topElem1 * topElem2;
				Push(s, e);
			}
			if( str[i]=='/' ) {
				e = topElem2 / topElem1;
				Push(s, e);
			}
		}
	}
	printf("%f\n", e);
	bool flag = StackEmpty(s);
	DestoryStack(s);
	return flag;
}

int main()
{
//    char f[]="A+B*C-D/E";
	char f[]="118+52*3-6/2";

    BTNode *root=createBTree(f);
    postioder(root);
    printf("%s\n", s0);
    printf("\n");
    
    calcul(s0, strlen(s0));
 
    return 0;
}
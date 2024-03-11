//顺序栈的实现
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STACK_INIT_SIZE 100 //存储空间初始分配量
#define STACKINCREMENT 10 //存储空间分配增量

typedef int SElemType;

typedef struct {
	SElemType *base; //在栈构造之前和销毁之后，base的值为NULL
	SElemType *top; //栈顶指针
	int stacksize; //当前已分配的存储空间，以元素为单位
} SqStack;


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

//设置空栈
bool ClearStack(SqStack &s)
{
	if ( s.base == NULL ) {
		exit(1);
	}
	s.base = s.top;
	return true;
	
}

//返回当前栈的长度
int StackLength(SqStack &s)
{
	if ( s.base == NULL ) {
		exit(1);
	}
	//printf("s.top=%d\ts.base=%d\n", s.top, s.base);
	return s.top-s.base;
}

//取出栈顶元素
SElemType GetTop(SqStack &s)
{
	SElemType e = 0;
	if ( s.top - s.base == 0 ) {
		return false;
	}
	e = *(s.top-1);
	
	return e;
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
	printf("s.top=%d\ts.base=%d\n", s.top, s.base);
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

//遍历栈元素
bool PrintStack(SqStack &s)
{
	SElemType *i;
	if ( s.top - s.base == 0 ) {
		return false;
	}
	
	for ( i=s.base; i<s.top; i++ ) {
		printf("%d ", *i);
	}
	printf("\n");
	
	return true;
}

int main(int argc, char const *argv[])
{
	srand(time(0));
	
	SqStack s;
	bool flag = false;
	flag = InitStack(s);
	printf("是否成功初始化栈：flag = %d\n", flag);
	
	printf("--------------------------------------------------------\n");
	
	for ( int i=0; i<9; i++ ) {
		flag = false;	
		Push(s, -30+rand()%100);
	}
	
	PrintStack(s);
	
	int length = StackLength(s);
	printf("length = %d\n", length);
	
	int topNum = GetTop(s);
	printf("topNum = %d\n", topNum);
	
	printf("--------------------------------------------------------\n");
	
	for ( int i=0; i<3; i++ ) {
		topNum = 0;
		flag = false;
		flag = Pop(s, topNum);
		printf("flag = %d\ttopNum = %d\n", flag, topNum);
	}

	printf("--------------------------------------------------------\n");
	
	flag = true;
	flag = StackEmpty(s);
	printf("flag=0表示非空栈，flag=1表示空栈：\n");
	printf("flag = %d\n", flag);
	
	printf("--------------------------------------------------------\n");
	
	flag = false;
	flag = ClearStack(s);
	printf("是否成功设置空栈：flag = %d\n", flag);
	
	flag = false;
	DestoryStack(s);
	printf("是否成功销毁栈：flag = %d\n", flag);
	
	return 0;
}
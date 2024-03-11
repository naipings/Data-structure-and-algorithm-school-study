//顺序栈的应用————括号匹配

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_INIT_SIZE 100 //存储空间初始分配量
#define STACKINCREMENT 10 //存储空间分配增量

typedef char SElemType;

typedef struct {
	SElemType *base; //在栈构造之前和销毁之后，base的值为NULL
	SElemType *top; //栈顶指针
	int stacksize; //当前已分配的存储空间，以元素为单位
} SqStack;


//初始化
bool InitStack(SqStack &s)
{
	s.base = (char *)malloc(STACK_INIT_SIZE*sizeof(char));
	if ( !s.base ) {
		printf("Error!");
		exit(-1);
	}
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
bool Push(SqStack &s, char e)
{
	//插入元素e为新的栈顶元素
	if ( s.top - s.base >= s.stacksize ) { //栈满，追加存储空间
		s.base = (char *)realloc(s.base, (s.stacksize + STACKINCREMENT)*sizeof(char));
		s.top = s.base + s.stacksize;
		s.stacksize += STACKINCREMENT;	
	}
	* s.top++ = e;
	return true;
}

//出栈
bool Pop(SqStack &s, char &e)
{
	//若栈不空，则删除s的栈顶元素，用e返回其值，并返回true；否则返回false
	if ( s.top - s.base == 0 ) {
		return false;
	}
	e = * --s.top;
	
	return true;
}

//括号匹配
bool bracketCheck(char str[],int length)
{
	SqStack s;
	InitStack(s); //初始化栈
	for( int i=0; i<length; i++ ) {
		if( str[i]=='(' || str[i]=='{' || str[i]=='[' ) {
			Push(s,str[i]); //扫描到左括号就入栈
		} else {
			if( StackEmpty(s) ) { //扫描到右括号，当前栈为空，即右括号单身情况
				return false; //匹配失败
			}
			char topElem; //用来保存弹出栈的栈顶元素
			Pop(s, topElem); //栈顶元素出栈
			if( str[i]==')' && topElem!='(' ) {
				return false;
			}
			if( str[i]=='}' && topElem!='{' ) {
				return false;
			}
			if( str[i]==']' && topElem!='[' ) {
				return false;
			}
		}
	}
	bool flag = StackEmpty(s);
	DestoryStack(s);
	return flag;
}

int main(int argc, char const *argv[])
{
	char s[STACK_INIT_SIZE];
	printf("请输入需要判断的括号：\n");
	scanf("%s", s);
	
	int len = strlen(s);
	printf("当前输入的括号个数为：%d\n",len);
	
	printf("--------现在开始进行判断--------\n");
	if( bracketCheck(s, len) ) {
		printf("匹配成功！");
	} else {
		printf("匹配失败！");
	}


	return 0;
}
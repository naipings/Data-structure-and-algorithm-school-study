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

#define MAXSIZE 80
typedef struct {
	SElemType data[MAXSIZE];
	int length;
} HString;

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
void PrintStack(SqStack &s, SElemType *s0)
{
	SElemType *i;
	if ( s.top - s.base == 0 ) {
		return;
	}
	
	int cnt = 0;
	for ( i=s.base; i<s.top; i++ ) {
		s0[cnt++] = *i;
	}
	s0[cnt] = '\0';;
}

void PrintStack2(SqStack &s)
{
	SElemType *i;
	if ( s.top - s.base == 0 ) {
		return;
	}
	
	int cnt = 0;
	for ( i=s.base; i<s.top; i++ ) {
		printf("%c ", *i);
	}
	printf("\n");
	
}

//返回当前栈的长度
int StackLength(SqStack &s)
{
	if ( s.base == NULL ) {
		exit(1);
	}
	return s.top-s.base;
}

void GetNext(HString t, int next[])
{
	int j, k;
	j=0; k=-1;
	next[0] = -1;
	
	//因为next数组中j的最大为t.length-1，而没有被next数组赋值都是在j++之后，
	//所以最后一次经过while循环时，j为t.length-2
	while ( j < t.length-1 ) {
		if ( k==-1 || t.data[j]==t.data[k] ) { //k为-1，或比较的字符相等时
			j++;
			k++;
			next[j] = k;
			//对应字符匹配的情况下，主串与字串指向同步右移
			//对求字符串“aaaaab”求next数组，还需要改进
//			printf("(1) j=%d, k=%d, next[%d]=%d\n",j, k, j, k);
		}
		else {
			k = next[k];
			//由于next[k]的值 代表的是 下标为k的字符 前面的字符串 最长相等前后缀 的长度，
			//也表示 该处字符不匹配时 应该回溯到的字符的下标
			//这个值给k后 又进行while循环判断，此时t.data[k]即指 最长相等前缀 的后一个字符
//			printf("(2) k=%d\n", k);
			
		}
	}
}

bool KMP(HString s, HString t)
{
	int next[MAXSIZE], i=0, j=0;
	GetNext(t, next);
	
	while ( i<s.length && j<t.length ) {
		if ( j==-1 || s.data[i]==t.data[j] ) {
			i++;
			j++;
		}
		else {
			j = next[j]; //i不变，j后退
		}
	}
	
	if( j>= t.length ) {
		return true;// 返回匹配模式串的首字符下标
	}
	else {
		return false; //返回不匹配标志
	}
	
}

bool subStringMatch(char *s1, char *s2)
{
	SqStack s;
	InitStack(s);
	HString s0, t;
	
	for( int i=0; i<strlen(s1); i++ ) {
		Push(s, s1[i]);
		if ( StackLength(s) >= 1 ) {
			if( StackEmpty(s) ) {
				return false; //匹配失败
			}
			SElemType topElem; //用来保存弹出栈的栈顶元素
			Pop(s, topElem); //栈顶元素出栈
			
			//利用KMP算法查找字串（即：topElem是否存在）
			int cnt = 0;
			for ( int k=i+1; k<strlen(s1); k++ ) {
				s0.data[cnt] = s1[k];
				cnt++;
			}
			s0.data[cnt] = '\0';
			s0.length = strlen(s0.data);
			t.data[0] = topElem;
			t.length = strlen(t.data);
//			printf("strlen(s1)=%d\tcnt=%d\ts0.data=%s\tt.data=%s\t", strlen(s1), cnt, s0.data, t.data);
			bool flag = KMP(s0, t);
			
			if( flag ) {
				//判断删除位置
				char temps = s1[i+1];
//				printf("temps=%c\t", temps);	
				if ( topElem > temps ) {
					Push(s, topElem);
					int length = strlen(s1);
					char s3[80];
					int m = 0;
					int cnt = 0;
					for ( m=i; m<length; m++ ) {
						if ( s1[m] == topElem ) {						
							continue;
						}
						s3[cnt++] = s1[m];
					}
					s3[cnt] = '\0';
					s1 = s3;
					i = -1;
				}	
			} else {
				Push(s, topElem);
			}
//			printf("s1=%s\n\n", s1);
		}
	}
	
	PrintStack(s, s2);
	
	StackEmpty(s);
	DestoryStack(s);
	return true;
}

int main(int argc, char const *argv[])
{
	char s1[] = "CODEFORCES";
	char s2[] = "SWFLLDJGPAXS";
	char s3[] = "AEZAKMI";
	char s4[] = "ABACABA";
	char s5[] = "CONVEXHULL";
	char s6[] = "SWFLLDJGPAXS";
	char s7[] = "MYNEEOCKTXPQJPZ";

	char s8[40], s9[40], s10[40], s11[40], s12[40], s13[40], s14[40];
	
	printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n", s1, s2, s3, s4, s5, s6, s7);
	subStringMatch(s1, s8);
	subStringMatch(s2, s9);
	subStringMatch(s3, s10);
	subStringMatch(s4, s11);
	subStringMatch(s5, s12);
	subStringMatch(s6, s13);
	subStringMatch(s7, s14);
	printf("\n\n");
	printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n", s8, s9, s10, s11, s12, s13, s14);

	return 0;
}
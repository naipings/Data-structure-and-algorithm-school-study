//串的堆分配表示及相关函数实现
#include <stdio.h>
#include <Stdlib.h>
#include <string.h>
#include <time.h>

#define STRING_INIT_SIZE 80
#define STRINGINCREMENT 20

typedef struct {
	char *ch;
	int length;
	int stringsize;
} HString;

//串的初始化
bool init(HString &s)
{
	s.ch = (char *)malloc(STRING_INIT_SIZE*sizeof(char));
	if ( !s.ch ) {
		printf("Error!");
		exit(-1);
	}
	s.stringsize = STRING_INIT_SIZE;
	
	return true;
}

//串的销毁
bool destroyString(HString &s)
{
	if ( s.ch == NULL ) { //串结构不存在，程序异常退出
		exit(1);
	}
	free(s.ch);
	s.length=0;
	s.stringsize=0;
	
	return true;
}

//串的读入
bool readString(HString &s)
{
	if ( !s.ch ) {
		return false;
	}
	gets(s.ch);
	s.length = strlen(s.ch);
	
	while ( s.length > s.stringsize ) {
		s.ch = (char *)realloc(s.ch, (s.stringsize+STRINGINCREMENT)*sizeof(char));
		s.stringsize += STRINGINCREMENT;
	}
		
	return true;
}

void printString(HString &s)
{
	if ( !s.ch ) {
		printf("ERROR1");
		exit(-1);
	}
	puts(s.ch);
	
}

//插入函数insert()
bool myInsert(HString &s1, HString &s2, int pos)
{
	if( s1.length < pos ) {
		return false;
	}
	if ( s1.length + s2.length > s1.stringsize ) {
		s1.ch = (char *)realloc(s1.ch, (s1.length+s2.length)*sizeof(char));
		s1.stringsize = s1.length+s2.length;
	}
	
	int len = s1.length-pos;
	printf("len=%d\n", len);
	if ( len != 0 ) {
		char *temp = (char *)malloc((len)*sizeof(char));
		int cnt = pos;	
		for ( int i=0; i<len; i++ ) {
			temp[i] = s1.ch[cnt++];
		}
		temp[len] = '\0';
		printf("temp=");
		puts(temp);
		
		cnt = pos;
		s1.length = pos;
		for ( int i=0; i<s2.length; i++ ) {
			s1.ch[cnt++] = s2.ch[i];
			s1.length++;
		}
		s1.ch[s1.length] = '\0';
		
		for ( int i=0; i<len; i++ ) {
			s1.ch[s1.length] = temp[i];
			s1.length++;
		}
		free(temp);
	}
	else if ( len == 0 ) {
		for ( int i=0; i<s2.length; i++ ) {
			s1.ch[s1.length] = s2.ch[i];
			s1.length++;
		}
	}
	printf("s1.length=%d\n", s1.length);
	s1.ch[s1.length] = '\0';
	
	return true;
}

//取子串
bool subString(HString &s, HString &sub, int pos, int len)
{
	if ( pos<1 || pos>s.length || len<0 ) {
		return false;
	}
	if ( sub.ch ) {
		free(sub.ch); //释放旧空间
	}
	if ( !len ) { //空字串
		sub.ch = NULL;
		sub.length = 0;
	}
	else {
		sub.ch = (char *)malloc(len * sizeof(char));
		int cnt = pos-1;
		for ( int i=0; i<len; i++ ) {
			sub.ch[i] = s.ch[cnt+i];
		}
		sub.ch[len] = '\0';
		sub.length = len;
	}
	return true;
	
}


int main()
{
	HString s1;
	HString s2;
	HString sub;
	
	bool flag = false;
	
	flag = init(s1);
	printf("init(s1): flag=%d\n", flag);
	flag = init(s2);
	printf("init(s2): flag=%d\n", flag);
	
	flag = readString(s1);
	printf("readString(s1): flag=%d\n", flag);
	flag = readString(s2);
	printf("readString(s2): flag=%d\n", flag);
	
	printf("s1=");
	printString(s1);
	printf("s2=");
	printString(s2);
	
	flag = myInsert(s1, s2, 5);
	printf("myInsert(): flag=%d\n", flag);
	
	printf("insert s1=");
	printString(s1);
	
	init(sub);
	flag = subString(s1, sub, 5, 9);
	puts(sub.ch);
	
	flag = destroyString(s1);
	printf("destroyString(s1): flag=%d\n", flag);
	flag = destroyString(s2);
	printf("destroyString(s2): flag=%d\n", flag);
	
	
	return 0;
}
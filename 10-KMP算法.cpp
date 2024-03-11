// KMP算法
#include <stdio.h>
#include <Stdlib.h>
#include <string.h>

#define MAXSIZE 80

typedef struct {
	char data[MAXSIZE];
	int length;
} HString;

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
			printf("(1) j=%d, k=%d, next[%d]=%d\n",j, k, j, k);
		}
		else {
			k = next[k];
			//由于next[k]的值 代表的是 下标为k的字符 前面的字符串 最长相等前后缀 的长度，
			//也表示 该处字符不匹配时 应该回溯到的字符的下标
			//这个值给k后 又进行while循环判断，此时t.data[k]即指 最长相等前缀 的后一个字符
			printf("(2) k=%d\n", k);
			
		}
	}
}

int KMP(HString s, HString t)
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
		return (i-t.length);// 返回匹配模式串的首字符下标
	}
	else {
		return (-1); //返回不匹配标志
	}
	
}


int main()
{
	HString s, t;
	gets(s.data);
	s.length = strlen(s.data);
	gets(t.data);
	t.length = strlen(t.data);
	
	int pos = KMP(s, t);

	printf("pos=%d\n", pos);
	
	return 0;
}

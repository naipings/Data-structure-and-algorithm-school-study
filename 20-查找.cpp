//查找————顺序表的查找，二分查找
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXSIZE 80

typedef int KeyType;
//顺序表的查找————第一个元素用作监视哨（存储要查找的元素），然后从后往前进行查找，直到回到第一个位置（所以肯定能匹配上）
typedef struct {
	KeyType number[MAXSIZE];
	int length;
} SeqList;

void Init(SeqList &list)
{
	srand(time(0));
	int n = 0;
	printf("请输入顺序表的长度：\n");
	scanf("%d", &n);
	for ( int i=1; i<=n; i++ ) {
		list.number[i] = -40 + rand()%100;
	}
	list.length = n;
	
}

void printSeqList(SeqList list)
{
	for ( int i=1; i<=list.length; i++ ) {
		printf("%d ", list.number[i]);
	}
	printf("\n");	
}

int searchSeqList(SeqList &list, KeyType num)
{
	list.number[0] = num;
	for ( int i=list.length; i>=0; i-- ) {
		if ( list.number[i] == num ) {
			return i;
		}
	}
	return 0;
}

//二分查找
int binarySearchSeqList(SeqList &list, KeyType num)
{
	//冒泡排序
	int t = 0;
	for ( int i=1; i<=list.length; i++ ) {
		for ( int j=list.length; j>i; j-- ) {
			if ( list.number[j] < list.number[j-1] ) {
				t = list.number[j-1];
				list.number[j-1] = list.number[j];
				list.number[j] = t;
			}
		}
	}
	printSeqList(list);
	
	int left = 1;
	int right = list.length;
	int temp = 0;	
	for ( int i=0; left <= right; i++ ) {
		temp = (left + right) / 2;
		if ( list.number[temp] > num ) {
			right = temp - 1;
		} else if ( list.number[temp] < num ) {
			left = temp + 1;
		} else if ( list.number[temp] == num ) {
			return temp;
		}
	}
	
	return -1;		
}

int main()
{
	SeqList list;
	Init(list);
	
	printSeqList(list);
	
	int num = 0;
	printf("请输入要查找的数字：\n");
	scanf("%d", &num);
	int pos = searchSeqList(list, num);
	printf("pos=%d\tlist.number[pos]=%d\n", pos, list.number[pos]);
	
	printf("请输入通过二分查找要查找的数字：\n");
	scanf("%d", &num);
	pos = binarySearchSeqList(list, num);
	if ( pos != -1 ) {
		printf("pos=%d\tlist.number[pos]=%d\n", pos, list.number[pos]);
	} else {
		printf("pos=%d\tlist.number[pos]=NULL\n", pos);
	}
				
	return 0;
}
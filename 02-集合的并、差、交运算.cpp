//集合的并、差、交等运算
//#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <Stdlib.h>
#include <time.h>
//#include <assert.h>

#define MAXSIZE 20

typedef int SLDataType;
typedef struct SeqList {    //顺序表的结构
	SLDataType *Data;
	int size;
	int capacity;
}SeqList;

//初始化
void SLInit(SeqList* ps) {
	ps->Data = (SLDataType*)malloc(MAXSIZE * sizeof(SLDataType));
	if (!(ps->Data))
		exit(0);
	ps->size = 0;
	ps->capacity = MAXSIZE;
}

//容量判断（判断顺序表是否已经存满。如果已经存满了，那么我们就需要对它进行扩容
void Check_Capacity(SeqList* ps) {
	//assert(ps);
	if (ps->capacity == ps->size) {
		int new_capacity = ps->capacity = (ps->capacity) * 2; //每次存满时，让新容量为原容量的2倍

			SLDataType * tmp = (SLDataType*)realloc(ps->Data, new_capacity * sizeof(SLDataType));

		if (tmp == NULL) { //扩容失败
			perror("realloc fail");
			exit(-1);
		}
		ps->Data = tmp;
		ps->capacity = new_capacity;
	}
}

//插入
void SL_Insert(SeqList* ps, int pos, SLDataType x) {
	//判定pos是否合法
	if ( pos > ps->size || pos < 0 ) {
		return;
	}
	
	Check_Capacity(ps);
	//将pos位置后的元素全部都向后移动一位
	for (int i = ps->size - 1; i >= pos; i--) {
		ps->Data[i + 1] = ps->Data[i];
	}

	ps->Data[pos] = x;
	ps->size++;
}

//顺序表指定位置删除
void SL_Erase(SeqList* ps, int pos) {
	//检查pos是否合法
	if ( pos<0 || pos>=ps->size ) {
		return;
	}
	//将pos位置后的元素全部都向前移动一位
	for (int i = pos; i < ps->size; i++) {
		ps->Data[i] = ps->Data[i + 1];
	}

	ps->size--;
}
 
//打印
void SLPrint(SeqList * ps) {
	if(ps->size==0)
	{
		printf("顺序表为空！");
		return ;
	}
	for (int i = 0; i < ps->size; i++) {
		printf("%d ", ps->Data[i]);
	}
	printf("\n");
}

//销毁顺序表
void SL_Destroy(SeqList * ps) {
	//assert(ps);
	free(ps->Data);
	ps->Data = NULL;
	ps->capacity = 0;
	ps->size = 0;
}

//集合的并运算
void SL_Unite(SeqList * ps1, SeqList* ps2)
{	
	for ( int i=0; i<ps1->size; i++ ) {
		for ( int j=0; j<ps2->size; j++ ) {
			if ( ps1->Data[i] == ps2->Data[j] ) {
				ps2->Data[j] = ps1->Data[0];
			}
		}
		//SLPrint(ps2);
	}
	
	for ( int j=0; j<ps2->size; j++ ) {
		if ( ps2->Data[j] != ps1->Data[0] ) {
			ps1->Data[ps1->size] = ps2->Data[j];
			ps1->size++;
		}
	}
	
}

//集合的差运算
void SL_DifOperation(SeqList * ps1, SeqList* ps2)
{
	for ( int j=0; j<ps2->size; j++ ) {
		for ( int i=0; i<ps1->size; i++ ) {
			if ( ps1->Data[i] == ps2->Data[j] ) {
				SL_Erase(ps1, i);
			}
		}
		//SLPrint(ps1);
	}
}

//集合的交运算
void InsOperation(SeqList * ps1, SeqList* ps2, SeqList* ps3)
{
	for ( int i=0; i<ps1->size; i++ ) {
		for ( int j=0; j<ps2->size; j++ ) {
			if ( ps1->Data[i] == ps2->Data[j] ) {
				SL_Insert(ps3, ps3->size, ps1->Data[i]);	
			}
		}
		//SLPrint(ps3);
	}
}

int main(int argc, char const* argv[])
{
	srand(time(0));
	
	SeqList* ps1 = (SeqList*)malloc(1 * sizeof(SeqList));
	SLInit(ps1);
	for (int i = 1; i < 10; i++) {
		SL_Insert(ps1, i - 1, rand()%30);
//		SL_Insert(ps1, i - 1, i);
	}
	for ( int i=0; i<ps1->size; i++ ) {
		for ( int j=0; j<ps1->size; j++ ) {
			if ( ps1->Data[i] == ps1->Data[j] && j!=i ) {
				ps1->Data[j] = -rand()%30;
			}
		}
	}	
	SLPrint(ps1);

	SeqList* ps2 = (SeqList*)malloc(1 * sizeof(SeqList));
	SLInit(ps2);
	for ( int i=0; i<9; i++ ) {
		SL_Insert(ps2, i, rand()%30);
//		SL_Insert(ps2, i, i);
	}
	for ( int i=0; i<ps2->size; i++ ) {
		for ( int j=0; j<ps2->size; j++ ) {
			if ( ps2->Data[i] == ps2->Data[j] && j!=i ) {
				ps2->Data[j] = -rand()%30;
			}
		}
	}
	SLPrint(ps2);
	
	printf("--------------------------------\n");	
//	SL_Unite(ps1, ps2);	
//	//SL_DifOperation(ps1, ps2);
//	printf("--------------------------------\n");
//	SLPrint(ps1);
	
	SeqList* ps3 = (SeqList*)malloc(1 * sizeof(SeqList));
	SLInit(ps3);
	InsOperation(ps1, ps2, ps3);
	printf("--------------------------------\n");
	SLPrint(ps3);
	
	SL_Destroy(ps1);
	SL_Destroy(ps2);
	free(ps1);
	free(ps2);
	
	return 0;
}
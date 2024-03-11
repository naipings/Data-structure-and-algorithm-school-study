#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define MAXSIZE 100
 
typedef int SLDataType;
typedef struct SeqList {    //顺序表的结构
	SLDataType *Data;
	int size;
	int capacity;
}SeqList;

//初始化
int InitList(SeqList *ps)    //初始化顺序表
{
	ps->Data = (SLDataType*)malloc(MAXSIZE*sizeof(SLDataType));
	if(!(ps->Data))
		exit(0);
	ps->size=0;
	ps->capacity=MAXSIZE;
	return 1;
}

//容量判断
void Check_Capacity(SeqList* ps) {
	if (ps->capacity == ps->size) {
		int new_capacity = ps->capacity = 0 ? 4 : (ps->capacity) * 2; //如果是第一次添加元素，capacity就设置为4；以后每次存满时，让新容量为原容量的2倍
		//realloc()函数需两个参数：一个是包含地址的指针（该地址由之前的malloc()、calloc()或realloc()函数返回），另一个是要新分配的内存字节数。
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

//归并
void MergeList(SeqList *ps1,SeqList *ps2,SeqList *ps3) {        //合并两个顺序表放入c中
	int i=0;
	int j=0;
	int k=0;
	int La_len=ps1->size;
	int Lb_len=ps2->size;
	ps3->size=ps1->size+ps2->size;
	while((i<La_len)&&(j<Lb_len)){
		if(ps1->Data[i]<=ps2->Data[j])    //如果a当前的值小于b
		{
			ps3->Data[k]=ps1->Data[i];    //c放入当前a的值
			i++;                    //a,c都往后移一位
			k++;
			
		}
		else{                        //如果a当前值大于等于b
			ps3->Data[k]=ps2->Data[j];       //c放入当前b的值
			j++;                          //b,c都往后移一位
			k++;
 
		}
	}
	while(i<La_len){            //如果b遍历完，a还没遍历完，把a剩余的全放入c中
		ps3->Data[k]=ps1->Data[i];
		  k++;
		  i++;
	}
	while(j<Lb_len){            //如果a遍历完，b还没遍历完，把b剩余的全放入c中
		ps3->Data[k]=ps2->Data[j];
		  k++;
		  j++;
	}
}

//销毁
void SL_Destroy(SeqList * ps) {
	free(ps->Data);
	ps->Data = NULL;
	ps->capacity = 0;
	ps->size = 0;
}
	
int main(int argc, const char* argv[])
{
	srand(time(0));
	
	SeqList *ps1;
	SeqList *ps2;
	SeqList *ps3;
	ps1 = (SeqList*) malloc(sizeof(SeqList));
	ps2 = (SeqList*) malloc(sizeof(SeqList));
	ps3 = (SeqList*) malloc(sizeof(SeqList));
	InitList(ps1);
	InitList(ps2);
	
	for (int i = 1; i < 10; i++) {
		//SL_Insert(ps1, i - 1, rand()%100);
		SL_Insert(ps1, i - 1, i);
	}
	for ( int i=0; i<9; i++ ) {
		//SL_Insert(ps2, i, rand()%100);
		SL_Insert(ps2, i, i);
	}
	printf("输入顺序表A：");  
	SLPrint(ps1);
	printf("输入顺序表B：");
	SLPrint(ps2);
	
	ps3->Data = (SLDataType*)malloc(MAXSIZE*sizeof(SLDataType));
	MergeList(ps1,ps2,ps3);
	
	//getchar();
	printf("输入顺序表C：");
	SLPrint(ps3);
	//getchar();
	
	SL_Destroy(ps1);
	SL_Destroy(ps2);
	free(ps1);
	free(ps2);
	free(ps3->Data);
	free(ps3);
	
	return 0;
}
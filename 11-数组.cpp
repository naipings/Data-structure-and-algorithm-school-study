//数组与稀疏矩阵
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_DIM 8
#define MAX_SIZE 20
#define MAXSIZE 100 //非零元个数最大值

typedef bool Status;
typedef int ElemType;

//数组定义：
typedef struct {
	ElemType * base;
	int dim;
	int * bounds;
	int * constants;
} Array;

//稀疏矩阵定义：
typedef struct {
	int row, col; //具体非零元的行下标和列下标
	ElemType data;
} Triple;

typedef struct {
	Triple data[MAXSIZE+1]; //非零元三元组表，data[0]未使用
	int mu, nu, tu; //矩阵的行数、列数和非零元个数
} TSMatrix;


//Status initArray(Array &a, int dim, ...)
//{
//
//}

//生成随机稀疏矩阵
Status initTSMatrix(TSMatrix &m)
{
	int cnt = 1;
	for ( int i=0; i<m.mu; i++ ) {
		for ( int j=0; j<m.nu; j++ ) {
			j = rand()%m.nu;
			if ( j > m.data[cnt-1].col ) {
				m.data[cnt].data = -5 + rand()%15;
				m.data[cnt].row = i;
				m.data[cnt].col = j;
				cnt++;
				m.tu++;
			}

			if ( j%3 == 0 ) {
				break;
			}
		}
	}
	
	return true;
}

//打印稀疏矩阵
Status printTSMatrix(TSMatrix &m)
{
	if ( m.tu == 0 || m.mu == 0 || m.nu == 0 ) {
		return false;
	}
	
	int cnt=1;
	for ( int i=0; i<m.mu; i++ ) {
		for ( int j=0; j<m.nu; j++ ) {
			if ( i==m.data[cnt].row && j==m.data[cnt].col && cnt <=m.tu ) {
				printf("%d ", m.data[cnt].data);
				cnt++;
			}
			else {
				printf("0 ");
			}			
		}
		printf("\n");
	}
	printf("\n");
	
	return true;
}

//转置稀疏矩阵
Status TransposeTSMatrix(TSMatrix m, TSMatrix &tm)
{
	tm.mu = m.nu;
	tm.nu = m.mu;
	tm.tu = m.tu;
	if ( tm.tu ) {
		int q = 1;
		for ( int col=1; col<=m.nu; col++ ) {
			for ( int p=1; p<=m.tu; p++ ) {
				if ( m.data[p].col == col ) {
					tm.data[q].row = m.data[p].col;
					tm.data[q].col = m.data[p].row;
					tm.data[q].data = m.data[p].data;
					q++;
				}
			}
		}		
	}
	else {
		return false;
	}
	
	return true;
}

//快速转置求稀疏矩阵
Status FastTransposeTSMatrix(TSMatrix m, TSMatrix &tm)
{
	tm.mu = m.nu;
	tm.nu = m.mu;
	tm.tu = m.tu;
	int num[MAXSIZE], cpot[MAXSIZE];
	if ( tm.tu ) {
		for ( int col=1; col<=m.nu; col++ ) {
			num[col] = 0;
		}
		for ( int t=1; t<=m.tu; t++ ) {
			num[m.data[t].col]++;
		}
		cpot[1] = 1;
		for ( int col=2; col<=m.nu; col++ ) {
			cpot[col] = cpot[col-1] + num[col-1];	
		}
		for ( int p=1; p<=m.tu; p++ ) {
			int col = m.data[p].col;
			int q = cpot[col];
			tm.data[q].row = m.data[p].col;
			tm.data[q].col = m.data[p].row;
			tm.data[q].data = m.data[p].data;
			cpot[col]++;
		}
	}
	else {
		return false;
	}
	return true;
}

//矩阵加法、乘法见以前代码

int main()
{
	srand(time(0));
	
	TSMatrix m, tm, ftm;
	printf("请输入矩阵行列数：");
	scanf("%d %d", &m.mu, &m.nu);
	
	bool flag = initTSMatrix(m);
//	printf("flag=%d\n", flag);	
	flag = printTSMatrix(m);
//	printf("flag=%d\n", flag);
	printf("m.tu=%d\n", m.tu);
	
	flag = TransposeTSMatrix(m, tm);
//	printf("flag=%d\n", flag);
	printTSMatrix(tm);
	
	flag = FastTransposeTSMatrix(m, ftm);
//	printf("flag=%d\n", flag);
	printTSMatrix(ftm);
	
	return 0;
}
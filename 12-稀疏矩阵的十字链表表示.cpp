//稀疏矩阵的十字链表表示
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAXSIZE 100

typedef bool Status;
typedef int ElemType;

typedef struct OLNode {
	int row, col;
	ElemType value;
	struct OLNode *down, *right;
} OLNode, *OLink;

typedef struct {
	OLink *rhead, *chead; //行和列链表头指针
	int mu, nu, tu; //稀疏矩阵行数、列数和非零元个数
} CrossList, *CrossListPtr;

//创建稀疏矩阵，采用十字链表的方式存储表示
Status CreateTSMatrix(CrossListPtr mat)
{
	if ( mat ) free(mat);//释放mat原有的内存
	mat = (CrossListPtr)malloc(sizeof(CrossList));
	int a;
	int i, j, e;
	int cnt;
	OLNode *p, *q;
	printf("请分别输入行数，列数，非零元个数：");
	scanf("%d %d %d", &mat->mu, &mat->nu, &mat->tu);
	//分别对行链表头和列链表头分配内存
	if ( !(mat->rhead=(OLink*)malloc((mat->mu + 1)*sizeof(OLink))) ) exit(-1);
	if ( !(mat->chead=(OLink*)malloc((mat->nu + 1)*sizeof(OLink))) ) exit(-1);
	
	//使各行链表和各列链表都为空表
	for ( a=1; a<=mat->mu; a++ ) {
		mat->rhead[a] = NULL;
	}
	for ( a=1; a<=mat->nu; a++ ) {
		mat->chead[a] = NULL;
	}
	
	for ( cnt=1; cnt<=mat->tu; cnt++ ) {
		printf("请分别输入第%d个元素的行数、列数和值：", cnt);
		scanf("%d %d %d", &i, &j, &e);
		if ( !(p=(OLNode *)malloc(sizeof(OLNode))) ) exit (-1);
		//生成结点
		p->row = i;
		p->col = j;
		p->value = e;
		
		//如果行链表数组的第i行的头结点右边是空 或者右边元素的列数比j大，就让p左边被列表的rhead指针指向
		if ( mat->rhead[i] == NULL || mat->rhead[i]->col > j ) {
			p->right = mat->rhead[i];
			mat->rhead[i] = p;
		}
		else {
			//找到将要插入的合适位置，要么右边为空，要么q->right->col < j
			for ( q=mat->rhead[i]; (q->right)&&q->right->col < j; q=q->right );
			//行插入
			p->right = q->right;
			q->right = p;
		}
		
		if ( mat->chead[j] == NULL || mat->rhead[j]->row > i ) {
			p->down = mat->chead[j];
			mat->chead[j] = p;
		}
		else {
			for ( q=mat->chead[j]; (q->down)&&q->down->row < i; q=q->down );
			//列插入
			p->down = q->down;
			q->down = p;		
		}
	}
	
	//检验是否存储成功
	int check[10][10];
	memset(check, 0, sizeof(check));
	int i1, j1;
	OLink p1;
	for ( i1=1; i1<=mat->mu; i1++ ) {
		for ( p1=mat->rhead[i1]; p1; p1=p1->right ) {
			check[i1][p1->col] = p1->value;
		}
	}
	for ( i1=1; i1<=mat->mu; i1++ ) {
		for ( j1=1; j1<=mat->nu; j1++ ) {
			printf("%d ", check[i1][j1]);
		}
		printf("\n");
	}
	
	return true;
}

int main()
{
	CrossListPtr mat = NULL;
	CreateTSMatrix(mat);
	
	return 0;
}
//图的表示与实现
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "Queue.h"

#define MAX_VERTEX_NUM 10
typedef enum{DG, DN, UDG, UDN} GraphKind;

typedef bool Status;
typedef int ElemType;
//图的数组表示（邻接矩阵）
typedef struct MNode {
	ElemType vertex[MAX_VERTEX_NUM]; //顶点
	int Arc[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; //边/弧
	int vernum, arcnum; //顶点个数，边个数
	GraphKind kind;
}GraphNode, *Graph;

int IsRead[MAX_VERTEX_NUM]; //标记顶点是否被遍历过
static int count = 0; //深度优先搜索用于第一次清零操作

//图的初始化
Status GraphInit(Graph *G)
{
	(*G) = (GraphNode *)malloc(sizeof(GraphNode));
	(*G)->vernum = 0;
	(*G)->arcnum = 0;
	if ( !(*G) ) {
		printf("INIT ERROR");
		exit(-1);
	}
	return true;
}

//查找位置
void GraphFindPos(Graph G, ElemType a, ElemType b, int *pos1, int *pos2)
{
	int i = 0;
	*pos1 = -1; *pos2 = -1; //设置初值
	for ( i=0; i<G->vernum; i++ ) {
		if ( G->vertex[i] == a ) {
			(*pos1) = i;
			continue;
		} else if ( G->vertex[i] == b ) {
			(*pos2) = i;
			continue;
		}
	}
}

//建立图
Status GraphBuild(Graph G)
{
	int choice = 0, num = 0, pos1, pos2, i, j, weight;
	ElemType a, b, ch;
	printf("请选择建立的图的类型：1.有向图，2.有向网，3.无向图，4.无向网：\n");
	scanf("%d", &choice);
	getchar();
	printf("\n"); //下一行（换一下行）
	
	//有向图
	if ( choice == 1 ) {
		//初始化弧
		for ( i=0; i<MAX_VERTEX_NUM; i++ ) {
			for ( j=0; j<MAX_VERTEX_NUM; j++ ) {
				G->Arc[i][j] = 0;
			}
		}
		G->kind = DG; //设置图的类型
		
		printf("请输入顶点（不超过10个，以-1结束）：\n");
		do {		
			scanf("%d", &ch);
			if ( ch==-1 && num==0 ) {
				return false;
			} else if ( ch!=-1 ) {
				G->vertex[num] = ch;
				num++;
			}
		} while ( ch!=-1 && num<10 );
		
		G->vernum = num; //顶点个数
		printf("num=%d\n", num);
		
		getchar(); //清除键盘缓冲区
		
		printf("请输入对应的弧（以a b格式输入，以-1 -1结束）：\n");
//		scanf("%c->%c", &a, &b);
		scanf("%d %d", &a, &b);
		while ( a!=-1 && b!=-1 ) {
			printf("%d, %d", a, b);
			GraphFindPos(G, a, b, &pos1, &pos2);
			printf("位置a:%d，位置b:%d\n", pos1, pos2);
			
			if ( pos1!=-1 && pos2!=-1 ) { //忽略不存在的顶点
				G->Arc[pos1][pos2] = 1;
				G->arcnum++;
			}
//			scanf("%c->%c", &a, &b);
			scanf("%d %d", &a, &b);
		}
		getchar(); //清空键盘缓冲区
	}
	
	//有向网
	else if ( choice == 2 ) {
		
	}
	
	//无向图
	else if ( choice == 3 ) {
		
	}
	
	//无向网
	else if ( choice == 4 ) {
		
	}
	
	//其他情况（非法输入的选择）
	else {
		printf("输入非法，请输入正确的数字！！\n");
		return false;
	}
	
	return true;
}

//深度优先搜索（for图）
void DepthFS(Graph G, int pos)
{
	int i = 0, j = 0;
	
	//未被遍历前进行清零操作
	if ( count == 0 ) {
		for ( i=0; i<MAX_VERTEX_NUM; i++ ) {
			IsRead[i] = 0; //清零
		}
		count++;
	}

	
	if ( IsRead[pos] == 0 ) {
		IsRead[pos] = 1; //从第一个开始
		printf("遍历顶点：%d\n", G->vertex[pos]);
	}
	
	for ( i=0; i<G->vernum; i++ ) {
		if ( G->Arc[pos][i] == 1 && IsRead[i] == 0 ) { //存在弧
			DepthFS(G, i);
		}
	}
}

//深度优先搜索（for网）
void DepthFS1(Graph G, int pos)
{
	
}

//深度优先搜索（选择器）
void DFS(Graph G)
{
	if ( G->kind == DG || G->kind == UDG ) { //图
		DepthFS(G, 0);
	}
	else if ( G->kind == DN || G->kind == UDN ) { //网
		DepthFS1(G, 0);
	}
}

//广度优先搜索搜索（for图）
void BroadthFS(Graph G, int pos)
{
	int i = 0, temp;
	Queue Q;
	QueueInit(&Q);
	for ( i=0; i<G->vernum; i++ ) {
		IsRead[i] = 0; //清零
	}
	
	if ( IsRead[pos] == 0 ) {
		IsRead[pos] = 1;
		printf("遍历顶点：%d\n", G->vertex[pos]);
	}
	QueuePush(&Q, pos);
	
	while ( !QueueEmpty(&Q) ) { //当队列不为空
		QueuePop(&Q, &temp);
		for ( i=0; i<G->vernum; i++ ) {
			if ( G->Arc[temp][i] == 1 && IsRead[i] == 0 ) {
				IsRead[i] = 1;
				printf("遍历顶点：%d\n", G->vertex[i]);
				QueuePush(&Q, i);
			}
		}
	}
	QueueDestory(&Q);
}

//广度优先搜索搜索（for网）
void BroadthFS2(Graph G, int pos)
{
	
}

//广度优先搜索（选择器）
void BFS(Graph G)
{
	if ( G->kind == DG || G->kind == UDG ) { //图
		BroadthFS(G, 0);
	}
	else if ( G->kind == DN || G->kind == UDN ) { //网
		BroadthFS2(G, 0);
	}
}

int main()
{
	int i = 0;
	Graph G = NULL;
	GraphInit(&G);
	GraphBuild(G);
	
//	for ( i=0; i<MAX_VERTEX_NUM; i++ ) {
//		IsRead[i] = 0; //未被遍历
//	}
	printf("\n深度优先搜索：\n");
	DFS(G);
	printf("\n广度优先搜索：\n");
	BFS(G);
		
	return 0;
}
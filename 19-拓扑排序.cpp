#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 
#define MVNUM  100
 
typedef struct ArcNode {
	int adjvex;
	struct ArcNode* next;
}ArcNode;
 
typedef struct VNode {
	char data;
	ArcNode* firstarc;
}VNode, AdjList[MVNUM];
 
typedef struct {
	AdjList vertices;
	int vexnum, arcnum;
}ALGraph;
//定位
int LocateVex(ALGraph* G, char v) {
	int i;
	for (i = 0; i < G->vexnum; i++) {
		if (G->vertices[i].data == v) {
			return i;
		}
	}
	return -1;
}
 
//有向图邻接表的建立
ALGraph* CreateGraph() {
	int i, j, k, v1, v2;
	ALGraph* G = (ALGraph*)malloc(sizeof(ALGraph));
	printf("输入顶点数和边数:\n");
	scanf("%d%d", &G->vexnum, &G->arcnum);
	getchar();
	printf("输入顶点信息：\n");
	for (i = 0; i < G->vexnum; i++) {
		scanf("%c", &G->vertices[i].data);
		G->vertices[i].firstarc = NULL;
	}
	getchar();
	for (k = 0; k < G->arcnum; k++) {
		printf("输入一条弧依附的起点和终点：\n");
		scanf("%c%c", &v1, &v2);
		getchar();
		i = LocateVex(G, v1), j = LocateVex(G, v2);
		ArcNode* p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = j;
		p->next = G->vertices[i].firstarc;
		G->vertices[i].firstarc = p;
	}
	return G;
}
//输出邻接表
void print(ALGraph* G) {
	int i;
	ArcNode* p = NULL;
	for (i = 0; i < G->vexnum; i++) {
		printf("%c", G->vertices[i].data);
		p = G->vertices[i].firstarc;
		while (p) {
			printf("-->%c", G->vertices[p->adjvex].data);
			p = p->next;
		}
		printf("\n");
	}
}
 
//Kahn算法实现拓扑排序
bool TopoSort(ALGraph* G) {
	int indegree[MVNUM] = { 0 };//记录顶点入度
	int i, j, v;
	int count = 0;//记录输出的顶点数
	int stack[MVNUM];//定义一个简单的数组栈
	int top = 0;//栈顶指针
	ArcNode* p = NULL;
 
	//统计各顶点入度
	for (i = 0; i < G->vexnum; i++) {
		p = G->vertices[i].firstarc;
		while (p != NULL) {
			indegree[p->adjvex]++;
			p = p->next;
		}
	}
 
	//将所有入度为0的顶点入队
	for (i = 0; i < G->vexnum; i++) {
		if (indegree[i] == 0) {
			stack[top++] = i;
		}
	}
 
	//栈非空时循环
	while (top > 0) {
		v = stack[--top];//出栈一个顶点
		printf("%c ", G->vertices[v].data);
		count++;//已输出的顶点数加1
		//遍历该顶点为起点的所有边
		p = G->vertices[v].firstarc;
		while (p != NULL) {
			indegree[p->adjvex]--;//入度减1
			//若入度为0，入队
			if (indegree[p->adjvex] == 0) {
				stack[top++] = p->adjvex;
			}
			p = p->next;//指向下一条边
		}
	}
 
	//输出顶点数小于总顶点数，说明有环
	if (count < G->vexnum) {
		printf("该图有环，拓扑排序失败。\n");
		return false;
	}
	return true;
}
 
int main() {
	ALGraph* G = CreateGraph();
	printf("邻接表：\n");
	print(G);
	printf("拓扑排序序列：\n");
	TopoSort(G);
	return 0;
}
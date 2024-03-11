#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MaxInt 32767
#define MVNum 100
#define ArcNum 100
#define OK 1
#define ERROR -1

typedef char VerTexType; 
typedef int ArcType;
typedef int status;

typedef struct{
	VerTexType vexs[MVNum] {'A','B','C','D','E','F'};
	ArcType arcs[MVNum][MVNum];
	int vexnum = 6,arcnum = 10;
}AMGraph; 

typedef struct{
	VerTexType Head;//起点 
	VerTexType Tail;//终点
	ArcType lowcast; 
}Edge[ArcNum];

VerTexType tempNum = 'A'; //存储prim()每一轮的mindot
VerTexType inNum[MVNum]; //已连通的结点数组
bool flag = false;

//创建无向图
status CreateUDN(AMGraph &G)
{
	for ( int i=0; i<G.vexnum; i++ ) {
		for ( int j=0; j<G.vexnum; j++ ) {
			if ( i == j ) {
				G.arcs[i][j] = 0;
			} else
				G.arcs[i][j] = MaxInt;//初始状态全部节点之间相互不可达
		}
	}
	G.arcs[0][1]=6;G.arcs[0][2]=1;G.arcs[0][3]=5;
	G.arcs[1][2]=5;G.arcs[1][4]=3;
	G.arcs[2][3]=5;G.arcs[2][4]=6;G.arcs[2][5]=4;
	G.arcs[3][5]=2;
	G.arcs[4][5]=6;
	for ( int i=0; i<G.vexnum; i++ ) {
		for ( int j=i+1; j<G.vexnum; j++ ) {
			if ( G.arcs[i][j] != MaxInt ) {
				G.arcs[j][i] = G.arcs[i][j];
			} 
		}
	}//矩阵对称 
	return OK; 
}

//打印表头，以及图的邻接矩阵
void ShowGraph(AMGraph G)
{
	printf(" ");
	for ( int i=0; i<G.vexnum;i++ ) {
		printf(" %c", G.vexs[i]);
	}
	printf("\n");
	for ( int i=0; i<G.vexnum; i++ ) {
		printf("%c ", G.vexs[i]);
		for ( int j=0; j<G.vexnum; j++ ) {
			if ( G.arcs[i][j] == MaxInt ) {
				printf("* ");
			} else {
				printf("%d ", G.arcs[i][j]);
			}
		}
		printf("\n");
	}
}

//定位Vexset数组中某一结点元素（本例即：大写字母），返回结点下标
int LocateVex(AMGraph G, VerTexType v)
{
	int i;
	for ( i=0; i<G.vexnum; i++ ) {
		if ( G.vexs[i] == v ) {
			return i;
		}
	} 
	return ERROR;
}

//返回结点元素
VerTexType Transform(AMGraph G, int vn)
{
	return G.vexs[vn]; 
}

//存储与上一轮mindot结点直接相连的边信息
int search_edge(AMGraph G, Edge &edge, int num)
{
	int cnt = 0;
	for ( int j=0; j<G.vexnum; j++ ) {
		if ( G.arcs[num][j] != MaxInt && G.arcs[num][j] != 0 ) {
			edge[cnt].Head = Transform(G, num);
			edge[cnt].Tail = Transform(G, j);
			edge[cnt].lowcast = G.arcs[num][j];
			cnt++;
		}
	}
	return cnt;
}

//确定与结点直接相连的最小权值的边，以及与之的另一个结点
VerTexType search_min(Edge edge, ArcType &minside, VerTexType &mindot, int cnt)
{
	VerTexType minhead = edge[0].Head;
	minside = edge[0].lowcast;
	mindot = edge[0].Tail;		
	for ( int j=0; j<cnt; j++ ) {
		if ( edge[j].lowcast < minside ) {
			minhead = edge[j].Head;
			minside = edge[j].lowcast;
			mindot = edge[j].Tail;
		}
	}
	return minhead;
}

void clear_edge(Edge &edge, int cnt)
{
	for ( int i=0; i<cnt; i++ ) {
		edge[i].Head = NULL;
		edge[i].Tail = NULL;
		edge[i].lowcast = 0;
	}
}

void Prim(AMGraph &G)
{
	//做一个结点的状态数组（用于判定该节点是否连通）
	int Vexset[MVNum];
	int incnt = 0;
	for ( int i=0; i<G.vexnum; i++ ) {
		Vexset[i] = 0;
	}
	
	for ( int i=0; i<G.vexnum; i++ ) {
	 	int num = LocateVex(G, tempNum);
		
		//存储与上一轮mindot结点直接相连的边信息（直接相连，即：权值不等于MaxInt），但如果与mindot相连的点Vexset[]=1，则换点。
		Edge edge;
		int cnt = search_edge(G, edge, num);
//		printf("cnt=%d\t", cnt);
			
		//确定与结点直接相连的最小权值的边，以及与之的另一个结点
		ArcType minside;
		VerTexType mindot;
		search_min(edge, minside, mindot, cnt);
//		printf("mindot=%c\tminside=%d\t", mindot, minside);
					
		//如果两个结点不是同一个结点，那么让这两个结点连通
		ArcType head = edge[0].Head;
		int pos = LocateVex(G, head);
		int pos2 = LocateVex(G, mindot);
		int row=num, col = LocateVex(G, mindot);
		if ( (Vexset[pos] != 1 && Vexset[pos2] != 1) || ( flag == true) ) {
			printf("%c-%d-%c\n", head, minside, mindot);
			G.arcs[row][col] = MaxInt;
			G.arcs[col][row] = MaxInt;
			Vexset[pos] = 1;
			inNum[incnt] = head;
			incnt++;
		}
		
//		for ( int i=0; i<incnt; i++ ) {
//			printf("%c\t", inNum[i]);
//		}
		
		//确定下一轮循环的tempNum
		VerTexType tempminhead[G.vexnum];
		VerTexType tempmindot[G.vexnum];
		ArcType tempminside[G.vexnum];
		VerTexType tempminDH;
		VerTexType tempminD;
		ArcType tempminS;
		int count = 0;
		
		if ( Vexset[LocateVex(G, mindot)] != 1 ) {
			tempNum = mindot;
			flag = false;
		}
		else {
			for ( int j=0; j<incnt; j++ ) {
				clear_edge(edge, cnt);
				cnt = search_edge(G, edge, LocateVex(G, inNum[j]));
//				printf("LocateVex(G, inNum[j])=%d\t", LocateVex(G, inNum[j]));
				tempminhead[j] = search_min(edge, tempminside[j], tempmindot[j], cnt);
//				printf("\ntempminside[j]=%d\ttempmindot[j]=%c\ttempminhead[j]=%c\n", tempminside[j], tempmindot[j], tempminhead[j]);
			}
			tempminDH = tempminhead[0];
			tempminD = tempmindot[0];
			tempminS = tempminside[0];
			for ( int j=0; j<incnt; j++ ) {
				if ( tempminside[j] <= tempminS && Vexset[LocateVex(G, tempmindot[j])] != 1 ) {
					tempminDH = tempminhead[j];
					tempminD = tempmindot[j];
					tempminS = tempminside[j];
				}
			}
			tempNum = tempminDH;
			flag = true;
		}
//		printf("tempNum=%c\n", tempNum);

	}
}

int main()
{
	AMGraph G;
	CreateUDN(G);
	
	ShowGraph(G);
	Prim(G);
	
	return 0;
}
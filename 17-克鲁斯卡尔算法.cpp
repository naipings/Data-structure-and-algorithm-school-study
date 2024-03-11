#include<stdio.h>

#define MaxInt 32767
#define MVNum 100
#define ArcNum 100
#define OK 1
#define ERROR -1

typedef char VerTexType; 
typedef int ArcType;
typedef int status;


int Vexset[MVNum];//辅助数组表示连通分量 

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

//初始化边表
void InitailEdge(AMGraph G,Edge &edge)
{ 
	int arcnum = 0;
	for ( int i=0; i<G.vexnum; i++ ) { //纵列为起点 
		for ( int j=i+1; j<G.vexnum; j++ ) { //横行为终点 
			if ( G.arcs[i][j] != MaxInt && G.arcs[i][j] != 0 ) {
				edge[arcnum].Head = Transform(G,i);
				edge[arcnum].Tail = Transform(G,j);
				edge[arcnum].lowcast = G.arcs[i][j];
				arcnum++;
			}
		}
	} 
}

//插入排序（根据权值大小，将Edge[]数组中的各个边 按从小到大顺序进行排序，）
void sort(AMGraph G,Edge &edge)
{
	VerTexType tv;
	ArcType tl;
	for ( int i=0; i<G.arcnum; i++ ) {
		for ( int j=0; j<G.arcnum-i-1; j++ ) {
			if ( edge[j].lowcast > edge[j+1].lowcast ) { //如果后面的结点权值 比 前面的结点的权值小
				//交换Edge[]中的头结点
				tv = edge[j].Head;
				edge[j].Head = edge[j+1].Head;
				edge[j+1].Head = tv;
				
				//交换Edge[]中的尾结点
				tv = edge[j].Tail;
				edge[j].Tail = edge[j+1].Tail;
				edge[j+1].Tail = tv;
				
				//交换Edge[]中的权值
				tl = edge[j].lowcast;
				edge[j].lowcast = edge[j+1].lowcast;
				edge[j+1].lowcast = tl;
			}
		}
	}
}

//打印最小生成树的边
void ShowEdge(AMGraph G,Edge edge)
{
	for ( int i=0; i<G.arcnum ;i++ ) {
		printf("%c-%d-%c\n", edge[i].Head, edge[i].lowcast, edge[i].Tail);
	}
}

//打印Vexset数组
void ShowVexset(AMGraph G)
{
	for ( int i=0; i<G.vexnum; i++ ) {
		printf("%d ", Vexset[i]);
	} 
	printf("\n");
}

//克鲁斯卡尔算法
void Kruskal(AMGraph &G)
{
	Edge edge;
	InitailEdge(G,edge); 
	//可以看看排序前后的效果
//	ShowEdge(G,edge);
//	printf("---------------------------------------\n");
	sort(G,edge);
//	ShowEdge(G,edge);
//	printf("---------------------------------------\n");

	for ( int i=0; i<G.vexnum; i++ ) {
		Vexset[i] = i; //每个节点自成一个分量 
	}
	int headi, taili; //边起点的下标、边终点的下标 
	int headt, tailt; //操作连通分量时的中间量 
	for ( int i=0; i<G.arcnum; i++ ) {
		headi = LocateVex(G,edge[i].Head); //起点下标 
		taili = LocateVex(G,edge[i].Tail); //终点下标
		
		headt = Vexset[headi]; //获取起点的连通分量 
		tailt = Vexset[taili]; //获取终点的连通分量
		
		if ( headt != tailt ) { //如果两个点不是同一个连通分量
			printf("%c-%d-%c\n", edge[i].Head, edge[i].lowcast, edge[i].Tail);
			for ( int j=0; j<G.vexnum; j++ ) {
				if ( Vexset[j] == headt ) { //更新Vexset数组，把 该边起点的连通分量 改成和 该边终点连通分量一致（其实就是合并连通分量） 
					Vexset[j] = tailt;
					//这里可以看看每次更新Vexset数组后，Vexset数组中各个连通分量的值
					//（如果=终点连通分量，表示该结点已连通）
					//printf("该边终点连通分量:%d\t", tailt);
					//ShowVexset(G);
					//printf("---------------------------------------\n");
				}
			}
		}
	} 	
}

int main()
{
	AMGraph G;
	CreateUDN(G);
	
	ShowGraph(G);
	Kruskal(G);
	
	return 0;
} 

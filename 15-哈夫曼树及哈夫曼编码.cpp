#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 10

typedef struct {
	unsigned int weight; //结点权重
	unsigned int parent, left, right; //父节点，左孩子，右孩子
} HTNode, *HuffmanTree;

//HT数组中存放哈夫曼树，end表示HT数组中存放结点的最终位置，s1和s2传递的是HT数组中权重最小的两个结点在数组中的位置
void select(HuffmanTree HT, int end, int *s1, int *s2)
{
	int min1, min2;
	//遍历数组初始下标为1
	int i = 1;
	//找到还没有构建树的结点
	while ( HT[i].parent != 0 && i <= end ) {
		i++;
	}
	min1 = HT[i].weight;
	*s1 = i;
	
	i++;
	while ( HT[i].parent != 0 && i <= end ) {
		i++;
	}
	
	//对找到的两个结点比较大小，min2为大的，min1为小的
	if ( HT[i].weight < min1 ) {
		min2 = min1;
		*s2 = *s1;
		min1 = HT[i].weight;
		*s1 = i;
	} else {
		min2 = HT[i].weight;
		*s2 = i;
	}
	
	//两个结点和后续的所有未构建成树的结点做比较
	for ( int j=i+1; j<=end; j++ ) {
		//如果有父结点，直接跳过，进行下一个
		if ( HT[j].parent != 0 ) {
			continue;
		}
		//如果比最小的还小，就将min2=min1，min1赋值为新的结点的权重和下标
		if ( HT[j].weight < min1 ) {
			min2 = min1;
			min1 = HT[j].weight;
			*s2 = *s1;	
			*s1 = j;
		}
		//如果介于两者之间，min2赋值为新的结点的权重和下标
		if ( HT[j].weight > min1 && HT[j].weight < min2 ) {
			min2 = HT[j].weight;
			*s2 = j;
		}
	}
}

//构建哈夫曼树
//HT为地址传递的是存储哈夫曼树的数组，w为存储结点权重值的数组，n为结点个数
void createHuffmanTree(HuffmanTree *HT, int *w, int n)
{
	if ( n<=1 ) return; //如果只有一个编码就相当于0
	int m = 2*n-1; //哈夫曼树总结点数，n就是叶子结点
	*HT = (HuffmanTree)malloc((m+1)*sizeof(HTNode)); //0号位置不用分配内存
	HuffmanTree p = * HT;
	//初始化哈夫曼树中的所有结点
	for ( int i=1; i<=n; i++ ) {
		(p+i)->weight = *(w+i-1);
//		printf("(p+i)->weight=%d\n", (p+i)->weight);
		(p+i)->parent = 0;
		(p+i)->left = 0;
		(p+i)->right = 0;
	}
	
	//从数组的下标n+1开始初始化哈夫曼树中 除叶子结点外的结点
	for ( int i=n+1; i<=m; i++ ) {
		(p+i)->weight = 0;
		(p+i)->parent = 0;
		(p+i)->left = 0;
		(p+i)->right = 0;
	}
	
	//构建哈夫曼树
	for ( int i=n+1; i<=m; i++ ) {
		int s1, s2;
		select(*HT, i-1, &s1, &s2);
		(*HT)[s1].parent = (*HT)[s2].parent = i;
		(*HT)[i].left = s1;
		(*HT)[i].right = s2;
		(*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
		
//		printf("i(parent)=%d\ts1(left)=%d\ts2(right)=%d\ti.weight=%d\n", (*HT)[s1].parent, (*HT)[i].left, (*HT)[i].right, (*HT)[i].weight);
	}
}

//打印信息
void showHuffmanTree(HuffmanTree HT, int n)
{
	for ( int i=1; i<=2*n-1; i++ ) {
		printf("第%d个结点：weight=%d\tparent=%d\tleft=%d\tright=%d\n", i, HT[i].weight, HT[i].parent, HT[i].left, HT[i].right);
	}
	printf("\n");
}

//哈夫曼编码
void codeHuffmanTree(HuffmanTree HT, int n)
{
	int j, k;
	
	//对叶子结点进行编码
	for ( int i=1; i<=n; i++ ) {
		int code[MAX]= {0};
		int count = 0; //记录每个结点的编码长度	
		j = n+1;
		k = i;
		while ( HT[j].parent != 0 || j<=2*n+1 ) {
			if ( HT[j].left == k ) {
				code[count] = 0;
				count++;
				k = j;
				j = HT[j].parent;				
			}
			else if ( HT[j].right == k ) {
				code[count] = 1;
				count++;
				k = j;
				j = HT[j].parent;				
			} else {
				j++;
			}
			
		}
		
		printf("%d\t", HT[i].weight);
		for ( int k=count-1; k>=0; k-- ) {
			printf("%d ", code[k]);
		}
		printf("\n");
	}
		
}

int main()
{
	HuffmanTree HT;
	int n = 8;
	int w[n] = {5, 29, 7, 8, 14, 23, 3, 11};
	
//	int n = 11;
//	int w[n] = {9, 5, 13, 6, 4, 25, 35, 21, 11, 3, 7};
	
	createHuffmanTree(&HT, w, n);
	showHuffmanTree(HT, n);
	
	codeHuffmanTree(HT, n);
	free(HT);
	
	return 0;
}
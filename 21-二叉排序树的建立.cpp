//二叉排序树的建立
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef bool Status;
typedef int TElemType;

//二叉树的链式存储
typedef struct BiTNode {
	TElemType data;
	struct BiTNode *lchild, *rchild, *parent;
} BiTNode, *BiTree;

//二叉排序树的插入
Status BiT_Insert(BiTree &bt, TElemType key, BiTNode *temp)
{
	if ( bt == NULL ) {
		bt = (BiTree)malloc(sizeof(BiTNode));
		bt->data = key;
		bt->lchild = bt->rchild = NULL;
		bt->parent = temp;
		return true;
	}
	else if ( key == bt->data ) { //存在相同值的结点，则插入失败
		return false;
	}
	else if ( key < bt->data ) {
		return BiT_Insert(bt->lchild, key, bt);
	}
	else {
		return BiT_Insert(bt->rchild, key, bt);
	}
	
}

//二叉排序树的创建
BiTree create_BiTree(TElemType num[], int length)
{
	BiTree bt = (BiTree)malloc(sizeof(BiTNode)); //建立二叉排序树头结点
	bt = NULL; //先将指针设置为空
	int i = 0;
	while ( i<length ) {
		BiT_Insert(bt, num[i], NULL);
		i++;
	}
	
	return bt;
}

//二叉树销毁
Status destroyTree(BiTree bt)
{
	BiTree pl, pr;
	if ( bt == NULL ) {
		return false;
	}
	else {
		pl = (bt)->lchild; //保存左孩子的地址
		pr = (bt)->rchild; //保存右孩子的地址
		(bt)->lchild = NULL;
		(bt)->rchild = NULL;
		free(bt); //释放根结点
		(bt) = NULL;
		//递归销毁
		destroyTree(pl);
		destroyTree(pr);
	}
	return true;
}

//遍历二叉树：（D表示根，L表示左子树，R表示右子树）
//递归实现：
//中序遍历（L D R）
void inOrder(BiTree bt)
{
	if ( bt == NULL ) {
		return;
	}
	else {
		inOrder(bt->lchild);
		printf("%d ", bt->data);
		inOrder(bt->rchild);
	}
}

//二叉排序树的查找
//递归方式
BiTNode* BiTree_search(BiTree bt, TElemType key)
{
	static int cnt = 0;
	if ( bt->data == key ) {
		printf("bt->data%d\tcnt=%d\n", bt->data, cnt);
		return bt;
	}
	if ( key < bt->data ) {
		if ( bt->lchild != NULL ) {
			cnt++;
			return BiTree_search(bt->lchild, key);
		} else {
			printf("查找无该数据");
			return NULL;
		}		
	} else {
		if ( bt->rchild != NULL ) {
			cnt++;
			return BiTree_search(bt->rchild, key);
		} else {
			printf("查找无该数据");
			return NULL;
		}		
	}
}

//查找最小结点
BiTNode* BiTree_minBTN(BiTree bt)
{
	if ( bt == NULL ) {
		return NULL;
	}
	while ( bt->lchild != NULL ) {
		bt = bt->lchild;
	}
	return bt;
}

//找结点btn的后继结点（即：查找二叉树中 数据值大于该结点的 最小结点）
BiTNode* BiTree_successor(BiTNode *btn)
{
	//如果该结点存在右孩子，则该结点btn的后继结点为 以其右孩子为根结点的子树的 最小结点
	if ( btn->rchild != NULL) {
		return BiTree_minBTN(btn->rchild);
	}
	BiTNode *tempx = btn->parent;
	while ( (tempx!=NULL) && (btn==tempx->rchild) ) {
		btn = tempx;
		tempx = tempx->parent;
	}
	return tempx;
}

//二叉排序树删除结点，返回根结点
BiTNode* BiTree_delete(BiTree bt, BiTNode* btn)
{
	BiTNode *tempx=NULL, *tempy=NULL;
	if ( (btn->lchild==NULL) || (btn->rchild==NULL) ) {
		tempy = btn;
	} else {
		tempy = BiTree_successor(btn);
	}
	
	if ( tempy->lchild != NULL ) {
		tempx = tempy->lchild;
	} else {
		tempx = tempy->rchild;
	}
	
	if ( tempx != NULL ) {
		tempx->parent = tempy->parent;
	}
	
	if ( tempy->parent == NULL ) {
		bt = tempx;
	} else if ( tempy == tempy->parent->lchild ) {
		tempy->parent->lchild = tempx;
	} else {
		tempy->parent->rchild = tempx;
	}
	
	if ( tempy != btn ) {
		btn->data = tempy->data;
	}
	if ( tempy != NULL) {
		free(tempy);
	}
	
	return bt;
}

//通过key删除二叉树结点
BiTNode* BiTNode_delete(BiTree bt, TElemType key)
{
	BiTNode *temp;
	if ( (temp = BiTree_search(bt, key)) != NULL ) {
		bt = BiTree_delete(bt, temp);
	}
	return bt;
}

int main()
{
	srand(time(0));
	int length = 0;
	printf("请输入数组长度：\n");
	scanf("%d", &length);
	TElemType num[length];
	for ( int i=0; i<length; i++ ) {
		num[i] = -40 + rand()%140;
		printf("%d ", num[i]);
	}
	printf("\n\n");
	
	BiTree bt = NULL;
	bt = create_BiTree(num, length);
	
	printf("中序遍历二叉树：\n");
	inOrder(bt);
	printf("\n\n");
	
	int key = 0;
	printf("请输入要查找的结点：\n");
	scanf("%d", &key);
//	BiTNode tempBi = (BiTNode*)malloc(sizeof(BiTNode));
	BiTree_search(bt, key);
	printf("\n");
	
	printf("请输入要删除的结点：\n");
	scanf("%d", &key);
	bt = BiTNode_delete(bt ,key);
	printf("中序遍历二叉树：\n");
	inOrder(bt);
	printf("\n\n");
	
	destroyTree(bt);
	
	return 0;
}
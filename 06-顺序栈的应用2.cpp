//顺序栈的应用2————迷宫求解

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define STACK_INIT_SIZE 100 //存储空间初始分配量
#define STACKINCREMENT 10 //存储空间分配增量

#define RANGE 100                 //迷宫大小  
#define ROW 10                    //迷宫的行数
#define COL 10                    //迷宫的列数  

//typedef int SElemType;

//迷宫的类型
typedef struct {
    int m, n;
    int arr[RANGE][RANGE];       //迷宫数组
} MazeType;

//坐标(row,col)
typedef struct {
    int row;                     //迷宫中的行
    int col;                     //迷宫中的列
} PosType;

typedef int DirectiveType;        //下一个通道方向  
//栈的元素类型
typedef struct {
    int step;                    //当前位置在路径上的"序号"
    PosType seat;                //当前的坐标位置
    DirectiveType di;            //往下一个坐标位置的方向
} SElemType;

typedef struct {
	SElemType *base; //在栈构造之前和销毁之后，base的值为NULL
	SElemType *top; //栈顶指针
	int stacksize; //当前已分配的存储空间，以元素为单位
} SqStack;                     

//初始化
bool InitStack(SqStack &s)
{
	s.base = (SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if ( !s.base ) {
		printf("Error!");
		exit(-1);
	}
	s.top = s.base;
	s.stacksize = STACK_INIT_SIZE;
	
	return true;
}

//销毁栈
bool DestoryStack(SqStack &s)
{
	if ( s.base == NULL ) { //栈结构不存在，程序异常退出
		exit(1);
	}
	free(s.base);
	s.base = NULL;
	return true;
}

//判断是否为空栈
//true————空栈；false————非空栈
bool StackEmpty(SqStack &s)
{
	if ( s.base == NULL ) {
	exit(1);	
	}
	bool ret = false;
	ret = s.top - s.base ? false : true;
	
	return ret;	
}

//设置空栈
bool ClearStack(SqStack &s)
{
	if ( s.base == NULL ) {
		exit(1);
	}
	s.base = s.top;
	return true;
	
}

//返回当前栈的长度
int StackLength(SqStack &s)
{
	if ( s.base == NULL ) {
		exit(1);
	}
	return s.top-s.base;
}

//取出栈顶元素
bool GetTop(SqStack &s, SElemType &e)
{
	if ( s.top - s.base == 0 ) {
		return false;
	}
	e = *(s.top-1);
	
	return true;
}

//入栈
bool Push(SqStack &s, SElemType e)
{
	//插入元素e为新的栈顶元素
	if ( s.top - s.base >= s.stacksize ) { //栈满，追加存储空间
		s.base = (SElemType *)realloc(s.base, (s.stacksize + STACKINCREMENT)*sizeof(SElemType));
		if ( !s.base ) {
			exit(-2);
		}
		s.top = s.base + s.stacksize;
		s.stacksize += STACKINCREMENT;	
	}
	* s.top++ = e;
	return true;
}

//出栈
bool Pop(SqStack &s, SElemType &e)
{
	//若栈不空，则删除s的栈顶元素，用e返回其值，并返回true；否则返回false
	if ( s.top - s.base == 0 ) {
		return false;
	}
	e = * --s.top;
	
	return true;
}

//遍历栈元素
bool PrintStack(SqStack &s)
{
	SElemType *i;
	if ( s.top - s.base == 0 ) {
		return false;
	}
	
	for ( i=s.base; i<s.top; i++ ) {
		printf("%d ", *i);
	}
	printf("\n");
	
	return true;
}

//迷宫求解：
//初始化迷宫
bool InitMaze(MazeType &maze, int a[ROW][COL], int row, int col)  
{
    int i, j;                            //设置迷宫maze的初值,包括加上边缘一圈的值
    for (i = 1; i<row - 1; i++) {
		for (j = 1; j<col - 1; j++) {
			maze.arr[i][j] = a[i][j];
		}
	}                                          

    for (j = 0; j<row; j++) {                    //加上围墙
		maze.arr[0][j] = maze.arr[row-1][j] = 1;
	}

    for (i = 0; i<col; i++) {
		maze.arr[i][0] = maze.arr[i][col-1] = 1;  	
	}

    return true;
}

//判断当前节点是否通过
bool Pass(MazeType maze, PosType curpos)
{
	if (maze.arr[curpos.row][curpos.col] == 0) {     //当节点为0时返回真
		return true;
	}
    else {
		return false;
	}
}

//留下足迹
bool FootPrint(MazeType &maze, PosType curpos)
{
    maze.arr[curpos.row][curpos.col] = 2;           //走过且走得通

    return true;
}

//留下不能通过的标记
bool MarkPrint(MazeType &maze, PosType curpos)
{
    maze.arr[curpos.row][curpos.col] = 3;           //走过但走不通

    return true;
}

//创建元素e
SElemType CreateSElem(int step, PosType pos, int di)
{
    SElemType e;
    e.step = step;
    e.seat = pos;
    e.di = di;

    return e;
}

//curpos当前位置
PosType NextPos(PosType curpos, DirectiveType di)
{
//返回当前节点的下一节点
	PosType pos = curpos;

    switch (di) {

	    case 1: pos.col++;        //右
	    break;
	
	    case 2: pos.row++;        //下
		break;
	
	    case 3: pos.col--;        //左
		break;
	
	    case 4: pos.row--;        //上
		break;
    }
    return pos;
}

//判断是不是出口
bool PosEqual(PosType pos1, PosType pos2)
{
    if (pos1.row == pos2.row && pos1.col == pos2.col) {
    	return true;
	} else {
		return false;
	} 
}

 
//打印路径
void PrintMaze(MazeType maze, int row, int col)
{
    int i, j;
    printf(" ");

    for (i = 0; i<col; i++) {                  //打印列数名
       printf("%d ", i);
	}
    printf("\n");

    for (i = 0; i<row; i++) {
       printf("%d", i);                      //打印行数名

       for (j = 0; j<col; j++) {

           	switch (maze.arr[i][j]) {

	           	case 0: printf("  ");                 //没走过，但是通路
				break;
	
	           	case 1:	printf("■ ");                  //墙，障碍物
	            break;
	
	           	case 2: printf("* ");                 //走过且走得通
	            break;
	
	           	case 3: printf("@ ");                 //走过但走不通，死胡同
	            break;
	
	           	default:
	            break;
        	}
		}
		printf("\n");
	}
	
}

//求解迷宫maze中,从入口start到出口end的一条路径
bool MazePath(MazeType &maze, PosType start, PosType end)
{
    SqStack s;                  //定义栈
    SElemType e;            
    InitStack(s);               //初始化栈
    PosType curpos = start;             

    int curstep = 1;                                //探索第一步
    do {
       if (Pass(maze, curpos)) {    //如果当前位置可以通过,即是未曾走到的通道块
			FootPrint(maze, curpos);                //留下足迹

          	e = CreateSElem(curstep, curpos, 1);    //创建元素

           	Push(s, e);                             //加入路径

           	if ( PosEqual(curpos, end) ) {              //到达终点（出口）
				return true;
			}

           curpos = NextPos(curpos, 1);            //获得下一节点

           curstep++;                              //探索下一步
       } else {                                           //当前位置不能通过
			if (!StackEmpty(s)) {
				Pop(s, e);
				while ( e.di == 4 && !StackEmpty(s) ) { //找寻了四个方向
					MarkPrint(maze, e.seat);
					Pop(s, e);                      //留下不能通过的标记,并退回一步
				}
				if ( e.di < 4 ) {
					e.di++;                         //换一个方向探索
					Push(s, e);
					curpos = NextPos(e.seat, e.di); //设定当前位置是该方向上的相邻块
				}
			}
		}
	} while ( !StackEmpty(s) );

    return false;
}

int main(int argc, char const *argv[])
{
	int i, j;                

    PosType start, end;      //开始，终点坐标

    MazeType maze;           

    int a[ROW][COL] = {                 //原始迷宫，其中'1'表示墙，'0'表示通道
       { 1,1,1,1,1,1,1,1,1,1 },
       { 1,0,0,1,0,0,0,1,0,1 },
       { 1,0,0,1,0,0,0,1,0,1 },
       { 1,0,0,0,0,1,1,0,0,1 },
       { 1,0,1,1,1,0,0,0,0,1 },
       { 1,0,0,0,1,0,0,0,0,1 },
       { 1,0,1,0,0,0,1,0,0,1 },
       { 1,0,1,1,1,0,1,1,0,1 },
       { 1,1,0,0,0,0,0,0,0,1 },
       { 1,1,1,1,1,1,1,1,1,1 }
    };

    printf("\n-------------------------------------------------\n");
    printf("\n原始迷宫如下：\n");
    printf("(其中'1'表示墙，'0'表示通道)\n");

    for (i = 0; i<10; i++) {       //双重循环输出原始迷宫
       for (j = 0; j<10; j++) {
           printf("%d ", a[i][j]);
		}
		printf("\n");
    }

    InitMaze(maze, a, ROW, COL);                 //初始化迷宫

    start.row = 1;                               //给定迷宫起点坐标
    start.col = 1;                               //（1，1）

    end.row = 8;                                 //给定迷宫终点坐标   
    end.col = 8;                                 //（8，8）

    if (MazePath(maze, start, end)) {          //如果找到一条路径
       	printf("\n-------------------------------------------------\n");
      	printf("\n穷举法求解迷宫路径如下：\n");
       	printf("(其中'*'表示求解路径，'@'表示死胡同)\n");

       PrintMaze(maze, ROW, COL);               //输出迷宫路径
    }
    else {//否则，没有通路
    	printf("\n---------从入口到出口没有通路!-----\n");	
	}
	  
	return 0;
}
//队列的应用————舞伴配对问题

/*队列从尾部插入头部出*/
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100   //最大队列长度
#define OVERFLOW -2
#define OK 1

#define MDER 11  //男舞者人数
#define WMDER 8  //女舞者人数

typedef int status;
typedef struct{
    char *name;    //初始化动态分配存储空间
    int front;     //头指针，若队列不空，指向队列头元素
    int rear;      //尾指针，若队列不空，指向队列尾元素的下一位置
}SqQueue;
 
/*初始化构造空队列*/
status InitQueue(SqQueue *Q)
{
    Q->name = (char *)malloc(MAXSIZE*sizeof(char));    //构造空队列
    if( !Q->name )
		exit(OVERFLOW);           //分配失败
    Q->front = Q->rear = 0;       //空时头指针和尾指针相等且为0
    return OK;
}
 
/*入队*/
status EnQueue(SqQueue *Q,char e)
{
    //插入新元素e为Q新队尾元素
    if( (Q->rear+1)%MAXSIZE == Q->front ) 
		return -1;                        //头指针大于尾指针，即进入下一轮（因为循环链表的问题导致的错误）
    Q->name[Q->rear] = e;                 //用头指针返回e值
    Q->rear = (Q->rear+1) % MAXSIZE;      //头指针向前一位
    return 1;
}
 
/*出队*/
status DeQueue(SqQueue *Q,char *e)
{
    //队列不空则删除Q头元素并用e返回，否则错误
    if( Q->front == Q->rear )
		return -1;
    *e = Q->name[Q->front];
    Q->front = (Q->front+1) % MAXSIZE;
    return 1;
}
 
/*舞伴匹配算法原始版*/
//注意此处算法内部并没有调用出栈和入栈算法
void DancePartner0(SqQueue *a,SqQueue *b)
{
    int j = 1;                                     //用于标记进行了几次舞蹈
    printf("1 dance chance:\n", j);                //第一次配对开始
    while( j <= 3 ) {                              //当配对次数在三次以内执行以下操作
        printf("%c<-->", a->name[a->front]);       //打印front指针所指的值
        a->front = (a->front+1) % WMDER;               //打印完毕front后移一位，其中%8为a队列队长
        printf("%c\n", b->name[b->front]);         //同理对b队列执行下列操作
        b->front = (b->front+1) % MDER;
        if( a->front == 0 ) {                      //若front为0时，即进入下一次循环队列时
        
            printf("%d dance end\n", j);           //此次配对完毕
            printf("%c will be the first to appear\n", b->name[b->front]);
            j++;                                   //进入下一次的配对
            printf("%d dance chance:\n", j);
        }
    }
} 
 
/*舞伴匹配算法改进版*/
//调用了入队和出队函数，通过打印出队元素返回的队头元素来实现，同时用两个空队临时按顺序储存出队元素，当出队完成重新入原队保持了先出先入的顺序
//不足：多用了两个队列临时储存出队元素，增加了程序运行时的内存空间
void DancePartner1(SqQueue *a,SqQueue *b)
{
    char e,w;      //用于出队时返回了值
    int j=1,i;      //j用于标记配对了几轮,i用于记录男女匹配对数
    SqQueue c,d;    //用于临时储存已配对完成了元素
    
    InitQueue(&c);
    InitQueue(&d);
    
    while( j <= 3 ) {   //要完成三轮配对
        printf("the %d match start:\n", j);
        for( i=0; i<WMDER; i++ ) {
            DeQueue(a, &e);      //注意调用格式！！！
            printf("%c<-->", e);   //打印出队元素
            EnQueue(&c, e);    //同时另外存储出队元素并按顺序入队
            DeQueue(b, &w);     //同理
            printf("%c\n", w);
            EnQueue(&d, w);
        }//一个for循环为一轮配对
 
    //各自重新入队，为下一次配对做准备
        for (i=0; i<WMDER; i++ ) {
            DeQueue(&c, &e);    //删除临时队列c并对其中元素重新入a队
            EnQueue(a, e);
            DeQueue(&d, &w);    //下两行代码同理
            EnQueue(b, w);
        }
        printf("the %d dance end...\n",j);
        printf("%c will be the first person matching in the next time...\n", b->name[b->front]);   //打印下一轮第一个出场的未配对者的姓名
        printf("\n");
        j++;
    } 
}
 
/*舞伴匹配算法最终版*/
//调用了入队和出队函数，通过打印出队元素返回的队头元素来实现，同时对该元素重新入队即插入到末位
void DancePartner(SqQueue *a,SqQueue *b, int length)
{
    char e,w;      //用于出队时返回了值
    int j=1,i;      //j用于标记配对了几轮,i用于记录男女匹配对数
    SqQueue c,d;    //用于临时储存已配对完成了元素
    InitQueue(&c);
    InitQueue(&d);
    while( j <= length ) {   //要完成length轮配对
        printf("the %d match start:\n", j);
        for( i=0; i<WMDER; i++ ) {
            DeQueue(a,&e);      //注意调用格式！！！
            printf("%c<-->", e);   //打印出队元素        
            EnQueue(a, e);      //出队元素重新入队到末位
            
            DeQueue(b, &w);     //同理
            printf("%c\n", w);
            EnQueue(b, w);
        } //一个for循环为一轮配对
        printf("the %d match end...\n",j);
        printf("%c will be the first person matching in the next time...\n", b->name[b->front]);   //打印下一轮第一个出场的未配对者的姓名
        printf("\n");
        j++;
    } 
}

/*主函数中生成一个队列，调用舞伴匹配算法时要求输入指针（*，*），因此要加&；而匹配算法里调用出队算法时要求的是指针（*，*），而匹配算法中输入的时候已经是指针了，所以不用再加&，而新生成的char型e则要加&；但入队函数要求调用的是（*， ），两个变量都不用加&。*/
 
int main()
{
    SqQueue F,M;   //生成F女士队列与M男士队列
    int i,j;
    
    InitQueue(&F);     //对队列初始化
    InitQueue(&M);
    
    char a[MDER+1]={"abcdefghijk"};    //给男队列元素起名
    char b[WMDER+1]={"opqrstuv"};     //给女队列元素起名
    
    int length = 0;
    printf("请输入舞会进行的轮数：\n");
    scanf("%d", &length);
    
    for ( i=0; i<MDER; i++ )     //用循环语句把元素入栈
        EnQueue(&M, a[i]);
        
    for( j=0; j<WMDER; j++ )
        EnQueue(&F, b[j]);
        
    DancePartner(&F, &M, length);    //舞伴配对
    
    return 0;
}
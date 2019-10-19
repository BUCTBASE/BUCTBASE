 /* algo3-5.c 利用栈求解迷宫问题（只输出一个解，算法3.3） */
 typedef struct /* 迷宫坐标位置类型 */
 {
   int x; /* 行值 */
   int y; /* 列值 */
 }PosType;

 #define MAXLENGTH 25 /* 设迷宫的最大行列为25 */
 typedef int MazeType[MAXLENGTH][MAXLENGTH]; /* 迷宫数组[行][列] */

 /* 全局变量 */
 MazeType m; /* 迷宫数组 */
 int curstep=1; /* 当前足迹,初值为1 */

 typedef struct /* 栈的元素类型 */
 {
   int ord; /* 通道块在路径上的＂序号＂ */
   PosType seat; /* 通道块在迷宫中的＂坐标位置＂ */
   int di; /* 从此通道块走向下一通道块的＂方向＂(0～3表示东～北) */
 }SElemType;

 #include"c1.h"
 #include"c3-1.h" /* 采用顺序栈存储结构 */
 #include"bo3-1.c" /* 采用顺序栈的基本操作函数 */

 /* 定义墙元素值为0,可通过路径为1,不能通过路径为-1,通过路径为足迹 */

 Status Pass(PosType b)
 { /* 当迷宫m的b点的序号为1(可通过路径)，return OK; 否则，return ERROR。 */
   if(m[b.x][b.y]==1)
     return OK;
   else
     return ERROR;
 }

 void FootPrint(PosType a)
 { /* 使迷宫m的a点的序号变为足迹(curstep) */
   m[a.x][a.y]=curstep;
 }

 PosType NextPos(PosType c,int di)
 { /* 根据当前位置及移动方向，返回下一位置 */
   PosType direc[4]={{0,1},{1,0},{0,-1},{-1,0}}; /* {行增量,列增量} */
   /* 移动方向,依次为东南西北 */
   c.x+=direc[di].x;
   c.y+=direc[di].y;
   return c;
 }

 void MarkPrint(PosType b)
 { /* 使迷宫m的b点的序号变为-1(不能通过的路径) */
   m[b.x][b.y]=-1;
 }

 Status MazePath(PosType start,PosType end) /* 算法3.3 */
 { /* 若迷宫maze中存在从入口start到出口end的通道，则求得一条 */
   /* 存放在栈中(从栈底到栈顶)，并返回TRUE；否则返回FALSE */
   SqStack S;
   PosType curpos;
   SElemType e;
   InitStack(&S);
   curpos=start;
   do
   {
     if(Pass(curpos))
     { /* 当前位置可以通过，即是未曾走到过的通道块 */
       FootPrint(curpos); /* 留下足迹 */
       e.ord=curstep;
       e.seat.x=curpos.x;
       e.seat.y=curpos.y;
       e.di=0;
       Push(&S,e); /* 入栈当前位置及状态 */
       curstep++; /* 足迹加1 */
       if(curpos.x==end.x&&curpos.y==end.y) /* 到达终点(出口) */
         return TRUE;
       curpos=NextPos(curpos,e.di);
     }
     else
     { /* 当前位置不能通过 */
       if(!StackEmpty(S))
       {
         Pop(&S,&e); /* 退栈到前一位置 */
         curstep--;
         while(e.di==3&&!StackEmpty(S)) /* 前一位置处于最后一个方向(北) */
         {
           MarkPrint(e.seat); /* 留下不能通过的标记(-1) */
           Pop(&S,&e); /* 退回一步 */
           curstep--;
         }
         if(e.di<3) /* 没到最后一个方向(北) */
         {
           e.di++; /* 换下一个方向探索 */
           Push(&S,e);
           curstep++;
           curpos=NextPos(e.seat,e.di); /* 设定当前位置是该新方向上的相邻块 */
         }
       }
     }
   }while(!StackEmpty(S));
   return FALSE;
 }

 void Print(int x,int y)
 { /* 输出迷宫的解 */
   int i,j;
   for(i=0;i<x;i++)
   {
     for(j=0;j<y;j++)
       printf("%3d",m[i][j]);
     printf("\n");
   }
 }

 void main()
 {
   PosType begin,end;
   int i,j,x,y,x1,y1;
   printf("请输入迷宫的行数,列数(包括外墙)：");
   scanf("%d,%d",&x,&y);
   for(i=0;i<x;i++) /* 定义周边值为0(同墙) */
   {
     m[0][i]=0; /* 行周边 */
     m[x-1][i]=0;
   }
   for(j=1;j<y-1;j++)
   {
     m[j][0]=0; /* 列周边 */
     m[j][y-1]=0;
   }
   for(i=1;i<x-1;i++)
     for(j=1;j<y-1;j++)
       m[i][j]=1; /* 定义通道初值为1 */
   printf("请输入迷宫内墙单元数：");
   scanf("%d",&j);
   printf("请依次输入迷宫内墙每个单元的行数,列数：\n");
   for(i=1;i<=j;i++)
   {
     scanf("%d,%d",&x1,&y1);
     m[x1][y1]=0; /* 定义墙的值为0 */
   }
   printf("迷宫结构如下:\n");
   Print(x,y);
   printf("请输入起点的行数,列数：");
   scanf("%d,%d",&begin.x,&begin.y);
   printf("请输入终点的行数,列数：");
   scanf("%d,%d",&end.x,&end.y);
   if(MazePath(begin,end)) /* 求得一条通路 */
   {
     printf("此迷宫从入口到出口的一条路径如下:\n");
     Print(x,y); /* 输出此通路 */
   }
   else
     printf("此迷宫没有从入口到出口的路径\n");
 }

 /* algo3-9.c 用递归函数求解迷宫问题(求出所有解) */
 #include<stdio.h> /* 根据《PASCAL程序设计》(郑启华编著)中的程序改编 */
 struct PosType /* 迷宫坐标位置类型 */
 {
   int x; /* 行值 */
   int y; /* 列值 */
 };

 #define MAXLENGTH 25 /* 设迷宫的最大行列为25 */
 typedef int MazeType[MAXLENGTH][MAXLENGTH]; /* [行][列] */

 /* 全局变量 */
 struct PosType end; /* 迷宫终点位置 */
 MazeType m; /* 迷宫数组 */
 int x,y; /* 迷宫行数，列数 */

 /* 定义墙元素值为0,可通过路径为-1,通过路径为足迹 */

 void Print(int x,int y)
 { /* 输出解 */
   int i,j;
   for(i=0;i<x;i++)
   {
     for(j=0;j<y;j++)
       printf("%3d",m[i][j]);
     printf("\n");
   }
   printf("\n");
 }

 void Try(struct PosType cur,int curstep)
 { /* 由当前位置cur、当前步骤curstep试探下一点 */
   int i;
   struct PosType next; /* 下一个位置 */
   struct PosType direc[4]={{0,1},{1,0},{0,-1},{-1,0}}; /* {行增量,列增量} */
   /* 移动方向,依次为东南西北 */
   for(i=0;i<=3;i++) /* 依次试探东南西北四个方向 */
   {
     next.x=cur.x+direc[i].x;
     next.y=cur.y+direc[i].y;
     if(m[next.x][next.y]==-1) /* 是通路 */
     {
       m[next.x][next.y]=++curstep;
       if(next.x!=end.x||next.y!=end.y) /* 没到终点 */
         Try(next,curstep); /* 试探下一点(递归调用) */
       else
         Print(x,y); /* 输出结果 */
       m[next.x][next.y]=-1; /* 恢复为通路，试探下一条路 */
       curstep--;
     }
   }
 }

 void main()
 {
   struct PosType begin;
   int i,j,x1,y1;
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
       m[i][j]=-1; /* 定义通道初值为-1 */
   printf("请输入迷宫内墙单元数：");
   scanf("%d",&j);
   if(j)
     printf("请依次输入迷宫内墙每个单元的行数,列数：\n");
   for(i=1;i<=j;i++)
   {
     scanf("%d,%d",&x1,&y1);
     m[x1][y1]=0;
   }
   printf("迷宫结构如下:\n");
   Print(x,y);
   printf("请输入起点的行数,列数：");
   scanf("%d,%d",&begin.x,&begin.y);
   printf("请输入终点的行数,列数：");
   scanf("%d,%d",&end.x,&end.y);
   m[begin.x][begin.y]=1;
   Try(begin,1); /* 由第一步起点试探起 */
 }

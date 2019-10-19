 /* algo3-11.c 利用非循环顺序队列采用广度搜索法求解迷宫问题(一条路径) */
 #include"c1.h"
 #define M 5 /* 迷宫行数(包括外墙) */
 #define N 5 /* 迷宫列数(包括外墙) */
 #define D 8 /* 移动方向数,只能取4和8。(8个,可斜行;4个,只可直走) */

 typedef struct /* 定义队列元素和栈元素为同类型的结构体 */
 {
   int x,y; /* 当前点的行值，列值 */
   int pre; /* 前一点在队列中的序号 */
 }QElemType,SElemType; /* 定义栈元素和队列元素 */
 #include"c3-1.h" /* 栈的存储结构 */
 #include"bo3-1.c" /* 栈的基本操作 */
 #include"c3-3.h" /* 队列的存储结构 */
 #include"bo3-4.c" /* 队列的基本操作 */

 struct /* 移动数组,移动方向由正东起顺时针转 */
 {
   int x,y;
 #if D==8
 }move[D]={{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};
 #endif
 #if D==4
 }move[D]={{0,1},{1,0},{0,-1},{-1,0}};
 #endif

 Status Path(int maze[M][N]) /* 广度搜索法求一条迷宫路径 */
 {
   SqQueue q; /* 采用非循环顺序队列 */
   QElemType qf,qt; /* 当前点和下一点 */
   SqStack s; /* 采用顺序栈 */
   int i,j,flag=1; /* 当找到出口,flag=0 */
   int x1,y1; /* 终点的坐标 */
   printf("请输入入口的行,列(左上角为1,1)\n");
   scanf("%d,%d",&qf.x,&qf.y);
   printf("请输入出口的行,列(右下角为%d,%d)\n",M-2,N-2);
   scanf("%d,%d",&x1,&y1);
   qf.pre=-1; /* 设入口(第一点)的上一点的序号=-1 */
   maze[qf.x][qf.y]=-1; /* 初始点设为-1(已访问过) */
   InitQueue(&q);
   EnQueue(&q,qf); /* 起点入队 */
   while(!QueueEmpty(q)&&flag)
   { /* 队列中还有没被广度搜索过的点且还没找到出口 */
     DeQueue(&q,&qf); /* 出队qf为当前点 */
     for(i=0;i<D;i++) /* 向各个方向尝试 */
     {
       qt.x=qf.x+move[i].x; /* 下一点的坐标 */
       qt.y=qf.y+move[i].y;
       if(maze[qt.x][qt.y]==1)
       { /* 此点是通道且不曾被访问过 */
         maze[qt.x][qt.y]=-1; /* 已访问过 */
         qt.pre=q.front-1; /* 上一点处于队列中现队头减一的位置(没删除) */
         EnQueue(&q,qt); /* 入队 */
         if(qt.x==x1&&qt.y==y1) /* 到达终点 */
         {
           flag=0;
           break;
         }
       }
     }
   }
   if(flag) /* 搜索完整个队列还没到达终点 */
   {
     printf("没有路径可到达终点！\n");
     return ERROR;
   }
   else
   {
     InitStack(&s); /* 初始化s栈 */
     i=q.rear-1; /* i为待入栈元素在队列中的位置 */
     while(i>=0) /* 没到入口 */
     {
       Push(&s,*(q.base+i));
       i=(*(q.base+i)).pre; /* i为前一元素在队列中的位置 */
     }
     i=0; /* i为走出迷宫的步骤 */
     while(!StackEmpty(s))
     {
       Pop(&s,&qf);
       i++;
       maze[qf.x][qf.y]=i;
     }
     printf("走出迷宫的一个方案：\n");
     for(i=1;i<M-1;i++) /* 输出maze[][],其值是走出迷宫的步骤 */
     {
       for(j=1;j<N-1;j++)
         printf("%3d",maze[i][j]);
       printf("\n");
     }
     return OK;
   }
 }

 void main()
 {
   int i,j;
   int maze[M][N]; /* 迷宫数组 */
   printf("%d行%d列迷宫(不包括外墙)\n",M-2,N-2);
   for(i=0;i<N;i++)
   { /* 0为墙,1为通道 */
     maze[0][i]=0; /* 北墙 */
     maze[M-1][i]=0; /* 南墙 */
   }
   for(i=1;i<M-1;i++)
   {
     maze[i][0]=0; /* 西墙 */
     maze[i][N-1]=0; /* 东墙 */
   }
   printf("请按行输入迷宫结构(不包括周边,0为墙,1为通道),如1 0 0 1\n");
   for(i=1;i<M-1;i++)
     for(j=1;j<N-1;j++)
       scanf("%d",&maze[i][j]);
   printf("迷宫结构(包括外墙):\n");
   for(i=0;i<M;i++)
   {
     for(j=0;j<N;j++)
       printf("%3d",maze[i][j]);
     printf("\n");
   }
   Path(maze);
 }

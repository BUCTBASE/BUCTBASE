 /* algo3-12.c 银行业务模拟。实现算法3.6、3.7的程序 */
 #define Qu 4 /* 客户队列数 */
 #define Khjg 5 /* 两相邻到达的客户的时间间隔最大值 */
 #define Blsj 30 /* 每个客户办理业务的时间最大值 */
 #include"c1.h"

 typedef struct /* 定义ElemType为结构体类型 */
 {
   int OccurTime; /* 事件发生时刻 */
   int NType; /* 事件类型，Qu表示到达事件,0至Qu-1表示Qu个窗口的离开事件 */
 }Event,ElemType; /* 事件类型，有序链表LinkList的数据元素类型 */

 #include"c2-5.h"
 typedef LinkList EventList; /* 事件链表类型，定义为有序链表 */
 #include"bo2-6.c" /* 使用已有的链表基本操作 */

 typedef struct
 {
   int ArrivalTime; /* 到达时刻 */
   int Duration; /* 办理事务所需时间 */
 }QElemType; /* 定义QElemType(队列的数据元素类型)为结构体类型; */

 #include"c3-2.h"
 #include"bo3-2.c" /* 使用已有的队列基本操作 */

 /* 程序中用到的主要变量(全局)。算法3.7 */
 EventList ev; /* 事件表 */
 Event en; /* 事件 */
 Event et; /* 临时变量 */
 LinkQueue q[Qu]; /* Qu个客户队列 */
 QElemType customer; /* 客户记录 */
 int TotalTime=0,CustomerNum=0; /* 累计客户逗留时间,客户数(初值为0) */
 int CloseTime; /* 银行营业时间(单位是分) */

 int cmp(Event a,Event b)
 { /* 依事件a的发生时刻<、=或>事件b的发生时刻分别返回-1、0或1 */
   if(a.OccurTime==b.OccurTime)
     return 0;
   else
     return (a.OccurTime-b.OccurTime)/abs(a.OccurTime-b.OccurTime);
 }

 void OpenForDay()
 { /* 初始化操作 */
   int i;
   InitList(&ev); /* 初始化事件链表为空 */
   en.OccurTime=0; /* 设定第一个客户到达事件 */
   en.NType=Qu; /* 到达 */
   OrderInsert(&ev,en,cmp); /* 插入事件表 */
   for(i=0;i<Qu;++i) /* 置空队列 */
     InitQueue(&q[i]);
 }

 void Random(int *d,int *i)
 {
   *d=rand()%Blsj+1; /* 1到Blsj之间的随机数 */
   *i=rand()%Khjg+1; /* 1到Khjg之间的随机数 */
 }

 int Minimum(LinkQueue Q[]) /* 返回最短队列的序号 */
 {
   int l[Qu];
   int i,k;
   for(i=0;i<Qu;i++)
     l[i]=QueueLength(Q[i]);
   k=0;
   for(i=1;i<Qu;i++)
     if(l[i]<l[0])
     {
       l[0]=l[i];
       k=i;
     }
   return k;
 }

 void CustomerArrived()
 { /* 处理客户到达事件，en.NType=Qu */
   QElemType f;
   int durtime,intertime,i;
   ++CustomerNum;
   Random(&durtime,&intertime); /* 生成随机数 */
   et.OccurTime=en.OccurTime+intertime; /* 下一客户到达时刻 */
   et.NType=Qu; /* 队列中只有一个客户到达事件 */
   if(et.OccurTime<CloseTime) /* 银行尚未关门，插入事件表 */
     OrderInsert(&ev,et,cmp);
   i=Minimum(q); /* 求长度最短队列的序号,等长为最小的序号 */
   f.ArrivalTime=en.OccurTime;
   f.Duration=durtime;
   EnQueue(&q[i],f);
   if(QueueLength(q[i])==1)
   {
     et.OccurTime=en.OccurTime+durtime;
     et.NType=i;
     OrderInsert(&ev,et,cmp); /* 设定第i队列的一个离开事件并插入事件表 */
   }
 }

 void CustomerDeparture()
 { /* 处理客户离开事件，en.NTyPe<Qu */
   int i;
   i=en.NType;
   DeQueue(&q[i],&customer); /* 删除第i队列的排头客户 */
   TotalTime+=en.OccurTime-customer.ArrivalTime; /* 累计客户逗留时间 */
   if(!QueueEmpty(q[i]))
   { /* 设定第i队列的一个离开事件并插入事件表 */
     GetHead_Q(q[i],&customer);
     et.OccurTime=en.OccurTime+customer.Duration;
     et.NType=i;
     OrderInsert(&ev,et,cmp);
   }
 }

 void Bank_Simulation()
 {
   Link p;
   OpenForDay(); /* 初始化 */
   while(!ListEmpty(ev))
   {
     DelFirst(&ev,GetHead(ev),&p);
     en.OccurTime=GetCurElem(p).OccurTime;
     en.NType=GetCurElem(p).NType;
     if(en.NType==Qu)
       CustomerArrived(); /* 处理客户到达事件 */
     else
       CustomerDeparture(); /* 处理客户离开事件 */
   } /* 计算并输出平均逗留时间 */
   printf("顾客总数:%d, 所有顾客共耗时:%d分钟, 平均每人耗时: %d分钟\n",CustomerNum,TotalTime,TotalTime/CustomerNum);
 }

 void main()
 {
   printf("请输入银行营业时间长度(单位:分)\n");
   scanf("%d",&CloseTime);
   Bank_Simulation();
 }

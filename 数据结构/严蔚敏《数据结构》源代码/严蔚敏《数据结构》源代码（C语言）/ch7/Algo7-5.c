 /* algo7-5.c 求关键路径。实现算法7.13、7.14的程序 */
 #include"c1.h"
 #define MAX_NAME 5 /* 顶点字符串的最大长度+1 */
 typedef int InfoType;
 typedef char VertexType[MAX_NAME]; /* 字符串类型 */
 #include"c7-2.h"
 #include"bo7-2.c"

 int ve[MAX_VERTEX_NUM]; /* 全局变量(用于算法7.13和算法7.14) */

 void FindInDegree(ALGraph G,int indegree[])
 { /* 求顶点的入度，算法7.12、7.13调用 */
   int i;
   ArcNode *p;
   for(i=0;i<G.vexnum;i++)
     indegree[i]=0; /* 赋初值 */
   for(i=0;i<G.vexnum;i++)
   {
     p=G.vertices[i].firstarc;
     while(p)
     {
       indegree[p->adjvex]++;
       p=p->nextarc;
     }
   }
 }

 typedef int SElemType; /* 栈类型 */
 #include"c3-1.h"
 #include"bo3-1.c"
 Status TopologicalOrder(ALGraph G,SqStack *T)
 { /* 算法7.13  有向网G采用邻接表存储结构,求各顶点事件的最早发生时间ve */
   /* (全局变量)。T为拓扑序列顶点栈,S为零入度顶点栈。若G无回路,则用栈T */
   /* 返回G的一个拓扑序列,且函数值为OK,否则为ERROR */
   int j,k,count,indegree[MAX_VERTEX_NUM];
   SqStack S;
   ArcNode *p;
   FindInDegree(G,indegree);/*对各顶点求入度indegree[0..vernum-1] */
   InitStack(&S); /* 初始化栈 */
   for(j=0;j<G.vexnum;++j) /* 建零入度顶点栈S */
     if(!indegree[j])
       Push(&S,j); /* 入度为0者进栈 */
   InitStack(T); /* 初始化拓扑序列顶点栈 */
   count=0; /* 对输出顶点计数 */
   for(j=0;j<G.vexnum;++j) /* 初始化ve[]=0 (最小值) */
     ve[j]=0;
   while(!StackEmpty(S))
   { /* 栈不空 */
     Pop(&S,&j);
     Push(T,j); /* j号顶点入T栈并计数 */
     ++count;
     for(p=G.vertices[j].firstarc;p;p=p->nextarc)
     { /* 对j号顶点的每个邻接点的入度减1 */
       k=p->adjvex;
       if(--indegree[k]==0) /* 若入度减为0,则入栈 */
         Push(&S,k);
       if(ve[j]+*(p->info)>ve[k])
         ve[k]=ve[j]+*(p->info);
     }
   }
   if(count<G.vexnum)
   {
     printf("此有向网有回路\n");
     return ERROR;
   }
   else
     return OK;
 }

 Status CriticalPath(ALGraph G)
 { /* 算法7.14 G为有向网,输出G的各项关键活动 */
   int vl[MAX_VERTEX_NUM];
   SqStack T;
   int i,j,k,ee,el;
   ArcNode *p;
   char dut,tag;
   if(!TopologicalOrder(G,&T)) /* 产生有向环 */
     return ERROR;
   j=ve[0];
   for(i=1;i<G.vexnum;i++) /* j=Max(ve[]) 完成点的值 */
     if(ve[i]>j)
       j=ve[i];
   for(i=0;i<G.vexnum;i++) /* 初始化顶点事件的最迟发生时间(最大值) */
     vl[i]=j; /* 完成点的最早发生时间 */
   while(!StackEmpty(T)) /* 按拓扑逆序求各顶点的vl值 */
     for(Pop(&T,&j),p=G.vertices[j].firstarc;p;p=p->nextarc)
     {
       k=p->adjvex;
       dut=*(p->info); /* dut<j,k> */
       if(vl[k]-dut<vl[j])
         vl[j]=vl[k]-dut;
     }
   printf(" j  k  dut  ee  el  tag\n");
   for(j=0;j<G.vexnum;++j) /* 求ee,el和关键活动 */
     for(p=G.vertices[j].firstarc;p;p=p->nextarc)
     {
       k=p->adjvex;
       dut=*(p->info);
       ee=ve[j];
       el=vl[k]-dut;
       tag=(ee==el)?'*':' ';
       printf("%2d %2d %3d %3d %3d    %c\n",j,k,dut,ee,el,tag); /* 输出关键活动 */
     }
   printf("关键活动为:\n");
   for(j=0;j<G.vexnum;++j) /* 同上 */
     for(p=G.vertices[j].firstarc;p;p=p->nextarc)
     {
       k=p->adjvex;
       dut=*(p->info);
       if(ve[j]==vl[k]-dut)
         printf("%s→%s\n",G.vertices[j].data,G.vertices[k].data); /* 输出关键活动 */
     }
   return OK;
 }

 void main()
 {
   ALGraph h;
   printf("请选择有向网\n");
   CreateGraph(&h);
   Display(h);
   CriticalPath(h);
 }

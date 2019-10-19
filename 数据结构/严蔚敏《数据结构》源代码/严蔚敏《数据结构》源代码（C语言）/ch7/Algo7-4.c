 /* algo7-4.c 输出有向图的一个拓扑序列。实现算法7.12的程序 */
 #include"c1.h"
 #define MAX_NAME 5 /* 顶点字符串的最大长度 */
 typedef int InfoType;
 typedef char VertexType[MAX_NAME]; /* 字符串类型 */
 #include"c7-2.h"
 #include"bo7-2.c"

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
 Status TopologicalSort(ALGraph G)
 { /* 有向图G采用邻接表存储结构。若G无回路,则输出G的顶点的一个拓扑序列并返回OK, */
   /* 否则返回ERROR。算法7.12 */
   int i,k,count,indegree[MAX_VERTEX_NUM];
   SqStack S;
   ArcNode *p;
   FindInDegree(G,indegree); /* 对各顶点求入度indegree[0..vernum-1] */
   InitStack(&S); /* 初始化栈 */
   for(i=0;i<G.vexnum;++i) /* 建零入度顶点栈S */
     if(!indegree[i])
       Push(&S,i); /* 入度为0者进栈 */
   count=0; /* 对输出顶点计数 */
   while(!StackEmpty(S))
   { /* 栈不空 */
     Pop(&S,&i);
     printf("%s ",G.vertices[i].data); /* 输出i号顶点并计数 */
     ++count;
     for(p=G.vertices[i].firstarc;p;p=p->nextarc)
     { /* 对i号顶点的每个邻接点的入度减1 */
       k=p->adjvex;
       if(!(--indegree[k])) /* 若入度减为0,则入栈 */
         Push(&S,k);
     }
   }
   if(count<G.vexnum)
   {
     printf("此有向图有回路\n");
     return ERROR;
   }
   else
   {
     printf("为一个拓扑序列。\n");
     return OK;
   }
 }

 void main()
 {
   ALGraph f;
   printf("请选择有向图\n");
   CreateGraph(&f);
   Display(f);
   TopologicalSort(f);
 }

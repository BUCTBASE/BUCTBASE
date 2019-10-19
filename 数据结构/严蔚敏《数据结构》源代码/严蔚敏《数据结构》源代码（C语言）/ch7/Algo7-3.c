 /* algo7-3.c 实现算法7.10、7.11的程序 */
 #include"c1.h"
 #define MAX_NAME 2 /* 顶点字符串的最大长度+1 */
 typedef int InfoType;
 typedef char VertexType[MAX_NAME]; /* 字符串类型 */
 #include"c7-2.h"
 #include"bo7-2.c"

 int count; /* 全局量count对访问计数 */
 int low[MAX_VERTEX_NUM];

 void DFSArticul(ALGraph G,int v0)
 { /* 从第v0个顶点出发深度优先遍历图G，查找并输出关节点。算法7.11 */
   int min,w;
   ArcNode *p;
   visited[v0]=min=++count; /* v0是第count个访问的顶点 */
   for(p=G.vertices[v0].firstarc;p;p=p->nextarc) /* 对v0的每个邻接顶点检查 */
   {
     w=p->adjvex; /* w为v0的邻接顶点 */
     if(visited[w]==0) /* w未曾访问，是v0的孩子 */
     {
       DFSArticul(G,w); /* 返回前求得low[w] */
       if(low[w]<min)
         min=low[w];
       if(low[w]>=visited[v0])
         printf("%d %s\n",v0,G.vertices[v0].data); /* 关节点 */
     }
     else if(visited[w]<min)
       min=visited[w]; /* w已访问，w是v0在生成树上的祖先 */
   }
   low[v0]=min;
 }

 void FindArticul(ALGraph G)
 { /* 连通图G以邻接表作存储结构，查找并输出G上全部关节点。算法7.10 */
   /* 全局量count对访问计数。 */
   int i,v;
   ArcNode *p;
   count=1;
   low[0]=visited[0]=1; /* 设定邻接表上0号顶点为生成树的根 */
   for(i=1;i<G.vexnum;++i)
     visited[i]=0; /* 其余顶点尚未访问 */
   p=G.vertices[0].firstarc;
   v=p->adjvex;
   DFSArticul(G,v); /* 从第v顶点出发深度优先查找关节点 */
   if(count<G.vexnum) /* 生成树的根有至少两棵子树 */
   {
     printf("%d %s\n",0,G.vertices[0].data); /* 根是关节点，输出 */
     while(p->nextarc)
     {
       p=p->nextarc;
       v=p->adjvex;
       if(visited[v]==0)
         DFSArticul(G,v);
     }
   }
 }

 void main()
 {
   int i;
   ALGraph g;
   printf("请选择无向图\n");
   CreateGraph(&g);
   printf("输出关节点：\n");
   FindArticul(g);
   printf(" i G.vertices[i].data visited[i] low[i]\n");
   for(i=0;i<g.vexnum;++i)
     printf("%2d %9s %14d %8d\n",i,g.vertices[i].data,visited[i],low[i]);
 }

 /* algo7-6.c 实现算法7.15的程序。迪杰斯特拉算法的实现 */
 #include"c1.h"
 #define MAX_NAME 5 /* 顶点字符串的最大长度+1 */
 #define MAX_INFO 20 /* 相关信息字符串的最大长度+1 */
 typedef int VRType;
 typedef char InfoType;
 typedef char VertexType[MAX_NAME];
 #include"c7-1.h"
 typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
 typedef int ShortPathTable[MAX_VERTEX_NUM];
 #include"bo7-1.c"

 void ShortestPath_DIJ(MGraph G,int v0,PathMatrix *P,ShortPathTable *D)
 { /* 用Dijkstra算法求有向网G的v0顶点到其余顶点v的最短路径P[v]及带权长度 */
   /* D[v]。若P[v][w]为TRUE,则w是从v0到v当前求得最短路径上的顶点。 */
   /* final[v]为TRUE当且仅当v∈S,即已经求得从v0到v的最短路径 算法7.15 */
   int v,w,i,j,min;
   Status final[MAX_VERTEX_NUM];
   for(v=0;v<G.vexnum;++v)
   {
     final[v]=FALSE;
     (*D)[v]=G.arcs[v0][v].adj;
     for(w=0;w<G.vexnum;++w)
       (*P)[v][w]=FALSE; /* 设空路径 */
     if((*D)[v]<INFINITY)
     {
       (*P)[v][v0]=TRUE;
       (*P)[v][v]=TRUE;
     }
   }
   (*D)[v0]=0;
   final[v0]=TRUE; /* 初始化,v0顶点属于S集 */
   for(i=1;i<G.vexnum;++i) /* 其余G.vexnum-1个顶点 */
   { /* 开始主循环,每次求得v0到某个v顶点的最短路径,并加v到S集 */
     min=INFINITY; /* 当前所知离v0顶点的最近距离 */
     for(w=0;w<G.vexnum;++w)
       if(!final[w]) /* w顶点在V-S中 */
	 if((*D)[w]<min)
	 {
	   v=w;
	   min=(*D)[w];
	 } /* w顶点离v0顶点更近 */
     final[v]=TRUE; /* 离v0顶点最近的v加入S集 */
     for(w=0;w<G.vexnum;++w) /* 更新当前最短路径及距离 */
     {
       if(!final[w]&&min<INFINITY&&G.arcs[v][w].adj<INFINITY&&(min+G.arcs[v][w].adj<(*D)[w]))
       { /* 修改D[w]和P[w],w∈V-S */
         (*D)[w]=min+G.arcs[v][w].adj;
         for(j=0;j<G.vexnum;++j)
           (*P)[w][j]=(*P)[v][j];
         (*P)[w][w]=TRUE;
       }
     }
   }
 }

 void main()
 {
   int i,j,v0=0; /* v0为源点 */
   MGraph g;
   PathMatrix p;
   ShortPathTable d;
   CreateDN(&g);
   ShortestPath_DIJ(g,v0,&p,&d);
   printf("最短路径数组p[i][j]如下:\n");
   for(i=0;i<g.vexnum;++i)
   {
     for(j=0;j<g.vexnum;++j)
       printf("%2d",p[i][j]);
     printf("\n");
   }
   printf("%s到各顶点的最短路径长度为：\n",g.vexs[0]);
   for(i=1;i<g.vexnum;++i)
     printf("%s-%s:%d\n",g.vexs[0],g.vexs[i],d[i]);
 }

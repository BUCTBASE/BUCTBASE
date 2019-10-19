 /* algo7-7.c 实现算法7.16的程序 */
 #define MAX_NAME 5 /* 顶点字符串的最大长度+1 */
 #define MAX_INFO 20 /* 相关信息字符串的最大长度+1 */
 typedef int VRType;
 typedef char VertexType[MAX_NAME];
 typedef char InfoType;
 #include"c1.h"
 #include"c7-1.h"
 #include"bo7-1.c"
 typedef int PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM];
 typedef int DistancMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

 void ShortestPath_FLOYD(MGraph G,PathMatrix *P,DistancMatrix *D)
 { /* 用Floyd算法求有向网G中各对顶点v和w之间的最短路径P[v][w]及其 */
   /* 带权长度D[v][w]。若P[v][w][u]为TRUE,则u是从v到w当前求得最短 */
   /* 路径上的顶点。算法7.16 */
   int u,v,w,i;
   for(v=0;v<G.vexnum;v++) /* 各对结点之间初始已知路径及距离 */
     for(w=0;w<G.vexnum;w++)
     {
       (*D)[v][w]=G.arcs[v][w].adj;
       for(u=0;u<G.vexnum;u++)
         (*P)[v][w][u]=FALSE;
       if((*D)[v][w]<INFINITY) /* 从v到w有直接路径 */
       {
         (*P)[v][w][v]=TRUE;
         (*P)[v][w][w]=TRUE;
       }
     }
   for(u=0;u<G.vexnum;u++)
     for(v=0;v<G.vexnum;v++)
       for(w=0;w<G.vexnum;w++)
         if((*D)[v][u]+(*D)[u][w]<(*D)[v][w]) /* 从v经u到w的一条路径更短 */
         {
           (*D)[v][w]=(*D)[v][u]+(*D)[u][w];
           for(i=0;i<G.vexnum;i++)
             (*P)[v][w][i]=(*P)[v][u][i]||(*P)[u][w][i];
         }
 }

 void main()
 {
   MGraph g;
   int i,j,k,l,m,n;
   PathMatrix p;
   DistancMatrix d;
   CreateDN(&g);
   for(i=0;i<g.vexnum;i++)
     g.arcs[i][i].adj=0; /* ShortestPath_FLOYD()要求对角元素值为0 */
   printf("邻接矩阵:\n");
   for(i=0;i<g.vexnum;i++)
   {
     for(j=0;j<g.vexnum;j++)
       printf("%11d",g.arcs[i][j]);
     printf("\n");
   }
   ShortestPath_FLOYD(g,&p,&d);
   printf("d矩阵:\n");
   for(i=0;i<g.vexnum;i++)
   {
     for(j=0;j<g.vexnum;j++)
       printf("%6d",d[i][j]);
     printf("\n");
   }
   for(i=0;i<g.vexnum;i++)
     for(j=0;j<g.vexnum;j++)
       printf("%s到%s的最短距离为%d\n",g.vexs[i],g.vexs[j],d[i][j]);
   printf("p矩阵:\n");
   l=strlen(g.vexs[0]); /* 顶点向量字符串的长度 */
   for(i=0;i<g.vexnum;i++)
   {
     for(j=0;j<g.vexnum;j++)
     {
       if(i!=j)
       {
         m=0; /* 占位空格 */
         for(k=0;k<g.vexnum;k++)
           if(p[i][j][k]==1)
             printf("%s",g.vexs[k]);
           else
             m++;
         for(n=0;n<m*l;n++) /* 输出占位空格 */
           printf(" ");
       }
       else
         for(k=0;k<g.vexnum*l;k++) /* 输出占位空格 */
           printf(" ");
       printf("   "); /* 输出矩阵元素之间的间距 */
     }
     printf("\n");
   }
 }


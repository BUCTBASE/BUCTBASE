 /* algo7-2.c 实现算法7.9的程序 */
 #include"c1.h"
 typedef int VRType;
 typedef char InfoType;
 #define MAX_NAME 3 /* 顶点字符串的最大长度+1 */
 #define MAX_INFO 20 /* 相关信息字符串的最大长度+1 */
 typedef char VertexType[MAX_NAME];
 #include"c7-1.h"
 #include"bo7-1.c"

 typedef struct
 { /* 记录从顶点集U到V-U的代价最小的边的辅助数组定义 */
   VertexType adjvex;
   VRType lowcost;
 }minside[MAX_VERTEX_NUM];

 int minimum(minside SZ,MGraph G)
 { /* 求closedge.lowcost的最小正值 */
   int i=0,j,k,min;
   while(!SZ[i].lowcost)
     i++;
   min=SZ[i].lowcost; /* 第一个不为0的值 */
   k=i;
   for(j=i+1;j<G.vexnum;j++)
     if(SZ[j].lowcost>0)
       if(min>SZ[j].lowcost)
       {
         min=SZ[j].lowcost;
         k=j;
       }
   return k;
 }

 void MiniSpanTree_PRIM(MGraph G,VertexType u)
 { /* 用普里姆算法从第u个顶点出发构造网G的最小生成树T,输出T的各条边 算法7.9 */
   int i,j,k;
   minside closedge;
   k=LocateVex(G,u);
   for(j=0;j<G.vexnum;++j) /* 辅助数组初始化 */
   {
     if(j!=k)
     {
       strcpy(closedge[j].adjvex,u);
       closedge[j].lowcost=G.arcs[k][j].adj;
     }
   }
   closedge[k].lowcost=0; /* 初始,U={u} */
   printf("最小代价生成树的各条边为:\n");
   for(i=1;i<G.vexnum;++i)
   { /* 选择其余G.vexnum-1个顶点 */
     k=minimum(closedge,G); /* 求出T的下一个结点：第K顶点 */
     printf("(%s-%s)\n",closedge[k].adjvex,G.vexs[k]); /* 输出生成树的边 */
     closedge[k].lowcost=0; /* 第K顶点并入U集 */
     for(j=0;j<G.vexnum;++j)
       if(G.arcs[k][j].adj<closedge[j].lowcost)
       { /* 新顶点并入U集后重新选择最小边 */
         strcpy(closedge[j].adjvex,G.vexs[k]);
         closedge[j].lowcost=G.arcs[k][j].adj;
       }
   }
 }

 void main()
 {
   MGraph G;
   CreateAN(&G);
   MiniSpanTree_PRIM(G,G.vexs[0]);
 }


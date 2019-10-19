 /* main7-4.cpp 检验bo7-4.cpp的主程序 */
 #include"c1.h"
 #define MAX_NAME 3 /* 顶点字符串的最大长度+1 */
 #define MAX_INFO 80 /* 相关信息字符串的最大长度+1 */
 typedef char InfoType;
 typedef char VertexType[MAX_NAME]; /* 字符串类型 */
 #include"c7-4.h"
 #include"bo7-4.c"
 Status visit(VertexType v)
 {
   printf("%s ",v);
   return OK;
 }

 void main()
 {
   int k,n;
   AMLGraph g;
   VertexType v1,v2;
   CreateGraph(&g);
   Display(g);
   printf("修改顶点的值，请输入原值 新值: ");
   scanf("%s%s",v1,v2);
   PutVex(&g,v1,v2);
   printf("插入新顶点，请输入顶点的值: ");
   scanf("%s",v1);
   InsertVex(&g,v1);
   printf("插入与新顶点有关的边，请输入边数: ");
   scanf("%d",&n);
   for(k=0;k<n;k++)
   {
     printf("请输入另一顶点的值: ");
     scanf("%s",v2);
     InsertArc(&g,v1,v2);
   }
   Display(g);
   printf("深度优先搜索的结果:\n");
   DFSTraverse(g,visit);
   printf("广度优先搜索的结果:\n");
   BFSTraverse(g,visit);
   DestroyGraph(&g);
 }
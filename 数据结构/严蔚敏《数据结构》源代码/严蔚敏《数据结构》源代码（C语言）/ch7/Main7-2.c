 /* main7-2.c 检验bo7-2.c的主程序 */
 #include"c1.h"
 #define MAX_NAME 3 /* 顶点字符串的最大长度+1 */
 typedef int InfoType; /* 存放网的权值 */
 typedef char VertexType[MAX_NAME]; /* 字符串类型 */
 #include"c7-2.h"
 #include"bo7-2.c"

 void print(char *i)
 {
   printf("%s ",i);
 }

 void main()
 {
   int i,j,k,n;
   ALGraph g;
   VertexType v1,v2;
   printf("请选择有向图\n");
   CreateGraph(&g);
   Display(g);
   printf("删除一条边或弧，请输入待删除边或弧的弧尾 弧头：");
   scanf("%s%s",v1,v2);
   DeleteArc(&g,v1,v2);
   printf("修改顶点的值，请输入原值 新值: ");
   scanf("%s%s",v1,v2);
   PutVex(&g,v1,v2);
   printf("插入新顶点，请输入顶点的值: ");
   scanf("%s",v1);
   InsertVex(&g,v1);
   printf("插入与新顶点有关的弧或边，请输入弧或边数: ");
   scanf("%d",&n);
   for(k=0;k<n;k++)
   {
     printf("请输入另一顶点的值: ");
     scanf("%s",v2);
     printf("对于有向图，请输入另一顶点的方向(0:弧头 1:弧尾): ");
     scanf("%d",&j);
     if(j)
       InsertArc(&g,v2,v1);
     else
       InsertArc(&g,v1,v2);
   }
   Display(g);
   printf("删除顶点及相关的弧或边，请输入顶点的值: ");
   scanf("%s",v1);
   DeleteVex(&g,v1);
   Display(g);
   printf("深度优先搜索的结果:\n");
   DFSTraverse(g,print);
   printf("广度优先搜索的结果:\n");
   BFSTraverse(g,print);
   DestroyGraph(&g);
   printf("请顺序选择有向网,无向图,无向网\n");
   for(i=0;i<3;i++) /* 验证另外3种情况 */
   {
     CreateGraph(&g);
     Display(g);
     printf("插入新顶点，请输入顶点的值: ");
     scanf("%s",v1);
     InsertVex(&g,v1);
     printf("插入与新顶点有关的弧或边，请输入弧或边数: ");
     scanf("%d",&n);
     for(k=0;k<n;k++)
     {
       printf("请输入另一顶点的值: ");
       scanf("%s",v2);
       if(g.kind<=1) /* 有向 */
       {
         printf("对于有向图或网，请输入另一顶点的方向(0:弧头 1:弧尾): ");
         scanf("%d",&j);
         if(j)
           InsertArc(&g,v2,v1);
         else
           InsertArc(&g,v1,v2);
       }
       else /* 无向 */
         InsertArc(&g,v1,v2);
     }
     Display(g);
     printf("删除顶点及相关的弧或边，请输入顶点的值: ");
     scanf("%s",v1);
     DeleteVex(&g,v1);
     Display(g);
     DestroyGraph(&g);
   }
 }

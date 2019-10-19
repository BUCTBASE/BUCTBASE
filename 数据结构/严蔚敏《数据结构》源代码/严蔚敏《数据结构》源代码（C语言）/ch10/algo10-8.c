 /* algo10-8.c 树形选择排序 */
 #include"c1.h"
 typedef int InfoType; /* 定义其它数据项的类型 */
 #include"c10-1.h"
 void TreeSort(SqList *L)
 { /* 树形选择排序 */
   int i,j,j1,k,k1,l,n=(*L).length;
   RedType *t;
   l=(int)ceil(log(n)/log(2))+1; /* 完全二叉树的层数 */
   k=(int)pow(2,l)-1; /* l层完全二叉树的结点总数 */
   k1=(int)pow(2,l-1)-1; /* l-1层完全二叉树的结点总数 */
   t=(RedType*)malloc(k*sizeof(RedType)); /* 二叉树采用顺序存储结构 */
   for(i=1;i<=n;i++) /* 将L.r赋给叶子结点 */
     t[k1+i-1]=(*L).r[i];
   for(i=k1+n;i<k;i++) /* 给多余的叶子的关键字赋无穷大 */
     t[i].key=INT_MAX;
   j1=k1;
   j=k;
   while(j1)
   { /* 给非叶子结点赋值 */
     for(i=j1;i<j;i+=2)
       t[i].key<t[i+1].key?(t[(i+1)/2-1]=t[i]):(t[(i+1)/2-1]=t[i+1]);
     j=j1;
     j1=(j1-1)/2;
   }
   for(i=0;i<n;i++)
   {
     (*L).r[i+1]=t[0]; /* 将当前最小值赋给L.r[i] */
     j1=0;
     for(j=1;j<l;j++) /* 沿树根找结点t[0]在叶子中的序号j1 */
       t[2*j1+1].key==t[j1].key?(j1=2*j1+1):(j1=2*j1+2);
     t[j1].key=INT_MAX;
     while(j1)
     {
       j1=(j1+1)/2-1; /* 序号为j1的结点的双亲结点序号 */
       t[2*j1+1].key<=t[2*j1+2].key?(t[j1]=t[2*j1+1]):(t[j1]=t[2*j1+2]);
     }
   }
   free(t);
 }

 void print(SqList L)
 {
   int i;
   for(i=1;i<=L.length;i++)
     printf("(%d,%d)",L.r[i].key,L.r[i].otherinfo);
   printf("\n");
 }

 #define N 8
 void main()
 {
   RedType d[N]={{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8}};
   SqList l;
   int i;
   for(i=0;i<N;i++)
     l.r[i+1]=d[i];
   l.length=N;
   printf("排序前:\n");
   print(l);
   TreeSort(&l);
   printf("排序后:\n");
   print(l);
 }
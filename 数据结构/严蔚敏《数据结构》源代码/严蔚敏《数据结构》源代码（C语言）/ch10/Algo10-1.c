 /* algo10-1.c 检验bo10-1.c的程序 */
 #include"c1.h"
 typedef int InfoType; /* 定义其它数据项的类型 */
 #include"c9.h"
 #include"c10-1.h"
 #include"bo10-1.c"
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
   SqList l1,l2,l3;
   int i;
   for(i=0;i<N;i++) /* 给l1.r赋值 */
     l1.r[i+1]=d[i];
   l1.length=N;
   l2=l3=l1; /* 复制顺序表l2、l3与l1相同 */
   printf("排序前:\n");
   print(l1);
   InsertSort(&l1);
   printf("直接插入排序后:\n");
   print(l1);
   BInsertSort(&l2);
   printf("折半插入排序后:\n");
   print(l2);
   P2_InsertSort(&l3);
   printf("2_路插入排序后:\n");
   print(l3);
 }

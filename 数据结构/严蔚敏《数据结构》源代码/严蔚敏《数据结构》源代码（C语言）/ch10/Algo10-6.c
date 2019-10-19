 /* algo10-6.c 调用算法10.6(b)的程序(算法10.6(a)的改进) */
 #include<stdio.h>
 typedef int InfoType; /* 定义其它数据项的类型 */
 #include"c10-1.h"
 int Partition(SqList *L,int low,int high)
 { /* 交换顺序表L中子表r[low..high]的记录，枢轴记录到位，并返回其 */
   /* 所在位置，此时在它之前（后）的记录均不大（小）于它。算法10.6(b) */
   KeyType pivotkey;
   (*L).r[0]=(*L).r[low]; /* 用子表的第一个记录作枢轴记录 */
   pivotkey=(*L).r[low].key; /* 枢轴记录关键字 */
   while(low< high)
   { /* 从表的两端交替地向中间扫描 */
     while(low<high&&(*L).r[high].key>=pivotkey)
       --high;
     (*L).r[low]=(*L).r[high]; /* 将比枢轴记录小的记录移到低端 */
     while(low<high&&(*L).r[low].key<=pivotkey)
       ++low;
     (*L).r[high]=(*L).r[low]; /* 将比枢轴记录大的记录移到高端 */
   }
   (*L).r[low]=(*L).r[0]; /* 枢轴记录到位 */
   return low; /* 返回枢轴位置 */
 }

 #include"bo10-2.c"
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
   QuickSort(&l);
   printf("排序后:\n");
   print(l);
 }

 /* algo10-5.c 调用算法10.6(a)的程序 */
 #include<stdio.h>
 typedef int InfoType; /* 定义其它数据项的类型 */
 #include"c10-1.h"
 int Partition(SqList *L,int low,int high)
 { /* 交换顺序表L中子表L.r[low..high]的记录，使枢轴记录到位， */
   /* 并返回其所在位置，此时在它之前(后)的记录均不大(小)于它。算法10.6(a) */
   RedType t;
   KeyType pivotkey;
   pivotkey=(*L).r[low].key; /* 用子表的第一个记录作枢轴记录 */
   while(low<high)
   { /* 从表的两端交替地向中间扫描 */
     while(low<high&&(*L).r[high].key>=pivotkey)
       --high;
     t=(*L).r[low]; /* 将比枢轴记录小的记录交换到低端 */
     (*L).r[low]=(*L).r[high];
     (*L).r[high]=t;
     while(low<high&&(*L).r[low].key<=pivotkey)
       ++low;
     t=(*L).r[low]; /* 将比枢轴记录大的记录交换到高端 */
     (*L).r[low]=(*L).r[high];
     (*L).r[high]=t;
   }
   return low; /* 返回枢轴所在位置 */
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

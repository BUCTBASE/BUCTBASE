 /* algo10-3.c 希尔排序 */
 #include<stdio.h>
 typedef int InfoType; /* 定义其它数据项的类型 */
 #include"c9.h"
 #include"c10-1.h"
 void ShellInsert(SqList *L,int dk)
 { /* 对顺序表L作一趟希尔插入排序。本算法是和一趟直接插入排序相比， */
   /* 作了以下修改： */
   /* 1.前后记录位置的增量是dk,而不是1; */
   /* 2.r[0]只是暂存单元,不是哨兵。当j<=0时,插入位置已找到。算法10.4 */
   int i,j;
   for(i=dk+1;i<=(*L).length;++i)
     if LT((*L).r[i].key,(*L).r[i-dk].key)
     { /* 需将(*L).r[i]插入有序增量子表 */
       (*L).r[0]=(*L).r[i]; /* 暂存在(*L).r[0] */
       for(j=i-dk;j>0&&LT((*L).r[0].key,(*L).r[j].key);j-=dk)
         (*L).r[j+dk]=(*L).r[j]; /* 记录后移，查找插入位置 */
       (*L).r[j+dk]=(*L).r[0]; /* 插入 */
     }
 }

 void print(SqList L)
 {
   int i;
   for(i=1;i<=L.length;i++)
     printf("%d ",L.r[i].key);
   printf("\n");
 }

 void print1(SqList L)
 {
   int i;
   for(i=1;i<=L.length;i++)
     printf("(%d,%d)",L.r[i].key,L.r[i].otherinfo);
   printf("\n");
 }

 void ShellSort(SqList *L,int dlta[],int t)
 { /* 按增量序列dlta[0..t-1]对顺序表L作希尔排序。算法10.5 */
   int k;
   for(k=0;k<t;++k)
   {
     ShellInsert(L,dlta[k]); /* 一趟增量为dlta[k]的插入排序 */
     printf("第%d趟排序结果: ",k+1);
     print(*L);
   }
 }

 #define N 10
 #define T 3
 void main()
 {
   RedType d[N]={{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8},{55,9},{4,10}};
   SqList l;
   int i,dt[T]={5,3,1}; /* 增量序列数组 */
   for(i=0;i<N;i++)
     l.r[i+1]=d[i];
   l.length=N;
   printf("排序前: ");
   print(l);
   ShellSort(&l,dt,T);
   printf("排序后: ");
   print1(l);
 }

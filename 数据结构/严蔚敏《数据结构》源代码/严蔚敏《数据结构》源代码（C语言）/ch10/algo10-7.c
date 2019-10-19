 /* algo10-7.c 简单选择排序 */
 #include<stdio.h>
 typedef int InfoType; /* 定义其它数据项的类型 */
 #include"c10-1.h"
 int SelectMinKey(SqList L,int i)
 { /* 返回在L.r[i..L.length]中key最小的记录的序号 */
   KeyType min;
   int j,k;
   k=i; /* 设第i个为最小 */
   min=L.r[i].key;
   for(j=i+1;j<=L.length;j++)
     if(L.r[j].key<min) /* 找到更小的 */
     {
       k=j;
       min=L.r[j].key;
     }
   return k;
 }

 void SelectSort(SqList *L)
 { /* 对顺序表L作简单选择排序。算法10.9 */
   int i,j;
   RedType t;
   for(i=1;i<(*L).length;++i)
   { /*  选择第i小的记录，并交换到位 */
     j=SelectMinKey(*L,i); /* 在L.r[i..L.length]中选择key最小的记录 */
     if(i!=j)
     { /* 与第i个记录交换 */
       t=(*L).r[i];
       (*L).r[i]=(*L).r[j];
       (*L).r[j]=t;
     }
   }
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
   SelectSort(&l);
   printf("排序后:\n");
   print(l);
 }
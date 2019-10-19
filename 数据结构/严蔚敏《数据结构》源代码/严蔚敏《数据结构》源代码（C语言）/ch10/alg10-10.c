 /* alg10-10.c 归并排序 */
 #include<stdio.h>
 typedef int InfoType; /* 定义其它数据项的类型 */
 #include"c9.h"
 #include"c10-1.h"

 void Merge(RedType SR[],RedType TR[],int i,int m,int n)
 { /* 将有序的SR[i..m]和SR[m+1..n]归并为有序的TR[i..n] 算法10.12 */
   int j,k,l;
   for(j=m+1,k=i;i<=m&&j<=n;++k) /* 将SR中记录由小到大地并入TR */
     if LQ(SR[i].key,SR[j].key)
       TR[k]=SR[i++];
     else
       TR[k]=SR[j++];
   if(i<=m)
     for(l=0;l<=m-i;l++)
       TR[k+l]=SR[i+l]; /* 将剩余的SR[i..m]复制到TR */
   if(j<=n)
     for(l=0;l<=n-j;l++)
       TR[k+l]=SR[j+l]; /* 将剩余的SR[j..n]复制到TR */
 }

 void MSort(RedType SR[],RedType TR1[],int s, int t)
 { /* 将SR[s..t]归并排序为TR1[s..t]。算法10.13 */
   int m;
   RedType TR2[MAXSIZE+1];
   if(s==t)
     TR1[s]=SR[s];
   else
   {
     m=(s+t)/2; /* 将SR[s..t]平分为SR[s..m]和SR[m+1..t] */
     MSort(SR,TR2,s,m); /* 递归地将SR[s..m]归并为有序的TR2[s..m] */
     MSort(SR,TR2,m+1,t); /* 递归地将SR[m+1..t]归并为有序的TR2[m+1..t] */
     Merge(TR2,TR1,s,m,t); /* 将TR2[s..m]和TR2[m+1..t]归并到TR1[s..t] */
   }
 }

 void MergeSort(SqList *L)
 { /* 对顺序表L作归并排序。算法10.14 */
   MSort((*L).r,(*L).r,1,(*L).length);
 }

 void print(SqList L)
 {
   int i;
   for(i=1;i<=L.length;i++)
     printf("(%d,%d)",L.r[i].key,L.r[i].otherinfo);
   printf("\n");
 }

 #define N 7
 void main()
 {
   RedType d[N]={{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7}};
   SqList l;
   int i;
   for(i=0;i<N;i++)
     l.r[i+1]=d[i];
   l.length=N;
   printf("排序前:\n");
   print(l);
   MergeSort(&l);
   printf("排序后:\n");
   print(l);
 }

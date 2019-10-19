 /* bo10-2.c 快速排序的函数 */
 void QSort(SqList *L,int low,int high)
 { /* 对顺序表L中的子序列L.r[low..high]作快速排序。算法10.7 */
   int pivotloc;
   if(low<high)
   { /* 长度大于1 */
     pivotloc=Partition(L,low,high); /* 将L.r[low..high]一分为二 */
     QSort(L,low,pivotloc-1); /* 对低子表递归排序，pivotloc是枢轴位置 */
     QSort(L,pivotloc+1,high); /* 对高子表递归排序 */
   }
 }

 void QuickSort(SqList *L)
 { /* 对顺序表L作快速排序。算法10.8 */
   QSort(L,1,(*L).length);
 }

 void print(SqList L)
 {
   int i;
   for(i=1;i<=L.length;i++)
     printf("(%d,%d)",L.r[i].key,L.r[i].otherinfo);
   printf("\n");
 }
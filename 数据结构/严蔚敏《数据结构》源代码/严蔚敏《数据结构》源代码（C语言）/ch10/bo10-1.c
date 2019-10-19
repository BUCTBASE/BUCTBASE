 /* bo10-1.c 顺序表插入排序的函数(3个) */
 void InsertSort(SqList *L)
 { /* 对顺序表L作直接插入排序。算法10.1 */
   int i,j;
   for(i=2;i<=(*L).length;++i)
     if LT((*L).r[i].key,(*L).r[i-1].key) /* "<",需将L.r[i]插入有序子表 */
     {
       (*L).r[0]=(*L).r[i]; /* 复制为哨兵 */
       for(j=i-1;LT((*L).r[0].key,(*L).r[j].key);--j)
	 (*L).r[j+1]=(*L).r[j]; /* 记录后移 */
       (*L).r[j+1]=(*L).r[0]; /* 插入到正确位置 */
     }
 }

 void BInsertSort(SqList *L)
 { /* 对顺序表L作折半插入排序。算法10.2 */
   int i,j,m,low,high;
   for(i=2;i<=(*L).length;++i)
   {
     (*L).r[0]=(*L).r[i]; /* 将L.r[i]暂存到L.r[0] */
     low=1;
     high=i-1;
     while(low<=high)
     { /* 在r[low..high]中折半查找有序插入的位置 */
       m=(low+high)/2; /* 折半 */
       if LT((*L).r[0].key,(*L).r[m].key)
         high=m-1; /* 插入点在低半区 */
       else
         low=m+1; /* 插入点在高半区 */
     }
     for(j=i-1;j>=high+1;--j)
       (*L).r[j+1]=(*L).r[j]; /* 记录后移 */
     (*L).r[high+1]=(*L).r[0]; /* 插入 */
   }
 }

 void P2_InsertSort(SqList *L)
 { /* 2_路插入排序 */
   int i,j,first,final;
   RedType *d;
   d=(RedType*)malloc((*L).length*sizeof(RedType)); /* 生成L.length个记录的临时空间 */
   d[0]=(*L).r[1]; /* 设L的第1个记录为d中排好序的记录(在位置[0]) */
   first=final=0; /* first、final分别指示d中排好序的记录的第1个和最后1个记录的位置 */
   for(i=2;i<=(*L).length;++i)
   { /* 依次将L的第2个～最后1个记录插入d中 */
     if((*L).r[i].key<d[first].key)
     { /* 待插记录小于d中最小值，插到d[first]之前(不需移动d数组的元素) */
       first=(first-1+(*L).length)%(*L).length; /* 设d为循环向量 */
       d[first]=(*L).r[i];
     }
     else if((*L).r[i].key>d[final].key)
     { /* 待插记录大于d中最大值，插到d[final]之后(不需移动d数组的元素) */
       final=final+1;
       d[final]=(*L).r[i];
     }
     else
     { /* 待插记录大于d中最小值，小于d中最大值，插到d的中间(需要移动d数组的元素) */
       j=final++; /* 移动d的尾部元素以便按序插入记录 */
       while((*L).r[i].key<d[j].key)
       {
         d[(j+1)%(*L).length]=d[j];
         j=(j-1+(*L).length)%(*L).length;
       }
       d[j+1]=(*L).r[i];
     }
   }
   for(i=1;i<=(*L).length;i++) /* 把d赋给L.r */
     (*L).r[i]=d[(i+first-1)%(*L).length]; /* 线性关系 */
 }

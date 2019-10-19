 /* algo2-2.c 实现算法2.2的程序 */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-1.h"
 #include"bo2-1.c"

 void MergeList(SqList La,SqList Lb,SqList *Lc) /* 算法2.2 */
 { /* 已知线性表La和Lb中的数据元素按值非递减排列。 */
   /* 归并La和Lb得到新的线性表Lc,Lc的数据元素也按值非递减排列 */
   int i=1,j=1,k=0;
   int La_len,Lb_len;
   ElemType ai,bj;
   InitList(Lc); /* 创建空表Lc */
   La_len=ListLength(La);
   Lb_len=ListLength(Lb);
   while(i<=La_len&&j<=Lb_len) /* 表La和表Lb均非空 */
   {
     GetElem(La,i,&ai);
     GetElem(Lb,j,&bj);
     if(ai<=bj)
     {
       ListInsert(Lc,++k,ai);
       ++i;
     }
     else
     {
       ListInsert(Lc,++k,bj);
       ++j;
     }
   }
   while(i<=La_len) /* 表La非空且表Lb空 */
   {
     GetElem(La,i++,&ai);
     ListInsert(Lc,++k,ai);
   }
   while(j<=Lb_len) /* 表Lb非空且表La空 */
   {
     GetElem(Lb,j++,&bj);
     ListInsert(Lc,++k,bj);
   }
 }

 void print(ElemType *c)
 {
   printf("%d ",*c);
 }

 void main()
 {
   SqList La,Lb,Lc;
   int j,a[4]={3,5,8,11},b[7]={2,6,8,9,11,15,20};
   InitList(&La); /* 创建空表La */
   for(j=1;j<=4;j++) /* 在表La中插入4个元素 */
     ListInsert(&La,j,a[j-1]);
   printf("La= "); /* 输出表La的内容 */
   ListTraverse(La,print);
   InitList(&Lb); /* 创建空表Lb */
   for(j=1;j<=7;j++) /* 在表Lb中插入7个元素 */
     ListInsert(&Lb,j,b[j-1]);
   printf("Lb= "); /* 输出表Lb的内容 */
   ListTraverse(Lb,print);
   MergeList(La,Lb,&Lc);
   printf("Lc= "); /* 输出表Lc的内容 */
   ListTraverse(Lc,print);
 }
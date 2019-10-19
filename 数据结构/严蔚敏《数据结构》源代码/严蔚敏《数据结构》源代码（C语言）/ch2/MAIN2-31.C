 /* main2-31.c 检验bo2-3.c和bo2-31.cpp的主程序 */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-3.h"
 #include"bo2-3.c" /* 两种方法都适用的函数在此文件中 */
 #include"bo2-31.c"

 void visit(ElemType c)
 {
   printf("%d ",c);
 }

 void main()
 {
   int j,k;
   Status i;
   ElemType e,e0;
   SLinkList L;
   InitList(L);
   for(j=1;j<=5;j++)
     i=ListInsert(L,1,j);
   printf("在L的表头依次插入1～5后：L=");
   ListTraverse(L,visit);
   i=ListEmpty(L);
   printf("L是否空:i=%d(1:是 0:否)表L的长度=%d\n",i,ListLength(L));
   i=ClearList(L);
   printf("清空L后：L=");
   ListTraverse(L,visit);
   i=ListEmpty(L);
   printf("L是否空:i=%d(1:是 0:否)表L的长度=%d\n",i,ListLength(L));
   for(j=1;j<=10;j++)
     ListInsert(L,j,j);
   printf("在L的表尾依次插入1～10后：L=");
   ListTraverse(L,visit);
   GetElem(L,5,&e);
   printf("第5个元素的值为：%d\n",e);
   for(j=0;j<=1;j++)
   {
     k=LocateElem(L,j);
     if(k)
       printf("值为%d的元素在静态链表中的位序为%d\n",j,k);
     else
       printf("没有值为%d的元素\n",j);
   }
   for(j=1;j<=2;j++) /* 测试头两个数据 */
   {
     GetElem(L,j,&e0); /* 把第j个数据赋给e0 */
     i=PriorElem(L,e0,&e); /* 求e0的前驱 */
     if(!i)
       printf("元素%d无前驱\n",e0);
     else
       printf("元素%d的前驱为：%d\n",e0,e);
   }
   for(j=ListLength(L)-1;j<=ListLength(L);j++) /* 最后两个数据 */
   {
     GetElem(L,j,&e0); /* 把第j个数据赋给e0 */
     i=NextElem(L,e0,&e); /* 求e0的后继 */
     if(!i)
       printf("元素%d无后继\n",e0);
     else
       printf("元素%d的后继为：%d\n",e0,e);
   }
   k=ListLength(L); /* k为表长 */
   for(j=k+1;j>=k;j--)
   {
     i=ListDelete(L,j,&e); /* 删除第j个数据 */
     if(i)
       printf("删除的元素为：%d\n",e);
     else
       printf("删除第%d个数据失败\n",j);
   }
   printf("依次输出L的元素：");
   ListTraverse(L,visit); /* 依次对元素调用visit()，输出元素的值 */
 }

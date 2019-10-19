 /* main2-2.c 检验bo2-2.c的主程序(与main2-1.c很像) */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-2.h" /* 与main2-1.c不同 */
 #include"bo2-2.c" /* 与main2-1.c不同 */

 Status comp(ElemType c1,ElemType c2)
 { /* 数据元素判定函数(相等为TRUE,否则为FALSE) */
   if(c1==c2)
     return TRUE;
   else
     return FALSE;
 }

 void visit(ElemType c) /* 与main2-1.c不同 */
 {
   printf("%d ",c);
 }

 void main() /* 除了几个输出语句外，主程和main2-1.c很像 */
 {
   LinkList L; /* 与main2-1.c不同 */
   ElemType e,e0;
   Status i;
   int j,k;
   i=InitList(&L);
   for(j=1;j<=5;j++)
     i=ListInsert(L,1,j);
   printf("在L的表头依次插入1～5后：L=");
   ListTraverse(L,visit); /* 依次对元素调用visit()，输出元素的值 */
   i=ListEmpty(L);
   printf("L是否空：i=%d(1:是 0:否)\n",i);
   i=ClearList(L);
   printf("清空L后：L=");
   ListTraverse(L,visit);
   i=ListEmpty(L);
   printf("L是否空：i=%d(1:是 0:否)\n",i);
   for(j=1;j<=10;j++)
     ListInsert(L,j,j);
   printf("在L的表尾依次插入1～10后：L=");
   ListTraverse(L,visit);
   GetElem(L,5,&e);
   printf("第5个元素的值为：%d\n",e);
   for(j=0;j<=1;j++)
   {
     k=LocateElem(L,j,comp);
     if(k)
       printf("第%d个元素的值为%d\n",k,j);
     else
       printf("没有值为%d的元素\n",j);
   }
   for(j=1;j<=2;j++) /* 测试头两个数据 */
   {
     GetElem(L,j,&e0); /* 把第j个数据赋给e0 */
     i=PriorElem(L,e0,&e); /* 求e0的前驱 */
     if(i==INFEASIBLE)
       printf("元素%d无前驱\n",e0);
     else
       printf("元素%d的前驱为：%d\n",e0,e);
   }
   for(j=ListLength(L)-1;j<=ListLength(L);j++)/*最后两个数据 */
   {
     GetElem(L,j,&e0); /* 把第j个数据赋给e0 */
     i=NextElem(L,e0,&e); /* 求e0的后继 */
     if(i==INFEASIBLE)
       printf("元素%d无后继\n",e0);
     else
       printf("元素%d的后继为：%d\n",e0,e);
   }
   k=ListLength(L); /* k为表长 */
   for(j=k+1;j>=k;j--)
   {
     i=ListDelete(L,j,&e); /* 删除第j个数据 */
     if(i==ERROR)
       printf("删除第%d个数据失败\n",j);
     else
       printf("删除的元素为：%d\n",e);
   }
   printf("依次输出L的元素：");
   ListTraverse(L,visit);
   DestroyList(&L);
   printf("销毁L后：L=%u\n",L);
 }
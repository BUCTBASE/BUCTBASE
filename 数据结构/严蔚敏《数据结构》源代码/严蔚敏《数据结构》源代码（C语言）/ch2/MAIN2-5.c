 /* main2-5.c 检验bo2-5.c的主程序 */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-4.h"
 #include"bo2-5.c"

 Status compare(ElemType c1,ElemType c2) /* 数据元素判定函数(判定相等) */
 {
   if(c1==c2)
     return TRUE;
   else
     return FALSE;
 }

 void vd(ElemType c) /* ListTraverse()调用的函数(类型一致) */
 {
   printf("%d ",c);
 }

 void main()
 {
   DuLinkList L;
   int i,n;
   Status j;
   ElemType e;
   InitList(&L);
   for(i=1;i<=5;i++)
     ListInsert(L,i,i); /* 在第i个结点之前插入i */
   printf("正序输出链表：");
   ListTraverse(L,vd); /* 正序输出 */
   printf("逆序输出链表：");
   ListTraverseBack(L,vd); /* 逆序输出 */
   n=2;
   ListDelete(L,n,&e); /* 删除并释放第n个结点 */
   printf("删除第%d个结点，值为%d，其余结点为：",n,e);
   ListTraverse(L,vd); /* 正序输出 */
   printf("链表的元素个数为%d\n",ListLength(L));
   printf("链表是否空：%d(1:是 0:否)\n",ListEmpty(L));
   ClearList(L); /* 清空链表 */
   printf("清空后，链表是否空：%d(1:是 0:否)\n",ListEmpty(L));
   for(i=1;i<=5;i++)
     ListInsert(L,i,i); /* 重新插入5个结点 */
   ListTraverse(L,vd); /* 正序输出 */
   n=3;
   j=GetElem(L,n,&e); /* 将链表的第n个元素赋值给e */
   if(j)
     printf("链表的第%d个元素值为%d\n",n,e);
   else
     printf("不存在第%d个元素\n",n);
   n=4;
   i=LocateElem(L,n,compare);
   if(i)
     printf("等于%d的元素是第%d个\n",n,i);
   else
     printf("没有等于%d的元素\n",n);
   j=PriorElem(L,n,&e);
   if(j)
     printf("%d的前驱是%d\n",n,e);
   else
     printf("不存在%d的前驱\n",n);
   j=NextElem(L,n,&e);
   if(j)
     printf("%d的后继是%d\n",n,e);
   else
     printf("不存在%d的后继\n",n);
   DestroyList(&L);
 }
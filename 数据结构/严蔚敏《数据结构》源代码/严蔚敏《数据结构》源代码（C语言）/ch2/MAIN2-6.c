 /* main2-6.c 检验bo2-6.cpp的主程序 */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-5.h"
 #include"bo2-6.c"
 Status compare(ElemType c1,ElemType c2) /* c1等于c2 */
 {
   if(c1==c2)
     return TRUE;
   else
     return FALSE;
 }

 int cmp(ElemType a,ElemType b)
 { /* 根据a<、=或>b,分别返回-1、0或1 */
   if(a==b)
     return 0;
   else
     return (a-b)/abs(a-b);
 }

 void visit(ElemType c)
 {
   printf("%d ",c);
 }

 void main()
 {
   Link p,h;
   LinkList L;
   Status i;
   int j,k;
   i=InitList(&L);
   if(!i) /* 初始化空的线性表L不成功 */
     exit(FALSE); /* 退出程序运行 */
   for(j=1;j<=2;j++)
   {
     MakeNode(&p,j); /* 生成由p指向、值为j的结点 */
     InsFirst(&L,L.tail,p); /* 插在表尾 */
   }
   OrderInsert(&L,0,cmp); /* 按升序插在有序表头 */
   for(j=0;j<=3;j++)
   {
     i=LocateElemP(L,j,&p,cmp);
     if(i)
       printf("链表中有值为%d的元素。\n",p->data);
     else
       printf("链表中没有值为%d的元素。\n",j);
   }
   printf("输出链表：");
   ListTraverse(L,visit); /* 输出L */
   for(j=1;j<=4;j++)
   {
     printf("删除表头结点：");
     DelFirst(&L,L.head,&p); /* 删除L的首结点，并以p返回 */
     if(p)
       printf("%d\n",GetCurElem(p));
     else
       printf("表空，无法删除 p=%u\n",p);
   }
   printf("L中结点个数=%d L是否空 %d(1:空 0:否)\n",ListLength(L),ListEmpty(L));
   MakeNode(&p,10);
   p->next=NULL; /* 尾结点 */
   for(j=4;j>=1;j--)
   {
     MakeNode(&h,j*2);
     h->next=p;
     p=h;
   } /* h指向一串5个结点，其值依次是2 4 6 8 10 */
   Append(&L,h); /* 把结点h链接在线性链表L的最后一个结点之后 */
   OrderInsert(&L,12,cmp); /* 按升序插在有序表尾头 */
   OrderInsert(&L,7,cmp); /* 按升序插在有序表中间 */
   printf("输出链表：");
   ListTraverse(L,visit); /* 输出L */
   for(j=1;j<=2;j++)
   {
     p=LocateElem(L,j*5,compare);
     if(p)
       printf("L中存在值为%d的结点。\n",j*5);
     else
       printf("L中不存在值为%d的结点。\n",j*5);
   }
   for(j=1;j<=2;j++)
   {
     LocatePos(L,j,&p); /* p指向L的第j个结点 */
     h=PriorPos(L,p); /* h指向p的前驱 */
     if(h)
       printf("%d的前驱是%d。\n",p->data,h->data);
     else
       printf("%d没前驱。\n",p->data);
   }
   k=ListLength(L);
   for(j=k-1;j<=k;j++)
   {
     LocatePos(L,j,&p); /* p指向L的第j个结点 */
     h=NextPos(p); /* h指向p的后继 */
     if(h)
       printf("%d的后继是%d。\n",p->data,h->data);
     else
       printf("%d没后继。\n",p->data);
   }
   printf("L中结点个数=%d L是否空 %d(1:空 0:否)\n",ListLength(L),ListEmpty(L));
   p=GetLast(L); /* p指向最后一个结点 */
   SetCurElem(p,15); /* 将最后一个结点的值变为15 */
   printf("第1个元素为%d 最后1个元素为%d\n",GetCurElem(GetHead(L)->next),GetCurElem(p));
   MakeNode(&h,10);
   InsBefore(&L,&p,h); /* 将10插到尾结点之前，p指向新结点 */
   p=p->next; /* p恢复为尾结点 */
   MakeNode(&h,20);
   InsAfter(&L,&p,h); /* 将20插到尾结点之后 */
   k=ListLength(L);
   printf("依次删除表尾结点并输出其值：");
   for(j=0;j<=k;j++)
   {
     i=Remove(&L,&p);
     if(!i) /* 删除不成功 */
       printf("删除不成功 p=%u\n",p);
     else
       printf("%d ",p->data);
   }
   MakeNode(&p,29); /* 重建具有1个结点(29)的链表 */
   InsFirst(&L,L.head,p);
   DestroyList(&L); /* 销毁线性链表L */
   printf("销毁线性链表L之后: L.head=%u L.tail=%u L.len=%d\n",L.head,L.tail,L.len);
 }

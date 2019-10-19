 /* bo2-32.c 一个数组可生成若干静态链表(数据结构由c2-3.h定义)的基本操作(12个) */
 void InitSpace(SLinkList L) /* 算法2.14。另加 */
 { /* 将一维数组L中各分量链成一个备用链表，L[0].cur为头指针。“0”表示空指针 */
   int i;
   for(i=0;i<MAXSIZE-1;i++)
     L[i].cur=i+1;
   L[MAXSIZE-1].cur=0;
 }

 int InitList(SLinkList L)
 { /* 构造一个空链表，返回值为空表在数组中的位序 */
   int i;
   i=Malloc(L); /* 调用Malloc()，简化程序 */
   L[i].cur=0; /* 空链表的表头指针为空(0) */
   return i;
 }

 Status ClearList(SLinkList L,int n)
 { /* 初始条件：L中表头位序为n的静态链表已存在。操作结果：将此表重置为空表 */
   int j,k,i=L[n].cur; /* 链表第一个结点的位置 */
   L[n].cur=0; /* 链表空 */
   k=L[0].cur; /* 备用链表第一个结点的位置 */
   L[0].cur=i; /* 把链表的结点连到备用链表的表头 */
   while(i) /* 没到链表尾 */
   {
     j=i;
     i=L[i].cur; /* 指向下一个元素 */
   }
   L[j].cur=k; /* 备用链表的第一个结点接到链表的尾部 */
   return OK;
 }

 Status ListEmpty(SLinkList L,int n)
 { /* 判断L中表头位序为n的链表是否空,若是空表返回TRUE;否则返回FALSE */
   if(L[n].cur==0) /* 空表 */
     return TRUE;
   else
     return FALSE;
 }

 int ListLength(SLinkList L,int n)
 { /* 返回L中表头位序为n的链表的数据元素个数 */
   int j=0,i=L[n].cur; /* i指向第一个元素 */
   while(i) /* 没到静态链表尾 */
   {
     i=L[i].cur; /* 指向下一个元素 */
     j++;
   }
   return j;
 }

 Status GetElem(SLinkList L,int n, int i,ElemType *e)
 { /* 用e返回L中表头位序为n的链表的第i个元素的值 */
   int l,k=n; /* k指向表头序号 */
   if(i<1||i>ListLength(L,n)) /* i值不合理 */
     return ERROR;
   for(l=1;l<=i;l++) /* 移动i-1个元素 */
     k=L[k].cur;
   *e=L[k].data;
   return OK;
 }

 int LocateElem(SLinkList L,int n,ElemType e)
 { /* 在L中表头位序为n的静态单链表中查找第1个值为e的元素。 */
   /* 若找到，则返回它在L中的位序，否则返回0 */
   int i=L[n].cur; /* i指示表中第一个结点 */
   while(i&&L[i].data!=e) /* 在表中顺链查找(e不能是字符串) */
     i=L[i].cur;
   return i;
 }

 Status PriorElem(SLinkList L,int n,ElemType cur_e,ElemType *pre_e)
 { /* 初始条件：在L中表头位序为n的静态单链表已存在 */
   /* 操作结果：若cur_e是此单链表的数据元素，且不是第一个， */
   /*           则用pre_e返回它的前驱，否则操作失败，pre_e无定义 */
   int j,i=L[n].cur; /* i为链表第一个结点的位置 */
   do
   { /* 向后移动结点 */
     j=i;
     i=L[i].cur;
   }while(i&&cur_e!=L[i].data);
   if(i) /* 找到该元素 */
   {
     *pre_e=L[j].data;
     return OK;
   }
   return ERROR;
 }

 Status NextElem(SLinkList L,int n,ElemType cur_e,ElemType *next_e)
 { /* 初始条件：在L中表头位序为n的静态单链表已存在 */
   /* 操作结果：若cur_e是此单链表的数据元素，且不是最后一个， */
   /* 则用next_e返回它的后继，否则操作失败，next_e无定义 */
   int i;
   i=LocateElem(L,n,cur_e); /* 在链表中查找第一个值为cur_e的元素的位置 */
   if(i) /* 在静态单链表中存在元素cur_e */
   {
     i=L[i].cur; /* cur_e的后继的位置 */
     if(i) /* cur_e有后继 */
     {
       *next_e=L[i].data;
       return OK; /* cur_e元素有后继 */
     }
   }
   return ERROR; /* L不存在cur_e元素,cur_e元素无后继 */
 }

 Status ListInsert(SLinkList L,int n,int i,ElemType e)
 { /* 在L中表头位序为n的链表的第i个元素之前插入新的数据元素e */
   int l,j,k=n; /* k指向表头 */
   if(i<1||i>ListLength(L,n)+1)
     return ERROR;
   j=Malloc(L); /* 申请新单元 */
   if(j) /* 申请成功 */
   {
     L[j].data=e; /* 赋值给新单元 */
     for(l=1;l<i;l++) /* 移动i-1个元素 */
       k=L[k].cur;
     L[j].cur=L[k].cur;
     L[k].cur=j;
     return OK;
   }
   return ERROR;
 }

 Status ListDelete(SLinkList L,int n,int i,ElemType *e)
 { /* 删除在L中表头位序为n的链表的第i个数据元素e，并返回其值 */
   int j,k=n; /* k指向表头 */
   if(i<1||i>ListLength(L,n))
     return ERROR;
   for(j=1;j<i;j++) /* 移动i-1个元素 */
     k=L[k].cur;
   j=L[k].cur;
   L[k].cur=L[j].cur;
   *e=L[j].data;
   Free(L,j);
   return OK;
 }

 Status ListTraverse(SLinkList L,int n,void(*vi)(ElemType))
 { /* 依次对L中表头位序为n的链表的每个数据元素,调用函数vi()。一旦vi()失败,则操作失败 */
   int i=L[n].cur; /* 指向第一个元素 */
   while(i) /* 没到静态链表尾 */
   {
     vi(L[i].data); /* 调用vi() */
     i=L[i].cur; /* 指向下一个元素 */
   }
   printf("\n");
   return OK;
 }

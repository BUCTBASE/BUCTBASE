 /* bo2-4.c 设立尾指针的单循环链表(存储结构由c2-2.h定义)的12个基本操作 */
 Status InitList_CL(LinkList *L)
 { /* 操作结果：构造一个空的线性表L */
   *L=(LinkList)malloc(sizeof(struct LNode)); /* 产生头结点,并使L指向此头结点 */
   if(!*L) /* 存储分配失败 */
     exit(OVERFLOW);
   (*L)->next=*L; /* 指针域指向头结点 */
   return OK;
 }

 Status DestroyList_CL(LinkList *L)
 { /* 操作结果：销毁线性表L */
   LinkList q,p=(*L)->next; /* p指向头结点 */
   while(p!=*L) /* 没到表尾 */
   {
     q=p->next;
     free(p);
     p=q;
   }
   free(*L);
   *L=NULL;
   return OK;
 }

 Status ClearList_CL(LinkList *L) /* 改变L */
 { /* 初始条件：线性表L已存在。操作结果：将L重置为空表 */
   LinkList p,q;
   *L=(*L)->next; /* L指向头结点 */
   p=(*L)->next; /* p指向第一个结点 */
   while(p!=*L) /* 没到表尾 */
   {
     q=p->next;
     free(p);
     p=q;
   }
   (*L)->next=*L; /* 头结点指针域指向自身 */
   return OK;
 }

 Status ListEmpty_CL(LinkList L)
 { /* 初始条件：线性表L已存在。操作结果：若L为空表，则返回TRUE，否则返回FALSE */
   if(L->next==L) /* 空 */
     return TRUE;
   else
     return FALSE;
 }

 int ListLength_CL(LinkList L)
 { /* 初始条件：L已存在。操作结果：返回L中数据元素个数 */
   int i=0;
   LinkList p=L->next; /* p指向头结点 */
   while(p!=L) /* 没到表尾 */
   {
     i++;
     p=p->next;
   }
   return i;
 }

 Status GetElem_CL(LinkList L,int i,ElemType *e)
 { /* 当第i个元素存在时,其值赋给e并返回OK,否则返回ERROR */
   int j=1; /* 初始化,j为计数器 */
   LinkList p=L->next->next; /* p指向第一个结点 */
   if(i<=0||i>ListLength_CL(L)) /* 第i个元素不存在 */
     return ERROR;
   while(j<i)
   { /* 顺指针向后查找,直到p指向第i个元素 */
     p=p->next;
     j++;
   }
   *e=p->data; /* 取第i个元素 */
   return OK;
 }

 int LocateElem_CL(LinkList L,ElemType e,Status(*compare)(ElemType,ElemType))
 { /* 初始条件：线性表L已存在，compare()是数据元素判定函数 */
   /* 操作结果：返回L中第1个与e满足关系compare()的数据元素的位序。 */
   /*           若这样的数据元素不存在，则返回值为0 */
   int i=0;
   LinkList p=L->next->next; /* p指向第一个结点 */
   while(p!=L->next)
   {
     i++;
     if(compare(p->data,e)) /* 满足关系 */
       return i;
     p=p->next;
   }
   return 0;
 }

 Status PriorElem_CL(LinkList L,ElemType cur_e,ElemType *pre_e)
 { /* 初始条件：线性表L已存在 */
   /* 操作结果：若cur_e是L的数据元素，且不是第一个，则用pre_e返回它的前驱， */
   /*           否则操作失败，pre_e无定义 */
   LinkList q,p=L->next->next; /* p指向第一个结点 */
   q=p->next;
   while(q!=L->next) /* p没到表尾 */
   {
     if(q->data==cur_e)
     {
       *pre_e=p->data;
       return TRUE;
     }
     p=q;
     q=q->next;
   }
   return FALSE;
 }

 Status NextElem_CL(LinkList L,ElemType cur_e,ElemType *next_e)
 { /* 初始条件：线性表L已存在 */
   /* 操作结果：若cur_e是L的数据元素,且不是最后一个,则用next_e返回它的后继， */
   /*           否则操作失败，next_e无定义 */
   LinkList p=L->next->next; /* p指向第一个结点 */
   while(p!=L) /* p没到表尾 */
   {
     if(p->data==cur_e)
     {
       *next_e=p->next->data;
       return TRUE;
     }
     p=p->next;
   }
   return FALSE;
 }

 Status ListInsert_CL(LinkList *L,int i,ElemType e) /* 改变L */
 { /* 在L的第i个位置之前插入元素e */
   LinkList p=(*L)->next,s; /* p指向头结点 */
   int j=0;
   if(i<=0||i>ListLength_CL(*L)+1) /* 无法在第i个元素之前插入 */
     return ERROR;
   while(j<i-1) /* 寻找第i-1个结点 */
   {
     p=p->next;
     j++;
   }
   s=(LinkList)malloc(sizeof(struct LNode)); /* 生成新结点 */
   s->data=e; /* 插入L中 */
   s->next=p->next;
   p->next=s;
   if(p==*L) /* 改变尾结点 */
     *L=s;
   return OK;
 }

 Status ListDelete_CL(LinkList *L,int i,ElemType *e) /* 改变L */
 { /* 删除L的第i个元素,并由e返回其值 */
   LinkList p=(*L)->next,q; /* p指向头结点 */
   int j=0;
   if(i<=0||i>ListLength_CL(*L)) /* 第i个元素不存在 */
     return ERROR;
   while(j<i-1) /* 寻找第i-1个结点 */
   {
     p=p->next;
     j++;
   }
   q=p->next; /* q指向待删除结点 */
   p->next=q->next;
   *e=q->data;
   if(*L==q) /* 删除的是表尾元素 */
     *L=p;
   free(q); /* 释放待删除结点 */
   return OK;
 }

 Status ListTraverse_CL(LinkList L,void(*vi)(ElemType))
 { /* 初始条件:L已存在。操作结果:依次对L的每个数据元素调用函数vi()。一旦vi()失败,则操作失败 */
   LinkList p=L->next->next;
   while(p!=L->next)
   {
     vi(p->data);
     p=p->next;
   }
   printf("\n");
   return OK;
 }
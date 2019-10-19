 /* bo2-9.c 单链表线性表(存储结构由c2-2.h定义)的扩展操作(11个) */
 void InsertAscend(LinkList L,ElemType e)
 { /* 初始条件：按非降序排列的线性表L已存在。操作结果：在L中按非降序插入新的数据元素e */
   LinkList q=L,p=L->next;
   while(p&&e>p->data)
   {
     q=p;
     p=p->next;
   }
   q->next=(LinkList)malloc(sizeof(struct LNode)); /* 插在q后 */
   q->next->data=e;
   q->next->next=p;
 }

 void InsertDescend(LinkList L,ElemType e)
 { /* 初始条件：按非升序排列的线性表L已存在。操作结果：在L中按非升序插入新的数据元素e */
   LinkList q=L,p=L->next;
   while(p&&e<p->data)
   {
     q=p;
     p=p->next;
   }
   q->next=(LinkList)malloc(sizeof(struct LNode)); /* 插在q后 */
   q->next->data=e;
   q->next->next=p;
 }

 Status HeadInsert(LinkList L,ElemType e)
 { /* 初始条件：线性表L已存在。操作结果：在L的头部插入新的数据元素e,作为链表的第一个元素 */
   LinkList s;
   s=(LinkList)malloc(sizeof(struct LNode)); /* 生成新结点 */
   s->data=e; /* 给结点赋值 */
   s->next=L->next; /* 插在表头 */
   L->next=s;
   return OK;
 }

 Status EndInsert(LinkList L,ElemType e)
 { /* 初始条件：线性表L已存在。操作结果：在L的尾部插入新的数据元素e,作为链表的最后一个元素 */
   LinkList p=L;
   while(p->next) /* 使p指向表尾元素 */
     p=p->next;
   p->next=(LinkList)malloc(sizeof(struct LNode)); /* 在表尾生成新结点 */
   p->next->data=e; /* 给新结点赋值 */
   p->next->next=NULL; /* 表尾 */
   return OK;
 }

 Status DeleteFirst(LinkList L,ElemType *e)
 { /* 初始条件：线性表L已存在，且有不少于1个元素 */
   /* 操作结果：删除L的第一个数据元素，并由e返回其值 */
   LinkList p=L->next;
   if(p)
   {
     *e=p->data;
     L->next=p->next;
     free(p);
     return OK;
   }
   else
     return ERROR;
 }

 Status DeleteTail(LinkList L,ElemType *e)
 { /* 初始条件：线性表L已存在，且有不少于1个元素 */
   /* 操作结果：删除L的最后一个数据元素，并用e返回其值 */
   LinkList p=L,q;
   if(!p->next) /* 链表为空 */
     return ERROR;
   while(p->next)
   {
     q=p;
     p=p->next;
   }
   q->next=NULL; /* 新尾结点的next域设为NULL */
   *e=p->data;
   free(p);
   return OK;
 }

 Status DeleteElem(LinkList L,ElemType e)
 { /* 删除表中值为e的元素，并返回TRUE；如无此元素，则返回FALSE */
   LinkList p=L,q;
   while(p)
   {
     q=p->next;
     if(q&&q->data==e)
     {
       p->next=q->next;
       free(q);
       return TRUE;
     }
     p=q;
   }
   return FALSE;
 }

 Status ReplaceElem(LinkList L,int i,ElemType e)
 { /* 用e取代表L中第i个元素的值 */
   LinkList p=L;
   int j=0;
   while(p->next&&j<i)
   {
     j++;
     p=p->next;
   }
   if(j==i)
   {
     p->data=e;
     return OK;
   }
   else /* 表中不存在第i个元素 */
     return ERROR;
 }

 Status CreatAscend(LinkList *L,int n)
 { /* 按非降序建立n个元素的线性表 */
   int j;
   LinkList p,q,s;
   if(n<=0)
     return ERROR;
   InitList(L);
   printf("请输入%d个元素:\n",n);
   s=(LinkList)malloc(sizeof(struct LNode)); /* 第一个结点 */
   scanf("%d",&s->data);
   s->next=NULL;
   (*L)->next=s;
   for(j=1;j<n;j++)
   {
     s=(LinkList)malloc(sizeof(struct LNode)); /* 其余结点 */
     scanf("%d",&s->data);
     q=*L;
     p=(*L)->next;
     while(p&&p->data<s->data) /* p没到表尾，且所指元素值小于新值 */
     {
       q=p;
       p=p->next; /* 指针后移 */
     }
     s->next=q->next; /* 元素插在q的后面 */
     q->next=s;
   }
   return OK;
 }

 Status CreatDescend(LinkList *L,int n)
 { /* 按非升序建立n个元素的线性表 */
   int j;
   LinkList p,q,s;
   if(n<=0)
     return ERROR;
   InitList(L);
   printf("请输入%d个元素:\n",n);
   s=(LinkList)malloc(sizeof(struct LNode)); /* 第一个结点 */
   scanf("%d",&s->data);
   s->next=NULL;
   (*L)->next=s;
   for(j=1;j<n;j++)
   {
     s=(LinkList)malloc(sizeof(struct LNode)); /* 其余结点 */
     scanf("%d",&s->data);
     q=*L;
     p=(*L)->next;
     while(p&&p->data>s->data) /* p没到表尾，且所指元素值大于新值 */
     {
       q=p;
       p=p->next; /* 指针后移 */
     }
     s->next=q->next; /* 元素插在q的后面 */
     q->next=s;
   }
   return OK;
 }

 Status GetFirstElem(LinkList L,ElemType *e)
 { /* 返回表头元素的值 */
   LinkList p=L->next;
   if(!p) /* 空表 */
     return ERROR;
   else /* 非空表 */
     *e=p->data;
   return OK;
 }

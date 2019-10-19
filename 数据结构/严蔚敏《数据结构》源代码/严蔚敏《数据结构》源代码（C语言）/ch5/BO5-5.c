 /* bo5-5.c 广义表的头尾链表存储(存储结构由c5-5.h定义)的基本操作(11个) */
 Status InitGList(GList *L)
 { /* 创建空的广义表L */
   *L=NULL;
   return OK;
 }

 void DestroyGList(GList *L) /* 广义表的头尾链表存储的销毁操作 */
 { /* 销毁广义表L */
   GList q1,q2;
   if(*L)
   {
     if((*L)->tag==ATOM)
     {
       free(*L); /* 删除原子结点 */
       *L=NULL;
     }
     else /* 删除表结点 */
     {
       q1=(*L)->a.ptr.hp;
       q2=(*L)->a.ptr.tp;
       free(*L);
       *L=NULL;
       DestroyGList(&q1);
       DestroyGList(&q2);
     }
   }
 }

 Status CopyGList(GList *T,GList L)
 { /* 采用头尾链表存储结构,由广义表L复制得到广义表T。算法5.6 */
   if(!L) /* 复制空表 */
     *T=NULL;
   else
   {
     *T=(GList)malloc(sizeof(GLNode)); /* 建表结点 */
     if(!*T)
       exit(OVERFLOW);
     (*T)->tag=L->tag;
     if(L->tag==ATOM)
       (*T)->a.atom=L->a.atom; /* 复制单原子 */
     else
     {
       CopyGList(&((*T)->a.ptr.hp),L->a.ptr.hp);
       /* 复制广义表L->ptr.hp的一个副本T->ptr.hp */
       CopyGList(&((*T)->a.ptr.tp),L->a.ptr.tp);
       /* 复制广义表L->ptr.tp的一个副本T->ptr.tp */
     }
   }
   return OK;
 }

 int GListLength(GList L)
 { /* 返回广义表的长度,即元素个数 */
   int len=0;
   if(!L)
     return 0;
   if(L->tag==ATOM)
     return 1;
   while(L)
   {
     L=L->a.ptr.tp;
     len++;
   }
   return len;
 }

 int GListDepth(GList L)
 { /* 采用头尾链表存储结构,求广义表L的深度。算法5.5 */
   int max,dep;
   GList pp;
   if(!L)
     return 1; /* 空表深度为1 */
   if(L->tag==ATOM)
     return 0; /* 原子深度为0 */
   for(max=0,pp=L;pp;pp=pp->a.ptr.tp)
   {
     dep=GListDepth(pp->a.ptr.hp); /* 求以pp->a.ptr.hp为头指针的子表深度 */
     if(dep>max)
       max=dep;
   }
   return max+1; /* 非空表的深度是各元素的深度的最大值加1 */
 }

 Status GListEmpty(GList L)
 { /* 判定广义表是否为空 */
   if(!L)
     return TRUE;
   else
     return FALSE;
 }

 GList GetHead(GList L)
 { /* 取广义表L的头 */
   GList h,p;
   if(!L)
   {
     printf("空表无表头!\n");
     exit(0);
   }
   p=L->a.ptr.tp;
   L->a.ptr.tp=NULL;
   CopyGList(&h,L);
   L->a.ptr.tp=p;
   return h;
 }

 GList GetTail(GList L)
 { /* 取广义表L的尾 */
   GList t;
   if(!L)
   {
     printf("空表无表尾!\n");
     exit(0);
   }
   CopyGList(&t,L->a.ptr.tp);
   return t;
 }

 Status InsertFirst_GL(GList *L,GList e)
 { /* 初始条件: 广义表存在 */
   /* 操作结果: 插入元素e作为广义表L的第一元素(表头,也可能是子表) */
   GList p=(GList)malloc(sizeof(GLNode));
   if(!p)
     exit(OVERFLOW);
   p->tag=LIST;
   p->a.ptr.hp=e;
   p->a.ptr.tp=*L;
   *L=p;
   return OK;
 }

 Status DeleteFirst_GL(GList *L,GList *e)
 { /* 初始条件: 广义表L存在 */
   /* 操作结果: 删除广义表L的第一元素,并用e返回其值 */
   GList p;
   *e=(*L)->a.ptr.hp;
   p=*L;
   *L=(*L)->a.ptr.tp;
   free(p);
   return OK;
 }

 void Traverse_GL(GList L,void(*v)(AtomType))
 { /* 利用递归算法遍历广义表L */
   if(L) /* L不空 */
     if(L->tag==ATOM) /* L为单原子 */
       v(L->a.atom);
     else /* L为广义表 */
     {
       Traverse_GL(L->a.ptr.hp,v);
       Traverse_GL(L->a.ptr.tp,v);
     }
 }

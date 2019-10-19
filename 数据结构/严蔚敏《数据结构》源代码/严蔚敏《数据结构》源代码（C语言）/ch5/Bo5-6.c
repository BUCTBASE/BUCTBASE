 /* bo5-6.c 广义表的扩展线性链表存储(存储结构由c5-6.h定义)的基本操作(13个) */
 #include"c4-2.h" /* 定义HString类型 */
 #include"bo4-2.c" /* HString类型的基本操作 */
 /* 广义表的书写形式串为HString类型 */
 Status InitGList(GList *L)
 { /* 创建空的广义表L */
   *L=NULL;
   return OK;
 }

 Status sever(HString *str,HString *hstr) /* 同bo5-52.c */
 { /* 将非空串str分割成两部分:hstr为第一个','之前的子串,str为之后的子串 */
   int n,i=1,k=0; /* k记尚未配对的左括号个数 */
   HString ch,c1,c2,c3;
   InitString(&ch); /* 初始化HString类型的变量 */
   InitString(&c1);
   InitString(&c2);
   InitString(&c3);
   StrAssign(&c1,",");
   StrAssign(&c2,"(");
   StrAssign(&c3,")");
   n=StrLength(*str);
   do
   {
     SubString(&ch,*str,i,1);
     if(!StrCompare(ch,c2))
       ++k;
     else if(!StrCompare(ch,c3))
       --k;
     ++i;
   }while(i<=n&&StrCompare(ch,c1)||k!=0);
   if(i<=n)
   {
     StrCopy(&ch,*str);
     SubString(hstr,ch,1,i-2);
     SubString(str,ch,i,n-i+1);
   }
   else
   {
     StrCopy(hstr,*str);
     ClearString(str);
   }
   return OK;
 }

 Status CreateGList(GList *L,HString S)
 { /* 初始条件: S是广义表的书写形式串。操作结果: 由S创建广义表L */
   HString emp,sub,hsub;
   GList p;
   InitString(&emp);
   InitString(&sub);
   InitString(&hsub);
   StrAssign(&emp,"()"); /* 设emp="()" */
   *L=(GList)malloc(sizeof(GLNode));
   if(!*L) /* 建表结点不成功 */
     exit(OVERFLOW);
   if(!StrCompare(S,emp)) /* 创建空表 */
   {
     (*L)->tag=LIST;
     (*L)->a.hp=NULL;
     (*L)->tp=NULL;
   }
   else if(StrLength(S)==1) /* 创建单原子广义表 */
   {
     (*L)->tag=ATOM;
     (*L)->a.atom=S.ch[0];
     (*L)->tp=NULL;
   }
   else /* 创建一般表 */
   {
     (*L)->tag=LIST;
     (*L)->tp=NULL;
     SubString(&sub,S,2,StrLength(S)-2); /* 脱外层括号 */
     sever(&sub,&hsub); /* 从sub中分离出表头串hsub */
     CreateGList(&(*L)->a.hp,hsub);
     p=(*L)->a.hp;
     while(!StrEmpty(sub)) /* 表尾不空,则重复建n个子表 */
     {
       sever(&sub,&hsub); /* 从sub中分离出表头串hsub */
       CreateGList(&p->tp,hsub);
       p=p->tp;
     };
   }
   return OK;
 }

 void DestroyGList(GList *L)
 { /* 初始条件: 广义表L存在。操作结果: 销毁广义表L */
   GList ph,pt;
   if(*L) /* L不为空表 */
   { /* 由ph和pt接替L的两个指针 */
     if((*L)->tag) /* 是子表 */
       ph=(*L)->a.hp;
     else /* 是原子 */
       ph=NULL;
     pt=(*L)->tp;
     free(*L); /* 释放L所指结点 */
     *L=NULL; /* 令L为空 */
     DestroyGList(&ph); /* 递归销毁表ph */
     DestroyGList(&pt); /* 递归销毁表pt */
   }
 }

 Status CopyGList(GList *T,GList L)
 { /* 初始条件: 广义表L存在。操作结果: 由广义表L复制得到广义表T */
   if(!L) /* L空 */
   {
     *T=NULL;
     return OK;
   }
   *T=(GList)malloc(sizeof(GLNode));
   if(!*T)
     exit(OVERFLOW);
   (*T)->tag=L->tag; /* 复制枚举变量 */
   if(L->tag==ATOM) /* 复制共用体部分 */
     (*T)->a.atom=L->a.atom; /* 复制单原子 */
   else
     CopyGList(&(*T)->a.hp,L->a.hp); /* 复制子表 */
   if(L->tp==NULL) /* 到表尾 */
     (*T)->tp=L->tp;
   else
     CopyGList(&(*T)->tp,L->tp); /* 复制子表 */
   return OK;
 }

 int GListLength(GList L)
 { /* 初始条件: 广义表L存在。操作结果: 求广义表L的长度,即元素个数 */
   int len=0;
   GList p;
   if(L->tag==LIST&&!L->a.hp) /* 空表 */
     return 0; /* 空表返回0 */
   else if(L->tag==ATOM) /* 单原子表 */
     return 1;
   else /* 一般表 */
   {
     p=L->a.hp;
     do
     {
       len++;
       p=p->tp;
     }while(p);
     return len;
   }
 }

 int GListDepth(GList L)
 { /* 初始条件: 广义表L存在。操作结果: 求广义表L的深度 */
   int max,dep;
   GList pp;
   if(L==NULL||L->tag==LIST&&!L->a.hp)
     return 1; /* 空表深度为1 */
   else if(L->tag==ATOM)
     return 0; /* 单原子表深度为0 */
   else /* 求一般表的深度 */
     for(max=0,pp=L->a.hp;pp;pp=pp->tp)
     {
       dep=GListDepth(pp); /* 求以pp为头指针的子表深度 */
       if(dep>max)
         max=dep;
     }
   return max+1; /* 非空表的深度是各元素的深度的最大值加1 */
 }

 Status GListEmpty(GList L)
 { /* 初始条件: 广义表L存在。操作结果: 判定广义表L是否为空 */
   if(!L||L->tag==LIST&&!L->a.hp)
     return OK;
   else
     return ERROR;
 }

 GList GetHead(GList L)
 { /* 初始条件: 广义表L存在。操作结果: 取广义表L的头 */
   GList h;
   InitGList(&h);
   if(!L||L->tag==LIST&&!L->a.hp)
   {
     printf("\n空表无表头!");
     exit(0);
   }
   h=(GList)malloc(sizeof(GLNode));
   if(!h)
     exit(OVERFLOW);
   h->tag=L->a.hp->tag;
   h->tp=NULL;
   if(h->tag==ATOM)
     h->a.atom=L->a.hp->a.atom;
   else
     CopyGList(&h->a.hp,L->a.hp->a.hp);
   return h;
 }

 GList GetTail(GList L)
 { /* 初始条件: 广义表L存在。操作结果: 取广义表L的尾 */
   GList T;
   if(!L)
   {
     printf("\n空表无表尾!");
     exit(0);
   }
   T=(GList)malloc(sizeof(GLNode));
   if(!T)
     exit(OVERFLOW);
   T->tag=LIST;
   T->tp=NULL;
   CopyGList(&T->a.hp,L->a.hp->tp);
   return T;
 }

 Status InsertFirst_GL(GList *L,GList e)
 { /* 初始条件: 广义表存在 */
   /* 操作结果: 插入元素e作为广义表L的第一元素(表头,也可能是子表) */
   GList p=(*L)->a.hp;
   (*L)->a.hp=e;
   e->tp=p;
   return OK;
 }

 Status DeleteFirst_GL(GList *L,GList *e)
 { /* 初始条件:广义表L存在。操作结果:删除广义表L的第一元素,并用e返回其值 */
   if(*L)
   {
     *e=(*L)->a.hp;
     (*L)->a.hp=(*e)->tp;
     (*e)->tp=NULL;
   }
   else
     *e=*L;
   return OK;
 }

 void Traverse_GL(GList L,void(*v)(AtomType))
 { /* 利用递归算法遍历广义表L */
   GList hp;
   if(L) /* L不空 */
   {
     if(L->tag==ATOM) /* L为单原子 */
     {
       v(L->a.atom);
       hp=NULL;
     }
     else /* L为子表 */
       hp=L->a.hp;
     Traverse_GL(hp,v);
     Traverse_GL(L->tp,v);
   }
 }


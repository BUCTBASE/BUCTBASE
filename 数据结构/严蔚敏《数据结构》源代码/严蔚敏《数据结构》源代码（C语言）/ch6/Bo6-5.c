 /* bo6-5.c 树的二叉链表(孩子－兄弟)存储(存储结构由c6-5.h定义)的基本操作(17个) */
 Status InitTree(CSTree *T)
 { /* 操作结果: 构造空树T */
   *T=NULL;
   return OK;
 }

 void DestroyTree(CSTree *T)
 { /* 初始条件: 树T存在。操作结果: 销毁树T */
   if(*T)
   {
     if((*T)->firstchild) /* T有长子 */
       DestroyTree(&(*T)->firstchild); /* 销毁T的长子为根结点的子树 */
     if((*T)->nextsibling) /* T有下一个兄弟 */
       DestroyTree(&(*T)->nextsibling); /* 销毁T的下一个兄弟为根结点的子树 */
     free(*T); /* 释放根结点 */
     *T=NULL;
   }
 }

 typedef CSTree QElemType; /* 定义队列元素类型 */
 #include"c3-2.h" /* 定义LinkQueue类型 */
 #include"bo3-2.c" /* LinkQueue类型的基本操作 */
 Status CreateTree(CSTree *T)
 { /* 构造树T */
   char c[20]; /* 临时存放孩子结点(设不超过20个)的值 */
   CSTree p,p1;
   LinkQueue q;
   int i,l;
   InitQueue(&q);
   printf("请输入根结点(字符型,空格为空): ");
   scanf("%c%*c",&c[0]);
   if(c[0]!=Nil) /* 非空树 */
   {
     *T=(CSTree)malloc(sizeof(CSNode)); /* 建立根结点 */
     (*T)->data=c[0];
     (*T)->nextsibling=NULL;
     EnQueue(&q,*T); /* 入队根结点的指针 */
     while(!QueueEmpty(q)) /* 队不空 */
     {
       DeQueue(&q,&p); /* 出队一个结点的指针 */
       printf("请按长幼顺序输入结点%c的所有孩子: ",p->data);
       gets(c);
       l=strlen(c);
       if(l>0) /* 有孩子 */
       {
         p1=p->firstchild=(CSTree)malloc(sizeof(CSNode)); /* 建立长子结点 */
         p1->data=c[0];
         for(i=1;i<l;i++)
         {
           p1->nextsibling=(CSTree)malloc(sizeof(CSNode)); /* 建立下一个兄弟结点 */
           EnQueue(&q,p1); /* 入队上一个结点 */
           p1=p1->nextsibling;
           p1->data=c[i];
         }
         p1->nextsibling=NULL;
         EnQueue(&q,p1); /* 入队最后一个结点 */
       }
       else
         p->firstchild=NULL;
     }
   }
   else
     *T=NULL;
   return OK;
 }

 #define ClearTree DestroyTree /* 二者操作相同 */

 Status TreeEmpty(CSTree T)
 { /* 初始条件: 树T存在。操作结果: 若T为空树,则返回TURE,否则返回FALSE */
   if(T) /* T不空 */
     return FALSE;
   else
     return TRUE;
 }

 int TreeDepth(CSTree T)
 { /* 初始条件: 树T存在。操作结果: 返回T的深度 */
   CSTree p;
   int depth,max=0;
   if(!T) /* 树空 */
     return 0;
   if(!T->firstchild) /* 树无长子 */
     return 1;
   for(p=T->firstchild;p;p=p->nextsibling)
   {
     depth=TreeDepth(p);
     if(depth>max)
       max=depth;
   }
   return max+1;
 }

 TElemType Value(CSTree p)
 { /* 返回p所指结点的值 */
   return p->data;
 }

 TElemType Root(CSTree T)
 { /* 初始条件: 树T存在。操作结果: 返回T的根 */
   if(T)
     return Value(T);
   else
     return Nil;
 }

 CSTree Point(CSTree T,TElemType s)
 { /* 返回二叉链表(孩子－兄弟)树T中指向元素值为s的结点的指针。另加 */
   LinkQueue q;
   QElemType a;
   if(T) /* 非空树 */
   {
     InitQueue(&q); /* 初始化队列 */
     EnQueue(&q,T); /* 根结点入队 */
     while(!QueueEmpty(q)) /* 队不空 */
     {
       DeQueue(&q,&a); /* 出队,队列元素赋给a */
       if(a->data==s)
	 return a;
       if(a->firstchild) /* 有长子 */
         EnQueue(&q,a->firstchild); /* 入队长子 */
       if(a->nextsibling) /* 有下一个兄弟 */
         EnQueue(&q,a->nextsibling); /* 入队下一个兄弟 */
     }
   }
   return NULL;
 }

 Status Assign(CSTree *T,TElemType cur_e,TElemType value)
 { /* 初始条件: 树T存在,cur_e是树T中结点的值。操作结果: 改cur_e为value */
   CSTree p;
   if(*T) /* 非空树 */
   {
     p=Point(*T,cur_e); /* p为cur_e的指针 */
     if(p) /* 找到cur_e */
     {
       p->data=value; /* 赋新值 */
       return OK;
     }
   }
   return Nil; /* 树空或没找到 */
 }

 TElemType Parent(CSTree T,TElemType cur_e)
 { /* 初始条件: 树T存在,cur_e是T中某个结点 */
   /* 操作结果: 若cur_e是T的非根结点,则返回它的双亲,否则函数值为＂空＂ */
   CSTree p,t;
   LinkQueue q;
   InitQueue(&q);
   if(T) /* 树非空 */
   {
     if(Value(T)==cur_e) /* 根结点值为cur_e */
       return Nil;
     EnQueue(&q,T); /* 根结点入队 */
     while(!QueueEmpty(q))
     {
       DeQueue(&q,&p);
       if(p->firstchild) /* p有长子 */
       {
         if(p->firstchild->data==cur_e) /* 长子为cur_e */
           return Value(p); /* 返回双亲 */
         t=p; /* 双亲指针赋给t */
         p=p->firstchild; /* p指向长子 */
         EnQueue(&q,p); /* 入队长子 */
         while(p->nextsibling) /* 有下一个兄弟 */
         {
           p=p->nextsibling; /* p指向下一个兄弟 */
	   if(Value(p)==cur_e) /* 下一个兄弟为cur_e */
	     return Value(t); /* 返回双亲 */
	   EnQueue(&q,p); /* 入队下一个兄弟 */
	 }
       }
     }
   }
   return Nil; /* 树空或没找到cur_e */
 }

 TElemType LeftChild(CSTree T,TElemType cur_e)
 { /* 初始条件: 树T存在,cur_e是T中某个结点 */
   /* 操作结果: 若cur_e是T的非叶子结点,则返回它的最左孩子,否则返回＂空＂ */
   CSTree f;
   f=Point(T,cur_e); /* f指向结点cur_e */
   if(f&&f->firstchild) /* 找到结点cur_e且结点cur_e有长子 */
     return f->firstchild->data;
   else
     return Nil;
 }

 TElemType RightSibling(CSTree T,TElemType cur_e)
 { /* 初始条件: 树T存在,cur_e是T中某个结点 */
   /* 操作结果: 若cur_e有右兄弟,则返回它的右兄弟,否则返回＂空＂ */
   CSTree f;
   f=Point(T,cur_e); /* f指向结点cur_e */
   if(f&&f->nextsibling) /* 找到结点cur_e且结点cur_e有右兄弟 */
     return f->nextsibling->data;
   else
     return Nil; /* 树空 */
 }

 Status InsertChild(CSTree *T,CSTree p,int i,CSTree c)
 { /* 初始条件: 树T存在,p指向T中某个结点,1≤i≤p所指结点的度+1,非空树c与T不相交 */
   /* 操作结果: 插入c为T中p结点的第i棵子树 */
   /* 因为p所指结点的地址不会改变，故p不需是引用类型 */
   int j;
   if(*T) /* T不空 */
   {
     if(i==1) /* 插入c为p的长子 */
     {
       c->nextsibling=p->firstchild; /* p的原长子现是c的下一个兄弟(c本无兄弟) */
       p->firstchild=c;
     }
     else /* 找插入点 */
     {
       p=p->firstchild; /* 指向p的长子 */
       j=2;
       while(p&&j<i)
       {
         p=p->nextsibling;
         j++;
       }
       if(j==i) /* 找到插入位置 */
       {
         c->nextsibling=p->nextsibling;
         p->nextsibling=c;
       }
       else /* p原有孩子数小于i-1 */
         return ERROR;
     }
     return OK;
   }
   else /* T空 */
     return ERROR;
 }

 Status DeleteChild(CSTree *T,CSTree p,int i)
 { /* 初始条件: 树T存在,p指向T中某个结点,1≤i≤p所指结点的度 */
   /* 操作结果: 删除T中p所指结点的第i棵子树 */
   /* 因为p所指结点的地址不会改变，故p不需是引用类型 */
   CSTree b;
   int j;
   if(*T) /* T不空 */
   {
     if(i==1) /* 删除长子 */
     {
       b=p->firstchild;
       p->firstchild=b->nextsibling; /* p的原次子现是长子 */
       b->nextsibling=NULL;
       DestroyTree(&b);
     }
     else /* 删除非长子 */
     {
       p=p->firstchild; /* p指向长子 */
       j=2;
       while(p&&j<i)
       {
         p=p->nextsibling;
         j++;
       }
       if(j==i) /* 找到第i棵子树 */
       {
         b=p->nextsibling;
         p->nextsibling=b->nextsibling;
         b->nextsibling=NULL;
         DestroyTree(&b);
       }
       else /* p原有孩子数小于i */
         return ERROR;
     }
     return OK;
   }
   else
     return ERROR;
 }

 void PreOrderTraverse(CSTree T,void(*Visit)(TElemType))
 { /* 先根遍历孩子－兄弟二叉链表结构的树T */
   if(T)
   {
     Visit(Value(T)); /* 先访问根结点 */
     PreOrderTraverse(T->firstchild,Visit); /* 再先根遍历长子子树 */
     PreOrderTraverse(T->nextsibling,Visit); /* 最后先根遍历下一个兄弟子树 */
   }
 }

 void PostOrderTraverse(CSTree T,void(*Visit)(TElemType))
 { /* 后根遍历孩子－兄弟二叉链表结构的树T */
   CSTree p;
   if(T)
   {
     if(T->firstchild) /* 有长子 */
     {
       PostOrderTraverse(T->firstchild,Visit); /* 后根遍历长子子树 */
       p=T->firstchild->nextsibling; /* p指向长子的下一个兄弟 */
       while(p)
       {
         PostOrderTraverse(p,Visit); /* 后根遍历下一个兄弟子树 */
         p=p->nextsibling; /* p指向再下一个兄弟 */
       }
     }
     Visit(Value(T)); /* 最后访问根结点 */
   }
 }

 void LevelOrderTraverse(CSTree T,void(*Visit)(TElemType))
 { /* 层序遍历孩子－兄弟二叉链表结构的树T */
   CSTree p;
   LinkQueue q;
   InitQueue(&q);
   if(T)
   {
     Visit(Value(T)); /* 先访问根结点 */
     EnQueue(&q,T); /* 入队根结点的指针 */
     while(!QueueEmpty(q)) /* 队不空 */
     {
       DeQueue(&q,&p); /* 出队一个结点的指针 */
       if(p->firstchild) /* 有长子 */
       {
         p=p->firstchild;
         Visit(Value(p)); /* 访问长子结点 */
         EnQueue(&q,p); /* 入队长子结点的指针 */
         while(p->nextsibling) /* 有下一个兄弟 */
         {
           p=p->nextsibling;
           Visit(Value(p)); /* 访问下一个兄弟 */
           EnQueue(&q,p); /* 入队兄弟结点的指针 */
         }
       }
     }
   }
 }

 /* bo6-6.c 二叉树的三叉链表存储(存储结构由c6-7.h定义)的基本操作(21个) */
 Status InitBiTree(BiPTree *T)
 { /* 操作结果: 构造空二叉树T */
   *T=NULL;
   return OK;
 }

 void DestroyBiTree(BiPTree *T)
 { /* 初始条件: 二叉树T存在。操作结果: 销毁二叉树T */
   if(*T) /* 非空树 */
   {
     if((*T)->lchild) /* 有左孩子 */
       DestroyBiTree(&(*T)->lchild); /* 销毁左孩子子树 */
     if((*T)->rchild) /* 有右孩子 */
       DestroyBiTree(&(*T)->rchild); /* 销毁右孩子子树 */
     free(*T); /* 释放根结点 */
     *T=NULL; /* 空指针赋0 */
   }
 }

 void Create(BiPTree *T) /* CreateBiTree()调用 */
 { /* 按先序次序输入二叉树中结点的值（可为字符型或整型，在主程中定义）， */
   /* 构造仅缺双亲指针的三叉链表表示的二叉树T。变量Nil表示空（子）树 */
   TElemType ch;
 #ifdef CHAR
   scanf("%c",&ch);
 #endif
 #ifdef INT
   scanf("%d",&ch);
 #endif
   if(ch==Nil) /* 空 */
     *T=NULL;
   else
   {
     *T=(BiPTree)malloc(sizeof(BiTPNode));
     if(!*T)
       exit(OVERFLOW);
     (*T)->data=ch; /* 生成根结点 */
     Create(&(*T)->lchild); /* 构造左子树 */
     Create(&(*T)->rchild); /* 构造右子树 */
   }
 }

 typedef BiPTree QElemType; /* 设队列元素为二叉树的指针类型 */
 #include"c3-2.h"
 #include"bo3-2.c"
 Status CreateBiTree(BiPTree *T)
 { /* 按先序次序输入二叉树中结点的值（可为字符型或整型，在主程中定义）， */
   /* 构造三叉链表表示的二叉树T */
   LinkQueue q;
   QElemType a;
   Create(T); /* 构造二叉树(缺双亲指针) */
   if(*T) /* 非空树 */
   {
     (*T)->parent=NULL; /* 根结点的双亲为＂空＂ */
     InitQueue(&q); /* 初始化队列 */
     EnQueue(&q,*T); /* 根指针入队 */
     while(!QueueEmpty(q)) /* 队不空 */
     {
       DeQueue(&q,&a); /* 出队,队列元素赋给a */
       if(a->lchild) /* 有左孩子 */
       {
         a->lchild->parent=a; /* 给左孩子的双亲指针赋值 */
         EnQueue(&q,a->lchild); /* 左孩子入队 */
       }
       if(a->rchild) /* 有右孩子 */
       {
	 a->rchild->parent=a; /* 给右孩子的双亲指针赋值 */
         EnQueue(&q,a->rchild); /* 右孩子入队 */
       }
     }
   }
   return OK;
 }

 #define ClearBiTree DestroyBiTree

 Status BiTreeEmpty(BiPTree T)
 { /* 初始条件: 二叉树T存在。操作结果: 若T为空二叉树,则返回TRUE,否则FALSE */
   if(T)
     return FALSE;
   else
     return TRUE;
 }

 int BiTreeDepth(BiPTree T)
 { /* 初始条件: 二叉树T存在。操作结果: 返回T的深度 */
   int i,j;
   if(!T)
     return 0;
   if(T->lchild)
     i=BiTreeDepth(T->lchild);
   else
     i=0;
   if(T->rchild)
     j=BiTreeDepth(T->rchild);
   else
     j=0;
   return i>j?i+1:j+1;
 }

 TElemType Root(BiPTree T)
 { /* 初始条件: 二叉树T存在。操作结果: 返回T的根 */
   if(T)
     return T->data;
   else
     return Nil;
 }

 TElemType Value(BiPTree p)
 { /* 初始条件: 二叉树T存在，p指向T中某个结点 */
   /* 操作结果: 返回p所指结点的值 */
   return p->data;
 }

 void Assign(BiPTree p,TElemType value)
 { /* 给p所指结点赋值为value */
   p->data=value;
 }

 BiPTree Point(BiPTree T,TElemType e)
 { /* 返回二叉树T中指向元素值为e的结点的指针。加 */
   LinkQueue q;
   QElemType a;
   if(T) /* 非空树 */
   {
     InitQueue(&q); /* 初始化队列 */
     EnQueue(&q,T); /* 根结点入队 */
     while(!QueueEmpty(q)) /* 队不空 */
     {
       DeQueue(&q,&a); /* 出队,队列元素赋给a */
       if(a->data==e)
         return a;
       if(a->lchild) /* 有左孩子 */
         EnQueue(&q,a->lchild); /* 入队左孩子 */
       if(a->rchild) /* 有右孩子 */
         EnQueue(&q,a->rchild); /* 入队右孩子 */
     }
   }
   return NULL;
 }

 TElemType Parent(BiPTree T,TElemType e)
 { /* 初始条件: 二叉树T存在,e是T中某个结点 */
   /* 操作结果: 若e是T的非根结点,则返回它的双亲,否则返回＂空＂ */
   BiPTree a;
   if(T) /* 非空树 */
   {
     a=Point(T,e); /* a是结点e的指针 */
     if(a&&a!=T) /* T中存在结点e且e是非根结点 */
       return a->parent->data; /* 返回e的双亲的值 */
   }
   return Nil; /* 其余情况返回空 */
 }

 TElemType LeftChild(BiPTree T,TElemType e)
 { /* 初始条件: 二叉树T存在,e是T中某个结点 */
   /* 操作结果: 返回e的左孩子。若e无左孩子,则返回＂空＂ */
   BiPTree a;
   if(T) /* 非空树 */
   {
     a=Point(T,e); /* a是结点e的指针 */
     if(a&&a->lchild) /* T中存在结点e且e存在左孩子 */
       return a->lchild->data; /* 返回e的左孩子的值 */
   }
   return Nil; /* 其余情况返回空 */
 }

 TElemType RightChild(BiPTree T,TElemType e)
 { /* 初始条件: 二叉树T存在,e是T中某个结点 */
   /* 操作结果: 返回e的右孩子。若e无右孩子,则返回＂空＂ */
   BiPTree a;
   if(T) /* 非空树 */
   {
     a=Point(T,e); /* a是结点e的指针 */
     if(a&&a->rchild) /* T中存在结点e且e存在右孩子 */
       return a->rchild->data; /* 返回e的右孩子的值 */
   }
   return Nil; /* 其余情况返回空 */
 }

 TElemType LeftSibling(BiPTree T,TElemType e)
 { /* 初始条件: 二叉树T存在,e是T中某个结点 */
   /* 操作结果: 返回e的左兄弟。若e是T的左孩子或无左兄弟,则返回＂空＂ */
   BiPTree a;
   if(T) /* 非空树 */
   {
     a=Point(T,e); /* a是结点e的指针 */
     if(a&&a!=T&&a->parent->lchild&&a->parent->lchild!=a) /* T中存在结点e且e存在左兄弟 */
       return a->parent->lchild->data; /* 返回e的左兄弟的值 */
   }
   return Nil; /* 其余情况返回空 */
 }

 TElemType RightSibling(BiPTree T,TElemType e)
 { /* 初始条件: 二叉树T存在,e是T中某个结点 */
   /* 操作结果: 返回e的右兄弟。若e是T的右孩子或无右兄弟,则返回＂空＂ */
   BiPTree a;
   if(T) /* 非空树 */
   {
     a=Point(T,e); /* a是结点e的指针 */
     if(a&&a!=T&&a->parent->rchild&&a->parent->rchild!=a) /* T中存在结点e且e存在右兄弟 */
       return a->parent->rchild->data; /* 返回e的右兄弟的值 */
   }
   return Nil; /* 其余情况返回空 */
 }

 Status InsertChild(BiPTree p,int LR,BiPTree c) /* 形参T无用 */
 { /* 初始条件: 二叉树T存在,p指向T中某个结点,LR为0或1,非空二叉树c与T */
   /*           不相交且右子树为空 */
   /* 操作结果: 根据LR为0或1,插入c为T中p所指结点的左或右子树。p所指结点 */
   /*           的原有左或右子树则成为c的右子树。 */
   if(p) /* p不空 */
   {
     if(LR==0)
     {
       c->rchild=p->lchild;
       if(c->rchild) /* c有右孩子(p原有左孩子) */
         c->rchild->parent=c;
       p->lchild=c;
       c->parent=p;
     }
     else /* LR==1 */
     {
       c->rchild=p->rchild;
       if(c->rchild) /* c有右孩子(p原有右孩子) */
         c->rchild->parent=c;
       p->rchild=c;
       c->parent=p;
     }
     return OK;
   }
   return ERROR; /* p空 */
 }

 Status DeleteChild(BiPTree p,int LR) /* 形参T无用 */
 { /* 初始条件: 二叉树T存在,p指向T中某个结点,LR为0或1 */
   /* 操作结果: 根据LR为0或1,删除T中p所指结点的左或右子树 */
   if(p) /* p不空 */
   {
     if(LR==0) /* 删除左子树 */
       ClearBiTree(&p->lchild);
     else /* 删除右子树 */
       ClearBiTree(&p->rchild);
     return OK;
   }
   return ERROR; /* p空 */
 }

 void PreOrderTraverse(BiPTree T,Status(*Visit)(BiPTree))
 { /* 先序递归遍历二叉树T */
   if(T)
   {
     Visit(T); /* 先访问根结点 */
     PreOrderTraverse(T->lchild,Visit); /* 再先序遍历左子树 */
     PreOrderTraverse(T->rchild,Visit); /* 最后先序遍历右子树 */
   }
 }

 void InOrderTraverse(BiPTree T,Status(*Visit)(BiPTree))
 { /* 中序递归遍历二叉树T */
   if(T)
   {
     InOrderTraverse(T->lchild,Visit); /* 中序遍历左子树 */
     Visit(T); /* 再访问根结点 */
     InOrderTraverse(T->rchild,Visit); /* 最后中序遍历右子树 */
   }
 }

 void PostOrderTraverse(BiPTree T,Status(*Visit)(BiPTree))
 { /* 后序递归遍历二叉树T */
   if(T)
   {
     PostOrderTraverse(T->lchild,Visit); /* 后序遍历左子树 */
     PostOrderTraverse(T->rchild,Visit); /* 后序遍历右子树 */
     Visit(T); /* 最后访问根结点 */
   }
 }

 void LevelOrderTraverse(BiPTree T,Status(*Visit)(BiPTree))
 { /* 层序遍历二叉树T(利用队列) */
   LinkQueue q;
   QElemType a;
   if(T)
   {
     InitQueue(&q);
     EnQueue(&q,T);
     while(!QueueEmpty(q))
     {
       DeQueue(&q,&a);
       Visit(a);
       if(a->lchild!=NULL)
         EnQueue(&q,a->lchild);
       if(a->rchild!=NULL)
         EnQueue(&q,a->rchild);
     }
   }
 }

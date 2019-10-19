 /* bo9-2.c 动态查找表(二叉排序树)的基本操作(8个) */
 typedef ElemType TElemType;
 #include"c6-2.h"

 Status InitDSTable(BiTree *DT) /* 同bo6-2.c */
 { /* 操作结果: 构造一个空的动态查找表DT */
   *DT=NULL;
   return OK;
 }

 void DestroyDSTable(BiTree *DT) /* 同bo6-2.c */
 { /* 初始条件: 动态查找表DT存在。操作结果: 销毁动态查找表DT */
   if(*DT) /* 非空树 */
   {
     if((*DT)->lchild) /* 有左孩子 */
       DestroyDSTable(&(*DT)->lchild); /* 销毁左孩子子树 */
     if((*DT)->rchild) /* 有右孩子 */
       DestroyDSTable(&(*DT)->rchild); /* 销毁右孩子子树 */
     free(*DT); /* 释放根结点 */
     *DT=NULL; /* 空指针赋0 */
   }
 }

 BiTree SearchBST(BiTree T,KeyType key)
 { /* 在根指针T所指二叉排序树中递归地查找某关键字等于key的数据元素， */
   /* 若查找成功，则返回指向该数据元素结点的指针,否则返回空指针。算法9.5(a) */
   if((!T)||EQ(key,T->data.key))
     return T; /* 查找结束 */
   else if LT(key,T->data.key) /* 在左子树中继续查找 */
     return SearchBST(T->lchild,key);
   else
     return SearchBST(T->rchild,key); /* 在右子树中继续查找 */
 }

 void SearchBST1(BiTree *T,KeyType key,BiTree f,BiTree *p,Status *flag) /* 算法9.5(b)改 */
 { /* 在根指针T所指二叉排序树中递归地查找其关键字等于key的数据元素，若查找 */
   /* 成功，则指针p指向该数据元素结点，并返回TRUE，否则指针p指向查找路径上 */
   /* 访问的最后一个结点并返回FALSE,指针f指向T的双亲，其初始调用值为NULL */
   if(!*T) /* 查找不成功 */
   {
     *p=f;
     *flag=FALSE;
   }
   else if EQ(key,(*T)->data.key) /*  查找成功 */
   {
     *p=*T;
     *flag=TRUE;
   }
   else if LT(key,(*T)->data.key)
     SearchBST1(&(*T)->lchild,key,*T,p,flag); /* 在左子树中继续查找 */
   else
     SearchBST1(&(*T)->rchild,key,*T,p,flag); /*  在右子树中继续查找 */
 }

 Status InsertBST(BiTree *T, ElemType e)
 { /* 当二叉排序树T中不存在关键字等于e.key的数据元素时，插入e并返回TRUE， */
   /* 否则返回FALSE。算法9.6(改) */
   BiTree p,s;
   Status flag;
   SearchBST1(T,e.key,NULL,&p,&flag);
   if(!flag) /* 查找不成功 */
   {
     s=(BiTree)malloc(sizeof(BiTNode));
     s->data=e;
     s->lchild=s->rchild=NULL;
     if(!p)
       *T=s; /* 被插结点*s为新的根结点 */
     else if LT(e.key,p->data.key)
       p->lchild=s; /* 被插结点*s为左孩子 */
     else
       p->rchild=s; /* 被插结点*s为右孩子 */
     return TRUE;
   }
   else
     return FALSE; /* 树中已有关键字相同的结点，不再插入 */
 }

 void Delete(BiTree *p)
 { /* 从二叉排序树中删除结点p，并重接它的左或右子树。算法9.8 */
   BiTree q,s;
   if(!(*p)->rchild) /* 右子树空则只需重接它的左子树（待删结点是叶子也走此分支） */
   {
     q=*p;
     *p=(*p)->lchild;
     free(q);
   }
   else if(!(*p)->lchild) /* 只需重接它的右子树 */
   {
     q=*p;
     *p=(*p)->rchild;
     free(q);
   }
   else /* 左右子树均不空 */
   {
     q=*p;
     s=(*p)->lchild;
     while(s->rchild) /* 转左，然后向右到尽头（找待删结点的前驱） */
     {
       q=s;
       s=s->rchild;
     }
     (*p)->data=s->data; /* s指向被删结点的＂前驱＂（将被删结点前驱的值取代被删结点的值） */
     if(q!=*p)
       q->rchild=s->lchild; /* 重接*q的右子树 */
     else
       q->lchild=s->lchild; /* 重接*q的左子树 */
     free(s);
   }
 }

 Status DeleteBST(BiTree *T,KeyType key)
 { /* 若二叉排序树T中存在关键字等于key的数据元素时，则删除该数据元素结点， */
   /* 并返回TRUE；否则返回FALSE。算法9.7 */
   if(!*T) /* 不存在关键字等于key的数据元素 */
     return FALSE;
   else
   {
     if EQ(key,(*T)->data.key) /* 找到关键字等于key的数据元素 */
       Delete(T);
     else if LT(key,(*T)->data.key)
       DeleteBST(&(*T)->lchild,key);
     else
       DeleteBST(&(*T)->rchild,key);
     return TRUE;
   }
 }

 void TraverseDSTable(BiTree DT,void(*Visit)(ElemType))
 { /* 初始条件: 动态查找表DT存在，Visit是对结点操作的应用函数 */
   /* 操作结果: 按关键字的顺序对DT的每个结点调用函数Visit()一次且至多一次 */
   if(DT)
   {
     TraverseDSTable(DT->lchild,Visit); /* 先中序遍历左子树 */
     Visit(DT->data); /* 再访问根结点 */
     TraverseDSTable(DT->rchild,Visit); /* 最后中序遍历右子树 */
   }
 }
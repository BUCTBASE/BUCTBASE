 /* bo9-3.c 动态查找表(平衡二叉树)的基本操作 */
 Status InitDSTable(BSTree *DT) /* 同bo6-2.c */
 { /* 操作结果: 构造一个空的动态查找表DT */
   *DT=NULL;
   return OK;
 }

 void DestroyDSTable(BSTree *DT) /* 同bo6-2.c */
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

 BSTree SearchBST(BSTree T,KeyType key)
 { /* 在根指针T所指二叉排序树中递归地查找某关键字等于key的数据元素， */
   /* 若查找成功，则返回指向该数据元素结点的指针,否则返回空指针。算法9.5(a) */
   if((!T)||EQ(key,T->data.key))
     return T; /* 查找结束 */
   else if LT(key,T->data.key) /* 在左子树中继续查找 */
     return SearchBST(T->lchild,key);
   else
     return SearchBST(T->rchild,key); /* 在右子树中继续查找 */
 }

 void R_Rotate(BSTree *p)
 { /* 对以*p为根的二叉排序树作右旋处理，处理之后p指向新的树根结点，即旋转 */
   /* 处理之前的左子树的根结点。算法9.9 */
   BSTree lc;
   lc=(*p)->lchild; /* lc指向p的左子树根结点 */
   (*p)->lchild=lc->rchild; /* lc的右子树挂接为p的左子树 */
   lc->rchild=*p;
   *p=lc; /* p指向新的根结点 */
 }

 void L_Rotate(BSTree *p)
 { /* 对以*p为根的二叉排序树作左旋处理，处理之后p指向新的树根结点，即旋转 */
   /* 处理之前的右子树的根结点。算法9.10 */
   BSTree rc;
   rc=(*p)->rchild; /* rc指向p的右子树根结点 */
   (*p)->rchild=rc->lchild; /* rc的左子树挂接为p的右子树 */
   rc->lchild=*p;
   *p=rc; /* p指向新的根结点 */
 }

 #define LH +1 /* 左高 */
 #define EH 0  /* 等高 */
 #define RH -1 /* 右高 */

 void LeftBalance(BSTree *T)
 { /* 对以指针T所指结点为根的二叉树作左平衡旋转处理，本算法结束时， */
   /* 指针T指向新的根结点。算法9.12 */
   BSTree lc,rd;
   lc=(*T)->lchild; /* lc指向*T的左子树根结点 */
   switch(lc->bf)
   { /* 检查*T的左子树的平衡度，并作相应平衡处理 */
     case LH: /* 新结点插入在*T的左孩子的左子树上，要作单右旋处理 */
              (*T)->bf=lc->bf=EH;
              R_Rotate(T);
              break;
     case RH: /* 新结点插入在*T的左孩子的右子树上，要作双旋处理 */
              rd=lc->rchild; /* rd指向*T的左孩子的右子树根 */
              switch(rd->bf)
              { /* 修改*T及其左孩子的平衡因子 */
                case LH: (*T)->bf=RH;
                         lc->bf=EH;
                         break;
                case EH: (*T)->bf=lc->bf=EH;
                         break;
                case RH: (*T)->bf=EH;
                         lc->bf=LH;
	      }
              rd->bf=EH;
              L_Rotate(&(*T)->lchild); /* 对*T的左子树作左旋平衡处理 */
              R_Rotate(T); /* 对*T作右旋平衡处理 */
   }
 }

 void RightBalance(BSTree *T)
 { /* 对以指针T所指结点为根的二叉树作右平衡旋转处理，本算法结束时， */
   /* 指针T指向新的根结点 */
   BSTree rc,rd;
   rc=(*T)->rchild; /* rc指向*T的右子树根结点 */
   switch(rc->bf)
   { /* 检查*T的右子树的平衡度，并作相应平衡处理 */
     case RH: /* 新结点插入在*T的右孩子的右子树上，要作单左旋处理 */
              (*T)->bf=rc->bf=EH;
              L_Rotate(T);
              break;
     case LH: /* 新结点插入在*T的右孩子的左子树上，要作双旋处理 */
              rd=rc->lchild; /* rd指向*T的右孩子的左子树根 */
	      switch(rd->bf)
              { /* 修改*T及其右孩子的平衡因子 */
                case RH: (*T)->bf=LH;
                         rc->bf=EH;
                         break;
                case EH: (*T)->bf=rc->bf=EH;
                         break;
                case LH: (*T)->bf=EH;
                         rc->bf=RH;
              }
              rd->bf=EH;
              R_Rotate(&(*T)->rchild); /* 对*T的右子树作右旋平衡处理 */
              L_Rotate(T); /* 对*T作左旋平衡处理 */
   }
 }

 Status InsertAVL(BSTree *T,ElemType e,Status *taller)
 { /* 若在平衡的二叉排序树T中不存在和e有相同关键字的结点，则插入一个 */
   /* 数据元素为e的新结点，并返回1，否则返回0。若因插入而使二叉排序树 */
   /* 失去平衡，则作平衡旋转处理，布尔变量taller反映T长高与否。算法9.11 */
   if(!*T)
   { /* 插入新结点，树“长高”，置taller为TRUE */
     *T=(BSTree)malloc(sizeof(BSTNode));
     (*T)->data=e;
     (*T)->lchild=(*T)->rchild=NULL;
     (*T)->bf=EH;
     *taller=TRUE;
   }
   else
   {
     if EQ(e.key,(*T)->data.key)
     { /* 树中已存在和e有相同关键字的结点则不再插入 */
       *taller=FALSE;
       return FALSE;
     }
     if LT(e.key,(*T)->data.key)
     { /* 应继续在*T的左子树中进行搜索 */
       if(!InsertAVL(&(*T)->lchild,e,taller)) /* 未插入 */
         return FALSE;
       if(*taller) /*  已插入到*T的左子树中且左子树“长高” */
         switch((*T)->bf) /* 检查*T的平衡度 */
         {
           case LH: /* 原本左子树比右子树高，需要作左平衡处理 */
                    LeftBalance(T);
                    *taller=FALSE;
                    break;
           case EH: /* 原本左、右子树等高，现因左子树增高而使树增高 */
                    (*T)->bf=LH;
                    *taller=TRUE;
                    break;
           case RH: (*T)->bf=EH; /* 原本右子树比左子树高，现左、右子树等高 */
                    *taller=FALSE;
         }
     }
     else
     { /* 应继续在*T的右子树中进行搜索 */
       if(!InsertAVL(&(*T)->rchild,e,taller)) /* 未插入 */
         return FALSE;
       if(*taller) /* 已插入到T的右子树且右子树“长高” */
         switch((*T)->bf) /* 检查T的平衡度 */
         {
           case LH: (*T)->bf=EH; /* 原本左子树比右子树高，现左、右子树等高 */
                    *taller=FALSE;
                    break;
           case EH: /* 原本左、右子树等高，现因右子树增高而使树增高 */
                    (*T)->bf=RH;
                    *taller=TRUE;
		    break;
	   case RH: /* 原本右子树比左子树高，需要作右平衡处理 */
		    RightBalance(T);
		    *taller=FALSE;
	 }
     }
   }
   return TRUE;
 }

 void TraverseDSTable(BSTree DT,void(*Visit)(ElemType))
 { /* 初始条件: 动态查找表DT存在，Visit是对结点操作的应用函数 */
   /* 操作结果: 按关键字的顺序对DT的每个结点调用函数Visit()一次且至多一次 */
   if(DT)
   {
     TraverseDSTable(DT->lchild,Visit); /* 先中序遍历左子树 */
     Visit(DT->data); /* 再访问根结点 */
     TraverseDSTable(DT->rchild,Visit); /* 最后中序遍历右子树 */
   }
 }

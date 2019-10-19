 /* bo5-4.c 稀疏矩阵的十字链表存储(存储结构由c5-4.h定义)的基本操作(9个) */
 Status InitSMatrix(CrossList *M) /* 加 */
 { /* 初始化M(CrossList类型的变量必须初始化,否则创建、复制矩阵将出错) */
   (*M).rhead=(*M).chead=NULL;
   (*M).mu=(*M).nu=(*M).tu=0;
   return OK;
 }

 Status DestroySMatrix(CrossList *M)
 { /* 初始条件: 稀疏矩阵M存在。操作结果: 销毁稀疏矩阵M */
   int i;
   OLNode *p,*q;
   for(i=1;i<=(*M).mu;i++) /* 按行释放结点 */
   {
     p=*((*M).rhead+i);
     while(p)
     {
       q=p;
       p=p->right;
       free(q);
     }
   }
   free((*M).rhead);
   free((*M).chead);
   (*M).rhead=(*M).chead=NULL;
   (*M).mu=(*M).nu=(*M).tu=0;
   return OK;
 }

 Status CreateSMatrix(CrossList *M)
 { /* 创建稀疏矩阵M,采用十字链表存储表示。算法5.4 */
   int i,j,k,m,n,t;
   ElemType e;
   OLNode *p,*q;
   if((*M).rhead)
     DestroySMatrix(M);
   printf("请输入稀疏矩阵的行数 列数 非零元个数: ");
   scanf("%d%d%d",&m,&n,&t);
   (*M).mu=m;
   (*M).nu=n;
   (*M).tu=t;
   (*M).rhead=(OLink*)malloc((m+1)*sizeof(OLink));
   if(!(*M).rhead)
     exit(OVERFLOW);
   (*M).chead=(OLink*)malloc((n+1)*sizeof(OLink));
   if(!(*M).chead)
     exit(OVERFLOW);
   for(k=1;k<=m;k++) /* 初始化行头指针向量;各行链表为空链表 */
     (*M).rhead[k]=NULL;
   for(k=1;k<=n;k++) /* 初始化列头指针向量;各列链表为空链表 */
     (*M).chead[k]=NULL;
   printf("请按任意次序输入%d个非零元的行 列 元素值:\n",(*M).tu);
   for(k=0;k<t;k++)
   {
     scanf("%d%d%d",&i,&j,&e);
     p=(OLNode*)malloc(sizeof(OLNode));
     if(!p)
       exit(OVERFLOW);
     p->i=i; /* 生成结点 */
     p->j=j;
     p->e=e;
     if((*M).rhead[i]==NULL||(*M).rhead[i]->j>j) /* p插在该行的第一个结点处 */
     {
       p->right=(*M).rhead[i];
       (*M).rhead[i]=p;
     }
     else /* 寻查在行表中的插入位置 */
     {
       for(q=(*M).rhead[i];q->right&&q->right->j<j;q=q->right);
       p->right=q->right; /* 完成行插入 */
       q->right=p;
     }
     if((*M).chead[j]==NULL||(*M).chead[j]->i>i) /* p插在该列的第一个结点处 */
     {
       p->down=(*M).chead[j];
       (*M).chead[j]=p;
     }
     else /* 寻查在列表中的插入位置 */
     {
       for(q=(*M).chead[j];q->down&&q->down->i<i;q=q->down);
       p->down=q->down; /* 完成列插入 */
       q->down=p;
     }
   }
   return OK;
 }

 Status PrintSMatrix(CrossList M)
 { /* 初始条件: 稀疏矩阵M存在。操作结果: 按行或按列输出稀疏矩阵M */
   int i,j;
   OLink p;
   printf("%d行%d列%d个非零元素\n",M.mu,M.nu,M.tu);
   printf("请输入选择(1.按行输出 2.按列输出): ");
   scanf("%d",&i);
   switch(i)
   {
     case 1: for(j=1;j<=M.mu;j++)
             {
               p=M.rhead[j];
               while(p)
               {
                 printf("%d行%d列值为%d\n",p->i,p->j,p->e);
                 p=p->right;
               }
             }
             break;
     case 2: for(j=1;j<=M.nu;j++)
             {
               p=M.chead[j];
               while(p)
               {
                 printf("%d行%d列值为%d\n",p->i,p->j,p->e);
                 p=p->down;
               }
             }
   }
   return OK;
 }

 Status CopySMatrix(CrossList M,CrossList *T)
 { /* 初始条件: 稀疏矩阵M存在。操作结果: 由稀疏矩阵M复制得到T */
   int i;
   OLink p,q,q1,q2;
   if((*T).rhead)
     DestroySMatrix(T);
   (*T).mu=M.mu;
   (*T).nu=M.nu;
   (*T).tu=M.tu;
   (*T).rhead=(OLink*)malloc((M.mu+1)*sizeof(OLink));
   if(!(*T).rhead)
     exit(OVERFLOW);
   (*T).chead=(OLink*)malloc((M.nu+1)*sizeof(OLink));
   if(!(*T).chead)
     exit(OVERFLOW);
   for(i=1;i<=M.mu;i++) /* 初始化矩阵T的行头指针向量;各行链表为空链表 */
     (*T).rhead[i]=NULL;
   for(i=1;i<=M.nu;i++) /* 初始化矩阵T的列头指针向量;各列链表为空链表 */
     (*T).chead[i]=NULL;
   for(i=1;i<=M.mu;i++) /* 按行复制 */
   {
     p=M.rhead[i];
     while(p) /* 没到行尾 */
     {
       q=(OLNode*)malloc(sizeof(OLNode)); /* 生成结点 */
       if(!q)
         exit(OVERFLOW);
       q->i=p->i; /* 给结点赋值 */
       q->j=p->j;
       q->e=p->e;
       if(!(*T).rhead[i]) /* 插在行表头 */
         (*T).rhead[i]=q1=q;
       else /* 插在行表尾 */
         q1=q1->right=q;
       if(!(*T).chead[q->j]) /* 插在列表头 */
       {
         (*T).chead[q->j]=q;
         q->down=NULL;
       }
       else /* 插在列表尾 */
       {
         q2=(*T).chead[q->j];
         while(q2->down)
           q2=q2->down;
         q2->down=q;
         q->down=NULL;
       }
       p=p->right;
     }
     q->right=NULL;
   }
   return OK;
 }

 Status AddSMatrix(CrossList M,CrossList N,CrossList *Q)
 { /* 初始条件: 稀疏矩阵M与N的行数和列数对应相等。 */
   /* 操作结果: 求稀疏矩阵的和Q=M+N */
   int i,k;
   OLink p,pq,pm,pn;
   OLink *col;
   if(M.mu!=N.mu||M.nu!=N.nu)
   {
     printf("两个矩阵不是同类型的,不能相加\n");
     exit(OVERFLOW);
   }
   (*Q).mu=M.mu; /* 初始化Q矩阵 */
   (*Q).nu=M.nu;
   (*Q).tu=0; /* 元素个数的初值 */
   (*Q).rhead=(OLink*)malloc(((*Q).mu+1)*sizeof(OLink));
   if(!(*Q).rhead)
     exit(OVERFLOW);
   (*Q).chead=(OLink*)malloc(((*Q).nu+1)*sizeof(OLink));
   if(!(*Q).chead)
     exit(OVERFLOW);
   for(k=1;k<=(*Q).mu;k++) /* 初始化Q的行头指针向量;各行链表为空链表 */
     (*Q).rhead[k]=NULL;
   for(k=1;k<=(*Q).nu;k++) /* 初始化Q的列头指针向量;各列链表为空链表 */
     (*Q).chead[k]=NULL;
   col=(OLink*)malloc(((*Q).nu+1)*sizeof(OLink)); /* 生成指向列的最后结点的数组 */
   if(!col)
     exit(OVERFLOW);
   for(k=1;k<=(*Q).nu;k++) /* 赋初值 */
     col[k]=NULL;
   for(i=1;i<=M.mu;i++) /* 按行的顺序相加 */
   {
     pm=M.rhead[i]; /* pm指向矩阵M的第i行的第1个结点 */
     pn=N.rhead[i]; /* pn指向矩阵N的第i行的第1个结点 */
     while(pm&&pn) /* pm和pn均不空 */
     {
       if(pm->j<pn->j) /* 矩阵M当前结点的列小于矩阵N当前结点的列 */
       {
         p=(OLink)malloc(sizeof(OLNode)); /* 生成矩阵Q的结点 */
         if(!p)
           exit(OVERFLOW);
         (*Q).tu++; /* 非零元素数加1 */
         p->i=i; /* 给结点赋值 */
         p->j=pm->j;
         p->e=pm->e;
         p->right=NULL;
         pm=pm->right; /* pm指针向右移 */
       }
       else if(pm->j>pn->j) /* 矩阵M当前结点的列大于矩阵N当前结点的列 */
       {
         p=(OLink)malloc(sizeof(OLNode)); /* 生成矩阵Q的结点 */
         if(!p)
           exit(OVERFLOW);
         (*Q).tu++; /* 非零元素数加1 */
         p->i=i; /* 给结点赋值 */
         p->j=pn->j;
         p->e=pn->e;
         p->right=NULL;
         pn=pn->right; /* pn指针向右移 */
       }
       else if(pm->e+pn->e) /* 矩阵M、N当前结点的列相等且两元素之和不为0 */
       {
         p=(OLink)malloc(sizeof(OLNode)); /* 生成矩阵Q的结点 */
         if(!p)
           exit(OVERFLOW);
         (*Q).tu++; /* 非零元素数加1 */
         p->i=i; /* 给结点赋值 */
         p->j=pn->j;
         p->e=pm->e+pn->e;
         p->right=NULL;
         pm=pm->right; /* pm指针向右移 */
         pn=pn->right; /* pn指针向右移 */
       }
       else /* 矩阵M、N当前结点的列相等且两元素之和为0 */
       {
         pm=pm->right; /* pm指针向右移 */
         pn=pn->right; /* pn指针向右移 */
         continue;
       }
       if((*Q).rhead[i]==NULL) /* p为该行的第1个结点 */
         (*Q).rhead[i]=pq=p; /* p插在该行的表头且pq指向p(该行的最后一个结点) */
       else /* 插在pq所指结点之后 */
       {
         pq->right=p; /* 完成行插入 */
         pq=pq->right; /* pq指向该行的最后一个结点 */
       }
       if((*Q).chead[p->j]==NULL) /* p为该列的第1个结点 */
         (*Q).chead[p->j]=col[p->j]=p; /* p插在该列的表头且col[p->j]指向p */
       else /* 插在col[p->]所指结点之后 */
       {
         col[p->j]->down=p; /* 完成列插入 */
         col[p->j]=col[p->j]->down; /* col[p->j]指向该列的最后一个结点 */
       }
     }
     while(pm) /* 将矩阵M该行的剩余元素插入矩阵Q */
     {
       p=(OLink)malloc(sizeof(OLNode)); /* 生成矩阵Q的结点 */
       if(!p)
         exit(OVERFLOW);
       (*Q).tu++; /* 非零元素数加1 */
       p->i=i; /* 给结点赋值 */
       p->j=pm->j;
       p->e=pm->e;
       p->right=NULL;
       pm=pm->right; /* pm指针向右移 */
       if((*Q).rhead[i]==NULL) /* p为该行的第1个结点 */
         (*Q).rhead[i]=pq=p; /* p插在该行的表头且pq指向p(该行的最后一个结点) */
       else /* 插在pq所指结点之后 */
       {
         pq->right=p; /* 完成行插入 */
         pq=pq->right; /* pq指向该行的最后一个结点 */
       }
       if((*Q).chead[p->j]==NULL) /* p为该列的第1个结点 */
         (*Q).chead[p->j]=col[p->j]=p; /* p插在该列的表头且col[p->j]指向p */
       else /* 插在col[p->j]所指结点之后 */
       {
         col[p->j]->down=p; /* 完成列插入 */
         col[p->j]=col[p->j]->down; /* col[p->j]指向该列的最后一个结点 */
       }
     }
     while(pn) /* 将矩阵N该行的剩余元素插入矩阵Q */
     {
       p=(OLink)malloc(sizeof(OLNode)); /* 生成矩阵Q的结点 */
       if(!p)
         exit(OVERFLOW);
       (*Q).tu++; /* 非零元素数加1 */
       p->i=i; /* 给结点赋值 */
       p->j=pn->j;
       p->e=pn->e;
       p->right=NULL;
       pn=pn->right; /* pm指针向右移 */
       if((*Q).rhead[i]==NULL) /* p为该行的第1个结点 */
         (*Q).rhead[i]=pq=p; /* p插在该行的表头且pq指向p(该行的最后一个结点) */
       else /* 插在pq所指结点之后 */
       {
         pq->right=p; /* 完成行插入 */
         pq=pq->right; /* pq指向该行的最后一个结点 */
       }
       if((*Q).chead[p->j]==NULL) /* p为该列的第1个结点 */
         (*Q).chead[p->j]=col[p->j]=p; /* p插在该列的表头且col[p->j]指向p */
       else /* 插在col[p->j]所指结点之后 */
       {
         col[p->j]->down=p; /* 完成列插入 */
         col[p->j]=col[p->j]->down; /* col[p->j]指向该列的最后一个结点 */
       }
     }
   }
   for(k=1;k<=(*Q).nu;k++)
     if(col[k]) /* k列有结点 */
       col[k]->down=NULL; /*  令该列最后一个结点的down指针为空 */
   free(col);
   return OK;
 }

 Status SubtSMatrix(CrossList M,CrossList N,CrossList *Q)
 { /* 初始条件: 稀疏矩阵M与N的行数和列数对应相等。 */
   /* 操作结果: 求稀疏矩阵的差Q=M-N */
   int i,k;
   OLink p,pq,pm,pn;
   OLink *col;
   if(M.mu!=N.mu||M.nu!=N.nu)
   {
     printf("两个矩阵不是同类型的,不能相加\n");
     exit(OVERFLOW);
   }
   (*Q).mu=M.mu; /* 初始化Q矩阵 */
   (*Q).nu=M.nu;
   (*Q).tu=0; /* 元素个数的初值 */
   (*Q).rhead=(OLink*)malloc(((*Q).mu+1)*sizeof(OLink));
   if(!(*Q).rhead)
     exit(OVERFLOW);
   (*Q).chead=(OLink*)malloc(((*Q).nu+1)*sizeof(OLink));
   if(!(*Q).chead)
     exit(OVERFLOW);
   for(k=1;k<=(*Q).mu;k++) /* 初始化Q的行头指针向量;各行链表为空链表 */
     (*Q).rhead[k]=NULL;
   for(k=1;k<=(*Q).nu;k++) /* 初始化Q的列头指针向量;各列链表为空链表 */
     (*Q).chead[k]=NULL;
   col=(OLink*)malloc(((*Q).nu+1)*sizeof(OLink)); /* 生成指向列的最后结点的数组 */
   if(!col)
     exit(OVERFLOW);
   for(k=1;k<=(*Q).nu;k++) /* 赋初值 */
     col[k]=NULL;
   for(i=1;i<=M.mu;i++) /* 按行的顺序相加 */
   {
     pm=M.rhead[i]; /* pm指向矩阵M的第i行的第1个结点 */
     pn=N.rhead[i]; /* pn指向矩阵N的第i行的第1个结点 */
     while(pm&&pn) /* pm和pn均不空 */
     {
       if(pm->j<pn->j) /* 矩阵M当前结点的列小于矩阵N当前结点的列 */
       {
         p=(OLink)malloc(sizeof(OLNode)); /* 生成矩阵Q的结点 */
         if(!p)
           exit(OVERFLOW);
         (*Q).tu++; /* 非零元素数加1 */
         p->i=i; /* 给结点赋值 */
         p->j=pm->j;
         p->e=pm->e;
         p->right=NULL;
         pm=pm->right; /* pm指针向右移 */
       }
       else if(pm->j>pn->j) /* 矩阵M当前结点的列大于矩阵N当前结点的列 */
       {
         p=(OLink)malloc(sizeof(OLNode)); /* 生成矩阵Q的结点 */
         if(!p)
           exit(OVERFLOW);
         (*Q).tu++; /* 非零元素数加1 */
         p->i=i; /* 给结点赋值 */
         p->j=pn->j;
         p->e=-pn->e;
         p->right=NULL;
         pn=pn->right; /* pn指针向右移 */
       }
       else if(pm->e-pn->e) /* 矩阵M、N当前结点的列相等且两元素之差不为0 */
       {
         p=(OLink)malloc(sizeof(OLNode)); /* 生成矩阵Q的结点 */
         if(!p)
           exit(OVERFLOW);
         (*Q).tu++; /* 非零元素数加1 */
         p->i=i; /* 给结点赋值 */
         p->j=pn->j;
         p->e=pm->e-pn->e;
         p->right=NULL;
         pm=pm->right; /* pm指针向右移 */
         pn=pn->right; /* pn指针向右移 */
       }
       else /* 矩阵M、N当前结点的列相等且两元素之差为0 */
       {
         pm=pm->right; /* pm指针向右移 */
         pn=pn->right; /* pn指针向右移 */
         continue;
       }
       if((*Q).rhead[i]==NULL) /* p为该行的第1个结点 */
         (*Q).rhead[i]=pq=p; /* p插在该行的表头且pq指向p(该行的最后一个结点) */
       else /* 插在pq所指结点之后 */
       {
         pq->right=p; /* 完成行插入 */
         pq=pq->right; /* pq指向该行的最后一个结点 */
       }
       if((*Q).chead[p->j]==NULL) /* p为该列的第1个结点 */
         (*Q).chead[p->j]=col[p->j]=p; /* p插在该列的表头且col[p->j]指向p */
       else /* 插在col[p->]所指结点之后 */
       {
         col[p->j]->down=p; /* 完成列插入 */
         col[p->j]=col[p->j]->down; /* col[p->j]指向该列的最后一个结点 */
       }
     }
     while(pm) /* 将矩阵M该行的剩余元素插入矩阵Q */
     {
       p=(OLink)malloc(sizeof(OLNode)); /* 生成矩阵Q的结点 */
       if(!p)
         exit(OVERFLOW);
       (*Q).tu++; /* 非零元素数加1 */
       p->i=i; /* 给结点赋值 */
       p->j=pm->j;
       p->e=pm->e;
       p->right=NULL;
       pm=pm->right; /* pm指针向右移 */
       if((*Q).rhead[i]==NULL) /* p为该行的第1个结点 */
         (*Q).rhead[i]=pq=p; /* p插在该行的表头且pq指向p(该行的最后一个结点) */
       else /* 插在pq所指结点之后 */
       {
         pq->right=p; /* 完成行插入 */
         pq=pq->right; /* pq指向该行的最后一个结点 */
       }
       if((*Q).chead[p->j]==NULL) /* p为该列的第1个结点 */
         (*Q).chead[p->j]=col[p->j]=p; /* p插在该列的表头且col[p->j]指向p */
       else /* 插在col[p->j]所指结点之后 */
       {
         col[p->j]->down=p; /* 完成列插入 */
         col[p->j]=col[p->j]->down; /* col[p->j]指向该列的最后一个结点 */
       }
     }
     while(pn) /* 将矩阵N该行的剩余元素插入矩阵Q */
     {
       p=(OLink)malloc(sizeof(OLNode)); /* 生成矩阵Q的结点 */
       if(!p)
         exit(OVERFLOW);
       (*Q).tu++; /* 非零元素数加1 */
       p->i=i; /* 给结点赋值 */
       p->j=pn->j;
       p->e=-pn->e;
       p->right=NULL;
       pn=pn->right; /* pm指针向右移 */
       if((*Q).rhead[i]==NULL) /* p为该行的第1个结点 */
         (*Q).rhead[i]=pq=p; /* p插在该行的表头且pq指向p(该行的最后一个结点) */
       else /* 插在pq所指结点之后 */
       {
         pq->right=p; /* 完成行插入 */
         pq=pq->right; /* pq指向该行的最后一个结点 */
       }
       if((*Q).chead[p->j]==NULL) /* p为该列的第1个结点 */
         (*Q).chead[p->j]=col[p->j]=p; /* p插在该列的表头且col[p->j]指向p */
       else /* 插在col[p->j]所指结点之后 */
       {
         col[p->j]->down=p; /* 完成列插入 */
         col[p->j]=col[p->j]->down; /* col[p->j]指向该列的最后一个结点 */
       }
     }
   }
   for(k=1;k<=(*Q).nu;k++)
     if(col[k]) /* k列有结点 */
       col[k]->down=NULL; /* 令该列最后一个结点的down指针为空 */
   free(col);
   return OK;
 }

 Status MultSMatrix(CrossList M,CrossList N,CrossList *Q)
 { /* 初始条件: 稀疏矩阵M的列数等于N的行数。操作结果: 求稀疏矩阵乘积Q=M*N */
   int i,j,e;
   OLink q,p0,q0,q1,q2;
   InitSMatrix(Q);
   (*Q).mu=M.mu;
   (*Q).nu=N.nu;
   (*Q).tu=0;
   (*Q).rhead=(OLink*)malloc(((*Q).mu+1)*sizeof(OLink));
   if(!(*Q).rhead)
     exit(OVERFLOW);
   (*Q).chead=(OLink*)malloc(((*Q).nu+1)*sizeof(OLink));
   if(!(*Q).chead)
     exit(OVERFLOW);
   for(i=1;i<=(*Q).mu;i++) /* 初始化矩阵Q的行头指针向量;各行链表为空链表 */
     (*Q).rhead[i]=NULL;
   for(i=1;i<=(*Q).nu;i++) /* 初始化矩阵Q的列头指针向量;各列链表为空链表 */
     (*Q).chead[i]=NULL;
   for(i=1;i<=(*Q).mu;i++)
     for(j=1;j<=(*Q).nu;j++)
     {
       p0=M.rhead[i];
       q0=N.chead[j];
       e=0;
       while(p0&&q0)
       {
         if(q0->i<p0->j)
           q0=q0->down; /* 列指针后移 */
         else if(q0->i>p0->j)
           p0=p0->right; /* 行指针后移 */
         else /* q0->i==p0->j */
         {
           e+=p0->e*q0->e; /* 乘积累加 */
           q0=q0->down; /* 行列指针均后移 */
           p0=p0->right;
         }
       }
       if(e) /* 值不为0 */
       {
	 (*Q).tu++; /* 非零元素数加1 */
	 q=(OLink)malloc(sizeof(OLNode)); /* 生成结点 */
	 if(!q) /* 生成结点失败 */
	   exit(OVERFLOW);
	 q->i=i; /* 给结点赋值 */
	 q->j=j;
	 q->e=e;
	 q->right=NULL;
	 q->down=NULL;
	 if(!(*Q).rhead[i]) /* 行表空时插在行表头 */
	   (*Q).rhead[i]=q1=q;
	 else /* 否则插在行表尾 */
	   q1=q1->right=q;
	 if(!(*Q).chead[j]) /* 列表空时插在列表头 */
	   (*Q).chead[j]=q;
	 else /* 否则插在列表尾 */
	 {
	   q2=(*Q).chead[j]; /* q2指向j行第1个结点 */
	   while(q2->down)
             q2=q2->down; /* q2指向j行最后1个结点 */
           q2->down=q;
         }
       }
     }
   return OK;
 }

 Status TransposeSMatrix(CrossList M,CrossList *T)
 { /* 初始条件: 稀疏矩阵M存在。操作结果: 求稀疏矩阵M的转置矩阵T */
   int u,i;
   OLink *head,p,q,r;
   if((*T).rhead)
     DestroySMatrix(T);
   CopySMatrix(M,T); /* T=M */
   u=(*T).mu; /* 交换(*T).mu和(*T).nu */
   (*T).mu=(*T).nu;
   (*T).nu=u;
   head=(*T).rhead; /* 交换(*T).rhead和(*T).chead */
   (*T).rhead=(*T).chead;
   (*T).chead=head;
   for(u=1;u<=(*T).mu;u++) /* 对T的每一行 */
   {
     p=(*T).rhead[u]; /* p为行表头 */
     while(p) /* 没到表尾,对T的每一结点 */
     {
       q=p->down; /* q指向下一个结点 */
       i=p->i; /* 交换.i和.j */
       p->i=p->j;
       p->j=i;
       r=p->down; /* 交换.down.和right */
       p->down=p->right;
       p->right=r;
       p=q; /* p指向下一个结点 */
     }
   }
   return OK;
 }

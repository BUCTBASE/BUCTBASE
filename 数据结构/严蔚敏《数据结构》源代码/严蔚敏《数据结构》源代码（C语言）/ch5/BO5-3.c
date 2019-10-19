 /* bo5-3.c 行逻辑链接稀疏矩阵(存储结构由c5-3.h定义)的基本操作(8个) */
 Status CreateSMatrix(RLSMatrix *M)
 { /* 创建稀疏矩阵M */
   int i;
   Triple T;
   Status k;
   printf("请输入矩阵的行数,列数,非零元素数：");
   scanf("%d,%d,%d",&(*M).mu,&(*M).nu,&(*M).tu);
   (*M).data[0].i=0; /* 为以下比较做准备 */
   for(i=1;i<=(*M).tu;i++)
   {
     do
     {
       printf("请按行序顺序输入第%d个非零元素所在的行(1～%d),列(1～%d),元素值：",i,(*M).mu,(*M).nu);
       scanf("%d,%d,%d",&T.i,&T.j,&T.e);
       k=0;
       if(T.i<1||T.i>(*M).mu||T.j<1||T.j>(*M).nu) /* 行、列超出范围 */
         k=1;
       if(T.i<(*M).data[i-1].i||T.i==(*M).data[i-1].i&&T.j<=(*M).data[i-1].j) /* 没有按顺序输入非零元素 */
         k=1;
     }while(k); /* 当输入有误,重新输入 */
     (*M).data[i]=T;
   }
   for(i=1;i<=(*M).tu;i++) /* 计算rpos[] */
     if((*M).data[i].i>(*M).data[i-1].i)
       for(T.i=0;T.i<(*M).data[i].i-(*M).data[i-1].i;T.i++)
         (*M).rpos[(*M).data[i].i-T.i]=i;
   for(i=(*M).data[(*M).tu].i+1;i<=(*M).mu;i++) /* 给最后没有非零元素的几行赋值 */
     (*M).rpos[i]=(*M).tu+1;
   return OK;
 }

 void DestroySMatrix(RLSMatrix *M)
 { /* 销毁稀疏矩阵M(使M为0行0列0个非零元素的矩阵) */
   (*M).mu=0;
   (*M).nu=0;
   (*M).tu=0;
 }

 void PrintSMatrix(RLSMatrix M)
 { /* 输出稀疏矩阵M */
   int i;
   printf("%d行%d列%d个非零元素。\n",M.mu,M.nu,M.tu);
   printf("行  列  元素值\n");
   for(i=1;i<=M.tu;i++)
     printf("%2d%4d%8d\n",M.data[i].i,M.data[i].j,M.data[i].e);
   for(i=1;i<=M.mu;i++)
     printf("第%d行的第一个非零元素是本矩阵第%d个元素\n",i,M.rpos[i]);
 }

 Status CopySMatrix(RLSMatrix M,RLSMatrix *T)
 { /* 由稀疏矩阵M复制得到T */
   *T=M;
   return OK;
 }

 Status AddSMatrix(RLSMatrix M,RLSMatrix N,RLSMatrix *Q)
 { /* 求稀疏矩阵的和Q=M+N */
   int k,p,q;
   if(M.mu!=N.mu||M.nu!=N.nu)
     return ERROR;
   (*Q).mu=M.mu;
   (*Q).nu=M.nu;
   (*Q).tu=0;
   M.rpos[M.mu+1]=M.tu+1; /* 为方便后面的while循环临时设置 */
   N.rpos[N.mu+1]=N.tu+1;
   for(k=1;k<=M.mu;++k) /* 对于每一行，k指示行号 */
   {
     (*Q).rpos[k]=(*Q).tu+1;
     p=M.rpos[k]; /* p指示M矩阵第k行当前元素的序号 */
     q=N.rpos[k]; /* q指示N矩阵第k行当前元素的序号 */
     while(p<M.rpos[k+1]&&q<N.rpos[k+1])
     { /* M,N矩阵均有第k行元素未处理 */
       if(M.data[p].j==N.data[q].j) /* M矩阵当前元素和N矩阵当前元素的列相同 */
       {
         (*Q).data[(*Q).tu+1].e=M.data[p].e+N.data[q].e;
         if((*Q).data[(*Q).tu+1].e!=0)
         {
           ++(*Q).tu;
           (*Q).data[(*Q).tu].i=k;
           (*Q).data[(*Q).tu].j=M.data[p].j;
         }
         ++p;
         ++q;
       }
       else if(M.data[p].j<N.data[q].j)
       { /* M矩阵当前元素的列<N矩阵当前元素的列 */
         ++(*Q).tu;
         (*Q).data[(*Q).tu].e=M.data[p].e;
         (*Q).data[(*Q).tu].i=k;
         (*Q).data[(*Q).tu].j=M.data[p].j;
         ++p;
       }
       else /* M矩阵当前元素的列>N矩阵当前元素的列 */
       {
         ++(*Q).tu;
         (*Q).data[(*Q).tu].e=N.data[q].e;
         (*Q).data[(*Q).tu].i=k;
         (*Q).data[(*Q).tu].j=N.data[q].j;
         ++q;
       }
     }
     while(p<M.rpos[k+1]) /* M矩阵还有k行的元素未处理 */
     {
       ++(*Q).tu;
       (*Q).data[(*Q).tu].e=M.data[p].e;
       (*Q).data[(*Q).tu].i=k;
       (*Q).data[(*Q).tu].j=M.data[p].j;
       ++p;
     }
     while(q<N.rpos[k+1]) /* N矩阵还有k行的元素未处理 */
     {
       ++(*Q).tu;
       (*Q).data[(*Q).tu].e=N.data[q].e;
       (*Q).data[(*Q).tu].i=k;
       (*Q).data[(*Q).tu].j=N.data[q].j;
       ++q;
     }
   }
   return OK;
 }

 Status SubtSMatrix(RLSMatrix M,RLSMatrix N,RLSMatrix *Q)
 { /* 求稀疏矩阵的差Q=M-N */
   int i;
   if(M.mu!=N.mu||M.nu!=N.nu)
     return ERROR;
   for(i=1;i<=N.tu;++i) /* 对于N的每一元素,其值乘以-1 */
     N.data[i].e*=-1;
   AddSMatrix(M,N,Q); /* Q=M+(-N) */
   return OK;
 }

 Status MultSMatrix(RLSMatrix M,RLSMatrix N,RLSMatrix *Q)
 { /* 求稀疏矩阵乘积Q=M＊N。算法5.3 */
   int arow,brow,p,q,ccol,ctemp[MAXRC+1];
   if(M.nu!=N.mu) /* 矩阵M的列数应和矩阵N的行数相等 */
     return ERROR;
   (*Q).mu=M.mu; /* Q初始化 */
   (*Q).nu=N.nu;
   (*Q).tu=0;
   M.rpos[M.mu+1]=M.tu+1; /* 为方便后面的while循环临时设置 */
   N.rpos[N.mu+1]=N.tu+1;
   if(M.tu*N.tu!=0) /* M和N都是非零矩阵 */
   {
     for(arow=1;arow<=M.mu;++arow)
     { /* 从M的第一行开始，到最后一行，arow是M的当前行 */
       for(ccol=1;ccol<=(*Q).nu;++ccol)
         ctemp[ccol]=0; /* Q的当前行的各列元素累加器清零 */
       (*Q).rpos[arow]=(*Q).tu+1; /* Q当前行的第1个元素位于上1行最后1个元素之后 */
       for(p=M.rpos[arow];p<M.rpos[arow+1];++p)
       { /* 对M当前行中每一个非零元 */
         brow=M.data[p].j; /* 找到对应元在N中的行号(M当前元的列号) */
         for(q=N.rpos[brow];q<N.rpos[brow+1];++q)
	 {
           ccol=N.data[q].j; /* 乘积元素在Q中列号 */
           ctemp[ccol]+=M.data[p].e*N.data[q].e;
         }
       } /* 求得Q中第arow行的非零元 */
       for(ccol=1;ccol<=(*Q).nu;++ccol) /* 压缩存储该行非零元 */
         if(ctemp[ccol])
         {
           if(++(*Q).tu>MAXSIZE)
             return ERROR;
           (*Q).data[(*Q).tu].i=arow;
           (*Q).data[(*Q).tu].j=ccol;
           (*Q).data[(*Q).tu].e=ctemp[ccol];
         }
     }
   }
   return OK;
 }

 Status TransposeSMatrix(RLSMatrix M,RLSMatrix *T)
 { /* 求稀疏矩阵M的转置矩阵T */
   int p,q,t,col,*num;
   num=(int *)malloc((M.nu+1)*sizeof(int));
   (*T).mu=M.nu;
   (*T).nu=M.mu;
   (*T).tu=M.tu;
   if((*T).tu)
   {
     for(col=1;col<=M.nu;++col)
       num[col]=0;  /* 设初值 */
     for(t=1;t<=M.tu;++t) /* 求M中每一列非零元个数 */
       ++num[M.data[t].j];
     (*T).rpos[1]=1;
     for(col=2;col<=M.nu;++col) /* 求M中第col中第一个非零元在(*T).data中的序号 */
       (*T).rpos[col]=(*T).rpos[col-1]+num[col-1];
     for(col=1;col<=M.nu;++col)
       num[col]=(*T).rpos[col];
     for(p=1;p<=M.tu;++p)
     {
       col=M.data[p].j;
       q=num[col];
       (*T).data[q].i=M.data[p].j;
       (*T).data[q].j=M.data[p].i;
       (*T).data[q].e=M.data[p].e;
       ++num[col];
     }
   }
   free(num);
   return OK;
 }

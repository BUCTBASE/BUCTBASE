 /* bo5-2.c 三元组稀疏矩阵的基本操作,包括算法5.1(9个) */
 Status CreateSMatrix(TSMatrix *M)
 { /* 创建稀疏矩阵M */
   int i,m,n;
   ElemType e;
   Status k;
   printf("请输入矩阵的行数,列数,非零元素数：");
   scanf("%d,%d,%d",&(*M).mu,&(*M).nu,&(*M).tu);
   (*M).data[0].i=0; /* 为以下比较顺序做准备 */
   for(i=1;i<=(*M).tu;i++)
   {
     do
     {
       printf("请按行序顺序输入第%d个非零元素所在的行(1～%d),列(1～%d),元素值：",i,(*M).mu,(*M).nu);
       scanf("%d,%d,%d",&m,&n,&e);
       k=0;
       if(m<1||m>(*M).mu||n<1||n>(*M).nu) /* 行或列超出范围 */
         k=1;
       if(m<(*M).data[i-1].i||m==(*M).data[i-1].i&&n<=(*M).data[i-1].j) /* 行或列的顺序有错 */
         k=1;
     }while(k);
     (*M).data[i].i=m;
     (*M).data[i].j=n;
     (*M).data[i].e=e;
   }
   return OK;
 }

 void DestroySMatrix(TSMatrix *M)
 { /* 销毁稀疏矩阵M */
   (*M).mu=0;
   (*M).nu=0;
   (*M).tu=0;
 }

 void PrintSMatrix(TSMatrix M)
 { /* 输出稀疏矩阵M */
   int i;
   printf("%d行%d列%d个非零元素。\n",M.mu,M.nu,M.tu);
   printf("行  列  元素值\n");
   for(i=1;i<=M.tu;i++)
     printf("%2d%4d%8d\n",M.data[i].i,M.data[i].j,M.data[i].e);
 }

 Status CopySMatrix(TSMatrix M,TSMatrix *T)
 { /* 由稀疏矩阵M复制得到T */
   (*T)=M;
   return OK;
 }

 int comp(int c1,int c2) /* 另加 */
 { /* AddSMatrix函数要用到 */
   int i;
   if(c1<c2)
     i=1;
   else if(c1==c2)
     i=0;
   else
     i=-1;
   return i;
 }

 Status AddSMatrix(TSMatrix M,TSMatrix N,TSMatrix *Q)
 { /* 求稀疏矩阵的和Q=M+N */
   Triple *Mp,*Me,*Np,*Ne,*Qh,*Qe;
   if(M.mu!=N.mu)
     return ERROR;
   if(M.nu!=N.nu)
     return ERROR;
   (*Q).mu=M.mu;
   (*Q).nu=M.nu;
   Mp=&M.data[1]; /* Mp的初值指向矩阵M的非零元素首地址 */
   Np=&N.data[1]; /* Np的初值指向矩阵N的非零元素首地址 */
   Me=&M.data[M.tu]; /* Me指向矩阵M的非零元素尾地址 */
   Ne=&N.data[N.tu]; /* Ne指向矩阵N的非零元素尾地址 */
   Qh=Qe=(*Q).data; /* Qh、Qe的初值指向矩阵Q的非零元素首地址的前一地址 */
   while(Mp<=Me&&Np<=Ne)
   {
     Qe++;
     switch(comp(Mp->i,Np->i))
     {
       case  1: *Qe=*Mp;
                Mp++;
                break;
       case  0: switch(comp(Mp->j,Np->j)) /* M、N矩阵当前非零元素的行相等,继续比较列 */
                {
                  case  1: *Qe=*Mp;
                           Mp++;
                           break;
                  case  0: *Qe=*Mp;
                           Qe->e+=Np->e;
                           if(!Qe->e) /* 元素值为0，不存入压缩矩阵 */
                             Qe--;
                           Mp++;
                           Np++;
                           break;
                  case -1: *Qe=*Np;
                           Np++;
                }
                break;
       case -1: *Qe=*Np;
                Np++;
     }
   }
   if(Mp>Me) /* 矩阵M的元素全部处理完毕 */
     while(Np<=Ne)
     {
       Qe++;
       *Qe=*Np;
       Np++;
     }
   if(Np>Ne) /* 矩阵N的元素全部处理完毕 */
     while(Mp<=Me)
     {
       Qe++;
       *Qe=*Mp;
       Mp++;
     }
   (*Q).tu=Qe-Qh; /* 矩阵Q的非零元素个数 */
   return OK;
 }

 Status SubtSMatrix(TSMatrix M,TSMatrix N,TSMatrix *Q)
 { /* 求稀疏矩阵的差Q=M-N */
   int i;
   for(i=1;i<=N.tu;i++)
     N.data[i].e*=-1;
   AddSMatrix(M,N,Q);
   return OK;
 }

 Status MultSMatrix(TSMatrix M,TSMatrix N,TSMatrix *Q)
 { /* 求稀疏矩阵的乘积Q=M*N */
   int i,j,h=M.mu,l=N.nu,Qn=0;
   /* h,l分别为矩阵Q的行、列值,Qn为矩阵Q的非零元素个数，初值为0 */
   ElemType *Qe;
   if(M.nu!=N.mu)
     return ERROR;
   (*Q).mu=M.mu;
   (*Q).nu=N.nu;
   Qe=(ElemType *)malloc(h*l*sizeof(ElemType)); /* Qe为矩阵Q的临时数组 */
   /* 矩阵Q的第i行j列的元素值存于*(Qe+(i-1)*l+j-1)中，初值为0 */
   for(i=0;i<h*l;i++)
     *(Qe+i)=0; /* 赋初值0 */
   for(i=1;i<=M.tu;i++) /* 矩阵元素相乘，结果累加到Qe */
     for(j=1;j<=N.tu;j++)
       if(M.data[i].j==N.data[j].i)
         *(Qe+(M.data[i].i-1)*l+N.data[j].j-1)+=M.data[i].e*N.data[j].e;
   for(i=1;i<=M.mu;i++)
     for(j=1;j<=N.nu;j++)
       if(*(Qe+(i-1)*l+j-1)!=0)
       {
         Qn++;
         (*Q).data[Qn].e=*(Qe+(i-1)*l+j-1);
         (*Q).data[Qn].i=i;
         (*Q).data[Qn].j=j;
       }
   free(Qe);
   (*Q).tu=Qn;
   return OK;
 }

 Status TransposeSMatrix(TSMatrix M,TSMatrix *T)
 { /* 求稀疏矩阵M的转置矩阵T。算法5.1 */
   int p,q,col;
   (*T).mu=M.nu;
   (*T).nu=M.mu;
   (*T).tu=M.tu;
   if((*T).tu)
   {
     q=1;
     for(col=1;col<=M.nu;++col)
       for(p=1;p<=M.tu;++p)
         if(M.data[p].j==col)
         {
           (*T).data[q].i=M.data[p].j;
           (*T).data[q].j=M.data[p].i;
           (*T).data[q].e=M.data[p].e;
           ++q;
         }
   }
   return OK;
 }

 /* bo5-1.c 顺序存储数组(存储结构由c5-1.h定义)的基本操作(5个) */
 Status InitArray(Array *A,int dim,...)
 { /* 若维数dim和各维长度合法，则构造相应的数组A，并返回OK */
   int elemtotal=1,i; /* elemtotal是元素总值 */
   va_list ap;
   if(dim<1||dim>MAX_ARRAY_DIM)
     return ERROR;
   (*A).dim=dim;
   (*A).bounds=(int *)malloc(dim*sizeof(int));
   if(!(*A).bounds)
     exit(OVERFLOW);
   va_start(ap,dim);
   for(i=0;i<dim;++i)
   {
     (*A).bounds[i]=va_arg(ap,int);
     if((*A).bounds[i]<0)
       return UNDERFLOW; /* 在math.h中定义为4 */
     elemtotal*=(*A).bounds[i];
   }
   va_end(ap);
   (*A).base=(ElemType *)malloc(elemtotal*sizeof(ElemType));
   if(!(*A).base)
     exit(OVERFLOW);
   (*A).constants=(int *)malloc(dim*sizeof(int));
   if(!(*A).constants)
     exit(OVERFLOW);
   (*A).constants[dim-1]=1;
   for(i=dim-2;i>=0;--i)
     (*A).constants[i]=(*A).bounds[i+1]*(*A).constants[i+1];
   return OK;
 }

 Status DestroyArray(Array *A)
 { /* 销毁数组A */
   if((*A).base)
   {
     free((*A).base);
     (*A).base=NULL;
   }
   else
     return ERROR;
   if((*A).bounds)
   {
     free((*A).bounds);
     (*A).bounds=NULL;
   }
   else
     return ERROR;
   if((*A).constants)
   {
     free((*A).constants);
     (*A).constants=NULL;
   }
   else
     return ERROR;
   return OK;
 }

 Status Locate(Array A,va_list ap,int *off) /* Value()、Assign()调用此函数 */
 { /* 若ap指示的各下标值合法，则求出该元素在A中的相对地址off */
   int i,ind;
   *off=0;
   for(i=0;i<A.dim;i++)
   {
     ind=va_arg(ap,int);
     if(ind<0||ind>=A.bounds[i])
       return OVERFLOW;
     *off+=A.constants[i]*ind;
   }
   return OK;
 }

 Status Value(ElemType *e,Array A,...) /* 在VC++中，...之前的形参不能是引用类型 */
 { /* ...依次为各维的下标值，若各下标合法，则e被赋值为A的相应的元素值 */
   va_list ap;
   Status result;
   int off;
   va_start(ap,A);
   if((result=Locate(A,ap,&off))==OVERFLOW) /* 调用Locate() */
     return result;
   *e=*(A.base+off);
   return OK;
 }

 Status Assign(Array *A,ElemType e,...)
 { /* ...依次为各维的下标值，若各下标合法，则将e的值赋给A的指定的元素 */
   va_list ap;
   Status result;
   int off;
   va_start(ap,e);
   if((result=Locate(*A,ap,&off))==OVERFLOW) /* 调用Locate() */
     return result;
   *((*A).base+off)=e;
   return OK;
 }

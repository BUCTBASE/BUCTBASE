 /* algo5-1.c 实现算法5.2的程序 */
 #include"c1.h"
 typedef int ElemType;
 #include"c5-2.h"
 #include"bo5-2.c"

 Status FastTransposeSMatrix(TSMatrix M,TSMatrix *T)
 { /* 快速求稀疏矩阵M的转置矩阵T。算法5.2 */
   int p,q,t,col,*num,*cpot;
   num=(int *)malloc((M.nu+1)*sizeof(int)); /* 生成数组（[0]不用） */
   cpot=(int *)malloc((M.nu+1)*sizeof(int)); /* 生成数组（[0]不用） */
   (*T).mu=M.nu;
   (*T).nu=M.mu;
   (*T).tu=M.tu;
   if((*T).tu)
   {
     for(col=1;col<=M.nu;++col)
       num[col]=0; /* 设初值 */
     for(t=1;t<=M.tu;++t) /* 求M中每一列含非零元素个数 */
       ++num[M.data[t].j];
     cpot[1]=1;
     for(col=2;col<=M.nu;++col) /* 求第col列中第一个非零元在(*T).data中的序号 */
       cpot[col]=cpot[col-1]+num[col-1];
     for(p=1;p<=M.tu;++p)
     {
       col=M.data[p].j;
       q=cpot[col];
       (*T).data[q].i=M.data[p].j;
       (*T).data[q].j=M.data[p].i;
       (*T).data[q].e=M.data[p].e;
       ++cpot[col];
     }
   }
   free(num);
   free(cpot);
   return OK;
 }

 void main()
 {
   TSMatrix A,B;
   printf("创建矩阵A: ");
   CreateSMatrix(&A);
   PrintSMatrix(A);
   FastTransposeSMatrix(A,&B);
   printf("矩阵B(A的快速转置): ");
   PrintSMatrix(B);
   DestroySMatrix(&A);
   DestroySMatrix(&B);
 }
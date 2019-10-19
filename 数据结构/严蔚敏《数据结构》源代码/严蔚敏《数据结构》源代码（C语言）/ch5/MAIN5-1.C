 /* main5-1.c 检验bo5-1.c的主程序 */
 #include"c1.h"
 typedef int ElemType;
 #include"c5-1.h"
 #include"bo5-1.c"

 void main()
 {
   Array A;
   int i,j,k,*p,dim=3,bound1=3,bound2=4,bound3=2; /* a[3][4][2]数组 */
   ElemType e,*p1;
   InitArray(&A,dim,bound1,bound2,bound3); /* 构造3＊4＊2的3维数组A */
   p=A.bounds;
   printf("A.bounds=");
   for(i=0;i<dim;i++) /* 顺序输出A.bounds */
     printf("%d ",*(p+i));
   p=A.constants;
   printf("\nA.constants=");
   for(i=0;i<dim;i++) /* 顺序输出A.constants */
     printf("%d ",*(p+i));
   printf("\n%d页%d行%d列矩阵元素如下:\n",bound1,bound2,bound3);
   for(i=0;i<bound1;i++)
   {
     for(j=0;j<bound2;j++)
     {
       for(k=0;k<bound3;k++)
       {
         Assign(&A,i*100+j*10+k,i,j,k); /* 将i*100+j*10+k赋值给A[i][j][k] */
         Value(&e,A,i,j,k); /* 将A[i][j][k]的值赋给e */
         printf("A[%d][%d][%d]=%2d ",i,j,k,e); /* 输出A[i][j][k] */
       }
       printf("\n");
     }
     printf("\n");
   }
   p1=A.base;
   printf("A.base=\n");
   for(i=0;i<bound1*bound2*bound3;i++) /* 顺序输出A.base */
   {
     printf("%4d",*(p1+i));
     if(i%(bound2*bound3)==bound2*bound3-1)
       printf("\n");
   }
   DestroyArray(&A);
 }

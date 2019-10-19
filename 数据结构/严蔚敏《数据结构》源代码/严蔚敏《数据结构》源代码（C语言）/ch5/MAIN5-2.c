 /* main5-2.c 检验bo5-2.c的主程序 */
 #include"c1.h"
 typedef int ElemType;
 #include"c5-2.h"
 #include"bo5-2.c"
 void main()
 {
   TSMatrix A,B,C;
   printf("创建矩阵A: ");
   CreateSMatrix(&A);
   PrintSMatrix(A);
   printf("由矩阵A复制矩阵B: ");
   CopySMatrix(A,&B);
   PrintSMatrix(B);
   DestroySMatrix(&B);
   printf("销毁矩阵B后:\n");
   PrintSMatrix(B);
   printf("创建矩阵B2:(与矩阵A的行、列数相同，行、列分别为%d,%d)\n",A.mu,A.nu);
   CreateSMatrix(&B);
   PrintSMatrix(B);
   printf("矩阵C1(A+B): ");
   AddSMatrix(A,B,&C);
   PrintSMatrix(C);
   DestroySMatrix(&C);
   printf("矩阵C2(A-B): ");
   SubtSMatrix(A,B,&C);
   PrintSMatrix(C);
   DestroySMatrix(&C);
   printf("矩阵C3(A的转置): ");
   TransposeSMatrix(A,&C);
   PrintSMatrix(C);
   DestroySMatrix(&A);
   DestroySMatrix(&B);
   DestroySMatrix(&C);
   printf("创建矩阵A2: ");
   CreateSMatrix(&A);
   PrintSMatrix(A);
   printf("创建矩阵B3:(行数应与矩阵A2的列数相同=%d)\n",A.nu);
   CreateSMatrix(&B);
   PrintSMatrix(B);
   printf("矩阵C5(A*B): ");
   MultSMatrix(A,B,&C);
   PrintSMatrix(C);
   DestroySMatrix(&A);
   DestroySMatrix(&B);
   DestroySMatrix(&C);
 }
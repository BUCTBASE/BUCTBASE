 /* c5-2.h 稀疏矩阵的三元组顺序表存储表示 */
 #define MAXSIZE 100 /* 非零元个数的最大值 */
 typedef struct
 {
   int i,j; /* 行下标,列下标 */
   ElemType e; /* 非零元素值 */
 }Triple;
 typedef struct
 {
   Triple data[MAXSIZE+1]; /* 非零元三元组表,data[0]未用 */
   int mu,nu,tu; /* 矩阵的行数、列数和非零元个数 */
 }TSMatrix;

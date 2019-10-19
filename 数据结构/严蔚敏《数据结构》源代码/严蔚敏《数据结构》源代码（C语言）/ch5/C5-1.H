 /* c5-1.h 数组的顺序存储表示 */
 #include<stdarg.h> /* 标准头文件，提供宏va_start，va_arg和va_end， */
                    /* 用于存取变长参数表 */
 #define MAX_ARRAY_DIM 8 /* 假设数组维数的最大值为8 */
 typedef struct
 {
   ElemType *base; /* 数组元素基址，由InitArray分配 */
   int dim; /* 数组维数 */
   int *bounds; /* 数组维界基址，由InitArray分配 */
   int *constants; /* 数组映象函数常量基址，由InitArray分配 */
 }Array;

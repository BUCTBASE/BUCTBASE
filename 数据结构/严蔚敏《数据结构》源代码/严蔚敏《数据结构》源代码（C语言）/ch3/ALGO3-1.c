 /* algo3-1.c 调用算法3.1的程序 */
 typedef int SElemType; /* 定义栈元素类型为整型 */
 #include"c1.h"
 #include"c3-1.h" /* 采用顺序栈 */
 #include"bo3-1.c" /* 利用顺序栈的基本操作 */

 void conversion() /* 算法3.1 */
 { /* 对于输入的任意一个非负十进制整数，打印输出与其等值的八进制数 */
   SqStack s;
   unsigned n; /* 非负整数 */
   SElemType e;
   InitStack(&s); /* 初始化栈 */
   printf("n(>=0)=");
   scanf("%u",&n); /* 输入非负十进制整数n */
   while(n) /* 当n不等于0 */
   {
     Push(&s,n%8); /* 入栈n除以8的余数(8进制的低位) */
     n=n/8;
   }
   while(!StackEmpty(s)) /* 当栈不空 */
   {
     Pop(&s,&e); /* 弹出栈顶元素且赋值给e */
     printf("%d",e); /* 输出e */
   }
   printf("\n");
 }

 void main()
 {
   conversion();
 }
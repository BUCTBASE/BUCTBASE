 /* algo3-2.c 改算法3.1，10进制→16进制 */
 typedef int SElemType; /* 定义栈元素类型为整型 */
 #include"c1.h"
 #include"c3-1.h" /* 采用顺序栈 */
 #include"bo3-1.c" /* 利用顺序栈的基本操作 */

 void conversion()
 { /* 对于输入的任意一个非负10进制整数，打印输出与其等值的16进制数 */
   SqStack s;
   unsigned n; /* 非负整数 */
   SElemType e;
   InitStack(&s); /* 初始化栈 */
   printf("n(>=0)=");
   scanf("%u",&n); /* 输入非负十进制整数n */
   while(n) /* 当n不等于0 */
   {
     Push(&s,n%16); /* 入栈n除以16的余数(16进制的低位) */
     n=n/16;
   }
   while(!StackEmpty(s)) /* 当栈不空 */
   {
     Pop(&s,&e); /* 弹出栈顶元素且赋值给e */
     if(e<=9)
       printf("%d",e);
     else
       printf("%c",e+55);
   }
   printf("\n");
 }

 void main()
 {
   conversion();
 }

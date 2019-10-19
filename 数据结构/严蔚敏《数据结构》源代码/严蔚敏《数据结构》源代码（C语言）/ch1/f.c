 /* f.c 用函数指针代替C++的引用参数 */
 #include<stdio.h>
 void fa(int a) /* 在函数中改变a，将不会带回主调函数(主调函数中的a仍是原值) */
 {
   a=5;
   printf("在函数fa中：a=%d\n",a);
 }

 void fb(int *a) /* a为指针类型，在函数中改变*a，改变后的值将带回主调函数 */
 {
   *a=5;
   printf("在函数fb中：*a=%d\n",*a);
 }

 void main()
 {
   int n=1;
   printf("在主程中，调用函数fa之前：n=%d\n",n);
   fa(n);
   printf("在主程中，调用函数fa之后,调用函数fb之前：n=%d\n",n);
   fb(&n); /* 实参为n的地址 */
   printf("在主程中，调用函数fb之后：n=%d\n",n);
 }

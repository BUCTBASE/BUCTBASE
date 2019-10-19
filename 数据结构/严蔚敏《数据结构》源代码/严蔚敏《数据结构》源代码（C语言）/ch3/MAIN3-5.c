 /* main3-5.c 检验bo3-5.cpp的主程序 */
 #include"c1.h"
 typedef int SElemType; /* 定义栈元素的类型 */
 #include"bo3-5.c"

 void print(SElemType c)
 {
   printf("%d ",c);
 }

 void main()
 {
   int j;
   LinkStack s;
   SElemType e;
   if(InitStack(&s))
     for(j=1;j<=5;j++)
       Push(s,2*j);
   printf("栈中的元素从栈底到栈顶依次为: ");
   StackTraverse(s,print);
   Pop(s,&e);
   printf("弹出的栈顶元素为%d\n",e);
   printf("栈空否: %d(1:空 0:否)\n",StackEmpty(s));
   GetTop(s,&e);
   printf("当前栈顶元素为%d，栈的长度为%d\n",e,StackLength(s));
   ClearStack(s);
   printf("清空栈后，栈空否: %d(1:空 0:否)，栈的长度为%d\n",StackEmpty(s),StackLength(s));
   printf("是否销毁栈了: %d(1:是 0:否)\n",DestroyStack(&s));
 }

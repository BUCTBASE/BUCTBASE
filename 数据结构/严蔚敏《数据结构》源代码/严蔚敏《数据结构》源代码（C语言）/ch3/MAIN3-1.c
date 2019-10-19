 /* main3-1.c 检验bo3-1.cpp的主程序 */
 #include"c1.h"
 typedef int SElemType; /* 定义栈元素类型，此句要在c3-1.h的前面 */
 #include"c3-1.h"
 #include"bo3-1.c"

 Status visit(SElemType c)
 {
   printf("%d ",c);
   return OK;
 }

 void main()
 {
   int j;
   SqStack s;
   SElemType e;
   if(InitStack(&s)==OK)
     for(j=1;j<=12;j++)
       Push(&s,j);
   printf("栈中元素依次为：");
   StackTraverse(s,visit);
   Pop(&s,&e);
   printf("弹出的栈顶元素 e=%d\n",e);
   printf("栈空否：%d(1:空 0:否)\n",StackEmpty(s));
   GetTop(s,&e);
   printf("栈顶元素 e=%d 栈的长度为%d\n",e,StackLength(s));
   ClearStack(&s);
   printf("清空栈后，栈空否：%d(1:空 0:否)\n",StackEmpty(s));
   DestroyStack(&s);
   printf("销毁栈后，s.top=%u s.base=%u s.stacksize=%d\n",s.top,s.base, s.stacksize);
 }

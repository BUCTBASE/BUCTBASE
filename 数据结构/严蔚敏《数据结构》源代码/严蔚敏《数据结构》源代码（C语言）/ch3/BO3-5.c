 /* bo3-5.c 链栈(存储结构由c2-2.h定义)的基本操作(9个) */
 /* 大部分基本操作是由bo2-2.c和bo2-9.cpp中的函数改名得来 */
 typedef SElemType ElemType; /* 栈结点类型和链表结点类型一致 */
 #include"c2-2.h"
 typedef LinkList LinkStack; /* LinkStack是指向栈结点的指针类型 */
 #define InitStack InitList /* InitStack()与InitList()作用相同，下同 */
 #define DestroyStack DestroyList
 #define ClearStack ClearList
 #define StackEmpty ListEmpty
 #define StackLength ListLength
 #define GetTop GetFirstElem
 #define Push HeadInsert
 #define Pop DeleteFirst
 #include"bo2-2.c"
 #include"bo2-9.c"
 Status StackTraverse(LinkStack S,void(*visit)(SElemType))
 { /* 从栈底到栈顶依次对栈中每个元素调用函数visit()。 */
   SElemType e;
   LinkStack temp,p=S;
   InitStack(&temp); /* 初始化temp栈 */
   while(p->next)
   {
     GetTop(p,&e);
     Push(temp,e);
     p=p->next;
   }
   ListTraverse(temp,visit);
   return OK;
 }
 /* main3-2.c 检验bo3-2.c的主程序 */
 #include"c1.h"
 typedef int QElemType;
 #include"c3-2.h"
 #include"bo3-2.c"

 void visit(QElemType i)
 {
   printf("%d ",i);
 }

 void main()
 {
   int i;
   QElemType d;
   LinkQueue q;
   i=InitQueue(&q);
   if(i)
     printf("成功地构造了一个空队列!\n");
   printf("是否空队列？%d(1:空 0:否)  ",QueueEmpty(q));
   printf("队列的长度为%d\n",QueueLength(q));
   EnQueue(&q,-5);
   EnQueue(&q,5);
   EnQueue(&q,10);
   printf("插入3个元素(-5,5,10)后,队列的长度为%d\n",QueueLength(q));
   printf("是否空队列？%d(1:空 0:否)  ",QueueEmpty(q));
   printf("队列的元素依次为：");
   QueueTraverse(q,visit);
   i=GetHead_Q(q,&d);
   if(i==OK)
     printf("队头元素是：%d\n",d);
   DeQueue(&q,&d);
   printf("删除了队头元素%d\n",d);
   i=GetHead_Q(q,&d);
   if(i==OK)
     printf("新的队头元素是：%d\n",d);
   ClearQueue(&q);
   printf("清空队列后,q.front=%u q.rear=%u q.front->next=%u\n",q.front,q.rear,q.front->next);
   DestroyQueue(&q);
   printf("销毁队列后,q.front=%u q.rear=%u\n",q.front, q.rear);
 }
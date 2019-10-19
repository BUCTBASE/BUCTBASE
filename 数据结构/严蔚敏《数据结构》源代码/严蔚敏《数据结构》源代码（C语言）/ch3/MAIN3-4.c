 /* main3-4.c 顺序队列(非循环),检验bo3-4.c的主程序 */
 #include"c1.h"
 typedef int QElemType;
 #include"c3-3.h"
 #include"bo3-4.c"

 void visit(QElemType i)
 {
   printf("%d ",i);
 }

 void main()
 {
   Status j;
   int i,n;
   QElemType d;
   SqQueue Q;
   InitQueue(&Q);
   printf("初始化队列后，队列空否？%u(1:空 0:否)\n",QueueEmpty(Q));
   printf("队列长度为：%d\n",QueueLength(Q));
   printf("请输入队列元素个数n: ");
   scanf("%d",&n);
   printf("请输入%d个整型队列元素:\n",n);
   for(i=0;i<n;i++)
   {
     scanf("%d",&d);
     EnQueue(&Q,d);
   }
   printf("队列长度为：%d\n",QueueLength(Q));
   printf("现在队列空否？%u(1:空 0:否)\n",QueueEmpty(Q));
   printf("现在队列中的元素为: \n");
   QueueTraverse(Q,visit);
   DeQueue(&Q,&d);
   printf("删除队头元素%d\n",d);
   printf("队列中的元素为: \n");
   QueueTraverse(Q,visit);
   j=GetHead(Q,&d);
   if(j)
     printf("队头元素为: %d\n",d);
   else
     printf("无队头元素(空队列)\n");
   ClearQueue(&Q);
   printf("清空队列后, 队列空否？%u(1:空 0:否)\n",QueueEmpty(Q));
   j=GetHead(Q,&d);
   if(j)
     printf("队头元素为: %d\n",d);
   else
     printf("无队头元素(空队列)\n");
   DestroyQueue(&Q);
 }
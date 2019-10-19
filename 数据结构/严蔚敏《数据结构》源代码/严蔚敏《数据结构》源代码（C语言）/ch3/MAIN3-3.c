 /* main3-3.c 循环队列 检验bo3-3.c的主程序 */
 #include"c1.h"
 typedef int QElemType;
 #include"c3-3.h"
 #include"bo3-3.c"

 void visit(QElemType i)
 {
   printf("%d ",i);
 }

 void main()
 {
   Status j;
   int i=0,l;
   QElemType d;
   SqQueue Q;
   InitQueue(&Q);
   printf("初始化队列后，队列空否？%u(1:空 0:否)\n",QueueEmpty(Q));
   printf("请输入整型队列元素(不超过%d个),-1为提前结束符: ",MAXQSIZE-1);
   do
   {
     scanf("%d",&d);
     if(d==-1)
       break;
     i++;
     EnQueue(&Q,d);
   }while(i<MAXQSIZE-1);
   printf("队列长度为: %d\n",QueueLength(Q));
   printf("现在队列空否？%u(1:空 0:否)\n",QueueEmpty(Q));
   printf("连续%d次由队头删除元素,队尾插入元素:\n",MAXQSIZE);
   for(l=1;l<=MAXQSIZE;l++)
   {
     DeQueue(&Q,&d);
     printf("删除的元素是%d,请输入待插入的元素: ",d);
     scanf("%d",&d);
     EnQueue(&Q,d);
   }
   l=QueueLength(Q);
   printf("现在队列中的元素为: \n");
   QueueTraverse(Q,visit);
   printf("共向队尾插入了%d个元素\n",i+MAXQSIZE);
   if(l-2>0)
     printf("现在由队头删除%d个元素:\n",l-2);
   while(QueueLength(Q)>2)
   {
     DeQueue(&Q,&d);
     printf("删除的元素值为%d\n",d);
   }
   j=GetHead(Q,&d);
   if(j)
     printf("现在队头元素为: %d\n",d);
   ClearQueue(&Q);
   printf("清空队列后, 队列空否？%u(1:空 0:否)\n",QueueEmpty(Q));
   DestroyQueue(&Q);
 }
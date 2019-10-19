 /* bo3-2.c 链队列(存储结构由c3-2.h定义)的基本操作(9个) */
 Status InitQueue(LinkQueue *Q)
 { /* 构造一个空队列Q */
   (*Q).front=(*Q).rear=(QueuePtr)malloc(sizeof(QNode));
   if(!(*Q).front)
     exit(OVERFLOW);
   (*Q).front->next=NULL;
   return OK;
 }

 Status DestroyQueue(LinkQueue *Q)
 { /* 销毁队列Q(无论空否均可) */
   while((*Q).front)
   {
     (*Q).rear=(*Q).front->next;
     free((*Q).front);
     (*Q).front=(*Q).rear;
   }
   return OK;
 }

 Status ClearQueue(LinkQueue *Q)
 { /* 将Q清为空队列 */
   QueuePtr p,q;
   (*Q).rear=(*Q).front;
   p=(*Q).front->next;
   (*Q).front->next=NULL;
   while(p)
   {
     q=p;
     p=p->next;
     free(q);
   }
   return OK;
 }

 Status QueueEmpty(LinkQueue Q)
 { /* 若Q为空队列,则返回TRUE,否则返回FALSE */
   if(Q.front==Q.rear)
     return TRUE;
   else
     return FALSE;
 }

 int QueueLength(LinkQueue Q)
 { /* 求队列的长度 */
   int i=0;
   QueuePtr p;
   p=Q.front;
   while(Q.rear!=p)
   {
     i++;
     p=p->next;
   }
   return i;
 }

 Status GetHead_Q(LinkQueue Q,QElemType *e) /* 避免与bo2-6.c重名 */
 { /* 若队列不空,则用e返回Q的队头元素,并返回OK,否则返回ERROR */
   QueuePtr p;
   if(Q.front==Q.rear)
     return ERROR;
   p=Q.front->next;
   *e=p->data;
   return OK;
 }

 Status EnQueue(LinkQueue *Q,QElemType e)
 { /* 插入元素e为Q的新的队尾元素 */
   QueuePtr p=(QueuePtr)malloc(sizeof(QNode));
   if(!p) /* 存储分配失败 */
     exit(OVERFLOW);
   p->data=e;
   p->next=NULL;
   (*Q).rear->next=p;
   (*Q).rear=p;
   return OK;
 }

 Status DeQueue(LinkQueue *Q,QElemType *e)
 { /* 若队列不空,删除Q的队头元素,用e返回其值,并返回OK,否则返回ERROR */
   QueuePtr p;
   if((*Q).front==(*Q).rear)
     return ERROR;
   p=(*Q).front->next;
   *e=p->data;
   (*Q).front->next=p->next;
   if((*Q).rear==p)
     (*Q).rear=(*Q).front;
   free(p);
   return OK;
 }

 Status QueueTraverse(LinkQueue Q,void(*vi)(QElemType))
 { /* 从队头到队尾依次对队列Q中每个元素调用函数vi()。一旦vi失败,则操作失败 */
   QueuePtr p;
   p=Q.front->next;
   while(p)
   {
     vi(p->data);
     p=p->next;
   }
   printf("\n");
   return OK;
 }
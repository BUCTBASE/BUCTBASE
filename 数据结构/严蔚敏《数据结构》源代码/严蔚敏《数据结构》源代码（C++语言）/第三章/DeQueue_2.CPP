//DeQueue.cpp
//This program is to delete the first element of LinkQueue
# include <malloc.h>
# include <iostream.h>
# include <conio.h>

# define OK 1
# define ERROR 0
typedef int QElemType;

typedef struct QNode		//define structure QNode
{    QElemType data;
     struct QNode *next;
}QNode,*QueuePtr;

typedef struct LinkQueue	//define structure LinkQueue
{    QueuePtr front;
     QueuePtr rear;
}LinkQueue;

int InitQueue(LinkQueue &Q)	//InitQueue() sub-function
{    Q.front=Q.rear=(QueuePtr)malloc(sizeof(QNode));
     if(!Q.front)
     {    cout<<endl<<"Overflow !";
	  return (ERROR);
     }
     Q.front->next=NULL;
     return (OK);
} //InitQueue() end

int EnQueue(LinkQueue &Q,QElemType e)	//EnQueue() sub-function
{   QNode *p;
    p=(QueuePtr)malloc(sizeof(QNode));
    if(!p)
    {  cout<<endl<<"Overflow !";
       return (ERROR);
    }
    p->data=e;
    p->next=NULL;
    if(Q.front==NULL)
    {   Q.front=p;
	Q.rear=p;
	return (OK);
    }
    Q.rear->next=p;
    Q.rear=p;
    return (OK);
} //EnQueue() end

int DeQueue(LinkQueue &Q,QElemType &e)	//DeQueue() sub-function
{   if(Q.front==Q.rear)
    { cout<<endl<<"If it was deleted, it's empty !";
      return (ERROR);
    }
    QNode *p;
    p=Q.front->next;
    e=p->data;
    Q.front->next=p->next;
    free(p);
    return (OK);
} //DeQueue() end

void main()				//main() function
{  int i,e=1;
   LinkQueue Q;
   QNode *q;
   InitQueue(Q);
   cout<<endl<<endl<<"DeQueue.cpp";
   cout<<endl<<"==========="<<endl<<endl;
   while(e)
   {    cout<<"Please input integer (eg,58; 0 for exit ) : ";
	cin>>e;
	if(e)
	    EnQueue(Q,e);		//call EnQueue()
   }
   cout<<"The inputed QNode is : ";
   for(q=Q.front->next;q!=NULL;q=q->next)
      cout<<q->data<<"  ";
   if(DeQueue(Q,e))			//call DeQueue()
   {  cout<<endl<<"The first element is "<<e<<endl;
      cout<<"The new QNode is : ";
      for(q=Q.front->next;q!=NULL;q=q->next)
	  cout<<q->data<<"  ";
   }
   cout<<endl<<endl<<"...OK!...";
   getch();
} //main() end
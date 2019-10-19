//DestroyQueue.cpp
//This program is to destrpu SqQueue
# include <malloc.h>
# include <iostream.h>
# include <conio.h>

# define MAXQSIZE 100
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

int EnQueue(LinkQueue &Q,QElemType e)	//EnQueue() sub-function
{   QNode *p;
    p=(QueuePtr)malloc(sizeof(QNode));
    if(!p)
    {  cout<<endl<<"Overflow !";
       return (ERROR);
    }
    p->data=e;
    p->next=NULL;
    if(Q.front==NULL)		//new QNode
    {   Q.front=Q.rear=p;
	return (OK);
    }
    Q.rear->next=p;
    Q.rear=p;
    return (OK);
} //EnQueue() end

int DestroyQueue(LinkQueue &Q)	//DestroyQueue() sub-function
{   while(Q.front)
    {   Q.rear=Q.front->next;
	free(Q.front);
	Q.front=Q.rear;
    }
    return (OK);
} //DestroyQueue() end

void main()			//main() function
{  int i,e=1;
   LinkQueue Q;
   QNode *q;
   Q.front=Q.rear=NULL;
   cout<<endl<<endl<<"DestroyQueue.cpp";
   cout<<endl<<"================"<<endl<<endl;
   while(e)
   {    cout<<"Please input integer (eg,58; 0 for exit ) : ";
	cin>>e;
	if(e)
	    EnQueue(Q,e);       //call EnQueue()
   }
   cout<<endl<<"The new QNode is : ";
   for(q=Q.front;q!=NULL;q=q->next)
      cout<<q->data<<"  ";
   DestroyQueue(Q);		//call DestroyQueue()
   cout<<endl<<endl<<"It has been destroyed successfully !";
   cout<<endl<<endl<<"...OK!...";
   getch();
} //main() end
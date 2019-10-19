//Simulation System
//This program is a Simulation Systemo
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
      return 0;
    }
    QNode *p;
    p=Q.front->next;
    e=p->data;
    Q.front->next=p->next;
    free(p);
    return (OK);
} //DeQueue() end

void OutQueue(LinkQueue &Q)		//Output()  sub-function
{   QNode *p;
    p=Q.front;
    cout<<"Queue : ";
    while(p!=Q.rear)
    {  p=p->next;
       cout<<p->data<<"  ";
    }
    cout<<endl;
} //OutQueue() end

void main()				//main() function
{    int j;
     LinkQueue LQ;
     QNode *p;
     InitQueue(LQ);			//call InitQueue()
     cout<<endl<<endl<<"Simulation System";
     cout<<endl<<"================="<<endl<<endl;
     cout<<"Please input a integer ( 0 for exit ) :";
     cin>>j;
     while(j)
     {   if(j%2==1)    EnQueue(LQ,j);	//call EnQueue()
	 else	       DeQueue(LQ,j);	//call DeQueue()
	 OutQueue(LQ);			//call OutQueue()
	 cout<<endl<<"Please input a integer ( 0 for exit ) :";
	 cin>>j;
     }
     getch();
} //main() end
//LinkQueue operation
//This program is to initialize, Insert, Delete LinkQueue
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

typedef struct			//define structure LinkQueue
{   QueuePtr rear;
}LinkQueue;

int InitQueue(LinkQueue &Q)	//InitQueue() suvb-function
{    Q.rear=(QueuePtr)malloc(sizeof(QNode));
     if(!Q.rear)
     {    cout<<endl<<"Overflow !";
	  return (ERROR);
     }
     Q.rear->next=Q.rear;
     return (OK);
} //InitQueue() end

int Insert(LinkQueue &Q,QElemType x)	//EnQueue() sub-function
{   QNode *p;
    p=(QueuePtr)malloc(sizeof(QNode));
    if(!p)
    {  cout<<endl<<"Overflow !";
       return (ERROR);
    }
    p->data=x;
    p->next=Q.rear->next;
    Q.rear->next=p;
    Q.rear=p;
    return (OK);
} //Insert() end

int Delete(LinkQueue &Q,QElemType &x)	//Delete() sub-function
{   QNode *q,*p;
    if(Q.rear->next==Q.rear)
    {   cout<<"Empty! Can't delete!";
	return (ERROR);
    }
    else
    {   p=Q.rear->next;
	x=p->next->data;
	q=p->next;
	p->next=p->next->next;
    }
    free(q);
    return (OK);
} //Delete() end

void main()				//main() function
{    int j;
     QElemType x=1;
     LinkQueue Q;
     QNode *p;
     InitQueue(Q);
     cout<<endl<<endl<<"LinkQueue Operation";
     cout<<endl<<"==================="<<endl<<endl;
     while(x)
     {  cout<<"Please input an integar (eg,58; 0 for exit): ";
	cin>>x;
	Insert(Q,x);			//call Insert()
     }
     Delete(Q,x);			//call Delete()
     cout<<endl<<"The first element of LinkQueue is: "<<x;
     cout<<endl<<endl<<"...OK!...";
     getch();
} //main()
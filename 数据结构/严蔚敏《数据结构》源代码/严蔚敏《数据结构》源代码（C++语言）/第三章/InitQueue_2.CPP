//InitQueue.cpp
//This program is to delete the first element of the LinkQueue
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

void main()			//main() function
{  LinkQueue Q;
   cout<<endl<<endl<<"InitQueue.cpp";
   cout<<endl<<"===============";
   if(InitQueue(Q))		//call InitQueue()
      cout<<endl<<endl<<"Initial Success !";
   cout<<endl<<endl<<"...OK!...";
   getch();
} //main() end
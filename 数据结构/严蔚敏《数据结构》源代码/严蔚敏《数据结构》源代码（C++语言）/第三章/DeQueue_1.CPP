//DeQueue.cpp
//This program is to delete the first element of the SqQueue
# include <malloc.h>
# include <iostream.h>
# include <conio.h>

# define MAXQSIZE 100
# define OK 1
# define ERROR 0
typedef int QElemType;

typedef struct SqQueue			//define structure SqQueue
{    QElemType *base;
     int front;
     int rear;
}SqQueue;

int EnQueue(SqQueue &Q,QElemType e)	//EnQueue() sub-function
{   if((Q.rear+1)%MAXQSIZE==Q.front)
    {   cout<<"Errer ! The SqQeueu is full ! ";
	return (ERROR);
    }
    Q.base[Q.rear]=e;
    Q.rear=(Q.rear+1)%MAXQSIZE;
    return (OK);
} //EnQueue() end

int DeQueue(SqQueue &Q,QElemType &e)	//DeQueue() sub-function
{  if(Q.front==Q.rear)
   {    cout<<endl<<"Errer !  It's empty!";
	return (ERROR);
   }
   e=Q.base[Q.front];
   Q.front=(Q.front+1)%MAXQSIZE;
   return (e);
} //DeQueue() end

void main()				//main() function
{  int i,e=1;
   SqQueue Q;
   Q.base=(QElemType *)malloc(MAXQSIZE*sizeof(QElemType));
   Q.front=Q.rear=0;
   cout<<endl<<endl<<"DeQueue.cpp";
   cout<<endl<<"============="<<endl<<endl;
   while(e)
   {   cout<<"Please input the integer to insert (eg,58; 0 for exit) : ";
       cin>>e;
       if (e)
	  EnQueue(Q,e);
   }
   i=DeQueue(Q,e);
   if(i)
       cout<<endl<<"The first element is "<<i;
   cout<<endl<<"The new SqQueue is : ";		//output
   for(e=Q.front;e<Q.rear;e++)
      cout<<Q.base[e]<<"  ";
   cout <<endl<<endl<<"...OK!...";
   getch();
} //main() end
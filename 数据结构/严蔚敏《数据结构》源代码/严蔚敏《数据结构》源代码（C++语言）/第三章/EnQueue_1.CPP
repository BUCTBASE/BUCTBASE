//EnQueue.cpp
//This program is to calculate the length of the SqQueue
# include <malloc.h>
# include <iostream.h>
# include <conio.h>

# define MAXQSIZE 100
# define LENGTH 10
# define OK 1
# define ERROR 0

typedef int QElemType;
static int array[LENGTH]={5,8,12,18,25,30,37,46,51,89};

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

void main()				//main function
{  int i,e=1;
   SqQueue Q;
   Q.base=(QElemType *)malloc(MAXQSIZE*sizeof(QElemType));
   Q.front=Q.rear=0;
   cout<<endl<<endl<<"EnQueue.cpp";
   cout<<endl<<"==========="<<endl<<endl;
   while(e)
   {   cout<<"Please input the data to insert (eg,58; 0 for exit) : ";
       cin>>e;
       if (e)
	  EnQueue(Q,e);
   }
   cout<<endl<<"The SqQueue is : ";		//output the SqQueue
   for(e=0;e<Q.rear;e++)
      cout<<Q.base[e]<<"  ";
   cout<<endl<<endl<<"...OK!...";
   getch();
} //main() end
//ListInsert_L.cpp
//This program is to insert  a element into the LNode
# include <stdlib.h>
# include <malloc.h>
# include <iostream.h>
# include <conio.h>

# define INIT_LENGTH 10
# define OK 1
# define ERROR 0

typedef struct LNode		//define LNode structure
{	int data;
	struct LNode *next;
}LNode,*Linklist;

int ListInsert_L(Linklist &L,int i,int e) //ListInsert_L() sub-function
{   LNode *p=L;
    int j=0;
    while(p&&j<i-1)           	//find the location
    {  p=p->next;
       ++j;
    }
    if(!p||j>i-1)		//out of location
    {  cout<<"Errer! The location is illegal!"<<endl;
       return (ERROR);
    }
    LNode *s;
    s=(Linklist)malloc(sizeof(LNode));	//create new LNode
    s->data=e;
    s->next=p->next;
    p->next=s;
    return (OK);
} //ListInsert_L() end

void main()        		//main() function
{    int i,j,e;
     LNode node[10];
     LNode *L,*p;
     int array[INIT_LENGTH+1]={5,8,12,18,25,30,37,46,51,89};
     L=node;
     L=(Linklist)malloc(sizeof(LNode));
     L->next=NULL;
     for (i=10;i>0;i--)
     { 	 p=(Linklist)malloc(sizeof(LNode));
	 p->data=array[i-1];
	 p->next=L->next;
	 L->next=p;
     }
     p=L;
     cout<<endl<<endl<<"ListInsert_L.cpp";
     cout<<endl<<"================";
     cout <<endl<<endl<<"The old LNode is : ";
     for(i=0;i<INIT_LENGTH;i++)
     {   p=p->next;
	 cout<<p->data<<" ";
     }
     cout<<endl<<endl<<"Please input the location to insert (1--11): ";
     cin>>j;
     cout<<"Please input the integer to insert (eg,58) : ";
     cin>>e;
     if(ListInsert_L(L,j,e))
     {  cout <<endl<<"The new LNode is : ";
	p=L;
	for(i=0;i<11;i++)
	{   p=p->next;
	    cout<<p->data<<" ";
	}
     }
     cout<<endl<<endl<<"...OK!...";
     getch();
}
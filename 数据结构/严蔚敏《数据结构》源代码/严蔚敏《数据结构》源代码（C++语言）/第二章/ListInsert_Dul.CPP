//ListInsert_Dul.cpp
//This program is to insert a node into the DuLinkList
# include <stdlib.h>
# include <malloc.h>
# include <iostream.h>
# include <conio.h>

# define INIT_LENGTH 10
# define OK 1
# define ERROR 0

typedef struct DuLNode 		//define DuLinkList structure
{	int data;
	struct DuLNode *prior;
	struct DuLNode *next;
}DuLNode,*DuLinkList;

int ListInsert_DuL(DuLinkList &L,int i,int e)	//ListInsert_Dul()
{   DuLNode *p=L,*s;
    int j=0;
    if (i<1||i>INIT_LENGTH+1)	//out of location
    {   cout<<"Errer! Out of location !";
	return (ERROR);
    }
    while(j<i)                 	//delete the i_th element
    {  p=p->next;
       ++j;
    }
    if(!(s=(DuLinkList)malloc(sizeof(DuLNode))))
    {  cout<<endl<<"Allocate space failure ! " ;
       return (ERROR);
    }
    s->data=e;
    s->prior=p->prior;
    s->next=p;
    if(i==1)
	 L->next=s;
    p->prior->next=s;
    p->prior=s;
    return (OK);
} //ListInsert_Dul() end

void main()        		//main() function
{    int i,j,e;
     DuLNode node[10];
     DuLNode *L,*p;
     int array[INIT_LENGTH+1]={5,8,12,18,25,30,37,46,51,89};
     L=(DuLinkList)malloc(sizeof(DuLNode));
     L->next=NULL;
     L->prior=NULL;
     for (i=INIT_LENGTH;i>0;i--)
     {	 p=(DuLinkList)malloc(sizeof(DuLNode));
	 p->data=array[i-1];
	 p->next=L->next;
	 p->next->prior=p;
	 L->next=p;
     }
     p=L;
     cout<<endl<<endl<<"ListInsert_Dul.cpp";
     cout<<endl<<"==================";
     cout <<endl<<endl<<"The old DuLNode is : ";  //output the old DuLinkList
     for(j=0;j<INIT_LENGTH;j++)
     {   p=p->next;
	 cout<<p->data<<" ";
     }
     cout<<endl<<endl<<"Please input the location to insert (1--11) : ";
     cin>>i;
     cout<<"Please input the integer to insert (eg,58)  : ";
     cin>>e;
     if(ListInsert_DuL(L,i,e))
     {	cout <<endl<<"The new DuLNode is : ";
	p=L;
	for(i=0;i<INIT_LENGTH+1;i++)
	{   p=p->next;
	    cout<<p->data<<" ";
	}
     }
     cout<<endl<<endl<<"...OK!...";
     getch();
} //main() end
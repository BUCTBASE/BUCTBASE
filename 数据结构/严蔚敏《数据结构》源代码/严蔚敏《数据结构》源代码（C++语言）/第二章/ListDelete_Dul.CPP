//ListDelete_Dul.cpp
//This program is to delete an element in the DuLinkList
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

int ListDelete_DuL(DuLinkList &L,int i,int &e)	//ListDelete_Dul() sub-function
{   DuLNode *p=L;
    int j=0;
    if (i<1||i>INIT_LENGTH)	//out of location
    {   cout<<"Errer! Out of location!";
	return (ERROR);
    }
    if(i==1)			//delete the first element
    {  p->next->prior=NULL;
       p=p->next;
       e=p->data;
       L=p;
       free(p);
       return (e);
     }
    while(j<i)                 	//delete the i_th element
    {  p=p->next;
       ++j;
    }
    e=p->data;
    p->prior->next=p->next;
    p->next->prior=p->prior;
    free(p);
    return (e);
} //ListDelete_Dul() end

void main()        		//main() function
{    int i,j,e;
     DuLNode node[10];
     DuLNode *L,*p;
     int array[INIT_LENGTH]={5,8,12,18,25,30,37,46,51,89};
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
     cout<<endl<<endl<<"ListDelete_Dul.cpp";
     cout<<endl<<"==================";
     cout <<endl<<endl<<"The old DuLNode is : ";  //output the old DuLinkList
     for(i=0;i<INIT_LENGTH;i++)
     {   p=p->next;
	 cout<<p->data<<" ";
     }
     cout<<endl<<endl<<"Please input the location to delete (1--10): ";
     cin>>j;
     i=ListDelete_DuL(L,j,e);		//call ListDelete_Dul()
     if (i)
     {  cout <<"The deleted element is : "<<i<<endl;
	cout <<"The new DuLNode is : ";
	p=L;
	for(i=0;i<INIT_LENGTH-1;i++)
	{   p=p->next;
	    cout<<p->data<<" ";
	}
     }
     cout<<endl<<endl<<"...OK!...";
     getch();
}
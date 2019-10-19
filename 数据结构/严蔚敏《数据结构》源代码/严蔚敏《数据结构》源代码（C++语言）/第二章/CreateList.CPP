//CreateList.cpp
//This program is to create two LNode and merge them into one
# include <stdlib.h>
# include <malloc.h>
# include <iostream.h>
# include <conio.h>

# define OK 1
# define ERROR 0

typedef struct LNode		//define the LNode structure
{	int data;
	struct LNode *next;
}LNode,*LinkList;

int CreateList(LinkList &head,LinkList s,int x,int y)  	//CreateList()
{   head=(LinkList)malloc(sizeof(LNode));
    if(!head)
       {   cout <<endl<<"Overflow ! The first LNode isn't allocated !";
	   return (ERROR);
	}
    s=(LinkList)malloc(sizeof(LNode));
    if(!s)
       {   cout <<endl<<"Overflow ! The second LNode isn't allocated !";
	   return (ERROR);
	}
    head->next=s;
    s->next=NULL;
    head->data=x;
    s->data=y;
    return (OK);
} //CreateList() end

void main()        			//main()  function
{    int x=10,y=15;
     LNode L1,L2;
     LNode *p1,*p2;
     p1=&L1;
     p2=&L2;
     cout<<endl<<endl<<"CreateList.cpp";
     cout<<endl<<"==============";
     if(CreateList(p1,p2,x,y))		//call CreateList()
     {	 cout<<endl<<endl<<"OK! The two LNode are : ";
	 cout<<p1->data<<"->"<<p1->next->data;
     }
     cout<<endl<<endl<<"...OK!...";
     getch();
} //main() end
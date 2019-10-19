//Push_L.cpp
//This program is to push LinkStack
# include <malloc.h>
# include <iostream.h>
# include <conio.h>
# define Stack_Length 6
# define OK 1
# define ERROR 0
typedef int SElemType;

typedef struct SNode		//define structure LinkStack
{    SElemType data;
     struct SNode *next;
}SNode,*LinkStack;

int Push_L(LinkStack &top,SElemType e)	//Push_L() sub-function
{   SNode *q;
    q=(LinkStack)malloc(sizeof(SNode));
    if(!q)
    {   cout<<endl<<"Overfolow ! Allocate space failure ! ";
	return (ERROR);
    }
    q->data=e;
    q->next=top->next;
    top->next=q;
    return (OK);
} //Push_L() end

void main()	 		//main function
{   SElemType e,i;
    SNode node[Stack_Length];
    SNode *p,*top=node;
    SElemType array[Stack_Length]={5,8,12,18,30,37};
    top=(LinkStack)malloc(sizeof(SNode));
    top->next=NULL;
    for(i=0;i<Stack_Length;i++)
    {   p=(LinkStack)malloc(sizeof(SNode));
	p->data=array[i];
	p->next=top->next;
	top->next=p;
    }
    cout<<endl<<endl<<"Push_L.cpp";
    cout<<endl<<"==========";
    cout <<endl<<endl<<"The old LinkStack is (top to bottom) : ";	//output
    p=top;
    while(p->next)
    {   p=p->next;
	cout<<p->data<<" ";
    }
    cout<<endl<<"Please input the data to push : ";
    cin>>e;
    if(Push_L(top,e))			//call GetTop_L()
       cout<<"Success ! The top element of LinkStack="<<e;
    cout<<endl<<"The new LinkStack is :                 ";
    while(top->next)
    {   top=top->next;
	cout<<top->data<<" ";
    }
    cout<<endl<<endl<<"...OK!...";
    getch();
} //main() end
//Pop_L.cpp
//This program is to pop LinkStack
# include <malloc.h>
# include <iostream.h>
# include <conio.h>
# define Stack_Length 6
# define OK 1
# define ERROR 0
typedef int SElemType;
typedef struct SNode	//define structure LinkStack
{    SElemType data;
     struct SNode *next;
}SNode,*LinkStack;

int Pop_L(LinkStack &top,SElemType &e)	//Pop_L() sub-function
{   SNode *q;
    if(!top->next)
    {  cout<<endl<<"Errer! It's an empty LinkStack !";
       return (ERROR);
    }
    e=top->next->data;
    q=top->next;
    top->next=q->next;
    free(q);
    return (OK);
} //Pop_L() end

void main()			//main function
{   SElemType e,i;
    SNode node[Stack_Length];
    SNode *p,*top=node;
    SElemType array[Stack_Length]={5,8,12,18,30,37};
    top=(LinkStack)malloc(sizeof(SNode));
    top->next=NULL;
    cout<<endl<<endl<<"Pop_L.cpp";
    cout<<endl<<"=========";
    for(i=0;i<Stack_Length;i++)
    {   p=(LinkStack)malloc(sizeof(SNode));
	p->data=array[i];
	p->next=top->next;
	top->next=p;
    }
    cout <<endl<<endl<<"The old LinkStack is (top to bottom) : ";	//output
    p=top;
    while(p->next)
    {   p=p->next;
	cout<<p->data<<" ";
    }
    if(Pop_L(top,e))		//call GetTop_L()
       cout<<endl<<"Success ! The top element of LinkStack = "<<e;
    cout<<endl<<"The new LinkStack is                 : ";
    while(top->next)
    {   top=top->next;
	cout<<top->data<<" ";
    }
    cout<<endl<<endl<<"...OK!...";
    getch();
} //main() end
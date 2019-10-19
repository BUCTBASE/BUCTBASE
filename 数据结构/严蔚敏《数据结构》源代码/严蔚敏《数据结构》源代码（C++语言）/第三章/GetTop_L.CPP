//GetTop_L.cpp
//This program is to get the top element of LinkStack
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

int GetTop_L(LinkStack top,SElemType &e) //GetTop_L() sub-function
{   if(!top->next)
    {  cout<<endl<<"Errer! It's an empty LinkStack !";
       return (ERROR);
    }
    else
    {  e=top->next->data;
       return (OK);
    }
} //GetTop_L() end

void main()			//main function
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
    cout<<endl<<endl<<"GetTop_L.cpp";
    cout<<endl<<"============";
    cout<<endl<<endl<<"The LinkStack is (top to bottom) : ";
    p=top;
    while(p->next)
    {   p=p->next;
	cout<<p->data<<"  ";
    }
    if(GetTop_L(top,e))			//call GetTop_L()
      cout<<endl<<"Success ! The top element of LinkStack="<<e;
    cout<<endl<<endl<<"...OK!...";
    getch();
} //main() end
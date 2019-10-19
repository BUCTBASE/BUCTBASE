//Push.cpp
//This program is to Push SqStack
# include <malloc.h>
# include <iostream.h>
# include <conio.h>
# define STACK_INIT_SIZE 100
# define STACKINCREMENT 10
# define OK 1
# define ERROR 0
typedef int SElemType;

typedef struct SqStack			//define structure SqStack
{    SElemType *base;
     SElemType *top;
     int stacksize;
}SqStack;

int Push(SqStack &S,SElemType e)	//Push() sub-function
{   if(S.top-S.base>S.stacksize)
    {    S.base=(SElemType *)realloc(S.base,(S.stacksize+
		       STACKINCREMENT*sizeof(SElemType)));
	 if(!S.base)
	 {   cout<<endl<<"Overflow!";
	     return (ERROR);
	 }
	 S.top=S.base+S.stacksize;
	 S.stacksize+=STACKINCREMENT;
    }
    *S.top++=e;
    return (OK);
} //Push() end

void main()			//main() function
{   SElemType e;
    SqStack S;
    S.stacksize=STACK_INIT_SIZE;
    S.base=S.top=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    *S.top++=5;			//initial the old SqStack
    *S.top++=8;
    *S.top++=12;
    *S.top++=18;
    *S.top++=30;
    *S.top++=37;
    SElemType *p;
    cout<<endl<<endl<<"Push.cpp";
    cout<<endl<<"========";
    cout<<endl<<endl<<"The old SqStack is (base to top) : ";
    for(p=S.base;p!=S.top;p++)		//output the old SqStack
       cout<<*p<<"  ";
    cout<<endl<<"Please input the data to push into the SqStack : ";
    cin>>e;
    if(Push(S,e))
	cout<<"Success!  S.top = "<<e;	//output S.top
    cout<<endl<<"The new SqStack is :               ";
    for(p=S.base;p!=S.top;p++)		//output the new SqStack
       cout<<*p<<"  ";
    cout<<endl<<endl<<"...OK!...";
    getch();
}
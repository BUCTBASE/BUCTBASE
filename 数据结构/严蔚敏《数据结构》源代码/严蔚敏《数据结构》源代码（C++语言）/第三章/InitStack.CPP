//InitStack.cpp
//This program is to initialize a stack
# include <malloc.h>
# include <iostream.h>
# include <conio.h>
# define STACK_INIT_SIZE 100
# define STACKINCREMENT 10
# define OK 1
# define ERROR 0
typedef int SElemType;

typedef struct			//define structure SqStack()
{    SElemType *base;
     SElemType *top;
     int stacksize;
}SqStack;

int InitStack(SqStack &S)	//InitStack() sub-function
{   S.base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    if(!S.base)
    {    cout<<endl<<"Allocate space failure !";
	 return (ERROR);
    }
    S.top=S.base;
    S.stacksize=STACK_INIT_SIZE;
    return (OK);
} //InitStack() end

void main()        	//main() function
{   SqStack S;
    cout<<endl<<endl<<"InitStack.cpp";
    cout<<endl<<"=============";
    if(InitStack(S))
	cout<<endl<<endl<<"Success! The stack has been created !";
    cout<<endl<<endl<<"...OK!...";
    getch();
}
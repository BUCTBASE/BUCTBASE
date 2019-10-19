//GetTop.cpp
//This program is to get the top element of SqStack
# include <malloc.h>
# include <iostream.h>
# include <conio.h>
# define STACK_INIT_SIZE 100
# define STACKINCREMENT 10
# define OK 1
# define ERROR 0
typedef int SElemType;

typedef struct SqStack	//define structure SqStack
{    SElemType *base;
     SElemType *top;
     int stacksize;
}SqStack;

int GetTop(SqStack S,SElemType &e)	//GetTop() sub-function
{   if(S.top==S.base)
    {    cout<<endl<<"It's a empty SqStack !";	//if empty SqStack
	 return (ERROR);
    }
    e=*(S.top-1);
    return (OK);
} //GetTop() end

void main()			//main() function
{   SElemType e;
    SqStack S;
    S.stacksize=STACK_INIT_SIZE;
    S.base=S.top=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    *S.top++=5;				//initial the SqStack
    *S.top++=8;
    *S.top++=12;
    *S.top++=18;
    *S.top++=30;
    *S.top++=37;
    SElemType *p;
    cout<<endl<<endl<<"GetTop.cpp";
    cout<<endl<<"==========";
    cout<<endl<<endl<<"The old SqStack is (base to top) : ";
    for(p=S.base;p!=S.top;p++)		//output the old SqStack
       cout<<*p<<"  ";
    if(GetTop(S,e))
	cout<<endl<<"Success!  S.top="<<e;	//output S.top
    cout<<endl<<"The new SqStack is : ";
    for(p=S.base;p<S.top;p++)		//output the old SqStack
       cout<<*p<<"  ";
    cout<<endl<<endl<<"...OK!...";
    getch();
} //main() end
//Check.cpp
//Check round brackets fucntion

#include <stdlib.h>
#include <iostream.h>
#include <conio.h>
#include <stdio.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT  10
#define OK 1
#define ERROR 0
typedef int SElemType ;
typedef struct SqStack
{	SElemType  *base;
	SElemType   *top;
	int stacksize;
}SqStack;

int InitStack(SqStack &S)               //InitStack() subfunction
{   //construct  a empty stack                                               
    S.base=(SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if(!S.base)
		{  cout<<"OVERFLOW!"<<endl;
	       return (ERROR);
		}//end of if
	S.top =S.base ;
	S.stacksize =STACK_INIT_SIZE;
	cout<<"Success to constructe a empty stack!"<<endl;
	return (OK);
}//end of InitStack() subfunction

int Push(SqStack &S,SElemType e)                     //Push() subfunction
{   //Push element to SqStack                                                 
	if(S.top-S.base >S.stacksize)                    //Stack == full?
		{  S.base=(SElemType *)realloc(S.base,(S.stacksize+STACKINCREMENT*sizeof(SElemType)));
		   if(!S.base) { cout<<"Failure to reallocate the Memory units!"<<endl;
		                 return(0);
						}
		   S.top=S.base+S.stacksize;                 //To modify pointer of Stack top
		   S.stacksize+=STACKINCREMENT;              //To modify the size of stack
	}                                                //end of if
	*S.top++=e;                                      //S.top++ and push e into stack S
	return (1);
}//end fo Push() function

int Pop(SqStack &S,SElemType &e)                    //Pop () subfunction 
{                                                   //if empty(S) then Error,otherwise Delete the S.top element 
	                                                //and return it by variable e
	if(S.top==S.base)
		{ cout<<"Underflow!"<<endl;
		  return (ERROR);
		}
	e=*--S.top;                                     //S.top-- and assign the values to e
	return(OK);
}//end of Pop() function

SElemType GetTop(SqStack S)                         //GetTop () function
{                                                   //NOTICE:  S!=&S and the Old Stack S hasn't been changed
	if(S.top==S.base) 
		{cout<<"Error! The Stack has been empty."<<endl;
	     exit(0);
		}//end of if
	else 
		return (*(S.top-1));                        //return the top element of stack S;
}//end of GetTop() function


int Check()                                         //Check() function
{ 
 	SqStack S;                                      //S is a SqStack
	char ch;
	SElemType temp;                                 //to match two parameters of Pop fucntion and so on
	int CorrectInput;
	InitStack(S);                                   //constructe a empty stack S 
	Push(S,'#');
	printf("Please input the character: <eg. (((2x+3y)) >\n");
	ch=getchar();                                   //read a character '(' or ')'
	CorrectInput=1;                                 //if CorrectInput==1 then check right else check error
	while(ch!='\n' && CorrectInput)
		{  if (ch=='(') Push (S,ch);                //come across '(' then Push it into stack
	       if(ch==')')
			   if(GetTop(S)=='#')                   //get the top element of stack and compare to '#'
				   CorrectInput=0;                  //haven't '(' to match
			   else Pop(S,temp);                    //if have '(' to match then Delete '('
			ch=getchar();
		}  //end of while                                         
	if(GetTop(S)!='#')  CorrectInput=0;             //get the top element of stack and compare to  '#'
	                                                //if the number of '('   > the number of ')' then CorrectInput=0
	if(!CorrectInput) 
		{cout<<"Error! the Left Round bracket does not match the Right one. "<<endl;
	     return(ERROR);
		}//end of if
	else
		{cout<<"OK...! the Left Round bracket does match the Right one. "<<endl;
		 return(OK);
		}//end of else
}//end of Check() function
         
void main()                                         //main() function
{  
   cout<<"Check.cpp"<<endl<<"========="<<endl<<endl;
   Check();                                         //call Check()
   getch();
}//end of main() function

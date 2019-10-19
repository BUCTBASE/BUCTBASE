//Conversion.cpp
//Conversion from positive Deci. numeral to Octo. numeral Fucntion

#include <iostream.h>
#include <malloc.h>
#include <conio.h>
#include <stdio.h>

#define STACK_INIT_SIZE 100
#define STACKINCREMENT  10
typedef int SElemType ;
typedef struct SqStack
{	SElemType  *base;
	SElemType   *top;
	int stacksize;
}SqStack;

int InitStack(SqStack &S)                            //InitStack() subfunction
{   //constructe a empty stack
    S.base=(SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if(!S.base)
		{  cout<<"OVERFLOW!"<<endl;
	       return (0);
		}
	S.top =S.base ;
	S.stacksize =STACK_INIT_SIZE;
	cout<<"Success to constructe a empty stack!"<<endl;
	return (1);
}//end of InitStack() function

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
}//end of Push() subfunction


int StackEmpty(SqStack &S)                           //StackEmpty() function                       
{   //judge empty stack ?
	if(S.top==S.base) return(1);                    //empty return 1
		else return(0);
}

int Pop(SqStack &S,SElemType &e)
{                                                   //if empty(S) then Error,otherwise Delete the S.top element 
	                                                //and return it by variable e
	if(S.top==S.base)
		{ cout<<"Underflow!"<<endl;
		  return (0);
		}
	e=*--S.top;                                     //S.top-- and assign the values to e
	return(1);
}

void Conversion()                                   //Conversion() function 
{ 
 	SqStack S;                                      //S is a SqStack
	SElemType N,e;                                    
	InitStack(S);                                   //constructe a empty stack S 
	printf("Please input the Deca. number N=?: <eg. 1348> ");
	scanf("%d",&N);
	while(N)
		{  Push(S,N%8);
	       N=N/8;
		}
    printf("Conversed to Oct. number=: ");
	while(!StackEmpty(S))                           //no empty then output
		{   Pop(S,e);
	        printf("%d",e);
		}
	
}//end of conversion() function

         
void main()                                         //main() function
{  
   cout<<"Conversion.cpp"<<endl<<"=============="<<endl<<endl;
   Conversion();
   cout<<endl<<"...OK...!"<<endl;
   getch();
}//end of main() 

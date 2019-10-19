//ClearString.cpp
//Clear the String

#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <iostream.h>
#include <stdlib.h>
#define MAXSIZE_S 40
#define OK 1
#define ERROR 0

typedef struct
{	char * ch;
	int length;
}HString;

int ClearString(HString &S)         //ClearString() function
{//To clear the string S to be empty
   if (S.ch)
     {free(S.ch); S.ch=NULL;}       //if S.ch !=NULL then free it
   S.length =0;
   return(OK);                      //success to clear the string S
}//end of clearString

int StrAssign(HString &S,char * chars)               //StrAssign() function
{                                                    //create a string T=chars
	int i=0,j;
	char *c;
	if(S.ch) free(S.ch);                             //dispose(T)
	for(c=chars;c[i]!='\0';i=i+1);
                         							 //i get the length of chars
	if(!i)
	{S.ch=NULL;S.length=0;}                          //if i==0 then set String T NULL
    else
		{
		  if(!(S.ch=(char *)malloc(i*sizeof(char))))
			{ cout<<"OVERFLOW!"<<endl;
		      return (ERROR);
			}//end of if
		   else
			{  for(j=0;j<=i-1;j++)
			      S.ch[j]=chars[j];
		       S.length=i;
		   }//end of else                                        
	}//end of else                                                  
	return(OK);
}//end of StrAssign() function

void main()                                              //main() function
{
   char charsS[MAXSIZE_S];                               //user define here
   HString S;
   cout<<"ClearString.cpp"<<endl<<"================"<<endl;
   cout<<"Please input the string S: ";
   cin>>charsS;
   StrAssign(S,charsS);
   cout<<"Clear String result: "<<ClearString(S)<<endl;
   cout<<"...OK!"<<endl;
   getch();
}



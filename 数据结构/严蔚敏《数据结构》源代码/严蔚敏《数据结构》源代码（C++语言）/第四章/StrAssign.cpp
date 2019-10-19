//StrAssign.cpp
//Create a new string T equal a const string chars

#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <iostream.h>
#include <stdlib.h>
#define CHAR_MAX_LENGTH 100

typedef struct
{	char * ch;
	int length;
}HString;

int StrAssign(HString &T,char * chars)                 //StrAssign() function   
{                                                      //create a string T=chars
	int i=0,j;
	char *c;
	if(T.ch) free(T.ch);                               //dispose(T)
	for(c=chars;c[i]!='\0';i=i+1);
				                                       //i get the length of chars
	if(!i)
	{T.ch=NULL;T.length=0;}                            //if i==0 then set String T NULL
    else
		{
		  if(!(T.ch=(char *)malloc(i*sizeof(char))))
			{ cout<<"OVERFLOW!"<<endl;
		      return (0);
			}
		   else
			{  for(j=0;j<=i-1;j++)
			      T.ch[j]=chars[j];
		       T.length=i;
		   }//end of else
		}//end of else
	printf("\nThe new string has been assigned values:  Return String T= ");
	return(1);
}//end of StrAssign() function

void main()                                            //main() function
{ 
   HString T;
   char chars[CHAR_MAX_LENGTH];
   cout<<"StrAssign.cpp"<<endl<<"============="<<endl<<endl<<"Please input the assigned String: ";
   cin.getline(chars,CHAR_MAX_LENGTH);
   StrAssign(T,(char*)chars);
   printf("%s\n\n",T.ch);
   getch();
}//end of main() function

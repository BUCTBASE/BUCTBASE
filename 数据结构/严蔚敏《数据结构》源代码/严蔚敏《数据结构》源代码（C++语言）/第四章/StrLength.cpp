//StrLength.cpp
//Get the length of string

#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <iostream.h>
#define CHAR_MAX_LENGTH 100

typedef struct
{	char * ch;
	int length;
}HString;

int StrAssign(HString &S,char * chars)                   //StrAssing() function
{                                                        //create a string T=chars
	int i=0,j;
	char *c;
	if(S.ch) free(S.ch);                                 //dispose(T)
	for(c=chars;c[i]!='\0';i=i+1);
									                     //i get the length of chars
	if(!i)
	{S.ch=NULL;S.length=0;}                              //if i==0 then set String T NULL
    else
		{
		  if(!(S.ch=(char *)malloc(i*sizeof(char))))
			{ cout<<"OVERFLOW!"<<endl;
		      return (0);
			}
		   else
			{  for(j=0;j<=i-1;j++)
			      S.ch[j]=chars[j];
		       S.length=i;
		   }                                             //end of else
	}                                                    //end of else
	return(1);
}//end of StrAssign() function


int StrLength(HString S)                                 //StrLength() function
{                                                        //return the element number of String
	return S.length;
}//end of StrLength() function
	
void main()
{
   char chars[CHAR_MAX_LENGTH];//="Beijing is a beautiful city.";           //user define here
   HString S;
   cout<<"StrLength.cpp"<<endl<<"============="<<endl<<endl<<"Please input the String: <eg. DataStructure> ";
   cin.getline(chars,CHAR_MAX_LENGTH);
   StrAssign(S,chars);
   cout<<endl<<"The String is:  "<<chars<<endl;
   cout<<"The Length of String is: "<<StrLength(S)<<endl<<"...OK!..."<<endl;
   getch();
}//end of main() function



//SubString.cpp

#include <conio.h>
#include <malloc.h>
#include <iostream.h>
#include <stdio.h>
#define MAXSIZE 100

typedef struct
{   char * ch;
	int length;
}HString;

int SubHString(HString &Sub,HString S,int pos,int len)        //SubHString() function
{
   int i;
   if(pos<1 || pos>S.length || len<0 || len>S.length-pos+1)
      {cout<<endl<<"ERROR!"<<endl;
       return (0);
       }//end of if
  if(Sub.ch) free(Sub.ch);
   if(!len)
       { Sub.ch=NULL;
	     Sub.length=0;
         cout<<endl<<"SubString Length=0!"<<endl;
		 return(0);
		}//end of if
   else
       {
	 Sub.ch=(char*)malloc(len*sizeof(char));
	 if(!Sub.ch)
		 {cout<<"OVERFLOW!";
           return(0);
		  }
	  for(i=0;i<=len-1;i++)
	     Sub.ch[i]=S.ch[i+pos-1];
	  Sub.ch[len]=NULL;
	  Sub.length=len;
       }//end of else
   cout<<endl<<"Success to get the SubHString!"<<endl;
   printf("SubHString is: %s",Sub.ch);
   return (1);
}//end of SubHString() function

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
		   }//end of else
	}
	return(1);
}//end of StrAssign() function

void main()                                           //main() function
{
   char chars[MAXSIZE];
   HString S,Sub;
   int pos,len;
   cout<<"SubHString.cpp"<<endl<<"=============="<<endl;
   cout<<endl<<"Please input the string S1: <eg. DataStructure> ";
   cin.getline(chars,MAXSIZE);
   StrAssign(S,chars);                                 //create a new string S1
   cout<<"Position: <eg. 5> ";
   cin>>pos;
   cout<<"Length of Sub HString: <eg. 9> ";
   cin>>len;
   if(SubHString(Sub,S,pos,len))
       cout<<endl<<"...OK!... "<<endl;
   getch();
}//end of main() function



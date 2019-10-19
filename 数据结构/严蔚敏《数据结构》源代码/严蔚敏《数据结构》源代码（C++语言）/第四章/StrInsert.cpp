//StrInsert.cpp

#include <conio.h>
#include <malloc.h>
#include <iostream.h>
#include <stdio.h>
#define MAXSIZE_S 100
#define MAXSIZE_T 100

typedef struct
{
	char * ch;
	int length;
}HString;

int StrInsert(HString &S,int pos,HString T)      //StrInsert() function
{//1<=pos<=StrLength(S)+1;Insert the HString T before the NO.pos character of HString S
  int i;
  if(pos<1 ||pos>S.length+1)
     { cout<<"Postion has Error!"<<endl;
       return (0);
      }
   if(T.length)
     { if(!( S.ch=(char*)realloc(S.ch,(S.length+T.length)*sizeof(char))))
	  { cout<<"OVERFLOW";
	    return (0);
	   }
	for(i=S.length-1;i>=pos-1;--i)
	   S.ch[i+T.length]=S.ch[i];    //ready for inserting HString T
	for(i=0;i<=T.length-1;i++)
	   S.ch[pos-1+i]=T.ch[i];
	S.length+=T.length;
	S.ch[S.length]=NULL;
      }//end of if
   cout<<endl<<"Success to Insert another HString!"<<endl;
   printf("The new HString S is: %s",S.ch);
   return (1);
}//end of StrInsert() function

int StrAssign(HString &S,char * chars)                   //StrAssign() function
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

void main()                                             //main() function             
{
   char chars_S[MAXSIZE_S];
   char chars_T[MAXSIZE_T];
   HString S,T;
   int pos;
   cout<<"StrInsert.cpp"<<endl<<"=============="<<endl;
   cout<<endl<<"Please input the previos HString S:"<<endl<<"<eg. \"Show the what you are maded of!\">\n";
   cin.getline(chars_S,MAXSIZE_S);
   StrAssign(S,chars_S);                                 //create a new string S
   cout<<"Please input the inserted HString T: <eg. \"m\">\n";
   cin.getline(chars_T,MAXSIZE_T);
   StrAssign(T,chars_T);                                 //create a new string T
   printf("Before Position: <eg. 9>\n");             //Control for input position
   scanf("%d",&pos);
   StrInsert(S,pos,T);
   cout<<endl<<"...OK!..."<<endl;
   getch();
}//end of main() fucntion



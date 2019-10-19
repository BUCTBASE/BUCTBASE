//HStrConcat.cpp
//Concat HString S1 and S2 to T

#include <conio.h>
#include <malloc.h>
#include <iostream.h>
#include <stdio.h>
#define MAXSIZE_S1 100
#define MAXSIZE_S2 100

typedef struct
{	char * ch;
	int length;
}HString;

int HStrConcat(HString &T,HString S1,HString S2)         //HStrConcat() function
{
  int i;
  if (T.ch) free(T.ch);                                  //dispose previos space
  if (!(T.ch=(char *)malloc((S1.length+S2.length)*sizeof(char))))
      { cout<<"OVERFLOW"<<endl;
	return (0);
       }
  for(i=0;i<=S1.length-1;i++)
      T.ch[i]=S1.ch[i];
  T.length=S1.length+S2.length;
  for(i=0;i<=S2.length-1;i++)
     T.ch[i+S1.length]=S2.ch[i];
  T.ch[i+S1.length]=NULL;                                //end of HString T
  cout<<"Success to Concat HString S1 and S2!"<<endl<<"Concat HString S1 and S2 result: ";
  cout<<T.ch;
  return (1);
}//end of HStrConcat() function

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
	}//end of else                                                    
	return(1);
}//end of StrAssign() function

void main()                                               //main() function
{
   char charsS1[MAXSIZE_S1];                              //user define here
   char charsS2[MAXSIZE_S2];
   HString T,S1,S2;
   cout<<"HStrConcat.cpp"<<endl<<"==============="<<endl<<endl;
   cout<<"Please input the string S1: <eg. Bei> ";
   cin.getline(charsS1,MAXSIZE_S1);
   cout<<"Please input the string S2: <eg. jing> ";
   cin.getline(charsS2,MAXSIZE_S2);
   StrAssign(S1,charsS1);                                 //create a new string S
   StrAssign(S2,charsS2);                                 //create a new string T
   HStrConcat(T,S1,S2);
   cout<<endl<<"...OK!... "<<endl;
   getch();
}//end of main() function



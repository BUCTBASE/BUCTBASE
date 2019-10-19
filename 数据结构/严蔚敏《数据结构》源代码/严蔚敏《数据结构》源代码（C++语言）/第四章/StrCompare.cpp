//StrCompare.cpp
//Compare two string

#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <iostream.h>
#define MAXSIZE_S 40
#define MAXSIZE_T 40

typedef struct
{	char * ch;
	int length;
}HString;

int StrCompare(HString S,HString T)                     //StrCompare() function   
{//Compare string S and T from the first char on until no equal
    int i;                     							//if S[i]<T[i] then S<T,and return <0;
	for(i=0;i<S.length&&i<T.length;++i)			    	//if String S.length=T.length && all char are equal then S=T,return =0
	if (S.ch[i]!=T.ch[i]) return S.ch[i]-T.ch[i];       //if S[i]>T[i] then S>T and return >0
	return S.length-T.length;
}//end of StrCompare() function                         

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
		   }                                             //end of else
	}                                                    //end of else
	return(1);
}//end of StrAssing(0 function

void main()
{
   char charsS[MAXSIZE_S];                              //user define here
   char charsT[MAXSIZE_T];
   HString S,T;
   cout<<"StrCompare.cpp"<<endl<<"=============="<<endl;
   cout<<endl<<"Please input the string S: <eg. Beijing> ";
   cin>>charsS;
   cout<<"Please input the string T: <eg. Beihai> ";
   cin>>charsT;
   StrAssign(S,charsS);
   StrAssign(T,charsT);
   cout<<endl<<"String Compare result: "<<StrCompare(S,T)<<endl;
   cout<<"...OK!..."<<endl;
   getch();
}



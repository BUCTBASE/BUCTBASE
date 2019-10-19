//Index_BF.cpp

#include <stdio.h>
#include <conio.h>
#include <iostream.h>
#define MAXSTRLEN 255

typedef unsigned char SString[MAXSTRLEN+1];                    //from 0 to 256 becoz of '\0'

int Index_BF(SString S,SString T,int pos)                      //Index_BF() function
{
    int i=pos,j=1;                                             //from the pos char in main SString on
	while(i<=S[0]&&j<=T[0])
	{ if(S[i]==T[j])
		{++i;
	     ++j;
		}
	   else
		{ i=i-j+2;
	      j=1;
		}
	}// end of while
	if(j>T[0]) return (i-T[0]);
    else return (0);
}//end of Index_BF() function

 
void main()                                                     //main() function
{
   SString S,T;
   int pos;                                                     //  1<=pos<=S[0]-T[0]+1;
   int m,n,r;                                                   //  the length of SString S and T
   cout<<"Index_BF.cpp"<<endl<<"============"<<endl<<endl;
   cout<<"Please input the Main SString S: <eg. student> ";
   cin.getline(S+1,MAXSTRLEN);
   cout<<"Please input the SString T : <eg. den> ";
   cin.getline(T+1,MAXSTRLEN);
   cout<<"From ? on: <eg. 1> ";
   cin>>pos;

   for(m=0;S[m]!='\0';m++);                                      // get the length of SString S
   S[0]=m-1;
   for(n=0;T[n]!='\0';n++);                                      // get the length of SString T 
   T[0]=n-1;
 
   if(r=Index_BF(S,T,pos))                                
	  cout<<endl<<"The postion of T in the Main SString S is: "<<r<<endl<<"...OK...!"<<endl;
   else cout<<"Failure to Index the SString!"<<endl;
   getch();
}//end of main() function
 
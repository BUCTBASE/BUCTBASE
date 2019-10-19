//Index_KMP.cpp

#include <stdio.h>
#include <conio.h>
#include <iostream.h>
#define MAXSTRLEN 255

typedef unsigned char SString[MAXSTRLEN+1];                    //from 0 to 256 becoz of '\0'
int next[MAXSTRLEN+1];

void get_next(SString T,int *next)                             //get_next() function 
{// get the next value and save into array next,be ready for matching
	int	i=1,j=0;
	next[1]=0;                                                 //set Init_values
    while(i<=T[0])
	{   if(j==0||T[i]==T[j])
	   { ++i;++j;
	     next[i]=j;
		}//end of if
	   else j=next[j];                                         //if j!=0 or T[k]!=T[j] then j=next[j]
	}//end of while
}//end of get_next


int Index_KMP(SString S,SString T,int pos)                     //Index_KMP() function
{ //S[0] and T[0] are the length of SString 
  //use the "next" function to get the position of where the T is in main SString from pos on
  //1<=pos<=S[0]-T[0]+1
    int i=pos,j=1;                                             //set Init_values
	while(i<=S[0]&&j<=T[0])
		{if (j==0||S[i]==T[j])
			{++i;
	         ++j;
			}//end of if
	     else
			 j=next[j];
		}//end of while
	if(j>T[0]) return (i-T[0]);
	else return (0);
}//end of Index_KMP

   
void main()                                                      //main() function
{
   SString S,T;
   int pos;                                                      //  1<=pos<=S[0]-T[0]+1;
   int m,n,r;                                                    //  the length of SString S and T
   cout<<"Index_KMP.cpp"<<endl<<"============="<<endl<<endl;
   cout<<"Please input the Main SString S: <eg. Beijing> ";
   cin.getline(S+1,MAXSTRLEN);
   cout<<"Please input the other SString T: <eg. jing> ";
   cin.getline(T+1,MAXSTRLEN);
   cout<<"From ... on?: ";
   cin>>pos;

   for(m=0;S[m]!='\0';m++);                                      // get the length of SString S
   S[0]=m-1;
   for(n=0;T[n]!='\0';n++);                                      // get the length of SString T 
   T[0]=n-1;
 
   get_next(T,next);

   if(r=Index_KMP(S,T,pos))                                
	  cout<<"The postion of T in the Main SString S from "<<pos<<" chars on is: "<<r<<endl<<"...OK!..."<<endl;
   else cout<<"Failure to Index the SString!"<<endl;
   getch();
}//end of main() function
 
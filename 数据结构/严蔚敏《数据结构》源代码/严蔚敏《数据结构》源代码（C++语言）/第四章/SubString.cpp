//SubString.cpp
//To find out Substring

#include <stdio.h>
#include <conio.h>
#include <iostream.h>
#define MAXSTRLEN 255

typedef unsigned char SString[MAXSTRLEN+1];

int SubString(SString &Sub,SString S,int pos,int len)//SubString() function
{                                                    //return the SubString with the length ="len" from "pos" on by Sub[]
                                                     //1<=pos<=StrLength(S) && 0<=len<=StrLength(S)-pos+1
	int i,k;
	if(pos<1 || pos>S[0] || len<0 || len>S[0]-pos+1)
		{cout<<"Error! "<<pos<<" or "<<len<<" is out of range."<<endl;
         return(0);
		}
	for(i=1,k=pos;i<=len;i++)
	   Sub[i]=S[++k];                                //Sub[1...len]=S[pos...pos+len-1]
	Sub[i]='\0';
	Sub[0]=len;
	return (1);
}//end of SubString() function
                                          
	        		        		
void main()                                           //main() function
{  
   SString Sub;
   int pos,len;
   unsigned char S[MAXSTRLEN+1];
   printf("SubString.cpp\n=============\n\n");
   printf("Please input the main String: <eg. DataStructure> \n");
   scanf("%s",S);
   printf("Please input the position and length of SubString: \nposition= <eg. 5> ");
   scanf("%d",&pos);
   printf("length= <eg. 9> ");
   scanf("%d",&len);
   if(SubString(Sub,S,pos,len))
      printf("\nThe SubString is: %s\nSubString.length= %d\n...OK...!\n",Sub+1,Sub[0]);                      
   getch();
}//end of main() 

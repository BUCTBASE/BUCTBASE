//Concat.cpp
//To Concat the SString S1 and S2 

#include <iostream.h>
#include <conio.h>
#include <stdio.h>

#define MAXSTRLEN 255
typedef unsigned char SString[MAXSTRLEN+1];

int Concat(SString &T,SString S1,SString S2)      //Concat() function
{                                                 //T is the new string concat by S1 and S2
	                                              //if uncut then return 1,otherwise return 0
	                                              //T[0],S1[0],S2[0] are length of  string  
	int i,k,uncut;
	if (S1[0]+S2[0]<=MAXSTRLEN)                   //uncut
		{ for(i=1;i<=S1[0];i++)
		     T[i]=S1[i];
	      for(k=1,i=S1[0]+1;i<=S1[0]+S2[0];i++)
			 T[i]=S2[k++];                         
		  T[i]='\0';                              //end of string
		  T[0]=S1[0]+S2[0];
          uncut=1;
		  }                                        //end of if

	else if(S1[0]<MAXSTRLEN)                       //S2 will be cut
		{ for(i=1;i<=S1[0];i++)
			 T[i]=S1[i];
	      for(k=1,i=S1[0]+1;i<=MAXSTRLEN;i++)
			 T[i]=S2[k++];
		  T[i]='\0';                               //end of string
		  T[0]=MAXSTRLEN;
		  uncut=0;
			}                                      //end of else if            

	 else if(S1[0]=MAXSTRLEN)                      //just only cut S1 
		{ for(i=0;i<=MAXSTRLEN;i++)                //from i=o on becoz T[0]==S[0]==MAXSTRLEN
		      T[i]=S1[i];
	       T[i]='\0';                              //end of string
	       uncut=0;
			}                                      //end of else if
	    
	   else                                        //if S1[0]>MAXSTRLEN then cut S1
			{ for(i=1;i<=MAXSTRLEN;i++)
			    T[i]=S1[i];
	          T[i]='\0';                           //end of string
              T[0]=MAXSTRLEN;
			  uncut=0;
			}                                      //end of else
	   return (uncut);
}                                                  //end of Concat
	        		        		
void main()                                          //main() function
{  
   SString T;
   int j=0,k=0,m,n;
   unsigned char S1[MAXSTRLEN+1],S2[MAXSTRLEN+1];
   cout<<"Concat.cpp\n==========\n\n"; 
   cout<<"Please input the String S1: <eg. Bei> ";
   cin.getline(S1+1,MAXSTRLEN);
   cout<<"Please input the String S2: <eg. jing> ";
   cin.getline(S2+1,MAXSTRLEN);

   for(m=1;S1[m]!='\0';m++);
       S1[0]=m-1;
   for(n=1;S2[n]!='\0';n++);
       S2[0]=n-1;

   Concat(T,S1,S2);
   printf("For Example:\nS1= %s\n",S1+1);             //Hide the first element in unsigned char array                                         
   printf("S2= %s\n",S2+1);                           //becoz it records the real length of string        
   printf("T = %s\n\n",T+1);
   printf("S1[0]=S1[length]=%u\n",S1[0]);
   printf("S2[0]=S2[length]=%u\n",S2[0]);
   printf("Length of New string T is: %u \n\n...OK!...\n",T[0]);    //output unsigned char[]  T,S1,S2                                                       

   getch();
}//end of main()

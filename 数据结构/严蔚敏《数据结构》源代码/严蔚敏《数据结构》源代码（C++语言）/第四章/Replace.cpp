//Replace.cpp

#include <stdio.h>
#include <conio.h>
#include <iostream.h>
#define MAXSTRLEN 255

typedef unsigned char SString[MAXSTRLEN+1];         //from 0 to 256 becoz '\0'

void Copy(SString &A,SString B,int x,int y,int len) //Copy() function
{ //copy to SString A in x position from y position in SString B, in all be len character
	int i,j,k;
	for(i=x,j=y,k=1;k<=len;i++,j++,k++)
		A[i]=B[j];
}//end of Copy() function

int Replace(SString &D,SString S,SString T,SString V)
{ //Replace the SubSString T with V where T
	int m,n,p,i,j,k,q,overflow;
	for(m=0;S[m]!='\0';m++);
	for(n=0;T[n]!='\0';n++);
	for(p=0;V[p]!='\0';p++);
	overflow=0;                                              //Set overflow flag
	i=0;
	k=0;
	q=0; 
    while(!overflow&& m-k>=n)           //have been modified      
		{
		  j=0;
		  while((j<n) && (S[k+j]==T[j])  )//modified
			  j++;
		  if(j<n)                       //modified
			  k++;
		  else 
			   if(q+k-i+p>MAXSTRLEN)               
				   return (0);          //failure to match SString
		  else
			{ Copy(D,S,q,i,k-i);
		      q=q+k-i;                  //modify
		      Copy(D,V,q,0,p);
			  i=k+n;
			  q=q+p;                    //modify
			  k=i;				     
			}//end of if
	}//end of while 
	if((!overflow)&&(i<=m)&&((q+m-i+1)<=MAXSTRLEN))
		Copy(D,S,q,i,m-i+1);    
	else 
		overflow=1;
	return(!overflow);
}//end of Replace() function
   
void main()                                            //main() function
{
   SString D,S,T,V;
   cout<<"Replace.cpp"<<endl<<"============"<<endl<<endl;
   cout<<"Please input the previous SString S: <eg. abcb ccbcbad> ";
   cin.getline(S,MAXSTRLEN);
   cout<<"Find the key SString T : <eg. bc> ";
   cin.getline(T,MAXSTRLEN);
   cout<<"Replaced by the SString V: <eg. @> ";
   cin.getline(V,MAXSTRLEN);

      
   if(Replace(D,S,T,V))                                //call Replace function
	{ printf("The new SString D= %s",D);               //Output the new SString D
     cout<<endl<<"...OK!..."<<endl;
	}
   else cout<<"Failure to Replace the SString!"<<endl;
   getch();
}//end of main() function

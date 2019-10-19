//Compare.cpp
//Compare two SString

#include <stdio.h>
#include <conio.h>
#include <iostream.h>
#define MAXSTRLEN 255
typedef unsigned char SString[MAXSTRLEN+1];

int Compare(SString S1,SString S2)          //Compare() function
{
   int i,m,n;
   for(i=0;S1[i]!='\0'&&S2[i]!='\0';++i)
      if(S1[i]!=S2[i])  return (S1[i]-S2[i]);
   for(m=0;S1[m]!='\0';++m);
   for(n=0;S2[n]!='\0';++n);
   return (m-n);
}//end of Compare() function

void main()                                 //main() function
{
   SString S1,S2;
   cout<<"Compare.cpp"<<endl<<"==========="<<endl;
   cout<<"Please input the SString S1: <eg. Beijing> ";
   cin.getline(S1,MAXSTRLEN);
   cout<<"Please input another SString S2 to compare: <eg. Beihai> ";
   cin.getline(S2,MAXSTRLEN);
   cout<<"Compare SString S1 and S2 result: "<<Compare(S1,S2)<<endl;
   cout<<endl<<"...OK!... "<<endl;
   getch();
}//end of main() function

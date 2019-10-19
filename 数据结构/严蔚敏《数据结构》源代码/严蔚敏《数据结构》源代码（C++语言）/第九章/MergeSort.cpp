//MergeSort.cpp

#include <iostream.h>
#include <conio.h>
#define MAXSIZE 20
#define LENGTH 7
typedef int RedType;

typedef struct		         //SqList structure
{   RedType	r[MAXSIZE+1];    //Records Type
    int length;
}SqList;
typedef SqList RcdType;

void Merge(RcdType SR,RcdType &TR,int i,int m,int n)       //Merge() function
{   int j,k;
    for(j=m+1,k=i;i<=m&&j<=n;++k)
    {   if(SR.r[i]<=SR.r[j])
	     TR.r[k]=SR.r[i++];
	else
	     TR.r[k]=SR.r[j++];
    }
    while(i<=m)
       TR.r[k++]=SR.r[i++];
    while(j<=n)
       TR.r[k++]=SR.r[j++];
}//end of Merge() function

void MSort(RcdType SR,RcdType &TR1,int s, int t)           //MSort() function     
{  int m;
   RcdType TR2;//[LENGTH];
   if(s==t)
	 TR1.r[s]=SR.r[t];
   else
   {  m=(s+t)/2;
      MSort(SR,TR2,s,m);
      MSort(SR,TR2,m+1,t);
      Merge(TR2,TR1,s,m,t);
   }//end of else
}//end of MSort() function

void MergeSort(SqList &L)	//MergeSort() function
{
   MSort(L,L,1,L.length);
}//end of MergeSort() function

void main()		            //main function
{  int i;
   SqList L;//={{0,49,38,65,97,76,13,27,},LENGTH};
   cout<<"MergeSort.cpp"<<endl<<"============="<<endl<<endl;
   cout<<"Please input the length of SqList L: <eg. 7> ";
   cin>>L.length;

   cout<<"Please input the disordered array L.r: <eg. {49,38,65,97,76,13,27,...}>"<<endl;
   for(i=1;i<=L.length;i++)
       cin>>L.r[i];
   MergeSort(L);
   cout<<endl<<"The sorted array L.r:  ";
   for(i=1;i<=L.length;i++)
       cout<<L.r[i]<<"  ";
   cout<<endl;
   cout<<"...OK!..."<<endl;
   getch();
}//end of main() function
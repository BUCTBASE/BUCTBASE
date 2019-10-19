//BubbleSort.cpp
//This function is to sort SqList
# include <iostream.h>
# include <conio.h>

# define MAXSIZE 20
# define MAX_LENGTH 100
typedef int RedType;

typedef struct			//define structure SqList
{   RedType	r[MAXSIZE+1];
    int length;
}SqList;

void BubbleSort(SqList &L)
{   int i,j,temp;
    for(i=0;i<=L.length;++i)
       for(j=L.length-2;j>i;--j)
	  if(L.r[j+1]<L.r[j])
	  {   temp=L.r[j+1];
	      L.r[j+1]=L.r[j];
	      L.r[j]=temp;
	  }
}

void main()			//main() function
{  int i;
   SqList L;
   cout<<endl<<endl<<"BubbleSort.cpp";
   cout<<endl<<"=============="<<endl;
   cout<<endl<<"Please input the length of SqList (eg,5): ";
   cin>>L.length;
   L.length++;			//the last is aided space
   for(i=1;i<L.length;++i)
   {   cout<<"Please input the "<<i<<"th element of SqList (eg,58): ";
       cin>>L.r[i];
   }
   cout<<endl<<"The disordered : ";
   for(i=1;i<L.length;i++)
       cout<<L.r[i]<<"  ";
   BubbleSort(L);		//call BubbleSort()
   cout<<endl<<"The ordered    : ";
   for(i=1;i<L.length;i++)
     cout<<L.r[i]<<"  ";
   cout<<endl<<endl<<"...OK!...";
   getch();
} //main() end
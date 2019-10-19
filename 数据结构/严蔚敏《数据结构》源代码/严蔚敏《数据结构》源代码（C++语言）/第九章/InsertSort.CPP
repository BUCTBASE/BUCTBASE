//InsertSort.cpp
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

void InsertSort(SqList &L)	//InsertSort() sub-function
{  int i,j;
   for(i=2;i<=L.length;++i)
       if(L.r[i]<L.r[i-1])
       {  L.r[0]=L.r[i];
	  for(j=i-1;L.r[0]<L.r[j];--j)
	     L.r[j+1]=L.r[j];
	  L.r[j+1]=L.r[0];
       }
}

void main()			//main() function
{  int i;
   SqList L;
   cout<<endl<<endl<<"InsertSort.cpp";
   cout<<endl<<"==============";
   cout<<endl<<"Please input the length of SqList (eg,5): "<<endl<<endl;
   cin>>L.length;
   for(i=1;i<=L.length;++i)
   {   cout<<"Please input the "<<i<<"th integer (eg,58): ";
       cin>>L.r[i];
   }
   cout<<endl<<"The disordered : ";
   for(i=1;i<=L.length;i++)
       cout<<L.r[i]<<"  ";
   InsertSort(L);		//call InsertSort()
   cout<<endl<<"The ordered    : ";
   for(i=1;i<=L.length;i++)
     cout<<L.r[i]<<"  ";
   cout<<endl<<endl<<"...OK!...";
   getch();
} //main() end
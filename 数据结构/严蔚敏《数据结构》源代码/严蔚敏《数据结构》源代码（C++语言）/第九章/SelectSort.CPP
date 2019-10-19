//SelectSort.cpp
//This function is to SelectSort SqList
# include <iostream.h>
# include <conio.h>

# define MAXSIZE 20
typedef int RedType;

typedef struct			//define structure SqList
{   RedType	r[MAXSIZE+1];
    int length;
}SqList;

void SelectSort(SqList &L)	//SelectSort() sub-function
{   int i,j,k,temp;
    for(i=0;i<L.length;++i)
    {   k=i;
	for(j=i+1;j<L.length;++j)
	   if(L.r[j]<L.r[k])
	       k=j;
	if(i!=k)
	{   temp=L.r[i];
	    L.r[i]=L.r[k];
	    L.r[k]=temp;
	}
    }
}//SelectSort() end

void main()			//main() function
{  int i;
   SqList L={{49,38,65,97,76,13,27,49,},8};
   cout<<endl<<endl<<"SelectSort.cpp";
   cout<<endl<<"=============="<<endl;
   cout<<endl<<"The disordered : ";
   for(i=0;i<L.length;i++)
       cout<<L.r[i]<<"  ";
   SelectSort(L);		//call SelectSort()
   cout<<endl<<"The sorted     : ";
   for(i=0;i<L.length;i++)
     cout<<L.r[i]<<"  ";
   cout<<endl<<endl<<"...OK!...";
   getch();
} //main() end
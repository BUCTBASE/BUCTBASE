//QuickSort.cpp
//This function is to quick-sort SqList
# include <iostream.h>
# include <conio.h>

# define MAXSIZE 20
typedef int RedType;

typedef struct		//define SqList structure
{   RedType	r[MAXSIZE+1];
    int length;
}SqList;

int  Partition(SqList &L,int low,int high)	//Partition() sub-function
{  int pivotkey;
   L.r[0]=L.r[low];
   pivotkey=L.r[low];
   while(low<high)
      {  while(low<high&&L.r[high]>=pivotkey)
	    --high;
	 L.r[low]=L.r[high];
	 while(low<high&&L.r[low]<=pivotkey)
	    ++low;
	 L.r[high]=L.r[low];
      }
   L.r[low]=L.r[0];
   return (low);
} //Partition() end

void Qsort(SqList &L,int low,int high)	//Qsort() sub-function
{  int pivotloc;
   if(low<high)
   {  pivotloc=Partition(L,low,high);
      Qsort(L,low,pivotloc-1);
      Qsort(L,pivotloc+1,high);
   }
}

void QuickSort(SqList &L)		//QuickSort() sub-function
{  Qsort(L,1,L.length);			//call Qsort()
}

void main()				//main() function
{  int i;
   SqList L={{0,49,38,65,97,76,13,27,49},8};
   cout<<endl<<endl<<"QuickSort.cpp";
   cout<<endl<<"============="<<endl;
   cout<<endl<<"The disordered : ";
   for(i=1;i<=L.length;i++)
       cout<<L.r[i]<<"  ";
   QuickSort(L);			//call QuickSort()
   cout<<endl<<"The sorted     : ";
   for(i=1;i<=L.length;i++)
     cout<<L.r[i]<<"  ";
   cout<<endl<<endl<<"...OK!...";
   getch();
} //main() end
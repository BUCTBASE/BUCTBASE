//Shellinert.cpp
//This function is Shell sort
# include <iostream.h>
# include <conio.h>
# define MAXSIZE 20

# define OK 1
# define ERROR 0
typedef int RedType;

typedef struct				//structure SqList
{   RedType	r[MAXSIZE+1];
    int length;
}SqList;

void Shellinsert(SqList&L,int dk) 	//Shellinsert() sub-function
{  int i,j;
   for(i=dk+1;i<=L.length;++i)
       if(L.r[i]<L.r[i-dk])
       {   L.r[0]=L.r[i];
	   for(j=i-dk;j>0&&(L.r[0]<L.r[j]);j-=dk)
	      L.r[j+dk]=L.r[j];
	   L.r[j+dk]=L.r[0];
       }
}

void main()				//main() function
{  int i,dk=5;
   SqList L={{0,49,38,65,97,76,13,27,49,55,4},10};
   cout<<endl<<endl<<"Shellinsert.cpp";
   cout<<endl<<"==============="<<endl;
   cout<<endl<<endl<<"The disordered             : ";
   for(i=1;i<=L.length;i++)
       cout<<L.r[i]<<"  ";
   Shellinsert(L,dk);            	//call Shellinsert()
   cout<<endl<<"The once ShellSorted sorted: ";
   for(i=1;i<=L.length;i++)
     cout<<L.r[i]<<"  ";
   cout<<endl<<endl<<"...OK!...";
   getch();
} //main() end
//TransposeSMatrix.cpp

#include <stdarg.h>
#include <iostream.h>
#include <malloc.h>
#include <stdio.h>
#include <conio.h>

#define MAXSIZE 12500
#define OK 1
typedef int ElemType;
typedef struct 
{   int i,j;
	ElemType e;
}Triple;

typedef union
{    Triple  data[MAXSIZE+1];        //from data[1] on ,and data[0] has not been used
     int mu,nu,tu;
}TSMatrix;

int TransposeSMatrix(TSMatrix M,TSMatrix &T)
{
    int q,p,col;
	T.mu=M.nu;
	T.nu=M.mu;
	T.tu=M.tu;
	if(T.tu)
	{
		q=1;
		for(col=1;col<=M.nu;++col)
			for(p=1;p<=M.tu;++p)
			   if(M.data[p].j==col)
			   {
				T.data[q].i=M.data[p].j;
			    T.data[q].j=M.data[p].i;
				T.data[q].e=M.data[p].e;
				printf("%d       %d        %d\n",T.data[q].i,T.data[q].j,T.data[q].e);
				++q;
			   }//end of if(M.data[p])
	}//end of if(T.tu)
     return OK;
}//end of TransposeSMatrix() function

void main()                     //main() function
{
   TSMatrix M,T;
    int i;
	cout<<"TransposeSMatrix.cpp"<<endl<<"===================="<<endl<<endl;
	M.mu=3;                     //Default values of InitTSMstrix M
	M.nu=5;
	M.tu=4;

	printf("Please input the M.mu:<eg. 3> ");
	scanf("%d",&M.mu);
	printf("Please input the M.nu:<eg. 5> ");
	scanf("%d",&M.nu);
	printf("Please input the M.tu:<eg. 4> ");
	scanf("%d",&M.tu);   
    
	printf("\nPlease input the i,j and data of TransposeSMatrix M: \n");
	printf("<eg. (i,j,e)={(1,2,20),(3,4,19),(3,2,10),(1,3,10),...}\n");
	for(i=1;i<=M.tu;i++)                               //input the M.tu value
	{   printf("\nM.data[%d].i=  ",i);
	    scanf("%d",&M.data[i].i);
		printf("M.data[%d].j=  ",i);
		scanf("%d",&M.data[i].j);
		printf("M.data[%d].e=  ",i);
		scanf("%d",&M.data[i].e);
	    if(M.data[i].i>M.mu||M.data[i].j>M.nu)         //input control
		{ cout<<"Input Error!"<<endl;
		  i--;
		}
	}//end of for 
	
	printf("\nAfter Transposing the SMatrix T is:\n");	
	printf("i=    j=       data=\n");
    TransposeSMatrix(M,T);
	printf("\n");
   	getch();
}//end of main() function




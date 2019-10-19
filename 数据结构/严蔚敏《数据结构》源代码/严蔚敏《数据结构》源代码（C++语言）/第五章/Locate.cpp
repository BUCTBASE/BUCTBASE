//Locate.cpp

#include <stdarg.h>
#include <iostream.h>
#include <malloc.h>
#include <stdio.h>
#include <conio.h>

#define MAX_ARRAY_DIM 8
#define ERROR 0
#define OVERFLOW -1
#define UNDERFLOW -2
#define OK 1

typedef int ElemType;
typedef struct
{	ElemType *base;
	int dim;
	int *bounds;
	int *constants;
}Array;

int Locate(Array A,va_list ap,int &off)                        //Locate() function
{ //To get the offset of  element in the array A
	int ind,i;
	off=0;
	for(i=0;i<A.dim;++i)
	{
		ind=va_arg(ap,int);
		if(ind<0||ind>=A.bounds[i]) return OVERFLOW;          //Illegal substript
		off+=A.constants[i]*ind;
	}
	return OK;
}//end of Locate() function
 
int InitArray(Array &A,int dim,...)             //InitArray() function
{
	int i,elemtotal=1;                          //Initialize total element of A 
	va_list ap;
	if(dim<1||dim>MAX_ARRAY_DIM) return (ERROR);//if dimention is illegal then return ERROR;
	A.dim=dim;                                  //set dimention of array
	A.bounds=(int*)malloc(dim*sizeof(int));     //allocate space for array A.bounds
    if(!A.bounds) return (OVERFLOW);            //failure to allocate
	va_start(ap,dim);                           //ap are the type of va_list
	for(i=0;i<dim;i++)
	{A.bounds[i]=va_arg(ap,int);
	 if(A.bounds[i]<0) return (UNDERFLOW);
	 elemtotal *=A.bounds[i];
	}//end of if

	va_end(ap);
	A.base=(ElemType*)malloc(elemtotal*sizeof(ElemType));//allocating space to A.base
	if(!A.base) return(OVERFLOW);
	
	A.constants=(int*)malloc(dim*sizeof(int));           //allocating space to A.constants
	if (!A.constants) return(OVERFLOW);
	A.constants[dim-1]=1;                                 

	for(i=dim-2;i>=0;--i)                                 //get the const Ci and save into A.constants[i-i],i=1,..,dim
		A.constants[i]=A.bounds[i+1]*A.constants[i+1];
	return elemtotal;
}//end of InitArray() function

	
void main()                            //main() function
{
	Array A;
	int dim=2,r,i=0;                   //default dimention is 2;
	int off=0;
	int Abound[MAX_ARRAY_DIM];         //to save the array subscript of which you want to get its offset  
	int bound[MAX_ARRAY_DIM];
	printf("Locate.cpp\n==========\n\n");
	printf("Please input the dimentions of array you want to create: <eg. dimention=2>\n");
	scanf("%d",&dim);                   
	printf("please assign the length of each dimention: <eg. 5,4,...>\n");
	
	for(i=0;i<dim;i++)
		{   printf("Dimention%d.length= ",i+1);
		    scanf("%d",&bound[i]);
			
		}

	if(r=InitArray(A,dim,bound[0],bound[1],bound[2],bound[3],bound[4],bound[5],bound[6],bound[7]))
	{
		cout<<"Success to Initialize a Array!"<<endl
		    <<"Dimention= "<<dim<<endl<<"Total element is: "<<r<<endl<<endl;
	
	    cout<<"Please input the array subscripts of which you want to get its offset:"<<endl
			<<"Array[J1,J2,J3,...] <eg. J1=2,J2=3>"<<endl;
		//default: Abound[0]=0;Abound[1]=4;Abound[2]=1;Abound[3]=0;Abound[4]=1;Abound[5]=1;Abound[6]=0;Abound[7]=1;
		for(i=0;i<dim;i++)               //input the subscript of each dimention      
		{   printf("J%d= ",i+1);
		    scanf("%d",&Abound[i]);
		}
	    
        //	r=Locate(A,off,Abound[0],Abound[1],Abound[2],Abound[3],Abound[4],Abound[5],Abound[6],Abound[7]);
        va_list ap;
		va_start(ap,off);
		ap=(char *)&Abound[0];
		r=Locate(A,ap,off);
		va_end(ap);
		if(r!=OVERFLOW) 
		    cout<<"Location in Array is:(Begin with Array[0,0,0...]) "<<off<<endl;
	    else
		    cout<<"OVERFLOW"<<endl;
	}//end of if
getch();
}//end of main() function




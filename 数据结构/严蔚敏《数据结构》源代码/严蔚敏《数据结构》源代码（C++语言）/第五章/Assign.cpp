//Assign.cpp
//Assign e to the element of array A

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
{
	ElemType *base;
	int dim;
	int *bounds;
	int *constants;
}Array;

int Locate(Array A,va_list ap,int &off)    //Locate() function
{ //To get the offset of  element in the array A
	int ind,i;
	off=0;
	for(i=0;i<A.dim;++i)
	{
		ind=va_arg(ap,int);
		if(ind<0||ind>=A.bounds[i]) return OVERFLOW;           //Illegal substript
		off+=A.constants[i]*ind;
	}
	return (OK);
}//end of Locate() function
 
int Assign(Array &A,ElemType e,...)            //Assign () function
{
	va_list ap;
	int result,off;
	va_start(ap,e);
	if((result=Locate(A,ap,off))<=0)  return result;
	*(A.base+off)=e;
	va_end(ap);
	return (OK);
}//end of Assing() function

int InitArray(Array &A,int dim,...)             //InitArray() subfunction
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
	return (elemtotal);
}//end of InitArray

void main()                            //main() function
{
	Array A;
	int dim=2,r,i=0;                   //default dimention is 2;
	int off=0,e=50;                    //default Assign values=50;
	//int Abound[MAX_ARRAY_DIM];         //to save the array subscript of which you want to get its offset  
	int bound[MAX_ARRAY_DIM];
	int Assbound[MAX_ARRAY_DIM];
	printf("Assign.cpp\n==========\n\n");
	printf("Please input the dimentions of array you want to create: <Default dimention=2>\n");
	scanf("%d",&dim);                   
	printf("please assign the length of each dimention: <eg. Dimention[i]={3,4,...}>\n");
	
	for(i=0;i<dim;i++)
		{   printf("Dimention %d .length= ",i+1);
		    scanf("%d",&bound[i]);			
		}
	if(r=InitArray(A,dim,bound[0],bound[1],bound[2],bound[3],bound[4],bound[5],bound[6],bound[7]))
	{
		cout<<"Success to Initialize a Array!"<<endl
		    <<"Dimention= "<<dim<<endl<<"Total element is: "<<r<<endl<<endl;
        cout<<"Now begin to Assign!"<<endl<<"Assign values = <eg. 100> ";
		cin>>e;
	    cout<<"Please input the array subscripts of which you want to assign values: "<<endl
			<<"Array[J1,J2,J3,...] and 0<=Ji<Dimention[i] when i>1 "<<endl
			<<"<eg. J1=1,J2=0,...>"<<endl;	    
		//default: Abound[0]=0;Abound[1]=4;Abound[2]=1;Abound[3]=0;Abound[4]=1;Abound[5]=1;Abound[6]=0;Abound[7]=1;
		for(i=0;i<dim;i++)               //input the subscript of each dimention      
		{   printf("J%d= ",i+1);
		    scanf("%d",&Assbound[i]);
		}  
         
		if(Assign(A,e,Assbound[0],Assbound[1], Assbound[2], Assbound[3], Assbound[4], Assbound[5], Assbound[6], Assbound[7]))
			 cout<<"The assigned element value of array A is: "<<e<<endl<<"Success to Assign the array A!"<<endl; 
		else cout<<"Failure to Assign."<<endl;
	}//end of if
    getch();
}//end of main() function




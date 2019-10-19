//Merge_Sq.cpp
//To Merge two SqList A and B to C 

#include <stdlib.h>
#include <iostream.h>
#include <conio.h>

//#define LIST_INIT_LENGTH_A 10                 //LIST_INIT_LENGTH_A is the Init_Define_Length of SqList A
//#define LIST_INIT_LENGTH_B 10                 //LIST_INIT_LENGTH_B is the Init_Define_Length of SqList B
//int array_A[]={1,3,5,7,9,11,13,15,17,19};
//int array_B[]={2,4,6,8,10,12,14,16,18,20};    //array_A and array_B use to assign init value of SqList

typedef int ElemType;
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef struct 
{	int *elem;
	int length;
	int listsize;
}SqList;

int InitList_Sq(SqList &L)                                    //InitList_Sq() function
{   //Inititial a Sq_List
	L.elem=(int *)malloc(LIST_INIT_SIZE *sizeof(int));
	if (!L.elem) return(0);
	L.length=0;
	L.listsize=LIST_INIT_SIZE;
	return(1);
}//end of InitList_Sq() function

int Merge_Sq(SqList &A,SqList &B,SqList &C)  //Merge_Sq() function
{                                            //Merge the SqList A and B to C
   C.listsize=C.length=A.length+B.length;
   C.elem=(ElemType *)malloc(C.listsize*sizeof(ElemType));
   if(!C.elem)
	{ cout<<" OverFlow !"<<endl;             //failure to allocate room in RAM
	  return(0);                             
	};
   int i=0,j=0;                              //i and j is the Subscript of A.elem[] and B.elem []
   int k=0;                                  //k is the Subscript of C.elem[]
   while((i<A.length)&&(j<B.length ))        //To merge when i <=A.length and j>=B.length
	   if(A.elem [i]<=B.elem [j])
		{ C.elem [k]=A.elem [i];
	      i++;k++;
		}//end of if                                    
	   else
		{ C.elem [k]=B.elem [j];
	      j++;k++;
		}//end of else                                    
   
   while(i<A.length )                        //insert the rest of SqList A
	{ C.elem [k]=A.elem [i];
      i++;k++;
	}//end of while
                                        
   while (j<B.length )                       //insert the rest of SqList B
	{ C.elem [k]=B.elem [j];
      j++;k++;
	}
   cout<<"Success to Merge A and B !"<<endl;
   return(1);
}//end of Merge_Sq() function
	          
void main()                                   //Main() function
{
   SqList A,B,C;
   int j;
   cout<<"Merge_Sq.cpp"<<endl<<"============="<<endl<<endl;
   InitList_Sq(A);
   InitList_Sq(B);
   InitList_Sq(C);
   cout<<"The SqList A's Length is: <eg. 5>";
   cin>>A.length;
   cout<<endl<<"Please input the data of SqList A in acsendant order:  <eg. {1,3,5,7,9...}>"<<endl;
   for(j=0;j<A.length;j++)
      cin>>A.elem[j];
   cout<<endl;

   cout<<"The SqList B's Length is: <eg. 6>";
   cin>>B.length;
   cout<<endl<<"Please input the data of SqList B: <eg. {2,4,6,8,10,100,...}> "<<endl;
   for(j=0;j<B.length;j++)
      cin>>B.elem[j];
   cout<<endl;

   Merge_Sq(A,B,C);                                        //To Merge A and B SqList
   cout<<"The SqList C is:  "<<endl;
   for(j=0;j<C.length;j++)
      cout<<C.elem[j]<<"  ";
   cout<<endl<<"...OK...!"<<endl;
   getch();
}//end of main() function

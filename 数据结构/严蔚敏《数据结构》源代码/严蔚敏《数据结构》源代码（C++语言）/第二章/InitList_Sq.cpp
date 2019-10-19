//InitList_Sq.cpp

#include <stdlib.h>
#include <malloc.h>
#include <iostream.h>
#include <conio.h>
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

void main()                                                  //main() function 
{
    SqList L;
	cout<<"InitList_Sq.cpp"<<endl<<"==============="<<endl<<endl;
    if(!InitList_Sq(L))
       cout<<"Failure to Initialize a Sq_List !"<<endl;
    else
       cout<<"Success to Initialize a Sq_List !"<<endl;
    getch();
}//end of main() function

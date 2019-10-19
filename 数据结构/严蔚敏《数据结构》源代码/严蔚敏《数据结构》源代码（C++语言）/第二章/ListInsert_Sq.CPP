//ListInsert_sq.cpp
//This program is to insert a element into Sqlist
# include <malloc.h>
# include <iostream.h>
# include <conio.h>

# define LIST_INIT_SIZE 100
# define LIST_INIT_LENGTH 10
# define LISTINCREMENT 10
# define OK 1
# define ERROR 0

typedef struct SqList			//define structure SqList
{       int *elem;
	int length;
	int listsize;
}SqList;

int ListInsert_sq(SqList &L,int i,int e)//ListInsert_sq()
{   if(i<1||i>L.length+1)		//i (location) is illegal
    {  cout <<"Initial failure!"<<endl;
       getch();
       return (ERROR);
    }
    if(L.length>=L.listsize)          	//insert into the end of the Sqlist
    {  int *Newbase;
       Newbase=(int *)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(int));
       if(!Newbase)
       {  cout<<"Overflow!"<<endl;
	  getch();
	  return (ERROR);
       }
       L.elem=Newbase;
       L.listsize+=LISTINCREMENT;
     }
     int *p,*q;
     q=&(L.elem[i-1]);	//q point at the element before the inserted one
     for(p=&(L.elem[L.length-1]);p>=q;--p)  	//move the element
     *(p+1)=*p;
     *q=e;
     ++L.length;
     return (OK);
} //ListInser_sq() end

void main()        				//main() function
{    int i,e,j;
     SqList list;
     list.length=LIST_INIT_LENGTH;
     list.listsize=LIST_INIT_SIZE;
     int array[11]={5,8,12,18,25,30,37,46,51,89};
     list.elem=array;
     cout<<endl<<endl<<"ListInsert_sq.cpp";
     cout<<endl<<"=================";
     cout<<endl<<endl<<"The old Sqlist is : ";
     for(j=0;j<10;j++)
       cout<<array[j]<<" ";
     cout<<endl<<endl<<"Please input the location to insert (1 to 11) : ";
     cin>>i;
     while(i<1||i>11)
     {  cout<<endl<<"Please input the location to insert (1 to 11): ";
	cin>>i;
     }
     cout<<"Please input the integer to insert (eg,58)    : ";
     cin>>e;
     if(ListInsert_sq(list,i,e)) 		//call ListInsert_sq()
     {   cout<<endl<<"The new Sqlist is : ";
	 for(j=0;j<=10;j++)
	    cout <<array[j]<<" ";
     }
     cout<<endl<<endl<<"...OK!...";
     getch();
} //main() end
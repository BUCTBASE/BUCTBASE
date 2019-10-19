//Search_Seq.cpp
//This function is to find the element in SSTbale by sequence search
# include <malloc.h>
# include <iostream.h>
# include <conio.h>

# define MAX_LENGTH 100
typedef int KeyType;

typedef struct			//define structure SSTable
{   KeyType *elem;
    int length;
}SSTable;

int Search_Seq(SSTable ST,KeyType key)	//Search_Seq function
{  int i;
   ST.elem[0]=key;
   for(i=ST.length;!(ST.elem[i]==key);--i)
      ;
   return (i);				//if not find,return i=0
}

void main()  			   	//main function
{  int i,key;
   SSTable ST;
   ST.elem=(KeyType *)malloc(sizeof(KeyType));
   cout<<endl<<endl<<"Search_Seq.cpp";
   cout<<endl<<"==============";
   cout<<endl<<endl<<"Please input the length of array (eg,5) :";
   cin>>ST.length;
   for(i=1;i<=ST.length;++i)
   {  cout<<"Please input the "<<i<<"th element (eg,58) :   ";
      cin>>ST.elem[i];
   }
   cout<<endl<<"The SSTable ST is : ";
   for(i=1;i<=ST.length;i++)
      cout<<ST.elem[i]<<"  ";		//output ST.elem[]
   cout<<endl<<"Please input the data to find : ";
   cin >>key;				//input the element to find
   cout<<"The location of "<<key<<" is (0 for none): ";
   cout<<Search_Seq(ST,key);		//call Search_Seq()
   cout<<endl<<endl<<"...OK!...";
   getch();
} //main() end
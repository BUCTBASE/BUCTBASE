//CreateList_L.cpp
//To create a LinkList

#include <stdlib.h>
#include <iostream.h>
#include <conio.h>

typedef struct LNode
{	int data;
	struct LNode *next;
}LNode,*LinkList;

void CreateList_L(LinkList &L,int n)              //CreateList_L() function
{ //To Creatre a LinkList L with HeadNode 
  int i;
  LNode *p;
  L=(LinkList)malloc(sizeof(LNode));
  L->next=NULL;
  cout<<"Please input the data for LinkList Nodes: <eg. 34,67,3,-9,45,...>"<<endl;
  for(i=n;i>0;--i)
  {
	  p=(LinkList)malloc(sizeof(LNode));
	  cin>>p->data;                               //Reverse order inputing for Creating a LinkList
	  p->next=L->next;
	  L->next=p;
  }//end of for
  if(n) cout<<"Success to Create a LinkList !"<<endl;
  else cout<<"A NULL LinkList have been created !"<<endl;
}//end of CreateList() function 

void main()                                       //main() function
{
   LinkList L;
   int InitLNodeNum;                              //the Init LinkNode Numbers
   cout<<"CreateList_L.cpp"<<endl<<"================"<<endl;
   cout<<endl<<"Please input the Init LinkNode Number: <eg. 5> ";
   cin>>InitLNodeNum;
   CreateList_L(L,InitLNodeNum); 
   cout<<"OK...!"<<endl;
   getch();
}//end of main() function

//Contray.cpp
//To Contray all Elements of the LinkList 

#include <stdlib.h>
#include <iostream.h>
#include <stdio.h>
#include <conio.h>

#define LIST_INIT_LENGTH 10                  //LIST_INIT_LENGTH is the Init_Define_Length of LinkList
			                                 
typedef int ElemType;                     
typedef struct LNode
{
	int data;
	struct LNode *next;	
}LNode,*LinkList;

void CreateList_L(LinkList &L,int n)     //CreatList_L() subfunction
{                                        //To Creatre a LinkList L with HeadNode 
  int i;
  LNode *p;
  int array[LIST_INIT_LENGTH];
  L=(LinkList)malloc(sizeof(LNode));
  L->next=NULL;
    
  printf("Please input the nodes data: <eg. 34,20,2,3,10,51,12,...>\n"); 
  for(i=0;i<n;i++)               //input the data to create the LinkList
	  scanf("%d",&array[i]);

  for(i=0;i<n;++i)
  {
	  p=(LinkList)malloc(sizeof(LNode));
	  p->data=array[i];                 //for example to a CreateList
	  p->next=L->next;
	  L->next=p;
  }                                     //end of for
} //end of CreateList_L() function 

void Contray(LinkList &head)            //Contray() function 
{                                       //Delete the NO.i element of LinkList and return by variable e      
   LNode *p,*q;
   p=head;
   head=NULL;
   while(p)
	{
	   q=p;
	   p=p->next;
	   q->next=head;
	   head=q;
   }                                                       //end of while
    cout<<endl<<"Success to Contray the LinkList !";
}//end of Contray() function

void main()                                                //main() function
{
   LinkList L;
   LNode *p;
   int i,LNodeNum;                                           //j is just a counter for cycle 
   cout<<"Contray.cpp"<<endl<<"============"<<endl<<endl;
   cout<<"How many nodes do you want to create? <eg. 7> ";
   cin>>LNodeNum;
   CreateList_L(L,LNodeNum); 
   p=L;
   cout<<endl<<"The next one's Inserted Direction is always in front of this."<<endl;       
   for(i=0;i<LNodeNum;++i)
   {
	   p=p->next;
	   cout<<p->data<<"  ";                                  //output the LinkList before Contray
       
	}
   cout<<endl;
   cout<<"<------------------------------<"<<endl;
   Contray(L);                                               //call function Contray();
   cout<<endl<<"the LinkList after contray is: [  ";
   for(i=0;i<LNodeNum;++i)
   {
	   cout<<L->data<<"  ";                                  //output the LinkList after Contray
       L=L->next;         
   } 
   cout<<"]"<<endl<<"...OK...!"<<endl;
   getch();
}//end of main() function

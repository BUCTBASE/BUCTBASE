//ListDelete_L.cpp
//To Delete the NO.i Element of LinkList 

#include <malloc.h>
#include <iostream.h>
#include <conio.h>

//#define LIST_Max_LENGTH 10                  //LIST_INIT_LENGTH is the Init_Max_Length of LinkList
//int array[]={5,8,12,18,25,30,37,46,51,89};
                             			    //array use to assign init value of SqList
typedef struct LNode
{	int data;
	struct LNode *next;
}LNode,*LinkList;

void CreateList_L(LinkList &L,int n)       //CreateList_L() function
{ //To Creatre a LinkList L with HeadNode 
  int i;
  LNode *p;
  L=(LinkList)malloc(sizeof(LNode));
  L->next=NULL;
  for(i=0;i<n;++i)
  {
	  p=(LinkList)malloc(sizeof(LNode));
	  cin>>p->data;
	  p->next=L->next;
	  L->next=p;
  }//end of for
}//end of CreateList() function

int ListDelete_L(LinkList &L,int i,int &e)  //ListDelete_L() function
{  //Delete the NO.i element of LinkList and return by variable e       
   LNode *p,*q;
   int j=0;
   p=L;
   while(p->next&&j<i-1)
   {  p=p->next;++j;
   }
   if(!p||j>i-1) 
   { cout<<"The NO. "<<i<<" element is not exist !"<<endl;
     getch();
     return(0);
   }
   q=p->next;
   p->next=q->next;                     //delete the NO.i Node
   e=q->data;
   free(q);
   return (e); 
}//end of ListDelete() function

void main()                                                  //main() function
{
   LinkList L;
   LNode *p;
   int e;                                                    //e can be Every DataType 
   int i,j;                                                  //j is just a counter for cycle 
   int LListNodeNum;
   cout<<"ListDelete_L.cpp"<<endl<<"================"<<endl<<endl;
   cout<<"Please input the LinkListNodeNum: <eg. 6> ";
   cin>>LListNodeNum;
   cout<<endl<<"The Demo LinkList to be: <eg. 5,8,12,18,25,13,...> "<<endl;
   CreateList_L(L,LListNodeNum); 
   
   cout<<endl<<"Success to CreateList_L:   ";
   p=L->next;
   while(p)                                                 //display the Demo LinkList
   { cout<<p->data<<"  ";
     p=p->next;
   }//end of for   
   cout<<endl<<endl<<"Which NO.? element of LinkList you want to Delete: ";
   cin>>i;                                                  //input the No.i
   if(i<= LListNodeNum) 
   { cout<<"The NO. "<<i<<" element has been Delete: "<<ListDelete_L(L,i,e)<<endl;
     for(j=1;j<LListNodeNum;++j)
	 {
	   L=L->next;
	   cout<<L->data<<"  ";                                  //output the LinkList       
	 }//end of for 
     cout<<endl<<endl<<"...OK...!"<<endl;
   }//end of if
   else cout<<"Input Error!"<<endl;
   getch();
}//end of main() function

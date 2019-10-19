//MergeList_L.cpp
//This program is to merge two sorted LNode into one
# include <stdlib.h>
# include <iostream.h>
# include <conio.h>

# define INIT_LENGTH 10

typedef struct LNode		//define  LNode structure
{	int data;
	struct LNode *next;
}LNode,*LinkList;

void MergeList_L(LinkList &La,LinkList &Lb,LinkList &Lc) //MergeList_L()
{   LNode *pa,*pb,*pc;
    pa=La->next;
    pb=Lb->next;
    Lc=pc=La;
    cout<<endl;
    while(pa&&pb)
       if(pa->data<=pb->data)
       {   pc->next=pa;
	   pc=pa;
	   pa=pa->next;
       }
       else
       {   pc->next=pb;
	   pc=pb;
	   pb=pb->next;
       }
       if (!pa)			//the end of pb
       {  pc->next=pb;
	  pc=pc->next;
       }
       else		 	//the end of pa
       {  pc=pa;
	  pc=pc->next;
       }
} //MergeList_L() end

void main()       		//main() function
{    int i,j,e;
     LNode node1[INIT_LENGTH],node2[INIT_LENGTH],node3[INIT_LENGTH*2];
     LNode *La,*Lb,*Lc,*p,*q;
     int array1[INIT_LENGTH]={5,8,12,18,25,30,37,46,51,89};
     int array2[INIT_LENGTH]={6,9,13,19,26,31,38,47,52,90};
     La=node1;			//La points at node1[]
     La=(LinkList)malloc(sizeof(LNode));
     La->next=NULL;
     Lb=node2;			//Lb points at node2[]
     Lb=(LinkList)malloc(sizeof(LNode));
     Lb->next=NULL;
     Lc=node3;		//Lc points at node2[]
     Lc=(LinkList)malloc(sizeof(LNode));
     Lc->next=NULL;
     for (i=INIT_LENGTH;i>0;i--)
     {   p=(LinkList)malloc(sizeof(LNode));	//initial Lb
	 p->data=array1[i-1];
	 p->next=La->next;
	 La->next=p;
	 q=(LinkList)malloc(sizeof(LNode));	//initial Lb
	 q->data=array2[i-1];
	 q->next=Lb->next;
	 Lb->next=q;
     }
     p=La;				//output La
     cout<<endl<<endl<<"MergeList.cpp";
     cout<<endl<<"=============";
     cout <<endl<<endl<<"LNode La is : ";
     for(i=0;i<INIT_LENGTH;i++)
     {   p=p->next;
	 cout<<p->data<<"  ";
     }
     q=Lb;				//output Lb
     cout <<endl<<"LNode Lb is : ";
     for(i=0;i<INIT_LENGTH;i++)
     {   q=q->next;
	 cout<<q->data<<"  ";
     }
     MergeList_L(La,Lb,Lc);		//call MergeList()
     cout <<"LNode Lc is : ";
     p=La;
     for(i=0;i<INIT_LENGTH*2;i++)
     {   p=p->next;
	 cout<<p->data<<" ";
     }
     cout<<endl<<endl<<"...OK!...";
     getch();
} //main() end
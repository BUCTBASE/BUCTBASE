//AddPolyn.cpp
//Add Polynomial Pa and Pb 
#include <iostream.h>
#include <malloc.h>
#include <conio.h>
#include <stdio.h>

struct Term
{	float coef;
	int expn;
	struct Term *next;
}*LinkList;
                                                 //typedef LinkList with polynomial
void CreateList_L(struct Term * &L,int n)
{                                                 //To Creatre a LinkList L with HeadNode 
  int i;
  struct Term *p;
  L=(struct Term *)malloc(sizeof(Term));
  L->next=NULL;
  for(i=n;i>0;--i)
  {
	  p=(struct Term *)malloc(sizeof(Term));
	  cout<<"coef = ";
	  cin>>p->coef;                               //Reverse order inputing for Creating a LinkList
	  cout<<"expn = ";
	  cin>>p->expn; 
	  p->next=L->next;
	  L->next=p;
  }//end of for                                              
  if(n) cout<<"Success to Create a LinkList !"<<endl;
  else cout<<"A NULL LinkList have been created !"<<endl;
} //end of function CreateList
                                              
char cmp(int qa_expn,int qb_expn)               //cmp() function            
{//compare qa->expn and qb->expn
	if(qa_expn==qb_expn) 
		return '=';
	else 
		if(qa_expn>qb_expn) return'>';
			else return '<';
}//end of cmp() function

void AddPolyn(struct Term * &Pa,struct Term * &Pb) //AddPolyn() function
{ //Add the polynomial Pa and Pb                                                
   struct Term *qa,*qb,*pre,*u;  
   float sum;
   qa=Pa->next;                                 //qa point to current node of Pa 
   qb=Pb->next;                                 //qb point to current node of Pb 
   pre=Pa;                                      //pre point to the HeadNode of Pa
   
   while(qa&&qb)                                //neither qa nor qb are NULL
	   switch(cmp(qa->expn,qb->expn))
		{ case '<':
			  pre=qa;qa=qa->next;
			  break;
		  case '=':                             //when the expn of qa == the expn of qb 
			  sum=qa->coef+qb->coef;
			  if(sum!=0.0)               
				{ qa->coef=sum;pre=qa;          //modify the current Node coef values of Pa
				}                               //end of if
			  else
				{ pre->next=qa->next;           //otherwise qa->expn=qb->expn then delete current Node in Pa
			      free(qa);
				}                               //end of else
			  qa=pre->next;u=qb;qb=qb->next;
			  free(u);
			  break;
		  case '>':
                                   			  u=qb->next;
			  qb->next=qa;
			  pre->next=qb;
			  pre=qb;
			  qb=u;
			  break;
		}                                       //end of switch
   if(!qa) pre->next=qb;                        //to link the rest of node of Pb
   free(Pb);
   cout<<endl;
}//end of AddPolyn() function
         
void main()                                                 //main() function
{  
   struct Term *Pa,*Pb,*p;	    
   int InitLNodeNum_Pa,InitLNodeNum_Pb;                     //the Init LinkNode Numbers

   cout<<"AddPolyn.cpp"<<endl<<"============="<<endl;  
   cout<<endl<<"How many sessions of polynomial Pa do you want ? (eg. 4): ";
   cin>>InitLNodeNum_Pa;  
   cout<<"Please input the Pa.coef and Pa.expn in descent order:"<<endl;
   cout<<"For example: (coef=3,expn=21);(coef=7,expn=9);(coef=4,expn=1);(coef=5,expn=0)"<<endl;
   CreateList_L(Pa,InitLNodeNum_Pa);                       //to create polynomial Pa LinkList with 
                                                           //the InitLNodeNum_Pa=input number +1  
   cout<<endl<<"How many sessions of polynomial Pb do you want ? (eg. 3): ";
   cin>>InitLNodeNum_Pb;                                   
   cout<<"Please input the Pb.coef and Pb.expn in descent order:"<<endl;
   cout<<"For example: (coef=-7,expn=9);(coef=13,expn=6);(coef=8,expn=1)"<<endl;
   CreateList_L(Pb,InitLNodeNum_Pb);                       //to create polynomial Pb LinkList with
                                                           //the InitLNodeNum_Pb=input number +1  
   AddPolyn(Pa,Pb);                                        //AddPolyn Pa and Pb
   p=Pa;
   cout<<"Result:"<<endl;
   while(p->next)                                         //output Pa=Pa+Pb
		{ p=p->next;
          cout<<"(Pc.coef="<<p->coef<<",";
          cout<<"Pc.expn="<<p->expn<<")"<<endl;		  
		}// end of while
   cout<<endl<<"OK...!"<<endl;
   getch();
}//end of main() function

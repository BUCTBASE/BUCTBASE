//CreateSMatrix_OL.cpp

#include <stdarg.h>
#include <iostream.h>
#include <malloc.h>
#include <stdio.h>
#include <conio.h>

#define OVERFLOW -1
#define OK 1

typedef int ElemType;
typedef struct OLNode
{   int i,j;
	ElemType e;
	struct OLNode *right,*down;
}OLNode,*Olink;

typedef struct
{   Olink *rhead,*chead;
	int mu,nu,tu;
}CrossList;

int CreateSMatrix_OL(CrossList &M)
{//To CreateSMatrix M with CrossList type 
	int m,n,t,i,j,k,e;
	Olink p,q;
	if(&M) free(&M); 
	printf("Please input the M.mu,M.nu and M.tu: <eg. M.mu=5,M.nu=4,M.tu=7>\n");
	scanf("%d%d%d",&m,&n,&t);
	M.mu=m;
	M.nu=n;
	M.tu=t;
	if(M.tu>M.mu*M.nu) return(OVERFLOW);
	if((M.rhead=(Olink*) malloc((m+1)*sizeof(Olink)))==NULL) return(OVERFLOW);
	if((M.chead=(Olink*)malloc((n+1)*sizeof(Olink)))==NULL) return(OVERFLOW);
	for(i=0;i<M.mu;i++)
	   M.rhead[i]=NULL;
    for(i=0;i<M.nu;i++)
	   M.chead[i]=NULL;
	printf("Please input the i,j and e: <eg. i=2,j=3,e=89... To exit if input e=0>\n");
	printf("(0<=i<=%d),(0<=j<=%d)\n",M.mu-1,M.nu-1);
	for(scanf("%d%d%d",&i,&j,&e),k=1;e!=0&&k<=M.tu;printf("Please input the next i,j and e:\n"),scanf("%d%d%d",&i,&j,&e),k++)
	{ 
		if(i>=M.mu||j>=M.nu||i<0||j<0) return(OVERFLOW);         //Control user input,[] from zero on
		if((p=(OLNode*)malloc(sizeof(OLNode)))==NULL) return(OVERFLOW);
		p->i=i;
		p->j=j;
		p->e=e;
		if(M.rhead[i]==NULL)
		{ M.rhead[i]=p;
		  p->right=NULL;
		}//end of if
	    else
			if (M.rhead[i]->j>j)
			{ p->right=M.rhead[i];
			  M.rhead[i]=p;
			}//end of if
            else
			{  for(q=M.rhead[i];(q->right)&&q->right->j<j;q=q->right);
			   p->right=q->right;
			   q->right=p;
			}//over the line insert
			if(M.chead[j]==NULL)
			{ M.chead[j]=p;
			  p->down=NULL;
			}//end of if(M.chead[j]==NULL)
			else 
				if(M.chead[j]->i>i)
				{  p->down=M.rhead[j];
				   M.rhead[j]=p;
				}//end of if
				else
				{
				   for(q=M.chead[j];(q->down)&&q->down->i<i;q=q->down);
	 			   p->down=q->down;
				   q->down=p;
				}//end of column insert
	}// end of for
	return (OK);
}//CreateSMatrix_OL
				
void main()                                          //main() function
{   
    CrossList M;
	cout<<"CreateSMatrix_OL.cpp"<<endl<<"===================="<<endl<<endl;
	if(CreateSMatrix_OL(M)==OK)  
		cout<<"Success to CreateSMatrix M!"<<endl;
	else
		cout<<"Error!"<<endl;
   	getch();
}//end of main




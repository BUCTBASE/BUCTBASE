//Restore.cpp
//This function is to construct a BiTree

# include <malloc.h>
# include <stdio.h>
# include <iostream.h>
# include <conio.h>
# define LENGTH 7
# define OK 1
# define ERROR 0
typedef char TElemType;
typedef struct BiTNode		                     //define BiTree
{  TElemType data;
   struct BiTNode *lchild,*rchild;
}BiTNode, *BiTree;

BiTNode *Restore(char *pstr,char *istr,int n)    //Restore() function
{   if(n<=0)
	return (NULL);
    BiTree ptr;
    int k;
    char *rstr;
    ptr=(BiTNode*)malloc(sizeof(BiTNode));
    ptr->data=*pstr;
    for(rstr=istr;rstr<istr+n;rstr++)
		if(*rstr==*pstr)  break;
    k=rstr-istr;
    ptr->lchild=Restore(pstr+1,istr,k);
    ptr->rchild=Restore(pstr+k+1,rstr+1,n-k-1);
    return (ptr);
}//end of Restore() function 

int InOrderTraverse(BiTree T)               	//InOrderTravers() function
{  if(T)
     { 	if (InOrderTraverse(T->lchild))
	   {  cout<<T->data<<"  ";
	      if(InOrderTraverse(T->rchild))
		  return (OK);
	   }//end of if (InOrderTraverse(T->lchild))
	   return (ERROR);
     }//end of if(T)
   else
      return(OK);
}//end of Restore() function

int PostOrderTraverse(BiTree T)                //PostOrderTravers function
{  if(T)
   { if (PostOrderTraverse(T->lchild))
	    if(PostOrderTraverse(T->rchild))
	    { cout<<T->data<<"  ";
		  return (OK);
		}//end of if(PostOrderTraverse(T->rchild))
	return (ERROR);
   }//end of if(T)
   else
      return (OK);
}//end of PostOrderTravers function

void main()                                           //main() function
{
   char pstr[LENGTH]={'A','B','D','E','C','F','G'};
   char istr[LENGTH]={'D','B','E','A','C','G','F'};
   int n=LENGTH;
   BiTree T;
   cout<<"Restore.cpp"<<endl<<"==========="<<endl<<endl;
   if(T=Restore(pstr,istr,n))
   { cout<<"Success to construct the BiTree with the given PreOrder and InOrder serial!"<<endl<<endl;
	 cout<<"InOrderTraverse the BiTree:"<<endl<<"---------------------------"<<endl;
	 InOrderTraverse(T); 
	 cout<<endl<<endl<<"PostOrderTraverse the BiTree:"<<endl<<"----------------------------"<<endl;;
	 PostOrderTraverse(T);
     cout<<endl<<endl<<"...OK...!"<<endl;
   }//end of if
   getch();
}//end of main() function

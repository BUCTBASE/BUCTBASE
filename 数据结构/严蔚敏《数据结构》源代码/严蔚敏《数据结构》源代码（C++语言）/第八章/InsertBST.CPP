//InsertBST.cpp
//This function is to insert element into the gived BiTree
# include <malloc.h>
# include <iostream.h>
# include <conio.h>

# define OK 1
# define ERROR 0
typedef int KeyType;
typedef int TElemType;

typedef struct BiTNode				//define structure BiTree
{  TElemType data;
   struct BiTNode *lchild,*rchild;
}BiTNode, *BiTree;

int CreateBiTree(BiTree &T,int array[],int &i)	//createBiTree() function
{  TElemType ch;
   //cout<<"Pleae input data (0 for NULL node!) : ";
   //cin>>ch;
   ch=array[i];
   i++;
   if(ch==0)  T=NULL;
   else
   {  if(!(T=(BiTNode *)malloc(sizeof(BiTNode))))
      {  cout<<"Overflow!";		//no alloction
	 return (ERROR);
      }
      T->data=ch;
      CreateBiTree(T->lchild,array,i);	//create lchild
      CreateBiTree(T->rchild,array,i);  //create rchild
   }
   return (OK);
} //CreateBiTree() end

int PreOrderTraverse(BiTree T)	//PreOrderTraverse() sub-function
{  if(T)
     {  cout<<endl<<T->data;
	if (PreOrderTraverse(T->lchild))
	   if (PreOrderTraverse(T->rchild))
	   return (OK);
	return (ERROR);
     }
   else
      return (OK);
}

int SearchBST(BiTree T,KeyType key,BiTree f,BiTree &p) //SearchBST()
{  if(!T)
   {    p=f;
	return (ERROR);
   }
   else if(key==T->data)
	{  p=T;
	   return (OK);
	}
   else if(key<T->data)
	SearchBST(T->lchild,key,T,p);
   else
	SearchBST(T->rchild,key,T,p);
} //SearchBST() end

int InsertBST(BiTree &T,TElemType e)	//InsertBST() sub-function
{   BiTree p;
    if(!SearchBST(T,e,NULL,p))
    {  BiTree s;
       s=(BiTree)malloc(sizeof(BiTNode));
       s->data=e;
       s->lchild=NULL;
       s->rchild=NULL;
       if(!p)  		   T=s;
       else if(e<p->data)  p->lchild=s;
       else 		   p->rchild=s;
       return (OK);
    }
    else return(ERROR);
} //InsertBST() end

void main()				//main() function
{  BiTree T;
   int array[]={49,38,13,0,27,0,0,0,65,50,0,52,0,0,76,0,0};
   int i=0;
   cout<<endl<<endl<<"InsertBST.cpp";
   cout<<endl<<"============="<<endl;
   CreateBiTree(T,array,i);		//call CreateBiTree()
   cout<<endl<<"BiTree PreOrder :";
   PreOrderTraverse(T);
   TElemType e;
   cout<<endl<<endl<<"Please input the data to insert (eg,58): ";
   cin>>e;
   if(InsertBST(T,e))
       cout<<e<<" has been inserted to the BiTree !";
   else
       cout<<e<<" has existed and not been inserted to the BiTree !";
   cout<<endl<<endl<<"The new BiTree is as follows by PreOrderTraverse: ";
   PreOrderTraverse(T);			//call PreOrderTraverse()
   cout<<endl<<endl<<"...OK!...";
   getch();
} //main() end
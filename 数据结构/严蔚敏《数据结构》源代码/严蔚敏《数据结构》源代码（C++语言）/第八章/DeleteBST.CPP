//DeleteBST.cpp
# include <malloc.h>
# include <iostream.h>
# include <conio.h>

# define OK 1
# define ERROR 0
typedef int KeyType;
typedef int TElemType;

typedef struct BiTNode		//define structure BiTree
{  TElemType data;
   struct BiTNode *lchild,*rchild;
}BiTNode, *BiTree;

int CreateBiTree(BiTree &T,int array[],int &i)	//createBiTree() sub-function
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
}

int PreOrderTraverse(BiTree T)		//PreOrderTraverse() sub-function
{  if(T)
     {  cout<<endl<<T->data;
	if (PreOrderTraverse(T->lchild))
	   if (PreOrderTraverse(T->rchild))
	   return (OK);
	return (ERROR);
     }
   else
      return (OK);
} //PreOrderTraverse() end

int SearchBST(BiTree T,KeyType key,BiTree f,BiTree &p)	//SearchBSF()
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
}

int Delete(BiTree &p)		//Delete() sub-function
{  BiTree q,s;
   if(!p->data)
   {  q=p;
      p=p->lchild;
      free(q);
   }
   else if(!p->lchild)
   {  q=p;
      p=p->rchild;
      free(q);
   }
   else
   {  q=p;
      s=p->lchild;
      while(s->rchild)
      {  q=s;
	 s=s->rchild;
      }
   p->data=s->data;
   if(q!=p)  	q->rchild=s->lchild;
   else		q->lchild=s->rchild;
   }
}

int DeleteBST(BiTree &T,TElemType key)	//DeleteBST() sub-function
{  if(key!=49&&key!=38&&key!=13&&key!=27&&
	 key!=65&&key!=50&&key!=52&&key!=76)
       return (ERROR);
   else
   {  if(key==T->data)  	Delete(T);
      else if(key<T->data)	DeleteBST(T->lchild,key);
      else 	DeleteBST(T->rchild,key);
      return (OK);
   }
}

void main()				//main() function
{  BiTree T;
   int array[]={49,38,13,0,27,0,0,0,65,50,0,52,0,0,76,0,0};
   int i=0;
   TElemType key;
   cout<<endl<<endl<<"DeleteBST.cpp";
   cout<<endl<<"============="<<endl;
   CreateBiTree(T,array,i);		//call CreateBiTree()
   cout<<endl<<endl<<"The gived BiTree by PreOrder traverse is as follows:";
   PreOrderTraverse(T);
   cout<<endl<<endl<<"Please input the data to delete (eg,13): ";
   cin>>key;
   if(DeleteBST(T,key))
       cout<<key<<" has been deleted !";
   else
       cout<<key<<" doesn't existed !";
   cout<<endl<<endl<<"The new BiTree by PreOrder traverse is as follows: ";
   PreOrderTraverse(T);
   cout<<endl<<endl<<"...OK!...";
   getch();
}
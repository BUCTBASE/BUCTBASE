//SearchBST.cpp
//This function is to find element in the gived BiTree
# include <malloc.h>
# include <iostream.h>
# include <conio.h>
# include <stdio.h>

# define OK 1
# define ERROR 0
typedef int KeyType;
typedef int TElemType;
typedef struct BiTNode		//define structure BiTree
{  TElemType data;
   struct BiTNode *lchild,*rchild;
}BiTNode, *BiTree;

int CreateBiTree(BiTree &T,int array[],int &i)	//CreateBiTree() sub-function
{  TElemType ch;
   //cout<<"Pleae input data (0 for NULL node!) : ";
   //cin>>ch;
   ch=array[i];
   i++;
   if(ch==0)  T=NULL;
   else
   {  if(!(T=(BiTNode *)malloc(sizeof(BiTNode))))
      {  cout<<"Overflow!";	//no alloction
	 return (ERROR);
      }
      T->data=ch;
      CreateBiTree(T->lchild,array,i);	//create lchild
      CreateBiTree(T->rchild,array,i);  //create rchild
   }
   return (OK);
} //CreateBiTree() end

int PreOrderTraverse(BiTree T)	//PreOrderTraverse sub-function
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

int SearchBST(BiTree T,KeyType key,BiTree f,BiTree &p) //SearchBST() Sub-function
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

void main()			//main() function
{  BiTree T;
   int array[]={49,38,13,0,27,0,0,0,65,50,0,52,0,0,76,0,0};
   int i=0;
   cout<<endl<<endl<<"SearchBST.cpp";
   cout<<endl<<"=============";
   cout<<endl<<endl<<"The gived BiTree is as follows by PreOrderTraverse :";
   CreateBiTree(T,array,i);		//call CreateBiTree()
   PreOrderTraverse(T);
   BiTree f,p;
   KeyType key;
   cout<<endl<<endl<<"Please input the data to find (eg,27): ";
   scanf("%d",&key);
   if(SearchBST(T,key,f,p))             //call SearchBST()
      cout<<p->data<<" is found !";
   else
      cout<<key<<" isn't found !";
   cout<<endl<<endl<<"...OK!...";
   getch();
} //main() end
//InOrderTraverse.cpp
//This function is to Inorder BiTree
# include <malloc.h>
# include <iostream.h>
# include <conio.h>

# define OK 1
# define ERROR 0
typedef char TElemType;

typedef struct BiTNode		//define structureBiTree
{  TElemType data;
   struct BiTNode *lchild,*rchild;
}BiTNode, *BiTree;

int CreateBiTree(BiTree &T)	//createBiTree() sub-function
{  TElemType ch;
   cout<<"Please input data (/ for NULL node!) : ";
   cin>>ch;			//input data
   if(ch=='/')  T=NULL;
   else
   {  if(!(T=(BiTNode *)malloc(sizeof(BiTNode))))
      {  cout<<"Overflow!";	//no alloction
	 return (ERROR);
      }
      T->data=ch;
      CreateBiTree(T->lchild);	//create lchild
      CreateBiTree(T->rchild);  //create rchild
   }
   return (OK);
} //CreateBiTree() end

int InOrderTraverse(BiTree T)	//InOrderTraverse sub-function
{  if(T)
     { 	if (InOrderTraverse(T->lchild))		//traverse lchild
	   {  cout<<T->data<<"->";		//visite T
	      if(InOrderTraverse(T->rchild))	//traverse rchild
		 return (OK);
	   }
	return (ERROR);
     } //if end
   else
      return (OK);
} //InOrderTraverse() end

void main()				//main() function
{  BiTree T;
   cout<<endl<<endl<<"InOrderTraverse.cpp";
   cout<<endl<<"===================";
   cout<<endl<<endl<<"Please input data to create BiTree:"<<endl<<endl;
   CreateBiTree(T);			//call CreateBiTree()
   cout<<endl<<"InOrder :"<<endl<<endl<<"Begin->";
   InOrderTraverse(T);
   cout<<"End!";
   cout<<endl<<endl<<"...OK!...";
   getch();
} //main() end
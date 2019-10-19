//CreateBiTree.cpp
//This function is to create BiTree
# include <malloc.h>
# include <iostream.h>
# include <conio.h>

# define OK 1
# define ERROR 0
typedef char TElemType;

typedef struct BiTNode		//define stricture BiTree
{  TElemType data;
   struct BiTNode *lchild,*rchild;
}BiTNode, *BiTree;

int CreateBiTree(BiTree &T)	//createBiTree() sub-function
{  TElemType ch;
   cout<<"Please input data (/ for NULL node!) : ";
   cin>>ch;
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

void main()			//main() function
{  BiTree T;
   cout<<endl<<endl<<"CreateTree.cpp";
   cout<<endl<<"==============";
   cout<<endl<<endl<<"Please input data to create BiTree:"<<endl;
   if(CreateBiTree(T))		//call CreateBiTree
      cout<<endl<<"Create BiTree Success ! ";
   else
      cout<<endl<<"Create BiTree Failure ! ";
   cout<<endl<<endl<<"...OK!...";
   getch();
} //main() end
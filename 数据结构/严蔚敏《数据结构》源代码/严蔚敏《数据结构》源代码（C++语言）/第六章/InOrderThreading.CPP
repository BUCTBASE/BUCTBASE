//InOrderThreading.cpp
//This function is to InOrderTraverse BiThrTree
# include <malloc.h>
# include <iostream.h>
# include <conio.h>
# define OK 1
# define ERROR 0
typedef enum{Link,Thread} PointerTag;
typedef char TElemType;

typedef struct BiThrNode		//define structure BiTree
{  TElemType data;
   struct BiThrNode *lchild,*rchild;
   PointerTag ltag,rtag;
}BiThrNode, *BiThrTree;

int CreateBiThrTree(BiThrTree &T)	//sub-function
{  TElemType ch;
   cout<<"Please input data (/ for NULL node!) : ";
   cin>>ch;
   //ch=array[i];
   //cout<<ch<<"  ";
   //i++;
   if(ch=='/')  T=NULL;
   else
   {  if(!(T=(BiThrNode *)malloc(sizeof(BiThrNode))))
      {  cout<<"Overflow!";			//no alloction
	 return (ERROR);
      }
      T->data=ch;
      CreateBiThrTree(T->lchild);	//create lchild
      CreateBiThrTree(T->rchild);  	//create rchild
   }
   return (OK);
} //CreateBiTree() end

void InThreading(BiThrTree p,BiThrTree &pre)	//InThreading() sub-function
{   if(p)
    {  InThreading(p->lchild,pre);		//InThreading lchild
       if(!p->lchild)
       {  p->ltag=Link;
	  p->lchild=pre;
       }
       if(!pre->rchild)
       {  pre->rtag=Thread;
	  pre->rchild=p;
       }
    pre=p;
    InThreading(p->rchild,pre);			//InThreading rchild
    }
} //InThreading() end

int InOrderThreading(BiThrTree &Thrt,BiThrTree T)	//sub-function
{   BiThrTree pre;
    Thrt=(BiThrTree)malloc(sizeof(BiThrTree));	//allocate memory
    if(!Thrt)
       {   cout<<endl<<"Overflow!";
	   return (ERROR);
       }
    Thrt->ltag=Link;
    Thrt->rtag=Thread;
    Thrt->rchild=Thrt;
    if(!T)
      Thrt->lchild=Thrt;
    else
      {  Thrt->lchild=T;
	 pre=Thrt;
	 InThreading(T,pre);		//call InThreading()
	 pre->rchild=Thrt;
	 pre->rtag=Thread;
	 Thrt->rchild=pre;
      }
    return (OK);
} //InOrderThreadng() end

void main()			//main() function
{  BiThrTree Thrt,T;
   cout<<endl<<endl<<"InOrderThreading.cpp";
   cout<<endl<<"====================";
   cout<<endl<<endl<<"Please input data to create BiThrTree :"<<endl;
   CreateBiThrTree(T);		//call CreateBiTree()
   if(InOrderThreading(Thrt,T)) //call InOrderThreading()
      cout<<endl<<"InOrderThreading Success !!";
   cout<<endl<<endl<<"...OK!...";
   getch();
} //main() end
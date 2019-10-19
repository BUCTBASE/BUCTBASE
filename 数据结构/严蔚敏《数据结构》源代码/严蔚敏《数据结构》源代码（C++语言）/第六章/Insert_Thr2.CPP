//Insert-Thr.cpp
//This function is to insert a element into the BiThrTree
# include <malloc.h>
# include <iostream.h>
# include <conio.h>
# define OK 1
# define ERROR 0
typedef enum{Link,Thread} PointerTag;
typedef char TElemType;

typedef struct BiThrNode		//define structure BiThrTree
{  TElemType data;
   struct BiThrNode *lchild,*rchild;
   PointerTag ltag,rtag;
}BiThrNode, *BiThrTree;

int CreateBiThrTree(BiThrTree &T)	//CreateBiTree() sub-function
{  TElemType ch;
   cout<<"Pleae input data (/ for NULL node!) : ";
   cin>>ch;
   if(ch=='/')  T=NULL;
   else
   {  if(!(T=(BiThrNode *)malloc(sizeof(BiThrNode))))
      {  cout<<"Overflow!";		//no alloction
	 return (ERROR);
      }
      T->data=ch;
      CreateBiThrTree(T->lchild);	//create lchild
      CreateBiThrTree(T->rchild);  	//create rchild
   }
   return (OK);
} //CreateBiThrTree() end

void InThreading(BiThrTree p)		//InThreading() sub-function
{   BiThrTree pre;
    if(p)
    {  InThreading(p->lchild);		//InThreading lchild
       if(!p->lchild)
       {  p->ltag=Thread;
	  p->lchild=pre;
       }
       if(!pre->rchild)
       {  pre->rtag=Thread;
	  pre->rchild=p;
       }
    pre=p;
    InThreading(p->rchild);		//InThreading rchild
    }
} //InThreading() end

int InOrderThreading(BiThrTree &Thrt,BiThrTree T)  //sub-function
{   BiThrTree pre;
    Thrt=(BiThrTree)malloc(sizeof(BiThrTree)); 	//allocate memory
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
	 InThreading(T);
	 pre->rchild=Thrt;
	 pre->rtag=Thread;
	 Thrt->rchild=pre;
      }
    return (OK);
} //InOrderThreading() end

int Prior_Thr(BiThrTree t,BiThrTree Thrt,BiThrTree &p) 	//sub-function
{  p=t->lchild;
   if(p==Thrt)
   {  cout<<endl<<"Error!";
      return (ERROR);
   }
   if(t->ltag==Link)
   {  while(p->rtag==Link)
	 p=p->rchild;
   }
   return (OK);
} //Prior_Thr() end

int Insert_Thr(BiThrTree Thrt,BiThrTree t,TElemType e) 	//Insert_Thr() sub-function
{   BiThrTree q;
    q=(BiThrTree)malloc(sizeof(BiThrNode));
    if(!q)
    {  cout<<endl<<"Overflow!";
       return (ERROR);
    }
    q->data=e;
    q->lchild=t->lchild;
    q->rtag=t->ltag;
    q->rchild=t;
    q->rtag=Thread;
    t->lchild=q;
    t->ltag=Link;
    if(q->ltag==Link)
    {  BiThrTree p;
       Prior_Thr(q,Thrt,p);
       p->rchild=q;
    }
    return (OK);
} //Insert_Thr() end

void main()			//main() function
{  BiThrTree Thrt,T;
   BiThrTree t;
   TElemType e;
   cout<<endl<<endl<<"Insert_Thr.cpp";
   cout<<endl<<"=============="<<endl<<endl;
   if(CreateBiThrTree(T)) 	//call CreateBiTree
      cout<<endl<<"Create BiThrNode Success! ";
   else
      cout<<"Create BiThrNode Failure! ";
   if(InOrderThreading(Thrt,T))	//call InOrderThreading()
      cout<<endl<<"InOrderThreading Success!";
   cout<<endl<<"Please input the data to insert : ";
   cin>>e;
   if(Insert_Thr(Thrt,t,e))	//call Insert_Thr()
      cout<<endl<<"Insert success!";
   cout<<endl<<endl<<"...OK!...";
   getch();
} //main() end
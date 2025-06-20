//InOrderTraverse.cpp
//This function is to InOrder BiTree
# include <malloc.h>
# include <iostream.h>
# include <conio.h>

# define STACK_INIT_SIZE 100
# define STACKINCREMENT 10
# define OK 1
# define ERROR 0
typedef int SElemType ;
typedef char TElemType;

typedef struct SqStack  	//define structure SqStack
{    SElemType *base;
     SElemType *top;
     int stacksize;
}SqStack;

typedef struct BiTNode		//define structure BiTree
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

int InitStack(SqStack &S)	//InitStack() sub-function
{   S.base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    if(!S.base)
    {    cout<<endl<<"Allocate space failure !";
	 return (ERROR);
    }
    S.top=S.base;
    S.stacksize=STACK_INIT_SIZE;
    return (OK);
} //InitStack() end

int Push(SqStack &S,SElemType e)	//Push() sub-function
{   if(S.top-S.base>S.stacksize)
    {    S.base=(SElemType *)realloc(S.base,(S.stacksize+
		       STACKINCREMENT*sizeof(SElemType)));
	 if(!S.base)
	 {   cout<<endl<<"Overflow!";
	     return (ERROR);
	 }
	 S.top=S.base+S.stacksize;
	 S.stacksize+=STACKINCREMENT;
    }
    *S.top++=e;
    return (OK);
} //Push() end

int Pop(SqStack &S,SElemType &e)	//Pop() sub-function
{    if(S.top==S.base)
     {    cout<<endl<<"It's a empty SqStack!";
	  return (ERROR);
     }
     e=*--S.top;
     return (OK);
} //Pop() end

int StackEmpty(SqStack S)	//StackEmpty() sub-function
{  if(S.top==S.base)
      return (OK);
   else
      return (ERROR);
} //StackEmpty() end

int InOrderTraverse(BiTree T)	//InOrderTraverse sub-function
{   SqStack S;
    InitStack(S);		//call InitStack()
    BiTree p;
    p=T;
    while(p||!StackEmpty(S))
    {  if(p)
	  {  Push(S,int(p)); 	//call Push()
	     p=p->lchild;
	  }
       else
	  {  Pop(S,int(p));	//call Pop()
	     cout<<p->data<<"->";    	//visit p Node
	     p=p->rchild;
	  }
    }
    return (OK);
} //InOrderTraverse() end

void main()			//main() function
{  BiTree T;
   cout<<endl<<endl<<"InOrderTraverse.cpp";
   cout<<endl<<"==================="<<endl;
   cout<<endl<<"Please input data to create BiTree:"<<endl;
   CreateBiTree(T);		//call CreateBiTree()
   cout<<endl<<"InOrder :"<<endl<<endl<<"Begin->";
   InOrderTraverse(T);		//Call InOrderTraverse()
   cout<<"End !"<<endl<<endl<<"...OK!...";
   getch();
} //main() end
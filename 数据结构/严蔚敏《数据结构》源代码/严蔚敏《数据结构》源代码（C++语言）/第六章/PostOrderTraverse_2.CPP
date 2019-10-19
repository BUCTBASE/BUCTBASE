//PostOrderTraverse.cpp
//This function is to PostOrder BiTree
# include <malloc.h>
# include <iostream.h>
# include <conio.h>

# define STACK_INIT_SIZE 100
# define STACKINCREMENT 10
# define OK 1
# define ERROR 0
typedef char TElemType;

typedef struct BiTNode		//define structure BiTree
{  TElemType data;
   struct BiTNode *lchild,*rchild;
}BiTNode, *BiTree;

typedef struct Data       	//define structure Data
{  BiTNode *p;
   int tag;
}Data,SElemType;

typedef struct SqStack  	//define structure SqStack
{    SElemType *base;
     SElemType *top;
     int stacksize;
}SqStack;

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

int StackEmpty(SqStack S)		//StackEmpty() sub-function
{  if(S.top==S.base)
      return (OK);
   else
      return (ERROR);
} //StackEmpty() end

int PostOrderTraverse(BiTree T)		//PostOrderTraverse sub-function
{   SqStack S;
    InitStack(S);			//call Initstack()
    Data Data1;
    Data1.p=T;
    do
    {  if(Data1.p)
	  {  Data1.tag=0;
	     Push(S,Data1);             //call Push()
	     Data1.p=Data1.p->lchild;
	  }
       else
	  {  Pop(S,Data1);		//call Pop()
	     if(Data1.tag==0)
	     {  Data1.tag=1;
		Push(S,Data1);
		Data1.p=Data1.p->rchild;
	     }
	     else
	     {  cout<<Data1.p->data<<"->";    	//visit p Node
		Data1.p=NULL;
	     }
	  }
    }while(Data1.p||!StackEmpty(S));
    return (OK);
} //PostOrderTraverse() end

void main()				//main() function
{  BiTree T;
   cout<<endl<<endl<<"PostOrderTraverse.cpp";
   cout<<endl<<"=====================";
   cout<<endl<<endl<<"Please input data to create BiTree:"<<endl;
   CreateBiTree(T);			//call CreateBiTree()
   cout<<endl<<"PostOrder :"<<endl<<endl<<"Begin->";
   PostOrderTraverse(T);		//Call PostOrderTraverse()
   cout<<"End !"<<endl<<endl<<"...OK!...";
   getch();
} //main() end
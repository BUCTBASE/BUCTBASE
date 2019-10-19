//Build.cpp
//This function is to create a BiTree according string
# include <malloc.h>
# include <iostream.h>
# include <conio.h>

# define MAX_LENGTH 100
typedef char TElemType;

typedef struct BiTNode		//define stucture BiTree
{  TElemType data;
   struct BiTNode *lchild,*rchild;
}BiTNode, *BiTree;

BiTNode *Build(char *str,int i,int n)	//Build() sub-function
{   if(i>n)
	return (NULL);
    BiTree p;
    p=(BiTNode *)malloc(sizeof(BiTNode));
    p->data=str[i];
    cout<<endl<<"Node["<<i<<"].data="<<p->data;
    p->lchild=Build(str,2*i,n);
    p->rchild=Build(str,2*i+1,n);
    return (p);
} //Build() end

void main()			//main() function
{  char str[MAX_LENGTH];
   int i=1;
   int n;
   cout<<endl<<endl<<"Build.cpp";
   cout<<endl<<"=========";
   cout<<endl<<endl<<"Please input the length of string (eg,5): ";
   cin>>n;
   for(i=1;i<=n;++i)
   { cout<<"Please input the "<<i<<"th letter:";
     cin>>str[i];
   }
   cout<<endl<<"str[]=";
   for(i=1;i<=n;i++)
       cout<<str[i];
   i=1;
   cout<<endl<<endl<<"The BiTree is created in following order :"<<endl;
   if(Build(str,i,n))		//call Build()
     cout<<endl<<endl<<"...OK!...";
   getch();
} //main() end

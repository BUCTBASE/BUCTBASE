//TopologicalSort.cpp

# include <iostream.h>
# include <malloc.h>
# include <conio.h>
# include <stdio.h>

# define MAX_VERTEX_NUM 20
# define ERROR 0
# define OK 1
# define YES 1
# define NO 0
# define STACK_INIT_SIZE 100
# define STACKINCREMENT 10
# define  SElemType int

typedef int VertexType;
typedef int InfoType;
typedef struct ArcNode
{  int adjvex;
   struct ArcNode *nextarc;
   InfoType *info;
}ArcNode;

typedef struct 
{  VertexType data;
   ArcNode *firstarc;
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct
{  AdjList vertices;
   int vexnum,arcnum;
   int kind;
}ALGraph;

typedef struct 
{    SElemType *base;
     SElemType *top;
     int stacksize;
}SqStack;

int InitStack(SqStack &S)                      //InitStack() function
{   S.base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    if(!S.base)
    {    cout<<endl<<"Allocate space failure !";
	     return(ERROR);
    }
    S.top=S.base;
    S.stacksize=STACK_INIT_SIZE;
    return(OK);
}//end of InitStack() funtion

int Push(SqStack &S,SElemType e)	            //Push() function 
{   if(S.top-S.base>S.stacksize)
    {    S.base=(SElemType *)realloc(S.base,(S.stacksize+
		       STACKINCREMENT*sizeof(SElemType)));
	 if(!S.base)
	 {   cout<<endl<<"Overflow!";
	     return(ERROR);
	 }//end of if(!S.base)
	 S.top=S.base+S.stacksize;
	 S.stacksize+=STACKINCREMENT;
    }//end of if
    *S.top++=e;
    return(OK);
}//end of Push() function

int Pop(SqStack &S,SElemType &e)	            //Pop() function
{    if(S.top==S.base)
     {    cout<<endl<<"It's a empty SqStack!";
	  return(ERROR);
     }
     e=*--S.top;
     return(OK);
}//end of Pop() function

int StackEmpty(SqStack S)                       //StackEmpty() function      
{//judge Stack S is empty or not
	if(S.top==S.base) return (YES);
	else return(NO);
}//end of StackEmpty

int CreateDG(ALGraph &G)                        //CreateDG() function
{  int IncInfo,i,j,k,Vi,Vj;
   ArcNode *p;
   cout<<"Please input the number of G.vexnum: (eg. G.vexnum=4)   ";
   cin>>G.vexnum;
   cout<<"Please input the number of G.arcnum: (eg. G.arcnum=4)   ";
   cin>>G.arcnum;
   cout<<"Please input the number of IncInfo(0 for none):   ";
   cin>>IncInfo;
   for(i=0;i<G.vexnum;++i)
       { G.vertices[i].data=i;
	     G.vertices[i].firstarc=NULL;
       }//end of for
   cout<<endl<<"For example (Vi->Vj): Vi=1,Vj=2; Vi=1,Vj=3; Vi=3,Vj=4; Vi=1,Vj=4 ...";
   for(k=0;k<G.arcnum;++k)
   {  
	  cout<<endl<<"Please input the "<<k+1<<"th arc's Vi:   ";        
      cin>>Vi;
      cout<<"Please input the "<<k+1<<"th arc's Vj:   ";
      cin>>Vj;
      i=Vi;
      j=Vj;
      while(i<1||i>G.vexnum||j<1||j>G.vexnum)
       {  cout<<endl<<"Please input the "<<k+2<<"the arc's Vi:   ";
	  cin>>Vi;
	  cout<<"Please input the "<<k+2<<"the arc's Vj:   ";
	  cin>>Vj;
	  i=Vi;
	  j=Vj;
       }//end of while
	  i=i-1;
      j=j-1;
       p=(ArcNode *)malloc(sizeof(ArcNode));
       if(!p)
       {  cout<<"Overflow!";
	      return (ERROR);
       }//end of if(!p)
       p->adjvex=j;
       p->nextarc=G.vertices[i].firstarc;
       p->info=NULL;
       G.vertices[i].firstarc=p;
       if(IncInfo)
	  {  cout<<"Please input the info :";
	     cin>>*(p->info);
	  }//end of if(IncInfo)
   }//end of if
   return (OK);
}//end of CreateDG() function

void FindInDegree(ALGraph G,int *indegree)       //FindInDegree() function
{//indegree is a array name 
   int i;
   for(i=0;i<G.vexnum;i++)
	   indegree[i]=0;
   for(i=0;i<G.vexnum;i++)
       while(G.vertices[i].firstarc)
	   {  indegree[G.vertices[i].firstarc->adjvex]++;
	      G.vertices[i].firstarc=G.vertices[i].firstarc->nextarc;
	   } //end of while 
}//end of FindInDegree() function

int ToplogicalSort(ALGraph G)                    //ToplogicalSort() function
{
	int indegree[MAX_VERTEX_NUM],i,k,count;
	ArcNode *p;
	SqStack S;
	FindInDegree(G,indegree);                    //Find indegree of node[0...vexnum-1]
	InitStack(S);
	for(i=0;i<G.vexnum;++i)                      //create Stack S for 0 indegree node
		 if(!indegree[i]) Push(S,i);
	count=0;
	printf("The Sorted node are:  ");
	while(!StackEmpty(S))
	{   Pop(S,i);
	    printf(" %d ",G.vertices[i].data+1);     //output the i node  
		++count;
		for(p=G.vertices[i].firstarc;p;p=p->nextarc)
		{  k=p->adjvex;
		   if(!(--indegree[k]))  Push(S,k);
		}//end of for
	}//end of while
	if (count<G.vexnum)  return (ERROR);
	else return (OK);
}//end of ToptlogicalSort() function

void main()                                      //main() function
{  ALGraph G;
   cout<<"ToplogicalSort.cpp"<<endl<<"=================="<<endl<<endl;
   if(CreateDG(G))
      cout<<endl<<"Create ALGraph success !"<<endl;
   if(ToplogicalSort(G)) cout<<endl<<"...OK!..."<<endl;
   else cout<<endl<<"Error,it has loop!"<<endl;
   getch();
}//end of main() function
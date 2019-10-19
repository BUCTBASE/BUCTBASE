//CriticalPath.cpp

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
   InfoType info; 
}ArcNode;

typedef struct VNode
{  VertexType data;
   ArcNode *firstarc;
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct
{  AdjList vertices;
   int vexnum,arcnum;
   int kind;
}ALGraph;

typedef struct SqStack
{    SElemType *base;
     SElemType *top;
     int stacksize;
}SqStack;

int ve[MAX_VERTEX_NUM];    //the earlyest time array
int vl[MAX_VERTEX_NUM];    //the lastest time array

int InitStack(SqStack &S)                               //InitStack() function
{   S.base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
    if(!S.base)
    {    cout<<endl<<"Allocate space failure !";
	     return(ERROR);
    }
    S.top=S.base;
    S.stacksize=STACK_INIT_SIZE;
    return(OK);
}//end of InitStack() function

int Push(SqStack &S,SElemType e)	                    //Push() function
{   if(S.top-S.base>S.stacksize)
    {    S.base=(SElemType *)realloc(S.base,(S.stacksize+
		       STACKINCREMENT*sizeof(SElemType)));
	 if(!S.base)
	 {   cout<<endl<<"Overflow!";
	     return(ERROR);
	 }
	 S.top=S.base+S.stacksize;
	 S.stacksize+=STACKINCREMENT;
    }
    *S.top++=e;
    return(OK);
}//end of Push() function

int Pop(SqStack &S,SElemType &e)	                    //Pop() function
{    if(S.top==S.base)
     {    cout<<endl<<"It's a empty SqStack!";
	  return(ERROR);
     }
     e=*--S.top;
     return(OK);
}//end of Pop() function

int StackEmpty(SqStack S)                               //StackEmpty() function 
{//Judge Stack S is empty
	if(S.top==S.base) return (YES);
	else return(NO);
}//end of StackEmpty

int CreateDG(ALGraph &G)                                //CreateDG() function
{  int i,j,k,Vi,Vj;
   ArcNode *p;
   cout<<"Please input the number of G.vexnum: (eg. G.vexnum=6)   ";
   cin>>G.vexnum;
   cout<<"Please input the number of G.arcnum: (eg. G.arcnum=8)   ";
   cin>>G.arcnum;

   for(i=0;i<G.vexnum;++i)
       { G.vertices[i].data=i;
	     G.vertices[i].firstarc=NULL;
       }
   cout<<endl<<"For example (Vi->Vj): "<<endl
	   <<"Vi=1,Vj=2,Weight=3; Vi=1,Vj=3,Weight=2; Vi=2,Vj=4,Weight=2; Vi=2,Vj=5,Weight=3"<<endl 
	   <<"Vi=3,Vj=4,Weight=4; Vi=3,Vj=6,Weight=3; Vi=4,Vj=6,Weight=2; Vi=5,Vj=6,Weight=1"<<endl
	   <<"....."<<endl;
       
   for(k=0;k<G.arcnum;++k)
   {  
	  cout<<endl<<"Please input the "<<k+1<<"th arc's Vi: ";        
      cin>>Vi;
      cout<<"Please input the "<<k+1<<"th arc's Vj: ";
      cin>>Vj;
      i=Vi;
      j=Vj;
      while(i<1||i>G.vexnum||j<1||j>G.vexnum)
       {  cout<<endl<<"Please input the "<<k+2<<"the arc's Vi: ";
	  cin>>Vi;
	  cout<<"Please input the "<<k+2<<"the arc's Vj: ";
	  cin>>Vj;
	  i=Vi;
	  j=Vj;
       }
	  i=i-1;
      j=j-1;
       p=(ArcNode *)malloc(sizeof(ArcNode));
       if(!p)
       {  cout<<"Overflow!";
	      return (ERROR);
       }
       p->adjvex=j;
       p->nextarc=G.vertices[i].firstarc;
       p->info=NULL;
       G.vertices[i].firstarc=p;
	   printf("Please input the weight of Vi->Vj: ");
	   scanf("%d",&(p->info));
   }
   return (OK);
}//end of CreateDG() function

void FindInDegree(ALGraph G,int *indegree)              //FindeInDegree() function
{                                                       //indegree is a array name 
   int i;
   for(i=0;i<G.vexnum;i++)
	   indegree[i]=0;
   for(i=0;i<G.vexnum;i++)
       while(G.vertices[i].firstarc)
	   {  indegree[G.vertices[i].firstarc->adjvex]++;
	      G.vertices[i].firstarc=G.vertices[i].firstarc->nextarc;
	   } //end of while 
}//end of FindInDegree() function

int TopologicalOrder(ALGraph G,SqStack &T)           //TopologicalOrder() function
{
	int indegree[MAX_VERTEX_NUM];
	int i,count,j,k;
	ArcNode *p;
	SqStack S;
	FindInDegree(G,indegree);
    InitStack(S);
	for(i=0;i<G.vexnum;++i)
		if(!indegree[i]) Push(S,i);
	InitStack(T);
	count=0;
    for(i=0;i<=G.vexnum-1;i++)                        //ve[0...vexnum-1]=0
		ve[i]=0;
	while(!StackEmpty(S))
	{  Pop(S,j);
	   Push(T,j);
	   ++count;
	   for(p=G.vertices[j].firstarc; p; p=p->nextarc)
	   {   k=p->adjvex;
	       if(!(--indegree[k]))
			   Push(S,k);
           if(ve[j]+p->info>ve[k]) 
			   ve[k]=ve[j]+p->info;
	   }//end of for
	 }//end of while
	if(count<G.vexnum) return(ERROR) ;
	else return(OK);
}//end of ToptlogicalOrder() function

int CriticalPath(ALGraph G)
{
	int i,j,k,dut;   //activity during time
	int ee,el;       //ee:the earlyest beginning time   el:the lastest beginning time	 
	char tag;
	ArcNode *p;
	SqStack T;        
	if(!TopologicalOrder(G,T))
	    return(ERROR);
	for(i=0;i<=G.vexnum-1;i++)
		vl[i]=ve[G.vexnum-1];                        //Initialize the lastest time
	
	while(!StackEmpty(T))
	{ for(Pop(T,j),p=G.vertices[j].firstarc; p; p=p->nextarc)
		{  k=p->adjvex;
		   dut=p->info;   
		   if(vl[k]-dut<vl[j])   vl[j]=vl[k]-dut;   //modify 
		}//end of for
	}//end of while
	    for(j=0;j<G.vexnum;++j)
			for(p=G.vertices[j].firstarc; p; p=p->nextarc)
			{  k=p->adjvex;
			   dut=p->info;
			   ee=ve[j];
			   el=vl[k]-dut;
			   tag=(ee==el)?'*':' ';
			   printf("Path V%d->V%d: DuringTime=%d,  The ee Time=%d,  The el Time=%d  %c \n",j+1,k+1,dut,ee,el,tag);
			}//end of for(p=G.vertices[j].firstarc...)
		 printf("-------------------------------------------------------\n");
		 printf("The Critical Path is show as \"*\"\n");
	     return (OK);
}//end of CriticalPath() function

void main()
{  ALGraph G;
   cout<<"CriticalPath.cpp"<<endl<<"================"<<endl<<endl;
   if(CreateDG(G))
      cout<<endl<<"Create ALGraph success !"<<endl;
   if(CriticalPath(G))  cout<<endl<<"...OK!..."<<endl;
   else cout<<endl<<"Error,it has loop!"<<endl;
   getch();
} 
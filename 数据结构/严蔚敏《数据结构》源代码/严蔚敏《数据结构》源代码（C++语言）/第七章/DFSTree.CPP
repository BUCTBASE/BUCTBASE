//DFSTree.cpp
//This function is to create a Mini DFSTree
# include <iostream.h>
# include <malloc.h>
# include <conio.h>

# define MAX_VERTEX_NUM 20
# define TRUE 1
# define FALSE 0
# define OK 1
typedef int VertexType;
typedef int InfoType;
typedef int ElemType;

typedef struct ArcNode		//define structure ALGgraph
{  int adjvex;
   struct ArcNode *nextarc;
   InfoType *info;
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

typedef struct CSNode		//define structure CSNode
{   ElemType data;
    struct CSNode *firstchild,*nextsibling;
}CSNode,*CSTree;

int CreateDG(ALGraph &G)	//CreateDG() sub-function
{  int IncInfo,i,j,k,v1,v2,w;
   cout<<endl<<"Please input the number of G.vexnum (eg. G.vexnum=4): ";
   cin>>G.vexnum;		//input the number of vex
   cout<<"Please input the number of G.arcnum (eg. G.arcnum=4): ";
   cin>>G.arcnum;		//input the number of arc
   cout<<"Please input the number of IncInfo (0 for none) :     ";
   cin>>IncInfo;
   for(i=0;i<G.vexnum;++i)	//initial G.vertices
       {  G.vertices[i].data=i;
	  G.vertices[i].firstarc=NULL;
       }
   cout<<"Plese input arc(V1-->V2), For example: (V1=1,V2=3),(V1=2,V2=4)...";
   for(k=0;k<G.arcnum;++k)	//input arc(v1,v2)
   {  cout<<endl<<"Please input the "<<k+1<<"th arc's v1 (0<v1<G.vexnum): ";
      cin>>v1;
      cout<<"Please input the "<<k+1<<"th arc's v2 (0<v2<G.vexnum): ";
      cin>>v2;
      i=v1;
      j=v2;
      while(i<1||i>G.vexnum||j<1||j>G.vexnum)	//if (v1,v2) illegal, again
       {  cout<<endl<<"Please input the "<<k+1<<"th arc's v1 (0<v1<G.vexnum) : ";
	  cin>>v1;
	  cout<<"Please input the "<<k+1<<"th arc's v2 (0<v2<G.vexnum): ";
	  cin>>v2;
	  i=v1;
	  j=v2;
       }
       i--;
       j--;
       ArcNode *p;
       p=(ArcNode *)malloc(sizeof(ArcNode));	//allocate memory
       if(!p)
       {  cout<<"Overflow!";
	  return (0);
       }
       p->adjvex=j;			//assign p
       p->nextarc=G.vertices[i].firstarc;
       p->info=NULL;
       G.vertices[i].firstarc=p;
       if(IncInfo)
	  {  cout<<"Please input the info :";
	     cin>>*(p->info);		//input information
	  } //if end
   } //for end
   return (OK);
} //CreateDG() end

void DFSTree(ALGraph G,int v,CSTree &T,int *visited,int first)
{    int w;
     CSTree p,q;
     visited[v]=TRUE;
     cout<<endl<<"Create Node "<<v+1;
     for(   w=G.vertices[v].data;
	    G.vertices[v].firstarc!=NULL;
	    w=G.vertices[v].firstarc->adjvex,
	    G.vertices[v].firstarc=G.vertices[v].firstarc->nextarc)
       if(!visited[w]) 		//new CSNode
	  {  p=(CSTree)malloc(sizeof(CSNode));
	     p->data=w;
	     p->firstchild=NULL;
	     p->nextsibling=NULL;
	    if(first)
	    {    T->firstchild=p;
		 first=FALSE;
	    } //if end
	    else
		q->nextsibling=p;
	    q=p;
	    DFSTree(G,w,q,visited,first);	//call DFSTree()
	 } //if end
} //DFSTree() end

void main()		//main() function
{  ALGraph G;
   int first=TRUE;
   CSTree T;
   int visited[MAX_VERTEX_NUM],v;
   cout<<endl<<endl<<"DFSTree.cpp";
   cout<<endl<<"==========="<<endl;
   if(CreateDG(G))	//call CreateDG()
      cout<<endl<<"Create ALGraph success !";
   for(v=0;v<G.vexnum;++v)
      visited[v]=0;	//initial visited[]
   getch();
   cout<<endl<<endl<<"Create MiniSpanTree as follows:"<<endl;
   for(v=0;v<G.vexnum;++v)
      if(!visited[v])
	DFSTree(G,v,T,visited,first);	//call DFSTree()
   cout<<endl<<endl<<"...OK!...";
   getch();
} //main() end
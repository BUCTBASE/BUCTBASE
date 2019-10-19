//DFSTraverse.cpp
//This function is to traver ALGraph by DFS Algorithm
# include <iostream.h>
# include <malloc.h>
# include <conio.h>

# define MAX_VERTEX_NUM 20
# define OK 1
typedef int VertexType;
typedef int InfoType;

typedef struct ArcNode		//define structure ALGraph
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

int CreateDG(ALGraph &G)	//CreateDG() sub-fuction
{  int IncInfo,i,j,k,v1,v2,w;
   cout<<endl<<"Please input the number of G.vexnum (eg. G.vexnum=4): ";
   cin>>G.vexnum;		//input the number of vex
   cout<<"Please input the number of G.arcnum (eg. G.arcnum=4): ";
   cin>>G.arcnum;		//input the number of arc
   cout<<"Please input the number of IncInfo (0 for none)     : ";
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
      while(i<1||i>G.vexnum||j<1||j>G.vexnum)	//if (v1,v2) illegal,again
       {  cout<<endl<<"Please input the "<<k+1<<"th arc's v1 (0<v1<G.vexnum) : ";
	  cin>>v1;
	  cout<<"Please input the "<<k+1<<"th arc's v2 (0<v2<G.vexnum): ";
	  cin>>v2;
	  i=v1;
	  j=v2;
       } //while end
       i--;
       j--;
       ArcNode *p;
       p=(ArcNode *)malloc(sizeof(ArcNode));	//allocate memory
       if(!p)
       {  cout<<"Overflow!";		//if overflow
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

void DFS(ALGraph G,int v,int *visited)	//DFS() sub-fuction
{  int w;
   visited[v]=1;
   cout<<v+1<<"->";
   for(w=G.vertices[v].data;
	 G.vertices[v].firstarc!=NULL;
	  w=G.vertices[v].firstarc->adjvex,
       G.vertices[v].firstarc=G.vertices[v].firstarc->nextarc)

     if(visited[w]==0)
	 DFS(G,w,visited);		//call DFS()
} //DFS() end

void DFSTraverse(ALGraph G)	//DFSTraverse() sub-function
{  int v;
   int visited[MAX_VERTEX_NUM];
   for(v=0;v<G.vexnum;++v)
      visited[v]=0;		//initial visited[v]
   for(v=0;v<G.vexnum;++v)
     if(visited[v]==0)
	DFS(G,v,visited);	//call DFS()
} //DFSTraverse() end

void main()			//main() function
{  ALGraph G;
   cout<<endl<<endl<<"DFSTraverse.cpp";
   cout<<endl<<"==============="<<endl;
   CreateDG(G);			//call CreateDG()
   cout<<"DFS Traverse is as follows :";
   cout<<endl<<endl<<"Begin->";
   DFSTraverse(G);		//call DFSTraverse()
   cout<<"End !"<<endl<<endl<<"...OK!...";
   getch();
} //main() end
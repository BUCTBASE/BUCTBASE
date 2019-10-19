//BFSTraverse.cpp
//This function is to traverse ALGraph by BFS Algorithm
# include <iostream.h>
# include <malloc.h>
# include <conio.h>

# define MAX_VERTEX_NUM 20
# define MAXQSIZE 100
# define OK 1
typedef int VertexType;
typedef int QElemType;
typedef int InfoType;

typedef struct ArcNode
{  int adjvex;
   struct ArcNode *nextarc;
   InfoType *info;
}ArcNode;

typedef struct VNode		//define structure ALGraph
{  VertexType data;
   ArcNode *firstarc;
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct
{  AdjList vertices;
   int vexnum,arcnum;
   int kind;
}ALGraph;

typedef struct SqQueue		//define structure SqQueue
{    QElemType *base;
     int front;
     int rear;
}SqQueue;

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
   cout<<"Plese input arc(V1-->V2), For example: (V1=1,V2=3),(V1=2,V2=4)..."<<endl;
   for(k=0;k<G.arcnum;++k)	//input arc(v1,v2)
   {  cout<<endl<<"Please input the "<<k+1<<"th arc's v1 (0<v1<G.vexnum): ";
      cin>>v1;
      cout<<"Please input the "<<k+1<<"th arc's v2 (0<v2<G.vexnum): ";
      cin>>v2;
      i=v1;
      j=v2;
      while(i<1||i>G.vexnum||j<1||j>G.vexnum) //if (v1,v2) illegal, again
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
       p->adjvex=j;				//assign p
       p->nextarc=G.vertices[i].firstarc;
       p->info=NULL;
       G.vertices[i].firstarc=p;
       if(IncInfo)
	  {  cout<<"Please input the info :";
	     cin>>*(p->info);			//input information
	  } //if end
   } //for end
   return (OK);
} //CreateDG() end

int InitQueue(SqQueue &Q)	//InitQueue() sub-function
{   Q.base=(QElemType *)malloc(MAXQSIZE*sizeof(QElemType));
    if(!Q.base)			//allocate memory
    {   cout<<endl<<"Overflow ! ";	//if overflow
	return 0;
    }
    Q.front=Q.rear=0;		//assign Q.front=Q.rear=0
    return (OK);
} //InitQueue() end

int EnQueue(SqQueue &Q,QElemType e)	//EnQueue() sub-function
{   if((Q.rear+1)%MAXQSIZE==Q.front)	//if full
    {   cout<<"Errer ! The SqQeueu is full ! ";
	return 0;
    }
    Q.base[Q.rear]=e;
    Q.rear=(Q.rear+1)%MAXQSIZE;
    return (OK);
} //EnQueue() end

int QueueEmpty(SqQueue Q)	//QueueEmpty sub-function
{  if(Q.front==Q.rear)
      return (OK);
   else
      return (0);
} //QueueEmpty() end

int DeQueue(SqQueue &Q,QElemType &e)	//DeQueue() sub-function
{  if(Q.front==Q.rear)		//empty queue
   {    cout<<endl<<"Errer !  It's empty!";
	return 0;
   }
   e=Q.base[Q.front];
   Q.front=(Q.front+1)%MAXQSIZE;
   return (e);
} //DeQueue() end

void BFSTraverse(ALGraph G)	//BFSTraverse() sub-function
{  int v,w,u;
   int visited[MAX_VERTEX_NUM];
   SqQueue Q;
   for(v=0;v<G.vexnum;++v)
      visited[v]=0;		//initial visited[]
   InitQueue(Q);		//call InitQueue()
   for(v=0;v<G.vexnum;++v)
     if(visited[v]==0)
     {  visited[v]=1;
	cout<<v+1<<"-->";
	EnQueue(Q,v);			//call EnQueue()
	while(!QueueEmpty(Q))
	{    DeQueue(Q,u);		//call DeQueue()
	      for(w=G.vertices[u].data;
		  G.vertices[u].firstarc!=NULL;
		  w=G.vertices[u].firstarc->adjvex,
		  G.vertices[u].firstarc=G.vertices[u].firstarc->nextarc)
	      if(visited[w]==0)
		   {  visited[w]=1;
		      cout<<w+1<<"-->";
		      EnQueue(Q,w); 	//call EnQueue()
		   } //if end
	      if(visited[w]==0)
		   {  visited[w]=1;
		      cout<<w+1<<"-->";
		      EnQueue(Q,w);	//call EnQueue()
		   } //if end
	} //while end
     } //if end
} //BFSTraverse() end

void main()			//main() function
{  ALGraph G;
   cout<<endl<<endl<<"BFSTraverse.cpp";
   cout<<endl<<"==============="<<endl;
   CreateDG(G);			//call CreateDG()
   cout<<"BFS Traverse is as follows :";
   cout<<endl<<endl<<"Begin->";
   BFSTraverse(G);              //call BFSTraverse()
   cout<<"End !"<<endl<<endl<<"...OK!...";
   getch();
}



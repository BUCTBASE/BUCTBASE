//CreatDG.cpp
//This function is to create ALGraph
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

int CreateDG(ALGraph &G)	//CreateDG() subfunction
{  int IncInfo,i,j,k,v1,v2,w;
   cout<<endl<<"Please input the number of G.vexnum (eg,G.vexnum=4): ";
   cin>>G.vexnum;		//input the number of vex
   cout<<"Please input the number of G.arcnum (eg,G.arcnum=4): ";
   cin>>G.arcnum;		//input the numbe of arc
   cout<<"Please input the number of IncInfo (0 for none)    : ";
   cin>>IncInfo;		//if no information, input 0
   for(i=0;i<G.vexnum;++i)
       {  G.vertices[i].data=i; //initial G.vertices[i].data
	  G.vertices[i].firstarc=NULL;	//initial G.vertices[i].firstarc
       }
   cout<<"Plese input arc(V1-->V2), For example: (V1=1,V2=3),(V1=2,V2=4)..."<<endl;
   for(k=0;k<G.arcnum;++k)	//input arc(v1,v2)
   {  cout<<endl<<"Please input the "<<k+1<<"th arc's v1 (0<v1<G.vexnum): ";
	 cin>>v1;
      cout<<"Please input the "<<k+1<<"th arc's v2 (0<v2<G.vexnum0: ";
      cin>>v2;
      i=v1;
      j=v2;
      while(i<1||i>G.vexnum||j<1||j>G.vexnum)	//if (v1,v2) illegal
       {  cout<<endl<<"Please input the "<<k+1<<"th arc's v1 (0<v1<G.vexnum): ";
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
       {  cout<<"Overflow!";
	  return (0);
       }
       p->adjvex=j;		//assign p->adjvex
       p->nextarc=G.vertices[i].firstarc;
       p->info=NULL;
       G.vertices[i].firstarc=p;
       if(IncInfo)
	  {  cout<<"Please input the info :";
	     cin>>*(p->info);	//input information
	  }
   } //for end
   return (OK);
} //CreateDG() end

void main()		//main() function
{  ALGraph G;
   cout<<endl<<endl<<"CreateDG.cpp";
   cout<<endl<<"============"<<endl;
   if(CreateDG(G))	//call CreateDG()
      cout<<endl<<"Create ALGraph success !";	//if success, output information
   cout<<endl<<endl<<"...OK!...";
   getch();
} //main() end
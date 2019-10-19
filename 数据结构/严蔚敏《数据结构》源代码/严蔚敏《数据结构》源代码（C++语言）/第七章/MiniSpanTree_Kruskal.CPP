//MiniSpanTree_Kruskal.cpp
//This function is to create MiniSpanTree with Kruskal Algorithm
# include <iostream.h>
# include <malloc.h>
# include <conio.h>

# define MAX_VERTEX_NUM 20
# define MAXQSIZE 100
typedef int VertexType;
typedef int QElemType;
typedef int InfoType;

typedef struct ArcNode
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
}ALGraph;			//define ALGraph structure

typedef int VRType;
typedef struct
{  int begin,end;
   VRType cost;
}EDGE;				//define EDGE structure

void Swapn(EDGE *edges,int i,int j)	//subfunction Swapn()
{  int temp;				//exchange edges[i] and edges[j]
   temp=edges[i].begin;			//exchange edges[].begin
   edges[i].begin=edges[j].begin;
   edges[j].begin=temp;
   temp=edges[i].end;			//exchange edges[].end
   edges[i].end=edges[j].end;
   edges[j].end=temp;
   temp=edges[i].cost;			//exchange edges[].cost
   edges[i].cost=edges[j].cost;
   edges[j].cost=temp;
} //Swapn end

void Sort(EDGE *edges,ALGraph G)	//subfunction Sort()
{  int i,j;				//sort edges[] in ascending order
   for(i=1;i<=G.vexnum;++i)
     for(j=i;j<=G.vexnum;++j)
       if(edges[i].cost>edges[j].cost)	//if
	 Swapn(edges,i,j);              //call Swapn() subfunction
} //Sort() end

int Find(int *parents,int f)		//Find() subfunction
{    while(parents[f]>0)
	 f=parents[f];
   return (f);
} //Find() end

void MiniSpanTree_Kruskal(ALGraph G)	//MiniSpanTree_Kruskal subfunction
{  int i,v1,v2,value,bnf,edf;
   int parents[MAX_VERTEX_NUM];
   EDGE edges[MAX_VERTEX_NUM];
   cout<<endl<<"Please input the number of G.vexnum (eg. G.vexnum=4): ";
   cin>>G.vexnum;			//input the number of vex
   cout<<"Please input the number of G.arcnum (eg. G.arcnum=4): ";
   cin>>G.arcnum;			//input the number of arc
   cout<<"Please input arc(V1-->V2), For example: (V1=1,V2=3),(V1=2,V2=4)...";
   cout<<endl;				//input arc(v1,v2)
   for(i=1;i<=G.arcnum;++i)
   {  cout<<endl<<"Please input the "<<i<<"th arc's v1 (0<v1<G.vexnum): ";
      cin>>v1;				//input head point
      cout<<"Please input the "<<i<<"th arc's v2 (0<v2<G.vexnum): ";
      cin>>v2;				//input tail point
      cout<<"Please input the "<<i<<"th arc's weight            : ";
      cin>>value;			//input the weight of arc
      edges[i].begin=v1;
      edges[i].end=v2;
      while(v1<1||v1>G.vexnum||v2<1||v2>G.vexnum)   //if input illegal,again
       {  cout<<endl<<"Please input the "<<i<<"th arc's v1 (0<v1<G.vexnum) : ";
	  cin>>v1;
	  cout<<"Please input the "<<i<<"th arc's v2 (0<v2<G.vexnum): ";
	  cin>>v2;
	  cout<<"Please input the "<<i<<"th arc's v2                : ";
	  cin>>value;
	  edges[i].begin=v1;
	  edges[i].end=v2;
       } //while end
       edges[i].cost=value;
   } //for end
   Sort(edges,G);		       	//call Sort() subfunction
//   for(i=1;i<=G.arcnum;i++)
//   cout<<endl<<edges[i].cost;
   for(i=1;i<=G.vexnum;++i)
      parents[i]=0;			//initialize array parents[]
   cout<<endl<<"The MiniSpanTree_Kruskal is created in the following order:"<<endl;
   for(i=1;i<=G.vexnum;++i)
   {  bnf=Find(parents,edges[i].begin);
      edf=Find(parents,edges[i].end);
      if(bnf!=edf)
      {  parents[bnf]=edf;
	 cout<<endl<<"Arc("<<edges[i].begin<<",";	//output the MiniSpanTree
	 cout<<edges[i].end<<") weight ";
	 cout<<edges[i].cost;
      } //if end
   } //for end
} //MiniSpanTree_Kruskal() end

void main()			//main() function
{  ALGraph G;
   cout<<endl<<endl<<"MiniSpanTree_Kruskal.cpp";
   cout<<endl<<"========================"<<endl;
   MiniSpanTree_Kruskal(G);	//call MiniSpanTree_Kruskal()
   cout<<endl<<endl<<"...OK!...";
   getch();
} //main() end



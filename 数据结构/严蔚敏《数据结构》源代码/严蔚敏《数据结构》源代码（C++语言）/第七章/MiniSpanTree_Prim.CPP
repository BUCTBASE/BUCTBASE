//MiniSpanTree_Prim.cpp
//This function is to create MiniSpanTree_Prim with Prim Algorithm
# include <iostream.h>
# include <malloc.h>
# include <conio.h>

# define INFINITY 1000
# define MAX_VERTEX_NUM 20
# define OK 1
typedef enum{DG,DN,UDG,UDN} GraphKind;
typedef int EType;
typedef int InfoType;
typedef int VertexType;
typedef int VRType;
typedef int lowcost;

typedef struct		//define Closedege structure
{   VertexType adjvex;
    VRType    lowcost;
}Closedge;

typedef struct ArcCell	//define MGraph structure
{  EType adj;
   InfoType *info;
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct
{  VertexType vexs[MAX_VERTEX_NUM];
   AdjMatrix  arcs;
   int vexnum,arcnum;
   GraphKind kind;
}MGraph;

int CreatUDN(MGraph &G)		//CreatUDN() sub-function
{  int IncInfo,i=0,j=0,k,v1,v2,w;
   cout<<endl<<"Please input the number of G.vexnum (eg,G.vexnum=4) : ";
   cin>>G.vexnum;              	//input the number of vex
   cout<<"Please input the number of G.arcnum (eg,G.arcnum=4) : ";
   cin>>G.arcnum;		//input the number of arc
   for(i=0;i<G.vexnum;++i)
     for(j=i;j<G.vexnum;++j)
      {	 G.arcs[i][j].adj=G.arcs[j][i].adj=INFINITY;	//initial weigh
	 G.arcs[i][j].info=G.arcs[j][i].info=NULL;
      }
   cout<<"Please input IncInfo (0 for none)                   : ";
   cin>>IncInfo;		//if need information, input non-zero
   cout<<"Plese input arc(V1-->V2), For example: (V1=1,V2=3),(V1=2,V2=4)..."<<endl;
   for(k=0;k<G.arcnum;++k)	//input arc(v1,v2)
   {   cout<<endl<<"Please input the "<<k+1<<"th arc's v1 (0<v1<G.vexnum) : ";
       cin>>v1;
       cout<<"Please input the "<<k+1<<"th arc's v2 (0<v2<G.vexnum) : ";
       cin>>v2;
       cout<<"Please input the "<<k+1<<"th arc's weight             : ";
       cin>>w;
       i=v1;
       j=v2;
       while(i<1||i>G.vexnum||j<1||j>G.vexnum)	//if (v1,v2) illegal
       {   cout<<"Please input the "<<k+1<<"th arc's v1 (0<v1<G.vexnum) : ";
	   cin>>v1;
	   cout<<"Please input the "<<k+1<<"th arc's v2 (0<v1<G.vexnum) : ";
	   cin>>v2;
	   cout<<"Please input the "<<k+1<<"th arc's weight             : ";
	   cin>>w;
	   i=v1;
	   j=v2;
       } //while end
       i--;
       j--;
   G.arcs[i][j].adj=G.arcs[j][i].adj=w;		//
   cout<<"G.arcs["<<i+1<<"]["<<j+1<<"].adj=";
   cout<<"G.arcs["<<j+1<<"]["<<i+1<<"].adj="<<G.arcs[j][i].adj<<endl;
   if(IncInfo)
     {   cout<<"Please input the "<<k+1<<"th arc's Info : ";
	 cin>>*G.arcs[i][j].info;		//input information
     }
   } //for end
   return (OK);
} //CreatUDN() end

int Minimum(Closedge *closedge,int Vexnum)	//Minimum() sub-function
{   int min=1,j;                        //return min (closedge[min].lowcost)
    if(closedge[min].lowcost==0)
      min++;				//closedge[min].lowcost!=0
    for(j=0;j<Vexnum;++j)
      if(closedge[j].lowcost<closedge[min].lowcost
	      &&closedge[j].lowcost>0)
	min=j;
    return (min);
} //Minimim() end

int LocatedVex(MGraph G,VertexType u)	//LocatedVex() sub-fuction
{  return (u);
}

void MiniSpanTree_Prim(MGraph G,VertexType u)	//MiniSpanTree_Prim() sub-function
{  int k,j,i,Vexnum=G.vexnum;
   k=LocatedVex(G,u);
   Closedge closedge[MAX_VERTEX_NUM];
   for(j=0;j<G.vexnum;++j)	//initial closedge[]
     if(j!=k)
     {	closedge[j].adjvex=u;  	// (u,j)
	closedge[j].lowcost=G.arcs[k][j].adj;
     }
   closedge[k].lowcost=0;	//U include k
   for(i=1;i<G.vexnum;++i)
   {  k=Minimum(closedge,Vexnum);	//select k=min(closedge[vi].lowcost)
      cout<<endl<<"("<<closedge[k].adjvex+1<<","<<k+1<<")";
      cout<<"="<<G.arcs[closedge[k].adjvex][k].adj;
      closedge[k].lowcost=0;	//U include k
      for(j=0;j<G.vexnum;++j)   //renew closedge[k]
	if(G.arcs[k][j].adj<closedge[j].lowcost)
	   {  closedge[j].adjvex=k;
	      closedge[j].lowcost=G.arcs[k][j].adj;
	   } //if end
   } //for end
} //Minimun() end

void main()  			//main() function
{   MGraph G;
    VertexType u=0;
    cout<<endl<<endl<<"MiniSpanTree_Prim.cpp";
    cout<<endl<<"====================="<<endl;
    CreatUDN(G);		//call CreatUDN(G) function
    cout<<endl<<"The MiniSpanTree_Prim is created as follow order:";
    MiniSpanTree_Prim(G,u);	//call MiniSpanTree_Prim() function
    cout<<endl<<endl<<"...OK!...";
    getch();
} //main() end
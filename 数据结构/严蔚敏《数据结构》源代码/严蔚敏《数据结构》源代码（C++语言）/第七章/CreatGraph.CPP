//CreatUDN.cpp
//This function is to create MGraph
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

typedef struct ArcCell		//define structure MGraph
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
{  int IncInfo,i,j,k,v1,v2,w;
   cout<<endl<<"Please input the number of G.vexnum (eg,G.vexnum=4): ";
   cin>>G.vexnum;		//input the number of vex
   cout<<"Please input the number of G.arcnum (eg,G.arcnum=4): ";
   cin>>G.arcnum;		//input the number of arc
   cout<<"Please input IncInfo (0 for none)                  : ";
   cin>>IncInfo;
   for(i=0;i<G.vexnum;++i)
     for(j=0;j<G.vexnum;++j)
       {  G.arcs[i][j].adj=INFINITY;	//initial G.arcs[i][j].adj
	  G.arcs[i][j].info=NULL;	//initial G.arcs[i][j].info
       }
   cout<<"Plese input arc(V1-->V2), For example: (V1=1,V2=3),(V1=2,V2=4)..."<<endl;
   for(k=0;k<G.arcnum;++k)		//input arc(v1,v2)
   {   cout<<endl<<"Please input the "<<k+1<<"th arc's v1 (0<v1<G.vexnum) :";
       cin>>v1;				//input v1
       cout<<"Please input the "<<k+1<<"th arc's v2 (0<v2<G.vexnum) :";
       cin>>v2;				//input v2
       cout<<"Please input the "<<k+1<<"th arc's weight             :";
       cin>>w;				//input weight
       i=v1;
       j=v2;
       while(i<1||i>G.vexnum||j<1||j>G.vexnum)	//if (v1,v2) illegal,again
       {   cout<<"Please input the "<<k+1<<"th arc's v1 (0<v1<G.vexnum) :";
	   cin>>v1;
	   cout<<"Please input the "<<k+1<<"th arc's v2 (0<v1<G.vexnum) :";
	   cin>>v2;
	   cout<<"Please input the "<<k+1<<"th arc's weight             :";
	   cin>>w;
	   i=v1;
	   j=v2;
       } //while end
       i--;
       j--;
   G.arcs[i][j].adj=w;			//weight
   cout<<"G.arcs["<<i+1<<"]["<<j+1<<"].adj="<<w<<endl;
   if(IncInfo)
     {   cout<<"Please input the "<<k+1<<"th arc's Info :";
	 cin>>*G.arcs[i][j].info;
     }
   } //for end
   return (OK);
} //CreatUDN() end

//int CreateGraph(MGraph &G)
//{  cout<<endl<<"Please input the kind of Graph (DG, DN, UDG, UDN ) : ";
//   cin>>G.kind;
//   switch(G.kind)
//   {  case DG   : return CreatDG(G);
//      case DN   : return CreatD(Gn);
//      case UDG  : return CreatUDG(G);
//      case UDN  : return CreatUDN(G);
//      default   : return (0);
//   }
//}

void main()		//main() function
{   MGraph G;
    cout<<endl<<endl<<"CreatUDN.cpp";
    cout<<endl<<"============"<<endl;
    if(CreatUDN(G))	//call CreatUDN()
	cout<<endl<<"Create MGraph success !";	//if success,output informatin
    cout<<endl<<endl<<"...OK!...";
    getch();
} //main() end
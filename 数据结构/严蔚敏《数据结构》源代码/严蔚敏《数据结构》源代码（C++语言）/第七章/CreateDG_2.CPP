//CreateDG.cpp
//This function is to create OLGraph
# include <iostream.h>
# include <malloc.h>
# include <conio.h>

# define MAX_VERTEX_NUM 20
# define OK 1
typedef int VertexType;
typedef int InfoType;

typedef struct ArcBox		//define structure OLGraph
{  int tailvex,headvex;
   struct ArcBox *hlink,*tlink;
   InfoType *info;
}ArcBox;

typedef struct VexNode
{  VertexType data;
   ArcBox *firstin,*firstout;
}VexNode;

typedef struct
{  VexNode xlist[MAX_VERTEX_NUM];
   int vexnum,arcnum;
}OLGraph;

int CreateDG(OLGraph &G)	//CreateDG() sub-fuction
{  int IncInfo,i,j,k,v1,v2,w;
   cout<<endl<<"Please input the number of G.vexnum (eg,G.vexnum=4): ";
   cin>>G.vexnum;		//input the number of vex
   cout<<"Please input the number of G.arcnum (eg,G.arcnum=4): ";
   cin>>G.arcnum;		//input the number of arc
   cout<<"Please input IncInfo (0 for none)                  : ";
   cin>>IncInfo;		//not need information, input 0
   for(i=0;i<G.vexnum;++i)
       {  cout<<"Please input the value of the "<<i+1<<"th vex : ";
	  cin>>G.xlist[i].data;
	  G.xlist[i].firstin=NULL;
	  G.xlist[i].firstout=NULL;
       }
   cout<<"Plese input arc(V1-->V2), For example: (V1=1,V2=3),(V1=2,V2=4)..."<<endl;
   for(k=0;k<G.arcnum;++k)	//input arc(v1,v2)
   {   cout<<endl<<"Please input the "<<k+1<<"th arc's v1 (0<v1<G.vexnum): ";
       cin>>v1;
       cout<<"Please input the "<<k+1<<"th arc's v2 (0<v2<G.vexnum): ";
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
   ArcBox *p;
   p=(ArcBox *)malloc(sizeof(ArcBox));	//assign memory
   if(!p)
   {  cout<<"Overflow!";	//if voerflow
      return (0);
   }
   p->tailvex=i;		//assign p
   p->headvex=j ;
   p->hlink=G.xlist[j].firstin;
   p->tlink=G.xlist[i].firstout;
   p->info=NULL;
   G.xlist[j].firstin=p;
   if(IncInfo)
      {  cout<<"Please input the info :";
	 cin>>*(p->info);	//input information
      }
   } //for end
   return (OK);
} //CreateDG() end

void main()			//main() function
{   OLGraph G;
    cout<<endl<<endl<<"CreateDG.cpp";
    cout<<endl<<"============"<<endl;
    if(CreateDG(G))		//call CreateDG() function
       cout<<endl<<"Create OLGraph success!"; //if success, output information
    cout<<endl<<endl<<"...OK!...";
    getch();
} //main() end
//ShortestPath_DIJ.cpp

# include <iostream.h>
# include <stdio.h>
# include <malloc.h>
# include <conio.h>
# define INFINITY 1000
# define MAX_VERTEX_NUM 20
# define OK 1
# define ERROR 0 
# define FALSE 0
# define TRUE 1
typedef enum{DG,DN,UDG,UDN} GraphKind;
typedef int EType;
typedef int InfoType;
typedef int VertexType;
typedef int PathMatrix;
typedef int ShortPathTable; 

typedef struct ArcCell
{  EType adj;
   InfoType info;
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct
{  VertexType vexs[MAX_VERTEX_NUM];
   AdjMatrix  arcs;
   int vexnum,arcnum;
   GraphKind kind;
}MGraph;

int CreatUDN(MGraph &G)                                 //CreatUDN() function
{  int i=0,j=0,k,vi,vj,w;
   cout<<"Please input the number of G.vexnum (eg,G.vexnum=6) : ";
   cin>>G.vexnum;
   cout<<"Please input the number of G.arcnum (eg,G.arcnum=8) : ";
   cin>>G.arcnum;
   for(i=0;i<G.vexnum;++i)
     for(j=0;j<G.vexnum;++j)
     {  G.arcs[i][j].info=INFINITY;        
	 }
   cout<<"Plese input arc(Vi-->Vj):"<<endl
	   <<"For example:"<<endl<<"------------"<<endl
	   <<"(Vi=1,Vj=6,Weight=100),(Vi=1,Vj=5,Weight=30),(Vi=1,Vj=3,Weight=10)"<<endl
	   <<"(Vi=2,Vj=3,Weight=5),(Vi=3,Vj=4,Weight=50),(Vi=4,Vj=6,Weight=10)"<<endl
	   <<"(Vi=5,Vj=6,Weight=60),(Vi=5,Vj=4,Weight=20)..."<<endl;
   for(k=0;k<G.arcnum;++k)
   {   cout<<endl<<"Please input the "<<k+1<<"th arc's vi (0<vi<"<<G.vexnum+1<<"): ";
       cin>>vi;
       cout<<"Please input the "<<k+1<<"th arc's vj (0<vj<"<<G.vexnum+1<<"): ";
       cin>>vj;
       cout<<"Please input the "<<k+1<<"th arc's weight (0<weight<"<<INFINITY<<"): ";
       cin>>w;
       i=vi;
       j=vj;
       while(i<1||i>G.vexnum||j<1||j>G.vexnum||w<0||w>=INFINITY)
       {   
	   cout<<"Input ERROR!"<<endl
		   <<"Please input the "<<k+1<<"th arc's vi (0<vi<"<<G.vexnum+1<<"): ";
	   cin>>vi;
	   cout<<"Please input the "<<k+1<<"th arc's vj (0<vj<"<<G.vexnum+1<<"): ";
	   cin>>vj;
	   cout<<"Please input the "<<k+1<<"th arc's weight (0<weight<1000): ";
	   cin>>w;
	   i=vi;
	   j=vj;
       }//end of while
   i--;
   j--;         
   G.arcs[i][j].info=w;
   }//end of for(k=0;k<G.arcnum...)
   return (OK);
}//end CreatVDN() function

void ShortestPath_DIJ(MGraph G,int v0,PathMatrix Path[MAX_VERTEX_NUM][MAX_VERTEX_NUM],ShortPathTable Dist[MAX_VERTEX_NUM])
{   
	int i,j,v,w,min,final[MAX_VERTEX_NUM]; 
    for(v=0;v<G.vexnum;++v)
	{  final[v]=FALSE;
       Dist[v]=G.arcs[v0][v].info;
	   for(w=0;w<G.vexnum;++w)
		   Path[v][w]=FALSE;
	   if(Dist[v]<INFINITY)
	   {  Path[v][v0]=TRUE;
	      Path[v][v]=TRUE;
	   }  //end of if
	 }//end of for(v=0;v<G.vexnum...)
	Dist[v0]=0;
	final[v0]=TRUE;
    printf("Vertice");

	for(i=0;i<G.vexnum;i++)
		 printf("%5d",i+1);         
	printf("\n");
	printf("Step %d :",v0+1);      
	for(i=0;i<G.vexnum;i++)
		printf("%5d",Dist[i]);  
	printf("\n");

    for(i=1;i<G.vexnum;++i)         //Do the rest of G.vexnum-1 node 
	{   min=INFINITY;
		for(w=0;w<G.vexnum;++w)
	   	  if(!final[w])
			if(Dist[w]<min)
			{ v=w;
			  min=Dist[w];
			}//end of if
		   final[v]=TRUE;
		   printf("Step %d :",i+1);
		   for(w=0;w<G.vexnum;++w)
		   {if(!final[w]&&(min+G.arcs[v][w].info<Dist[w]))
				{  Dist[w]=min+G.arcs[v][w].info;
				   for(j=0;j<G.vexnum;j++)
				       Path[w][j]=Path[v][j];
				   Path[w][w]=TRUE;
				}//end of if				
				printf("%5d",Dist[w]);
		   }//end of for(w=0;w<G.vexnum;++w)          
		   printf("\n");	   
	}//end of for(i=1;,,,)
}//ShortPath_DIJ();

void main()                                                   //main() function
{   MGraph G;
    int v0=0;                                                 //modify
	int i,j;
	PathMatrix Path[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	ShortPathTable Dist[MAX_VERTEX_NUM];
	cout<<"ShortestPath_DIJ.cpp"<<endl<<"===================="<<endl<<endl;
    if(CreatUDN(G))
	cout<<endl<<"Create MGraph success !"<<endl<<"InitMGraph are Show:"<<endl<<"--------------------"<<endl;
    
    printf("Vertice");
	for(i=0;i<G.vexnum;i++)    
		 printf("%5d",i+1);       
	printf("\n");   
	for(i=0;i<G.vexnum;i++)
	{   printf("%5d   ",i+1); 
		for(j=0;j<G.vexnum;j++)   
              printf("%5d",G.arcs[i][j].info);  
	    printf("\n");
	}//end of for(i=0;i<G.vexnum;i++)

    cout<<endl<<"By Dijkstra Algorithm:"<<endl<<"----------------------"<<endl;
	ShortestPath_DIJ(G,v0,Path,Dist);
    cout<<endl<<"...OK!..."<<endl;	
    getch();
}//end of main() function
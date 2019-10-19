//ShortestPath_FLOYD.cpp

# include <iostream.h>
# include <stdio.h>
# include <conio.h>
# define INFINITY 1000
# define MAX_VERTEX_NUM 20
# define OK 1
# define FALSE 0
# define TRUE 1
typedef enum{DG,DN,UDG,UDN} GraphKind;
typedef int EType;
typedef int InfoType;
typedef int VertexType;

typedef int PathMatrix;
typedef int DistancMatrix; 

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

//typedef  struct
//{ SString  pathvexs;   // 最短路径字符
//  int  vexnum          // 当前顶点数
//} PathMatrix[vexnum][vexnum];

//typedef  struct  
//{ VRType *distant      // 存储空间基址
//  int  vexnum          // 当前顶点数
//} ShortPathTable

int CreatUDN(MGraph &G)                                     //CreatVDN() function
{  int i=0,j=0,k,vi,vj,w;

   //-----Demo G.vexnum and G.arcnum -----
   G.vexnum=3;
   G.arcnum=5;
   //-------------------------------------
   
   printf("Please input the number of G.vexnum (eg,G.vexnum=3) : ");
   scanf("%d",&G.vexnum);
   printf("Please input the number of G.arcnum (eg,G.arcnum=5) : ");
   scanf("%d",&G.arcnum);

   for(i=0;i<G.vexnum;++i)
     for(j=0;j<G.vexnum;++j)
     {  G.arcs[i][j].info=INFINITY;
	    if(i==j) G.arcs[i][j].info=0;     
	 }//end of for(j=0;j<G.vexnum;++j)

   cout<<"Plese input arc(Vi-->Vj):"<<endl
	   <<"For example:"<<endl<<"------------"<<endl
	   <<"(Vi=1,Vj=2,Weight=4),(Vi=1,Vj=3,Weight=11),(Vi=2,Vj=1,Weight=6)"<<endl
	   <<"(Vi=2,Vj=3,Weight=2),(Vi=3,Vj=1,Weight=3)..."<<endl;
   for(k=0;k<G.arcnum;++k)
   {   cout<<endl<<"Please input the "<<k+1<<"th arc's vi (0<vi<"<<G.vexnum+1<<"): ";
       cin>>vi;
       cout<<"Please input the "<<k+1<<"th arc's vj (0<vj<"<<G.vexnum+1<<"): ";
       cin>>vj;
       cout<<"Please input the "<<k+1<<"th arc's weight (0<weight<"<<INFINITY<<"): ";
       cin>>w;
       i=vi;
       j=vj;
       while(i<1||i>G.vexnum||j<1||j>G.vexnum||w<0)
       {   
	   cout<<"Input ERROR!"<<endl
		   <<"Please input the "<<k+1<<"th arc's vi (0<vi<"<<G.vexnum+1<<"): ";
	   cin>>vi;
	   cout<<"Please input the "<<k+1<<"th arc's vj (0<vj<"<<G.vexnum+1<<"): ";
	   cin>>vj;
	   cout<<"Please input the "<<k+1<<"th arc's weight (0<weight<"<<INFINITY<<"): ";
	   cin>>w;
	   i=vi;
	   j=vj;
       }//end of while
   i--;
   j--;         
   G.arcs[i][j].info=w;
   }//end of for(k=0;k<G.arcnum...)
   return (OK);
}//end of CreateVDN() function

void ShortestPath_FLOYD(MGraph G,PathMatrix Path[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM],DistancMatrix Dist[MAX_VERTEX_NUM][MAX_VERTEX_NUM])
{   
	int i,j,u,v,w; 
    for(v=0;v<G.vexnum;++v)
		for(w=0;w<G.vexnum;++w)
		{	Dist[v][w]=G.arcs[v][w].info;
		    for(u=0;u<G.vexnum;++u) 
			   Path[v][w][u]=FALSE;
	        if(Dist[v][w]<INFINITY)
			{  Path[v][w][v]=TRUE;
		       Path[v][w][w]=TRUE;
			}//end of if
		}//end of for
	for(u=0;u<G.vexnum;++u)
		for(v=0;v<G.vexnum;++v)
			for(w=0;w<G.vexnum;++w)
			  if(Dist[v][u]+Dist[u][w]<Dist[v][w])
			  {  Dist[v][w]=Dist[v][u]+Dist[u][w];
			     for(i=0;i<G.vexnum;++i)
					 Path[v][w][i]=Path[v][u][i]||Path[u][w][i];
			  }//end of if
    //------- print the last Dist[i][j]-----
		 printf("Vertice"); 
	     for(i=0;i<G.vexnum;i++)
	        printf("%5d",i+1);
	     printf("\n");  
		 for(i=0;i<G.vexnum;i++)
		 { printf("%5d  ",i+1); 
		   for(j=0;j<G.vexnum;j++)
		     printf("%5d",Dist[i][j]);
		   printf("\n");
		 }//end of for(i=0;i<G.vexnum;i++)
		 printf("\n");
	//--------------------------------------   

}//ShortestPath_FLOYD() function
			
void main()                                          //main() function
{   MGraph G;
   	int i,j;
	PathMatrix Path[MAX_VERTEX_NUM][MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	DistancMatrix Dist[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
	cout<<"ShortestPath_FLOYD.cpp"<<endl<<"======================"<<endl<<endl;
    if(CreatUDN(G))
	cout<<endl<<"Create MGraph success !"<<endl<<"InitMGraph are Show:"<<endl<<"----------------------"<<endl;
    
    printf("Vertice");
	for(i=0;i<G.vexnum;i++)    
		 printf("%5d",i+1);       
	printf("\n");   
	for(i=0;i<G.vexnum;i++)
	{   printf("%5d  ",i+1); 
		for(j=0;j<G.vexnum;j++)   
              printf("%5d",G.arcs[i][j].info);  
	    printf("\n");
	}//end of for(i=0;i<G.vexnum;i++)

    cout<<endl<<"By FLOYD Algorithm:"<<endl<<"----------------------"<<endl;
	ShortestPath_FLOYD(G,Path,Dist);
    cout<<endl<<"...OK!..."<<endl;	
    getch();
}//end of main() function
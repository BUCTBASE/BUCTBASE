 /* bo7-1.c 图的数组(邻接矩阵)存储(存储结构由c7-1.h定义)的基本操作(20个) */
 int LocateVex(MGraph G,VertexType u)
 { /* 初始条件:图G存在,u和G中顶点有相同特征 */
   /* 操作结果:若G中存在顶点u,则返回该顶点在图中位置;否则返回-1 */
   int i;
   for(i=0;i<G.vexnum;++i)
     if(strcmp(u,G.vexs[i])==0)
       return i;
   return -1;
 }

 Status CreateFAG(MGraph *G)
 { /* 采用数组(邻接矩阵)表示法,由文件构造没有相关信息的无向图G */
   int i,j,k;
   char filename[13];
   VertexType va,vb;
   FILE *graphlist;
   printf("请输入数据文件名(f7-1.dat)：");
   scanf("%s",filename);
   graphlist=fopen(filename,"r");
   fscanf(graphlist,"%d",&(*G).vexnum);
   fscanf(graphlist,"%d",&(*G).arcnum);
   for(i=0;i<(*G).vexnum;++i) /* 构造顶点向量 */
     fscanf(graphlist,"%s",(*G).vexs[i]);
   for(i=0;i<(*G).vexnum;++i) /* 初始化邻接矩阵 */
     for(j=0;j<(*G).vexnum;++j)
     {
       (*G).arcs[i][j].adj=0; /* 图 */
       (*G).arcs[i][j].info=NULL; /* 没有相关信息 */
     }
   for(k=0;k<(*G).arcnum;++k)
   {
     fscanf(graphlist,"%s%s",va,vb);
     i=LocateVex(*G,va);
     j=LocateVex(*G,vb);
     (*G).arcs[i][j].adj=(*G).arcs[j][i].adj=1; /* 无向图 */
   }
   fclose(graphlist);
   (*G).kind=AG;
   return OK;
 }

 Status CreateDG(MGraph *G)
 { /* 采用数组(邻接矩阵)表示法,构造有向图G */
   int i,j,k,l,IncInfo;
   char s[MAX_INFO],*info;
   VertexType va,vb;
   printf("请输入有向图G的顶点数,弧数,弧是否含其它信息(是:1,否:0): ");
   scanf("%d,%d,%d",&(*G).vexnum,&(*G).arcnum,&IncInfo);
   printf("请输入%d个顶点的值(<%d个字符):\n",(*G).vexnum,MAX_NAME);
   for(i=0;i<(*G).vexnum;++i) /* 构造顶点向量 */
     scanf("%s",(*G).vexs[i]);
   for(i=0;i<(*G).vexnum;++i) /* 初始化邻接矩阵 */
     for(j=0;j<(*G).vexnum;++j)
     {
       (*G).arcs[i][j].adj=0; /* 图 */
       (*G).arcs[i][j].info=NULL;
     }
   printf("请输入%d条弧的弧尾 弧头(以空格作为间隔): \n",(*G).arcnum);
   for(k=0;k<(*G).arcnum;++k)
   {
     scanf("%s%s%*c",va,vb);  /* %*c吃掉回车符 */
     i=LocateVex(*G,va);
     j=LocateVex(*G,vb);
     (*G).arcs[i][j].adj=1; /* 有向图 */
     if(IncInfo)
     {
       printf("请输入该弧的相关信息(<%d个字符): ",MAX_INFO);
       gets(s);
       l=strlen(s);
       if(l)
       {
         info=(char*)malloc((l+1)*sizeof(char));
         strcpy(info,s);
         (*G).arcs[i][j].info=info; /* 有向 */
       }
     }
   }
   (*G).kind=DG;
   return OK;
 }

 Status CreateDN(MGraph *G)
 { /* 采用数组(邻接矩阵)表示法,构造有向网G */
   int i,j,k,w,IncInfo;
   char s[MAX_INFO],*info;
   VertexType va,vb;
   printf("请输入有向网G的顶点数,弧数,弧是否含其它信息(是:1,否:0): ");
   scanf("%d,%d,%d",&(*G).vexnum,&(*G).arcnum,&IncInfo);
   printf("请输入%d个顶点的值(<%d个字符):\n",(*G).vexnum,MAX_NAME);
   for(i=0;i<(*G).vexnum;++i) /* 构造顶点向量 */
     scanf("%s",(*G).vexs[i]);
   for(i=0;i<(*G).vexnum;++i) /* 初始化邻接矩阵 */
     for(j=0;j<(*G).vexnum;++j)
     {
       (*G).arcs[i][j].adj=INFINITY; /* 网 */
       (*G).arcs[i][j].info=NULL;
     }
   printf("请输入%d条弧的弧尾 弧头 权值(以空格作为间隔): \n",(*G).arcnum);
   for(k=0;k<(*G).arcnum;++k)
   {
     scanf("%s%s%d%*c",va,vb,&w);  /* %*c吃掉回车符 */
     i=LocateVex(*G,va);
     j=LocateVex(*G,vb);
     (*G).arcs[i][j].adj=w; /* 有向网 */
     if(IncInfo)
     {
       printf("请输入该弧的相关信息(<%d个字符): ",MAX_INFO);
       gets(s);
       w=strlen(s);
       if(w)
       {
         info=(char*)malloc((w+1)*sizeof(char));
         strcpy(info,s);
         (*G).arcs[i][j].info=info; /* 有向 */
       }
     }
   }
   (*G).kind=DN;
   return OK;
 }

 Status CreateAG(MGraph *G)
 { /* 采用数组(邻接矩阵)表示法,构造无向图G */
   int i,j,k,l,IncInfo;
   char s[MAX_INFO],*info;
   VertexType va,vb;
   printf("请输入无向图G的顶点数,边数,边是否含其它信息(是:1,否:0): ");
   scanf("%d,%d,%d",&(*G).vexnum,&(*G).arcnum,&IncInfo);
   printf("请输入%d个顶点的值(<%d个字符):\n",(*G).vexnum,MAX_NAME);
   for(i=0;i<(*G).vexnum;++i) /* 构造顶点向量 */
     scanf("%s",(*G).vexs[i]);
   for(i=0;i<(*G).vexnum;++i) /* 初始化邻接矩阵 */
     for(j=0;j<(*G).vexnum;++j)
     {
       (*G).arcs[i][j].adj=0; /* 图 */
       (*G).arcs[i][j].info=NULL;
     }
   printf("请输入%d条边的顶点1 顶点2(以空格作为间隔): \n",(*G).arcnum);
   for(k=0;k<(*G).arcnum;++k)
   {
     scanf("%s%s%*c",va,vb); /* %*c吃掉回车符 */
     i=LocateVex(*G,va);
     j=LocateVex(*G,vb);
     (*G).arcs[i][j].adj=(*G).arcs[j][i].adj=1; /* 无向图 */
     if(IncInfo)
     {
       printf("请输入该边的相关信息(<%d个字符): ",MAX_INFO);
       gets(s);
       l=strlen(s);
       if(l)
       {
         info=(char*)malloc((l+1)*sizeof(char));
         strcpy(info,s);
         (*G).arcs[i][j].info=(*G).arcs[j][i].info=info; /* 无向 */
       }
     }
   }
   (*G).kind=AG;
   return OK;
 }

 Status CreateAN(MGraph *G)
 { /* 采用数组(邻接矩阵)表示法,构造无向网G。算法7.2 */
   int i,j,k,w,IncInfo;
   char s[MAX_INFO],*info;
   VertexType va,vb;
   printf("请输入无向网G的顶点数,边数,边是否含其它信息(是:1,否:0): ");
   scanf("%d,%d,%d",&(*G).vexnum,&(*G).arcnum,&IncInfo);
   printf("请输入%d个顶点的值(<%d个字符):\n",(*G).vexnum,MAX_NAME);
   for(i=0;i<(*G).vexnum;++i) /* 构造顶点向量 */
     scanf("%s",(*G).vexs[i]);
   for(i=0;i<(*G).vexnum;++i) /* 初始化邻接矩阵 */
     for(j=0;j<(*G).vexnum;++j)
     {
       (*G).arcs[i][j].adj=INFINITY; /* 网 */
       (*G).arcs[i][j].info=NULL;
     }
   printf("请输入%d条边的顶点1 顶点2 权值(以空格作为间隔): \n",(*G).arcnum);
   for(k=0;k<(*G).arcnum;++k)
   {
     scanf("%s%s%d%*c",va,vb,&w); /* %*c吃掉回车符 */
     i=LocateVex(*G,va);
     j=LocateVex(*G,vb);
     (*G).arcs[i][j].adj=(*G).arcs[j][i].adj=w; /* 无向 */
     if(IncInfo)
     {
       printf("请输入该边的相关信息(<%d个字符): ",MAX_INFO);
       gets(s);
       w=strlen(s);
       if(w)
       {
         info=(char*)malloc((w+1)*sizeof(char));
         strcpy(info,s);
         (*G).arcs[i][j].info=(*G).arcs[j][i].info=info; /* 无向 */
       }
     }
   }
   (*G).kind=AN;
   return OK;
 }

 Status CreateGraph(MGraph *G)
 { /* 采用数组(邻接矩阵)表示法,构造图G。算法7.1 */
   printf("请输入图G的类型(有向图:0,有向网:1,无向图:2,无向网:3): ");
   scanf("%d",&(*G).kind);
   switch((*G).kind)
   {
     case DG: return CreateDG(G); /* 构造有向图 */
     case DN: return CreateDN(G); /* 构造有向网 */
     case AG: return CreateAG(G); /* 构造无向图 */
     case AN: return CreateAN(G); /* 构造无向网 */
     default: return ERROR;
   }
 }

 void DestroyGraph(MGraph *G)
 { /* 初始条件: 图G存在。操作结果: 销毁图G */
   int i,j;
   if((*G).kind<2) /* 有向 */
     for(i=0;i<(*G).vexnum;i++) /* 释放弧的相关信息(如果有的话) */
     {
       for(j=0;j<(*G).vexnum;j++)
         if((*G).arcs[i][j].adj==1&&(*G).kind==0||(*G).arcs[i][j].adj!=INFINITY&&(*G).kind==1) /* 有向图的弧||有向网的弧 */
           if((*G).arcs[i][j].info) /* 有相关信息 */
           {
             free((*G).arcs[i][j].info);
             (*G).arcs[i][j].info=NULL;
           }
     }
   else /* 无向 */
     for(i=0;i<(*G).vexnum;i++) /* 释放边的相关信息(如果有的话) */
       for(j=i+1;j<(*G).vexnum;j++)
         if((*G).arcs[i][j].adj==1&&(*G).kind==2||(*G).arcs[i][j].adj!=INFINITY&&(*G).kind==3) /* 无向图的边||无向网的边 */
           if((*G).arcs[i][j].info) /* 有相关信息 */
           {
             free((*G).arcs[i][j].info);
             (*G).arcs[i][j].info=(*G).arcs[j][i].info=NULL;
           }
   (*G).vexnum=0;
   (*G).arcnum=0;
 }

 VertexType* GetVex(MGraph G,int v)
 { /* 初始条件: 图G存在，v是G中某个顶点的序号。操作结果: 返回v的值 */
   if(v>=G.vexnum||v<0)
     exit(ERROR);
   return &G.vexs[v];
 }

 Status PutVex(MGraph *G,VertexType v,VertexType value)
 { /* 初始条件: 图G存在，v是G中某个顶点。操作结果: 对v赋新值value */
   int k;
   k=LocateVex(*G,v); /* k为顶点v在图G中的序号 */
   if(k<0)
     return ERROR;
   strcpy((*G).vexs[k],value);
   return OK;
 }

 int FirstAdjVex(MGraph G,VertexType v)
 { /* 初始条件: 图G存在,v是G中某个顶点 */
   /* 操作结果: 返回v的第一个邻接顶点的序号。若顶点在G中没有邻接顶点,则返回-1 */
   int i,j=0,k;
   k=LocateVex(G,v); /* k为顶点v在图G中的序号 */
   if(G.kind==DN||G.kind==AN) /* 网 */
     j=INFINITY;
   for(i=0;i<G.vexnum;i++)
     if(G.arcs[k][i].adj!=j)
       return i;
   return -1;
 }

 int NextAdjVex(MGraph G,VertexType v,VertexType w)
 { /* 初始条件: 图G存在,v是G中某个顶点,w是v的邻接顶点 */
   /* 操作结果: 返回v的(相对于w的)下一个邻接顶点的序号, */
   /*           若w是v的最后一个邻接顶点,则返回-1 */
   int i,j=0,k1,k2;
   k1=LocateVex(G,v); /* k1为顶点v在图G中的序号 */
   k2=LocateVex(G,w); /* k2为顶点w在图G中的序号 */
   if(G.kind==DN||G.kind==AN) /* 网 */
     j=INFINITY;
   for(i=k2+1;i<G.vexnum;i++)
     if(G.arcs[k1][i].adj!=j)
       return i;
   return -1;
 }

 void InsertVex(MGraph *G,VertexType v)
 { /* 初始条件: 图G存在,v和图G中顶点有相同特征 */
   /* 操作结果: 在图G中增添新顶点v(不增添与顶点相关的弧,留待InsertArc()去做) */
   int i;
   strcpy((*G).vexs[(*G).vexnum],v); /* 构造新顶点向量 */
   for(i=0;i<=(*G).vexnum;i++)
   {
     if((*G).kind%2) /* 网 */
     {
       (*G).arcs[(*G).vexnum][i].adj=INFINITY; /* 初始化该行邻接矩阵的值(无边或弧) */
       (*G).arcs[i][(*G).vexnum].adj=INFINITY; /* 初始化该列邻接矩阵的值(无边或弧) */
     }
     else /* 图 */
     {
       (*G).arcs[(*G).vexnum][i].adj=0; /* 初始化该行邻接矩阵的值(无边或弧) */
       (*G).arcs[i][(*G).vexnum].adj=0; /* 初始化该列邻接矩阵的值(无边或弧) */
     }
     (*G).arcs[(*G).vexnum][i].info=NULL; /* 初始化相关信息指针 */
     (*G).arcs[i][(*G).vexnum].info=NULL;
   }
   (*G).vexnum+=1; /* 图G的顶点数加1 */
 }

 Status DeleteVex(MGraph *G,VertexType v)
 { /* 初始条件: 图G存在,v是G中某个顶点。操作结果: 删除G中顶点v及其相关的弧 */
   int i,j,k;
   VRType m=0;
   k=LocateVex(*G,v); /* k为待删除顶点v的序号 */
   if(k<0) /* v不是图G的顶点 */
     return ERROR;
   if((*G).kind==DN||(*G).kind==AN) /* 网 */
     m=INFINITY;
   for(j=0;j<(*G).vexnum;j++)
     if((*G).arcs[j][k].adj!=m) /* 有入弧或边 */
     {
       if((*G).arcs[j][k].info) /* 有相关信息 */
         free((*G).arcs[j][k].info); /* 释放相关信息 */
       (*G).arcnum--; /* 修改弧数 */
     }
   if((*G).kind==DG||(*G).kind==DN) /* 有向 */
     for(j=0;j<(*G).vexnum;j++)
       if((*G).arcs[k][j].adj!=m) /* 有出弧 */
       {
         if((*G).arcs[k][j].info) /* 有相关信息 */
           free((*G).arcs[k][j].info); /* 释放相关信息 */
         (*G).arcnum--; /* 修改弧数 */
       }
   for(j=k+1;j<(*G).vexnum;j++) /* 序号k后面的顶点向量依次前移 */
     strcpy((*G).vexs[j-1],(*G).vexs[j]);
   for(i=0;i<(*G).vexnum;i++)
     for(j=k+1;j<(*G).vexnum;j++)
       (*G).arcs[i][j-1]=(*G).arcs[i][j]; /* 移动待删除顶点之后的矩阵元素 */
   for(i=0;i<(*G).vexnum;i++)
     for(j=k+1;j<(*G).vexnum;j++)
       (*G).arcs[j-1][i]=(*G).arcs[j][i]; /* 移动待删除顶点之下的矩阵元素 */
   (*G).vexnum--; /* 更新图的顶点数 */
   return OK;
 }

 Status InsertArc(MGraph *G,VertexType v,VertexType w)
 { /* 初始条件: 图G存在,v和W是G中两个顶点 */
   /* 操作结果: 在G中增添弧<v,w>,若G是无向的,则还增添对称弧<w,v> */
   int i,l,v1,w1;
   char *info,s[MAX_INFO];
   v1=LocateVex(*G,v); /* 尾 */
   w1=LocateVex(*G,w); /* 头 */
   if(v1<0||w1<0)
     return ERROR;
   (*G).arcnum++; /* 弧或边数加1 */
   if((*G).kind%2) /* 网 */
   {
     printf("请输入此弧或边的权值: ");
     scanf("%d",&(*G).arcs[v1][w1].adj);
   }
   else /* 图 */
     (*G).arcs[v1][w1].adj=1;
   printf("是否有该弧或边的相关信息(0:无 1:有): ");
   scanf("%d%*c",&i);
   if(i)
   {
     printf("请输入该弧或边的相关信息(<%d个字符)：",MAX_INFO);
     gets(s);
     l=strlen(s);
     if(l)
     {
       info=(char*)malloc((l+1)*sizeof(char));
       strcpy(info,s);
       (*G).arcs[v1][w1].info=info;
     }
   }
   if((*G).kind>1) /* 无向 */
   {
     (*G).arcs[w1][v1].adj=(*G).arcs[v1][w1].adj;
     (*G).arcs[w1][v1].info=(*G).arcs[v1][w1].info; /* 指向同一个相关信息 */
   }
   return OK;
 }

 Status DeleteArc(MGraph *G,VertexType v,VertexType w)
 { /* 初始条件: 图G存在,v和w是G中两个顶点 */
   /* 操作结果: 在G中删除弧<v,w>,若G是无向的,则还删除对称弧<w,v> */
   int v1,w1;
   v1=LocateVex(*G,v); /* 尾 */
   w1=LocateVex(*G,w); /* 头 */
   if(v1<0||w1<0) /* v1、w1的值不合法 */
     return ERROR;
   if((*G).kind%2==0) /* 图 */
     (*G).arcs[v1][w1].adj=0;
   else /* 网 */
     (*G).arcs[v1][w1].adj=INFINITY;
   if((*G).arcs[v1][w1].info) /* 有其它信息 */
   {
     free((*G).arcs[v1][w1].info);
     (*G).arcs[v1][w1].info=NULL;
   }
   if((*G).kind>=2) /* 无向,删除对称弧<w,v> */
   {
     (*G).arcs[w1][v1].adj=(*G).arcs[v1][w1].adj;
     (*G).arcs[w1][v1].info=NULL;
   }
   (*G).arcnum--;
   return OK;
 }

 Boolean visited[MAX_VERTEX_NUM]; /* 访问标志数组(全局量) */
 Status(*VisitFunc)(VertexType); /* 函数变量 */
 void DFS(MGraph G,int v)
 { /* 从第v个顶点出发递归地深度优先遍历图G。算法7.5 */
   VertexType w1,v1;
   int w;
   visited[v]=TRUE; /* 设置访问标志为TRUE(已访问) */
   VisitFunc(G.vexs[v]); /* 访问第v个顶点 */
   strcpy(v1,*GetVex(G,v));
   for(w=FirstAdjVex(G,v1);w>=0;w=NextAdjVex(G,v1,strcpy(w1,*GetVex(G,w))))
     if(!visited[w])
       DFS(G,w); /* 对v的尚未访问的序号为w的邻接顶点递归调用DFS */
 }

 void DFSTraverse(MGraph G,Status(*Visit)(VertexType))
 { /* 初始条件: 图G存在,Visit是顶点的应用函数。算法7.4 */
   /* 操作结果: 从第1个顶点起,深度优先遍历图G,并对每个顶点调用函数Visit */
   /*           一次且仅一次。一旦Visit()失败,则操作失败 */
   int v;
   VisitFunc=Visit; /* 使用全局变量VisitFunc,使DFS不必设函数指针参数 */
   for(v=0;v<G.vexnum;v++)
     visited[v]=FALSE; /* 访问标志数组初始化(未被访问) */
   for(v=0;v<G.vexnum;v++)
     if(!visited[v])
       DFS(G,v); /* 对尚未访问的顶点调用DFS */
   printf("\n");
 }

 typedef VRType QElemType; /* 队列类型 */
 #include"c3-2.h" /* BFSTraverse()用 */
 #include"bo3-2.c" /* BFSTraverse()用 */
 void BFSTraverse(MGraph G,Status(*Visit)(VertexType))
 { /* 初始条件: 图G存在,Visit是顶点的应用函数。算法7.6 */
   /* 操作结果: 从第1个顶点起,按广度优先非递归遍历图G,并对每个顶点调用函数 */
   /*           Visit一次且仅一次。一旦Visit()失败,则操作失败。 */
   /*           使用辅助队列Q和访问标志数组visited */
   int v,u,w;
   VertexType w1,u1;
   LinkQueue Q;
   for(v=0;v<G.vexnum;v++)
     visited[v]=FALSE; /* 置初值 */
   InitQueue(&Q); /* 置空的辅助队列Q */
   for(v=0;v<G.vexnum;v++)
     if(!visited[v]) /* v尚未访问 */
     {
       visited[v]=TRUE; /* 设置访问标志为TRUE(已访问) */
       Visit(G.vexs[v]);
       EnQueue(&Q,v); /* v入队列 */
       while(!QueueEmpty(Q)) /* 队列不空 */
       {
         DeQueue(&Q,&u); /* 队头元素出队并置为u */
         strcpy(u1,*GetVex(G,u));
         for(w=FirstAdjVex(G,u1);w>=0;w=NextAdjVex(G,u1,strcpy(w1,*GetVex(G,w))))
           if(!visited[w]) /* w为u的尚未访问的邻接顶点的序号 */
           {
             visited[w]=TRUE;
             Visit(G.vexs[w]);
             EnQueue(&Q,w);
           }
       }
     }
   printf("\n");
 }

 void Display(MGraph G)
 { /* 输出邻接矩阵G */
   int i,j;
   char s[7],s1[3];
   switch(G.kind)
   {
     case DG: strcpy(s,"有向图\0");
              strcpy(s1,"弧\0");
              break;
     case DN: strcpy(s,"有向网\0");
              strcpy(s1,"弧\0");
              break;
     case AG: strcpy(s,"无向图\0");
              strcpy(s1,"边\0");
              break;
     case AN: strcpy(s,"无向网\0");
              strcpy(s1,"边\0");
   }
   printf("%d个顶点%d条%s的%s\n",G.vexnum,G.arcnum,s1,s);
   for(i=0;i<G.vexnum;++i) /* 输出G.vexs */
     printf("G.vexs[%d]=%s\n",i,G.vexs[i]);
   printf("G.arcs.adj:\n"); /* 输出G.arcs.adj */
   for(i=0;i<G.vexnum;i++)
   {
     for(j=0;j<G.vexnum;j++)
       printf("%6d",G.arcs[i][j].adj);
     printf("\n");
   }
   printf("G.arcs.info:\n"); /* 输出G.arcs.info */
   printf("顶点1(弧尾) 顶点2(弧头) 该%s信息：\n",s1);
   if(G.kind<2) /* 有向 */
     for(i=0;i<G.vexnum;i++)
       for(j=0;j<G.vexnum;j++)
       {
         if(G.arcs[i][j].info)
           printf("%5s %11s     %s\n",G.vexs[i],G.vexs[j],G.arcs[i][j].info);
       }
   else /* 无向 */
   {
     for(i=0;i<G.vexnum;i++)
       for(j=i+1;j<G.vexnum;j++)
	 if(G.arcs[i][j].info)
	   printf("%5s %11s     %s\n",G.vexs[i],G.vexs[j],G.arcs[i][j].info);
   }
 }


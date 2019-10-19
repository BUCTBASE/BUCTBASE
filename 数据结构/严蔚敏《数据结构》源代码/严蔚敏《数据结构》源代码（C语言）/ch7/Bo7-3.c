 /* bo7-3.c 有向图的十字链表存储(存储结构由c7-3.h定义)的基本函数(15个) */
 int LocateVex(OLGraph G,VertexType u)
 { /* 返回顶点u在有向图G中的位置(序号),如不存在则返回-1 */
   int i;
   for(i=0;i<G.vexnum;++i) /* 用循环查找该结点 */
     if(!strcmp(G.xlist[i].data,u))
       return i;
   return -1;
 }

 Status CreateDG(OLGraph *G)
 { /* 采用十字链表存储表示,构造有向图G。算法7.3 */
   int i,j,k;
   int IncInfo;
   char str[MAX_Info];
   ArcBox *p;
   VertexType v1,v2;
   printf("请输入有向图的顶点数,弧数,弧是否含其它信息(是:1，否:0): ");
   scanf("%d,%d,%d",&(*G).vexnum,&(*G).arcnum,&IncInfo);
   printf("请输入%d个顶点的值(<%d个字符):\n",(*G).vexnum,MAX_VERTEX_NAME);
   for(i=0;i<(*G).vexnum;++i)
   { /* 构造表头向量 */
     scanf("%s",&(*G).xlist[i].data); /* 输入顶点值 */
     (*G).xlist[i].firstin=NULL; /* 初始化指针 */
     (*G).xlist[i].firstout=NULL;
   }
   printf("请输入%d条弧的弧尾和弧头(空格为间隔):\n",(*G).arcnum);
   for(k=0;k<(*G).arcnum;++k)
   { /* 输入各弧并构造十字链表 */
     scanf("%s%s",&v1,&v2);
     i=LocateVex(*G,v1); /* 确定v1和v2在G中的位置 */
     j=LocateVex(*G,v2);
     p=(ArcBox *)malloc(sizeof(ArcBox)); /* 产生弧结点(假定有足够空间) */
     p->tailvex=i; /* 对弧结点赋值 */
     p->headvex=j;
     p->hlink=(*G).xlist[j].firstin; /* 完成在入弧和出弧链表表头的插入 */
     p->tlink=(*G).xlist[i].firstout;
     (*G).xlist[j].firstin=(*G).xlist[i].firstout=p;
     if(IncInfo)
     { /* 若弧含有相关信息，则输入 */
       printf("请输入该弧的相关信息(<%d个字符): ",MAX_Info);
       scanf("%s",str);
       p->info=(InfoType *)malloc((strlen(str)+1)*sizeof(InfoType));
       strcpy(p->info,str);
     }
     else /* 弧不含有相关信息 */
       p->info=NULL;
   }
   return OK;
 }

 void DestroyGraph(OLGraph *G)
 { /* 初始条件: 有向图G存在 */
   /* 操作结果: 销毁有向图G */
   int j;
   ArcBox *p,*q;
   for(j=0;j<(*G).vexnum;j++) /* 对所有顶点 */
   {
     p=(*G).xlist[j].firstout; /* 仅处理出弧 */
     while(p)
     {
       q=p;
       p=p->tlink;
       if(q->info)
         free(q->info);
       free(q);
     }
   }
   (*G).arcnum=0;
   (*G).vexnum=0;
 }

 VertexType* GetVex(OLGraph G,int v)
 { /* 初始条件:有向图G存在,v是G中某个顶点的序号。操作结果:返回v的值 */
   if(v>=G.vexnum||v<0)
     exit(ERROR);
   return &G.xlist[v].data;
 }

 Status PutVex(OLGraph *G,VertexType v,VertexType value)
 { /* 初始条件: 有向图G存在,v是G中某个顶点 */
   /* 操作结果: 对v赋新值value */
   int i;
   i=LocateVex(*G,v);
   if(i<0) /* v不是G的顶点 */
     return ERROR;
   strcpy((*G).xlist[i].data,value);
   return OK;
 }

 int FirstAdjVex(OLGraph G,VertexType v)
 { /* 初始条件: 有向图G存在,v是G中某个顶点 */
   /* 操作结果: 返回v的第一个邻接顶点的序号。若顶点在G中没有邻接顶点,则返回-1 */
   int i;
   ArcBox *p;
   i=LocateVex(G,v);
   p=G.xlist[i].firstout; /* p指向顶点v的第1个出弧 */
   if(p)
     return p->headvex;
   else
     return -1;
 }

 int NextAdjVex(OLGraph G,VertexType v,VertexType w)
 { /* 初始条件: 有向图G存在,v是G中某个顶点,w是v的邻接顶点 */
   /* 操作结果: 返回v的(相对于w的)下一个邻接顶点的序号, */
   /*           若w是v的最后一个邻接顶点,则返回-1 */
   int i,j;
   ArcBox *p;
   i=LocateVex(G,v); /* i是顶点v的序号 */
   j=LocateVex(G,w); /* j是顶点w的序号 */
   p=G.xlist[i].firstout; /* p指向顶点v的第1个出弧 */
   while(p&&p->headvex!=j)
     p=p->tlink;
   if(p) /* w不是v的最后一个邻接顶点 */
     p=p->tlink; /* p指向相对于w的下一个邻接顶点 */
   if(p) /* 有下一个邻接顶点 */
     return p->headvex;
   else
     return -1;
 }

 void InsertVex(OLGraph *G,VertexType v)
 { /* 初始条件: 有向图G存在,v和有向图G中顶点有相同特征 */
   /* 操作结果: 在有向图G中增添新顶点v(不增添与顶点相关的弧,留待InsertArc()去做) */
   strcpy((*G). xlist[(*G). vexnum].data,v);
   (*G). xlist[(*G). vexnum].firstin=(*G). xlist[(*G). vexnum].firstout=NULL;
   (*G). vexnum++;
 }

 Status DeleteVex(OLGraph *G,VertexType v)
 { /* 初始条件: 有向图G存在,v是G中某个顶点 */
   /* 操作结果: 删除G中顶点v及其相关的弧 */
   int j,k;
   ArcBox *p,*q;
   k=LocateVex(*G,v); /* k是顶点v的序号 */
   if(k<0) /* v不是图G的顶点 */
     return ERROR;
   /* 以下删除顶点v的出弧 */
   for(j=0;j<(*G). vexnum;j++) /* 顶点v的出弧是其它顶点的入弧 */
   {
     if(j==k)
       continue;
     p=(*G). xlist[j].firstin; /* 在其它顶点的入弧链表中删除顶点v的出弧 */
     while(p)
       if(p->tailvex==k&&p==(*G). xlist[j].firstin) /* 待删结点为首结点 */
       {
         (*G). xlist[j].firstin=p->hlink;
         break;
       }
       else if(p->tailvex!=k) /* 没找到待删结点 */
       {
         q=p;
         p=p->hlink;
       }
       else /* 找到待删结点且不是首结点 */
       {
         q->hlink=p->hlink;
         break;
       }
   }
   p=(*G). xlist[k].firstout; /* 删除与顶点v有关的出弧 */
   while(p)
   {
     q=p->tlink; /* q指向p的下一个出弧 */
     if(p->info) /* 释放p */
       free(p->info);
     free(p);
     (*G). arcnum--;
     p=q;
   }
   /* 以下删除顶点v的入弧 */
   for(j=0;j<(*G). vexnum;j++) /* 顶点v的入弧是其它顶点的出弧 */
   {
     if(j==k)
       continue;
     p=(*G). xlist[j].firstout; /* 在其它顶点的出弧链表中删除顶点v的入弧 */
     while(p)
       if(p->headvex==k&&p==(*G). xlist[j].firstout) /* 待删结点为首结点 */
       {
         (*G). xlist[j].firstout=p->tlink;
         break;
       }
       else if(p->headvex!=k) /* 没找到待删结点 */
       {
         q=p;
         p=p->tlink;
       }
       else /* 找到待删结点且不是首结点 */
       {
         q->tlink=p->tlink;
         break;
       }
   }
   p=(*G). xlist[k].firstin; /* 删除与顶点v有关的入弧 */
   while(p)
   {
     q=p->hlink; /* q指向p的下一个入弧 */
     if(p->info) /* 释放p */
       free(p->info);
     free(p);
     (*G). arcnum--;
     p=q;
   }
   for(j=k+1;j<(*G). vexnum;j++) /* 序号>k的顶点依次向前移 */
     (*G). xlist[j-1]=(*G). xlist[j];
   (*G). vexnum--; /* 顶点数减1 */
   for(j=0;j<(*G). vexnum;j++) /* 结点序号>k的要减1 */
   {
     p=(*G). xlist[j].firstout; /* 处理出弧 */
     while(p)
     {
       if(p->tailvex>k)
         p->tailvex--; /* 序号-1 */
       if(p->headvex>k)
         p->headvex--; /* 序号-1 */
       p=p->tlink;
     }
   }
   return OK;
 }

 Status InsertArc(OLGraph *G,VertexType v,VertexType w)
 { /* 初始条件: 有向图G存在,v和w是G中两个顶点 */
   /* 操作结果: 在G中增添弧<v,w> */
   int i,j;
   int IncInfo;
   char str[MAX_Info];
   ArcBox *p;
   i=LocateVex(*G,v); /* 弧尾的序号 */
   j=LocateVex(*G,w); /* 弧头的序号 */
   if(i<0||j<0)
     return ERROR;
   p=(ArcBox *)malloc(sizeof(ArcBox)); /* 生成新结点 */
   p->tailvex=i; /* 给新结点赋值 */
   p->headvex=j;
   p->hlink=(*G). xlist[j].firstin; /* 插在入弧和出弧的链头 */
   p->tlink=(*G). xlist[i].firstout;
   (*G). xlist[j].firstin=(*G). xlist[i].firstout=p;
   (*G). arcnum++; /* 弧数加1 */
   printf("要插入的弧是否含有其它信息(是: 1,否: 0): ");
   scanf("%d",&IncInfo);
   if(IncInfo)
   {
     printf("请输入该弧的相关信息(<%d个字符): ",MAX_Info);
     scanf("%s",str);
     p->info=(InfoType *)malloc((strlen(str)+1)*sizeof(InfoType));
     strcpy(p->info,str);
   }
   else
     p->info=NULL;
   return OK;
 }

 Status DeleteArc(OLGraph *G,VertexType v,VertexType w)
 { /* 初始条件: 有向图G存在,v和w是G中两个顶点 */
   /* 操作结果: 在G中删除弧<v,w> */
   int i,j;
   ArcBox *p1,*p2;
   i=LocateVex(*G,v); /* 弧尾的序号 */
   j=LocateVex(*G,w); /* 弧头的序号 */
   if(i<0||j<0||i==j)
     return ERROR;
   p2=(*G). xlist[i].firstout; /* 将弧结点从出弧链表中删去 */
   if(p2&&p2->headvex==j) /* 第1个结点为待删除结点 */
     (*G). xlist[i].firstout=p2->tlink;
   else
   {
     while(p2&&p2->headvex!=j) /* 向后找 */
     {
       p1=p2;
       p2=p2->tlink;
     }
     if(p2) /* 没到表尾 */
       p1->tlink=p2->tlink;
   }
   p2=(*G). xlist[j].firstin; /* 将弧结点从入弧链表中删去 */
   if(p2&&p2->tailvex==i)
     (*G). xlist[j].firstin=p2->hlink;
   else
   {
     while(p2&&p2->tailvex!=i)
     {
       p1=p2;
       p2=p2->hlink;
     }
     if(p2) /* 没到表尾 */
       p1->hlink=p2->hlink;
   }
   if(p2->info) /* 释放弧结点 */
     free(p2->info);
   free(p2);
   (*G). arcnum--; /* 弧数减1 */
   return OK;
 }

 Boolean visited[MAX_VERTEX_NUM]; /* 访问标志数组 */
 Status(*VisitFunc)(VertexType); /* 函数变量 */
 void DFS(OLGraph G,int i) /* DFSTraverse()调用 */
 {
   ArcBox *p;
   visited[i]=TRUE; /* 访问标志数组置1(已被访问) */
   VisitFunc(G.xlist[i].data); /* 遍历第i个顶点 */
   p=G.xlist[i].firstout; /* p指向第i个顶点的出度 */
   while(p&&visited[p->headvex]) /* p没到表尾且该弧的头顶点已被访问 */
     p=p->tlink; /* 查找下一个结点 */
   if(p&&!visited[p->headvex]) /* 该弧的头顶点未被访问 */
     DFS(G,p->headvex); /* 递归调用DFS() */
 }

 void DFSTraverse(OLGraph G,Status(*Visit)(VertexType))
 { /* 初始条件: 有向图G存在,v是G中某个顶点,Visit是顶点的应用函数 */
   /* 操作结果: 从第1个顶点起,按深度优先递归遍历有向图G,并对每个顶点调用 */
   /*           函数Visit一次且仅一次。一旦Visit()失败,则操作失败 */
   int i;
   for(i=0;i<G.vexnum;i++)
     visited[i]=FALSE; /* 访问标志数组置初值(未被访问) */
   VisitFunc=Visit;
   for(i=0;i<G.vexnum;i++) /* 由序号0开始,继续查找未被访问过的顶点 */
     if(!visited[i])
       DFS(G,i);
   printf("\n");
 }

 typedef int QElemType;
 #include"c3-3.h"
 #include"bo3-3.c"
 void BFSTraverse(OLGraph G,Status(*Visit)(VertexType))
 { /* 初始条件: 有向图G存在,Visit是顶点的应用函数。算法7.6 */
   /* 操作结果: 从第1个顶点起,按广度优先非递归遍历有向图G,并对每个顶点调用 */
   /*           函数Visit一次且仅一次。一旦Visit()失败,则操作失败。 */
   /*           使用辅助队列Q和访问标志数组visited */
   int v,u,w;
   VertexType u1,w1;
   SqQueue Q;
   for(v=0;v<G.vexnum;v++)
     visited[v]=FALSE;
   InitQueue(&Q);
   for(v=0;v<G.vexnum;v++)
     if(!visited[v])
     {
       visited[v]=TRUE;
       Visit(G.xlist[v].data);
       EnQueue(&Q,v);
       while(!QueueEmpty(Q))
       {
         DeQueue(&Q,&u);
         strcpy(u1,*GetVex(G,u));
         for(w=FirstAdjVex(G,u1);w>=0;w=NextAdjVex(G,u1,strcpy(w1,*GetVex(G,w))))
           if(!visited[w]) /* w为u的尚未访问的邻接顶点的序号 */
           {
             visited[w]=TRUE;
             Visit(G.xlist[w].data);
             EnQueue(&Q,w);
           }
       }
     }
   printf("\n");
 }

 void Display(OLGraph G)
 { /* 输出有向图G */
   int i;
   ArcBox *p;
   printf("共%d个顶点,%d条弧:\n",G.vexnum,G.arcnum);
   for(i=0;i<G.vexnum;i++)
   {
     printf("顶点%s: 入度: ",G.xlist[i].data);
     p=G.xlist[i].firstin;
     while(p)
     {
       printf("%s ",G.xlist[p->tailvex].data);
       p=p->hlink;
     }
     printf("出度: ");
     p=G.xlist[i].firstout;
     while(p)
     {
       printf("%s ",G.xlist[p->headvex].data);
       if(p->info) /* 该弧有相关信息 */
         printf("弧信息: %s ",p->info);
       p=p->tlink;
     }
     printf("\n");
   }
 }

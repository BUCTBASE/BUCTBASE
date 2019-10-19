 /* bo7-4.c 无向图的邻接多重表存储(存储结构由c7-4.h定义)的基本函数类型(16个) */
 int LocateVex(AMLGraph G,VertexType u)
 { /* 初始条件: 无向图G存在,u和G中顶点有相同特征 */
   /* 操作结果: 若G中存在顶点u,则返回该顶点在无向图中位置;否则返回-1 */
   int i;
   for(i=0;i<G.vexnum;++i)
     if(strcmp(u,G.adjmulist[i].data)==0)
       return i;
   return -1;
 }

 Status CreateGraph(AMLGraph *G)
 { /* 采用邻接多重表存储结构,构造无向图G */
   int i,j,k,l,IncInfo;
   char s[MAX_INFO];
   VertexType va,vb;
   EBox *p;
   printf("请输入无向图G的顶点数,边数,边是否含其它信息(是:1，否:0): ");
   scanf("%d,%d,%d",&(*G).vexnum,&(*G).edgenum,&IncInfo);
   printf("请输入%d个顶点的值(<%d个字符):\n",(*G).vexnum,MAX_NAME);
   for(i=0;i<(*G).vexnum;++i) /* 构造顶点向量 */
   {
     scanf("%s",(*G).adjmulist[i].data);
     (*G).adjmulist[i].firstedge=NULL;
   }
   printf("请顺序输入每条边的两个端点(以空格作为间隔):\n");
   for(k=0;k<(*G).edgenum;++k) /* 构造表结点链表 */
   {
     scanf("%s%s%*c",va,vb); /* %*c吃掉回车符 */
     i=LocateVex(*G,va); /* 一端 */
     j=LocateVex(*G,vb); /* 另一端 */
     p=(EBox*)malloc(sizeof(EBox));
     p->mark=unvisited; /* 设初值 */
     p->ivex=i;
     p->jvex=j;
     p->info=NULL;
     p->ilink=(*G).adjmulist[i].firstedge; /* 插在表头 */
     (*G).adjmulist[i].firstedge=p;
     p->jlink=(*G).adjmulist[j].firstedge; /* 插在表头 */
     (*G).adjmulist[j].firstedge=p;
     if(IncInfo) /* 边有相关信息 */
     {
       printf("请输入该弧的相关信息(<%d个字符)：",MAX_INFO);
       gets(s);
       l=strlen(s);
       if(l)
       {
         p->info=(char*)malloc((l+1)*sizeof(char));
         strcpy(p->info,s);
       }
     }
   }
   return OK;
 }

 VertexType* GetVex(AMLGraph G,int v)
 { /* 初始条件: 无向图G存在,v是G中某个顶点的序号。操作结果: 返回v的值 */
   if(v>=G.vexnum||v<0)
     exit(ERROR);
   return &G.adjmulist[v].data;
 }

 Status PutVex(AMLGraph *G,VertexType v,VertexType value)
 { /* 初始条件: 无向图G存在,v是G中某个顶点 */
   /* 操作结果: 对v赋新值value */
   int i;
   i=LocateVex(*G,v);
   if(i<0) /* v不是G的顶点 */
     return ERROR;
   strcpy((*G).adjmulist[i].data,value);
   return OK;
 }

 int FirstAdjVex(AMLGraph G,VertexType v)
 { /* 初始条件: 无向图G存在,v是G中某个顶点 */
   /* 操作结果: 返回v的第一个邻接顶点的序号。若顶点在G中没有邻接顶点,则返回-1 */
   int i;
   i=LocateVex(G,v);
   if(i<0)
     return -1;
   if(G.adjmulist[i].firstedge) /* v有邻接顶点 */
     if(G.adjmulist[i].firstedge->ivex==i)
       return G.adjmulist[i].firstedge->jvex;
     else
       return G.adjmulist[i].firstedge->ivex;
   else
     return -1;
 }

 int NextAdjVex(AMLGraph G,VertexType v,VertexType w)
 { /* 初始条件: 无向图G存在,v是G中某个顶点,w是v的邻接顶点 */
   /* 操作结果: 返回v的(相对于w的)下一个邻接顶点的序号。 */
   /*           若w是v的最后一个邻接点,则返回-1 */
   int i,j;
   EBox *p;
   i=LocateVex(G,v); /* i是顶点v的序号 */
   j=LocateVex(G,w); /* j是顶点w的序号 */
   if(i<0||j<0) /* v或w不是G的顶点 */
     return -1;
   p=G.adjmulist[i].firstedge; /* p指向顶点v的第1条边 */
   while(p)
     if(p->ivex==i&&p->jvex!=j) /* 不是邻接顶点w(情况1) */
       p=p->ilink; /* 找下一个邻接顶点 */
     else if(p->jvex==i&&p->ivex!=j) /* 不是邻接顶点w(情况2) */
       p=p->jlink; /* 找下一个邻接顶点 */
     else /* 是邻接顶点w */
       break;
   if(p&&p->ivex==i&&p->jvex==j) /* 找到邻接顶点w(情况1) */
   {
     p=p->ilink;
     if(p&&p->ivex==i)
       return p->jvex;
     else if(p&&p->jvex==i)
       return p->ivex;
   }
   if(p&&p->ivex==j&&p->jvex==i) /* 找到邻接顶点w(情况2) */
   {
     p=p->jlink;
     if(p&&p->ivex==i)
       return p->jvex;
     else if(p&&p->jvex==i)
       return p->ivex;
   }
   return -1;
 }

 Status InsertVex(AMLGraph *G,VertexType v)
 { /* 初始条件: 无向图G存在,v和G中顶点有相同特征 */
   /* 操作结果: 在G中增添新顶点v(不增添与顶点相关的弧,留待InsertArc()去做) */
   if((*G).vexnum==MAX_VERTEX_NUM) /* 结点已满，不能插入 */
     return ERROR;
   if(LocateVex(*G,v)>=0) /* 结点已存在,不能插入 */
     return ERROR;
   strcpy((*G).adjmulist[(*G).vexnum].data,v);
   (*G).adjmulist[(*G).vexnum].firstedge=NULL;
   (*G).vexnum++;
   return OK;
 }

 Status DeleteArc(AMLGraph *G,VertexType v,VertexType w)
 { /* 初始条件: 无向图G存在,v和w是G中两个顶点 */
   /* 操作结果: 在G中删除弧<v,w> */
   int i,j;
   EBox *p,*q;
   i=LocateVex(*G,v);
   j=LocateVex(*G,w);
   if(i<0||j<0||i==j)
     return ERROR;  /* 图中没有该点或弧 */
   /* 以下使指向待删除边的第1个指针绕过这条边 */
   p=(*G).adjmulist[i].firstedge; /* p指向顶点v的第1条边 */
   if(p&&p->jvex==j) /* 第1条边即为待删除边(情况1) */
     (*G).adjmulist[i].firstedge=p->ilink;
   else if(p&&p->ivex==j) /* 第1条边即为待删除边(情况2) */
     (*G).adjmulist[i].firstedge=p->jlink;
   else /* 第1条边不是待删除边 */
   {
     while(p) /* 向后查找弧<v,w> */
     {
       if(p->ivex==i&&p->jvex!=j) /* 不是待删除边 */
       {
         q=p;
         p=p->ilink; /* 找下一个邻接顶点 */
       }
       else if(p->jvex==i&&p->ivex!=j) /* 不是待删除边 */
       {
         q=p;
         p=p->jlink; /* 找下一个邻接顶点 */
       }
       else /* 是邻接顶点w */
         break;
     }
     if(!p) /* 没找到该边 */
       return ERROR;
     if(p->ivex==i&&p->jvex==j) /* 找到弧<v,w>(情况1) */
       if(q->ivex==i)
         q->ilink=p->ilink;
       else
         q->jlink=p->ilink;
     else if(p->ivex==j&&p->jvex==i) /* 找到弧<v,w>(情况2) */
       if(q->ivex==i)
         q->ilink=p->jlink;
       else
         q->jlink=p->jlink;
   }
   /* 以下由另一顶点起找待删除边且删除之 */
   p=(*G).adjmulist[j].firstedge; /* p指向顶点w的第1条边 */
   if(p->jvex==i) /* 第1条边即为待删除边(情况1) */
   {
     (*G).adjmulist[j].firstedge=p->ilink;
     if(p->info) /* 有相关信息 */
       free(p->info);
     free(p);
   }
   else if(p->ivex==i) /* 第1条边即为待删除边(情况2) */
   {
     (*G).adjmulist[j].firstedge=p->jlink;
     if(p->info) /* 有相关信息 */
       free(p->info);
     free(p);
   }
   else /* 第1条边不是待删除边 */
   {
     while(p) /* 向后查找弧<v,w> */
       if(p->ivex==j&&p->jvex!=i) /* 不是待删除边 */
       {
         q=p;
         p=p->ilink; /* 找下一个邻接顶点 */
       }
       else if(p->jvex==j&&p->ivex!=i) /* 不是待删除边 */
       {
         q=p;
         p=p->jlink; /* 找下一个邻接顶点 */
       }
       else /* 是邻接顶点v */
         break;
     if(p->ivex==i&&p->jvex==j) /* 找到弧<v,w>(情况1) */
     {
       if(q->ivex==j)
         q->ilink=p->jlink;
       else
         q->jlink=p->jlink;
       if(p->info) /* 有相关信息 */
         free(p->info);
       free(p);
     }
     else if(p->ivex==j&&p->jvex==i) /* 找到弧<v,w>(情况2) */
     {
       if(q->ivex==j)
         q->ilink=p->ilink;
       else
         q->jlink=p->ilink;
       if(p->info) /* 有相关信息 */
         free(p->info);
       free(p);
     }
   }
   (*G).edgenum--;
   return OK;
 }

 Status DeleteVex(AMLGraph *G,VertexType v)
 { /* 初始条件: 无向图G存在,v是G中某个顶点 */
   /* 操作结果: 删除G中顶点v及其相关的边 */
   int i,j;
   VertexType w;
   EBox *p;
   i=LocateVex(*G,v); /* i为待删除顶点的序号 */
   if(i<0)
     return ERROR;
   for(j=0;j<(*G).vexnum;j++) /* 删除与顶点v相连的边(如果有的话) */
   {
     if(j==i)
       continue;
     strcpy(w,*GetVex(*G,j)); /* w是第j个顶点的值 */
     DeleteArc(G,v,w);
   }
   for(j=i+1;j<(*G).vexnum;j++) /* 排在顶点v后面的顶点的序号减1 */
     (*G).adjmulist[j-1]=(*G).adjmulist[j];
   (*G).vexnum--; /* 顶点数减1 */
   for(j=i;j<(*G).vexnum;j++) /* 修改顶点的序号 */
   {
     p=(*G).adjmulist[j].firstedge;
     if(p)
     {
       if(p->ivex==j+1)
       {
         p->ivex--;
         p=p->ilink;
       }
       else
       {
         p->jvex--;
         p=p->jlink;
       }
     }
   }
   return OK;
 }

 void DestroyGraph(AMLGraph *G)
 {
   int i;
   for(i=(*G).vexnum-1;i>=0;i--)
     DeleteVex(G,(*G).adjmulist[i].data);
 }

 Status InsertArc(AMLGraph *G,VertexType v,VertexType w)
 { /* 初始条件: 无向图G存在,v和W是G中两个顶点 */
   /* 操作结果: 在G中增添弧<v,w> */
   int i,j,l,IncInfo;
   char s[MAX_INFO];
   EBox *p;
   i=LocateVex(*G,v); /* 一端 */
   j=LocateVex(*G,w); /* 另一端 */
   if(i<0||j<0)
     return ERROR;
   p=(EBox*)malloc(sizeof(EBox));
   p->mark=unvisited;
   p->ivex=i;
   p->jvex=j;
   p->info=NULL;
   p->ilink=(*G).adjmulist[i].firstedge; /* 插在表头 */
   (*G).adjmulist[i].firstedge=p;
   p->jlink=(*G).adjmulist[j].firstedge; /* 插在表头 */
   (*G).adjmulist[j].firstedge=p;
   printf("该边是否有相关信息(1:有 0:无): ");
   scanf("%d%*c",&IncInfo); /* 吃掉回车符 */
   if(IncInfo) /* 边有相关信息 */
   {
     printf("请输入该边的相关信息(<%d个字符)：",MAX_INFO);
     gets(s);
     l=strlen(s);
     if(l)
     {
       p->info=(char*)malloc((l+1)*sizeof(char));
       strcpy(p->info,s);
     }
   }
   (*G).edgenum++;
   return OK;
 }

 Boolean visite[MAX_VERTEX_NUM]; /* 访问标志数组(全局量) */
 Status(*VisitFunc)(VertexType v);
 void DFS(AMLGraph G,int v)
 {
   int j;
   EBox *p;
   VisitFunc(G.adjmulist[v].data);
   visite[v]=TRUE;
   p=G.adjmulist[v].firstedge;
   while(p)
   {
     j=p->ivex==v?p->jvex:p->ivex;
     if(!visite[j])
       DFS(G,j);
     p=p->ivex==v?p->ilink:p->jlink;
   }
 }

 void DFSTraverse(AMLGraph G,Status(*visit)(VertexType))
 { /* 初始条件: 图G存在,Visit是顶点的应用函数。算法7.4 */
   /* 操作结果: 从第1个顶点起,深度优先遍历图G,并对每个顶点调用函数Visit */
   /*           一次且仅一次。一旦Visit()失败,则操作失败 */
   int v;
   VisitFunc=visit;
   for(v=0;v<G.vexnum;v++)
     visite[v]=FALSE;
   for(v=0;v<G.vexnum;v++)
     if(!visite[v])
       DFS(G,v);
   printf("\n");
 }

 typedef int QElemType; /* 队列类型 */
 #include"c3-2.h" /* BFSTraverse()用 */
 #include"bo3-2.c" /* BFSTraverse()用 */
 void BFSTraverse(AMLGraph G,Status(*Visit)(VertexType))
 { /* 初始条件: 图G存在,Visit是顶点的应用函数。算法7.6 */
   /* 操作结果: 从第1个顶点起,按广度优先非递归遍历图G,并对每个顶点调用函数 */
   /*           Visit一次且仅一次。一旦Visit()失败,则操作失败。 */
   /*           使用辅助队列Q和访问标志数组visite */
   int v,u,w;
   VertexType w1,u1;
   LinkQueue Q;
   for(v=0;v<G.vexnum;v++)
     visite[v]=FALSE; /* 置初值 */
   InitQueue(&Q); /* 置空的辅助队列Q */
   for(v=0;v<G.vexnum;v++)
     if(!visite[v]) /* v尚未访问 */
     {
       visite[v]=TRUE; /* 设置访问标志为TRUE(已访问) */
       Visit(G.adjmulist[v].data);
       EnQueue(&Q,v); /* v入队列 */
       while(!QueueEmpty(Q)) /* 队列不空 */
       {
         DeQueue(&Q,&u); /* 队头元素出队并置为u */
         strcpy(u1,*GetVex(G,u));
         for(w=FirstAdjVex(G,u1);w>=0;w=NextAdjVex(G,u1,strcpy(w1,*GetVex(G,w))))
           if(!visite[w]) /* w为u的尚未访问的邻接顶点的序号 */
           {
             visite[w]=TRUE;
             Visit(G.adjmulist[w].data);
             EnQueue(&Q,w);
           }
       }
     }
   printf("\n");
 }

 void MarkUnvizited(AMLGraph G)
 { /* 置边的访问标记为未被访问 */
   int i;
   EBox *p;
   for(i=0;i<G.vexnum;i++)
   {
     p=G.adjmulist[i].firstedge;
     while(p)
     {
       p->mark=unvisited;
       if(p->ivex==i)
         p=p->ilink;
       else
         p=p->jlink;
     }
   }
 }

 void Display(AMLGraph G)
 { /* 输出无向图的邻接多重表G */
   int i;
   EBox *p;
   MarkUnvizited(G); /* 置边的访问标记为未被访问 */
   printf("%d个顶点：\n",G.vexnum);
   for(i=0;i<G.vexnum;++i)
     printf("%s ",G.adjmulist[i].data);
   printf("\n%d条边:\n",G.edgenum);
   for(i=0;i<G.vexnum;i++)
   {
     p=G.adjmulist[i].firstedge;
     while(p)
       if(p->ivex==i) /* 边的i端与该顶点有关 */
       {
         if(!p->mark) /* 只输出一次 */
         {
           printf("%s－%s ",G.adjmulist[i].data,G.adjmulist[p->jvex].data);
           p->mark=visited;
           if(p->info) /* 输出附带信息 */
             printf("相关信息: %s ",p->info);
         }
         p=p->ilink;
       }
       else /* 边的j端与该顶点有关 */
       {
         if(!p->mark) /* 只输出一次 */
         {
           printf("%s－%s ",G.adjmulist[p->ivex].data,G.adjmulist[i].data);
           p->mark=visited;
           if(p->info) /* 输出附带信息 */
             printf("相关信息: %s ",p->info);
         }
         p=p->jlink;
       }
     printf("\n");
   }
 }


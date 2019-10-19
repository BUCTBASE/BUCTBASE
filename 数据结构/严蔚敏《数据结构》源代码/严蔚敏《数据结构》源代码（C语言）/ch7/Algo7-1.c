 /* algo7-1.c 调用算法7.7、7.8 */
 #include"c1.h"
 #define MAX_NAME 2 /* 顶点字符串的最大长度+1 */
 typedef char ElemType[MAX_NAME];
 typedef ElemType TElemType;
 #include"c6-5.h"
 typedef int InfoType;
 typedef char VertexType[MAX_NAME];
 #include"c7-2.h"
 #include"bo7-2.c"

 void DFSTree(ALGraph G,int v,CSTree *T)
 { /* 从第v个顶点出发深度优先遍历图G,建立以T为根的生成树。算法7.8 */
   Boolean first=TRUE;
   int w;
   CSTree p,q;
   VertexType v1,w1;
   visited[v]=TRUE;
   strcpy(v1,*GetVex(G,v));
   for(w=FirstAdjVex(G,v1);w>=0;w=NextAdjVex(G,v1,strcpy(w1,*GetVex(G,w)))) /* w依次为v的邻接顶点 */
     if(!visited[w]) /* w顶点不曾被访问 */
     {
       p=(CSTree)malloc(sizeof(CSNode)); /* 分配孩子结点 */
       strcpy(p->data,*GetVex(G,w));
       p->firstchild=NULL;
       p->nextsibling=NULL;
       if(first)
       { /* w是v的第一个未被访问的邻接顶点 */
         (*T)->firstchild=p;
         first=FALSE; /* 是根的第一个孩子结点 */
       }
       else /* w是v的其它未被访问的邻接顶点 */
	 q->nextsibling=p; /* 是上一邻接顶点的兄弟姐妹结点 */
       q=p;
       DFSTree(G,w,&q); /* 从第w个顶点出发深度优先遍历图G,建立子生成树q */
     }
 }

 void DFSForest(ALGraph G,CSTree *T)
 { /* 建立无向图G的深度优先生成森林的(最左)孩子(右)兄弟链表T。算法7.7 */
   CSTree p,q;
   int v;
   *T=NULL;
   for(v=0;v<G.vexnum;++v)
     visited[v]=FALSE; /* 赋初值 */
   for(v=0;v<G.vexnum;++v) /* 从第0个顶点找起 */
     if(!visited[v])
     { /* 第v顶点为新的生成树的根结点 */
       p=(CSTree)malloc(sizeof(CSNode)); /* 分配根结点 */
       strcpy(p->data,*GetVex(G,v));
       p->firstchild=NULL;
       p->nextsibling=NULL;
       if(!*T) /* 是第一棵生成树的根(T的根) */
         *T=p;
       else /* 是其它生成树的根(前一棵的根的＂兄弟＂) */
         q->nextsibling=p;
       q=p; /* q指示当前生成树的根 */
       DFSTree(G,v,&p); /* 建立以p为根的生成树 */
     }
 }

 void PreOrderTraverse(CSTree T,void(*Visit)(TElemType))
 { /* 先根遍历孩子－兄弟二叉链表结构的树T(bo6-5.c改) */
   if(T)
   {
     Visit(T->data); /* 先访问根结点 */
     PreOrderTraverse(T->firstchild,Visit); /* 再先根遍历长子子树 */
     PreOrderTraverse(T->nextsibling,Visit); /* 最后先根遍历下一个兄弟子树 */
   }
 }

 void print(char *i)
 {
   printf("%s ",i);
 }

 void main()
 {
   ALGraph g;
   CSTree t;
   printf("请选择无向图\n");
   CreateGraph(&g);
   Display(g);
   DFSForest(g,&t);
   printf("先根遍历生成森林：\n");
   PreOrderTraverse(t,print);
   printf("\n");
 }

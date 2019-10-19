 /* bo11-1.c k路平衡归并的函数 */
 FILE *fp[k+1]; /* k+1个文件指针(fp[k]为大文件指针)，全局变量 */
 typedef int LoserTree[k]; /* 败者树是完全二叉树且不含叶子，可采用顺序存储结构 */
 typedef RedType ExNode,External[k+1]; /* 外结点,有改变 */
 External b; /* 全局变量 */
 #define MINKEY INT_MIN
 #define MAXKEY INT_MAX

 void input(int i,KeyType *a)
 { /* 从第i个文件(第i个归并段)读入该段当前第1个记录的关键字到外结点 */
   fread(a,sizeof(KeyType),1,fp[i]);
 }

 void output(int i)
 { /* 将第i个文件(第i个归并段)中当前的记录写至输出归并段 */
   ExNode a;
   a.key=b[i].key; /* 当前记录的关键字已读到b[i].key中 */
   fread(&a.otherinfo,sizeof(InfoType),1,fp[i]);
   fwrite(&a,sizeof(ExNode),1,fp[k]);
 }

 void Adjust(LoserTree ls,int s)
 { /* 沿从叶子结点b[s]到根结点ls[0]的路径调整败者树。算法11.2 */
   int i,t;
   t=(s+k)/2; /* ls[t]是b[s]的双亲结点 */
   while(t>0)
   {
     if(b[s].key>b[ls[t]].key)
     {
       i=s;
       s=ls[t]; /* s指示新的胜者 */
       ls[t]=i;
     }
     t=t/2;
   }
   ls[0]=s;
 }

 void CreateLoserTree(LoserTree ls)
 { /* 已知b[0]到b[k-1]为完全二叉树ls的叶子结点，存有k个关键字，沿从叶子 */
   /* 到根的k条路径将ls调整成为败者树。算法11.3 */
   int i;
   b[k].key=MINKEY;
   for(i=0;i<k;++i)
     ls[i]=k; /* 设置ls中“败者”的初值 */
   for(i=k-1;i>=0;--i) /* 依次从b[k-1]，b[k-2]，…，b[0]出发调整败者 */
     Adjust(ls,i);
 }

 void K_Merge(LoserTree ls,External b)
 { /* 利用败者树ls将编号从0到k-1的k个输入归并段中的记录归并到输出归并段。 */
   /* b[0]至b[k-1]为败者树上的k个叶子结点，分别存放k个输入归并段中当前 */
   /* 记录的关键字。算法11.1 */
   int i,q;
   for(i=0;i<k;++i) /* 分别从k个输入归并段读人该段当前第一个记录的关键字到外结点 */
     input(i,&b[i].key);
   CreateLoserTree(ls); /* 建败者树ls，选得最小关键字为b[ls[0]].key */
   while(b[ls[0]].key!=MAXKEY)
   {
     q=ls[0]; /* q指示当前最小关键字所在归并段 */
     output(q); /* 将编号为q的归并段中当前（关键字为b[q].key）的记录写至输出归并段 */
     input(q,&b[q].key); /* 从编号为q的输入归并段中读人下一个记录的关键字 */
     Adjust(ls,q); /* 调整败者树，选择新的最小关键字 */
   }
   output(ls[0]); /* 将含最大关键字MAXKEY的记录写至输出归并段 */
 }

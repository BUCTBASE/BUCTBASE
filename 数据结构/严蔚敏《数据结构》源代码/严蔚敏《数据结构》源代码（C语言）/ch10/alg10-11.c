 /* alg10-11.c 链式基数排序 */
 typedef int InfoType; /* 定义其它数据项的类型 */
 typedef int KeyType; /* 定义RedType类型的关键字为整型 */
 typedef struct
 {
   KeyType key; /* 关键字项 */
   InfoType otherinfo; /* 其它数据项 */
 }RedType; /* 记录类型(同c10-1.h) */
 typedef char KeysType; /* 定义关键字类型为字符型 */
 #include"c1.h"
 #include"c10-3.h"
 void InitList(SLList *L,RedType D[],int n)
 { /* 初始化静态链表L（把数组D中的数据存于L中） */
   char c[MAX_NUM_OF_KEY],c1[MAX_NUM_OF_KEY];
   int i,j,max=D[0].key; /* max为关键字的最大值 */
   for(i=1;i<n;i++)
     if(max<D[i].key)
       max=D[i].key;
   (*L).keynum=(int)(ceil(log10(max)));
   (*L).recnum=n;
   for(i=1;i<=n;i++)
   {
     (*L).r[i].otheritems=D[i-1].otherinfo;
     itoa(D[i-1].key,c,10); /* 将10进制整型转化为字符型,存入c */
     for(j=strlen(c);j<(*L).keynum;j++) /* 若c的长度<max的位数,在c前补'0' */
     {
       strcpy(c1,"0");
       strcat(c1,c);
       strcpy(c,c1);
     }
     for(j=0;j<(*L).keynum;j++)
       (*L).r[i].keys[j]=c[(*L).keynum-1-j];
   }
 }

 int ord(char c)
 { /* 返回k的映射(个位整数) */
   return c-'0';
 }

 void Distribute(SLCell r[],int i,ArrType f,ArrType e) /* 算法10.15 */
 { /* 静态键表L的r域中记录已按(keys[0],...,keys[i-1])有序。本算法按 */
   /* 第i个关键字keys[i]建立RADIX个子表,使同一子表中记录的keys[i]相同。 */
   /* f[0..RADIX-1]和e[0..RADIX-1]分别指向各子表中第一个和最后一个记录 */
   int j,p;
   for(j=0;j<RADIX;++j)
     f[j]=0; /* 各子表初始化为空表 */
   for(p=r[0].next;p;p=r[p].next)
   {
     j=ord(r[p].keys[i]); /* ord将记录中第i个关键字映射到[0..RADIX-1] */
     if(!f[j])
       f[j]=p;
     else
       r[e[j]].next=p;
     e[j]=p; /* 将p所指的结点插入第j个子表中 */
   }
 }

 int succ(int i)
 { /* 求后继函数 */
   return ++i;
 }

 void Collect(SLCell r[],ArrType f,ArrType e)
 { /* 本算法按keys[i]自小至大地将f[0..RADIX-1]所指各子表依次链接成 */
   /* 一个链表，e[0..RADIX-1]为各子表的尾指针。算法10.16 */
   int j,t;
   for(j=0;!f[j];j=succ(j)); /* 找第一个非空子表，succ为求后继函数 */
   r[0].next=f[j];
   t=e[j]; /* r[0].next指向第一个非空子表中第一个结点 */
   while(j<RADIX-1)
   {
     for(j=succ(j);j<RADIX-1&&!f[j];j=succ(j)); /* 找下一个非空子表 */
     if(f[j])
     { /* 链接两个非空子表 */
       r[t].next=f[j];
       t=e[j];
     }
   }
   r[t].next=0; /* t指向最后一个非空子表中的最后一个结点 */
 }

 void printl(SLList L)
 { /* 按链表输出静态链表 */
   int i=L.r[0].next,j;
   while(i)
   {
     for(j=L.keynum-1;j>=0;j--)
       printf("%c",L.r[i].keys[j]);
     printf(" ");
     i=L.r[i].next;
   }
 }

 void RadixSort(SLList *L)
 { /* L是采用静态链表表示的顺序表。对L作基数排序，使得L成为按关键字 */
   /* 自小到大的有序静态链表，L.r[0]为头结点。算法10.17 */
   int i;
   ArrType f,e;
   for(i=0;i<(*L).recnum;++i)
     (*L).r[i].next=i+1;
   (*L).r[(*L).recnum].next=0; /* 将L改造为静态链表 */
   for(i=0;i<(*L).keynum;++i)
   { /* 按最低位优先依次对各关键字进行分配和收集 */
     Distribute((*L).r,i,f,e); /* 第i趟分配 */
     Collect((*L).r,f,e); /* 第i趟收集 */
     printf("第%d趟收集后:\n",i+1);
     printl(*L);
     printf("\n");
   }
 }

 void print(SLList L)
 { /* 按数组序号输出静态链表 */
   int i,j;
   printf("keynum=%d recnum=%d\n",L.keynum,L.recnum);
   for(i=1;i<=L.recnum;i++)
   {
     printf("keys=");
     for(j=L.keynum-1;j>=0;j--)
       printf("%c",L.r[i].keys[j]);
     printf(" otheritems=%d next=%d\n",L.r[i].otheritems,L.r[i].next);
   }
 }

 void Sort(SLList L,int adr[]) /* 改此句(类型) */
 { /* 求得adr[1..L.length]，adr[i]为静态链表L的第i个最小记录的序号 */
   int i=1,p=L.r[0].next;
   while(p)
   {
     adr[i++]=p;
     p=L.r[p].next;
   }
 }

 void Rearrange(SLList *L,int adr[]) /* 改此句(类型) */
 { /* adr给出静态链表L的有序次序，即L.r[adr[i]]是第i小的记录。 */
   /* 本算法按adr重排L.r，使其有序。算法10.18(L的类型有变) */
   int i,j,k;
   for(i=1;i<(*L).recnum;++i) /* 改此句(类型) */
     if(adr[i]!=i)
     {
       j=i;
       (*L).r[0]=(*L).r[i]; /* 暂存记录(*L).r[i] */
       while(adr[j]!=i)
       { /* 调整(*L).r[adr[j]]的记录到位直到adr[j]=i为止 */
         k=adr[j];
         (*L).r[j]=(*L).r[k];
         adr[j]=j;
         j=k; /* 记录按序到位 */
       }
       (*L).r[j]=(*L).r[0];
       adr[j]=j;
     }
 }

 #define N 10
 void main()
 {
   RedType d[N]={{278,1},{109,2},{63,3},{930,4},{589,5},{184,6},{505,7},{269,8},{8,9},{83,10}};
   SLList l;
   int *adr;
   InitList(&l,d,N);
   printf("排序前(next域还没赋值):\n");
   print(l);
   RadixSort(&l);
   printf("排序后(静态链表):\n");
   print(l);
   adr=(int*)malloc((l.recnum)*sizeof(int));
   Sort(l,adr);
   Rearrange(&l,adr);
   printf("排序后(重排记录):\n");
   print(l);
 }

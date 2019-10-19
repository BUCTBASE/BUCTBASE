 /* algo8-2.c 伙伴系统。实现算法8.2的程序 */
 #include"c1.h"
 #include"c8-2.h"
 #define N 100 /* 占用块个数的最大值 */
 Space r; /* r为生成空间的首地址,全局量 */

 Space AllocBuddy(FreeList *avail,int n)
 { /* avail[0..m]为可利用空间表,n为申请分配量,若有不小于n的空闲块, */
   /* 则分配相应的存储块,并返回其首地址;否则返回NULL。算法8.2 */
   int i,k;
   Space pa,pi,pre,suc;
   for(k=0;k<=m&&((*avail)[k].nodesize<n+1||!(*avail)[k].first);++k); /* 查找满足分配要求的子表 */
   if(k>m) /* 分配失败，返回NULL */
     return NULL;
   else /* 进行分配 */
   {
     pa=(*avail)[k].first; /* 指向可分配子表的第一个结点 */
     pre=pa->llink; /* 分别指向前驱和后继 */
     suc=pa->rlink;
     if(pa==suc)
       (*avail)[k].first=NULL; /* 分配后该子表变成空表 */
     else /* 从子表删去*pa结点 */
     {
       pre->rlink=suc;
       suc->llink=pre;
       (*avail)[k].first=suc;
     }
     for(i=1;(*avail)[k-i].nodesize>=n+1;++i)
     {
       pi=pa+(int)pow(2,k-i);
       pi->rlink=pi;
       pi->llink=pi;
       pi->tag=0;
       pi->kval=k-i;
       (*avail)[k-i].first=pi;
     } /* 将剩余块插入相应子表 */
     pa->tag=1;
     pa->kval=k-(--i);
   }
   return pa;
 }

 Space buddy(Space p)
 { /* 返回相对起始地址为p,块大小为pow(2,k)的块的伙伴地址 */
   if((p-r)%(int)pow(2,p->kval+1)==0) /* p为前块 */
     return p+(int)pow(2,p->kval);
   else /* p为后块 */
     return p-(int)pow(2,p->kval);
 }

 void Reclaim(FreeList *pav,Space *p)
 { /* 伙伴系统的回收算法 将p所指的释放块回收到可利用空间表pav中 */
   Space s;
   s=buddy(*p); /* 伙伴块的起始地址 */
   while(s>=r&&s<r+(*pav)[m].nodesize&&s->tag==0) /* 归并伙伴块,伙伴块起始地址在有效范围内且伙伴块空闲 */
   { /* 从链表上删除该结点 */
     if(s->llink==s&&s->rlink==s) /* 链表上仅此一个结点 */
       (*pav)[s->kval].first=NULL; /* 置此链表为空 */
     else /* 链表上不止一个结点 */
     {
       s->llink->rlink=s->rlink; /* 前驱的后继为该结点的后继 */
       s->rlink->llink=s->llink; /* 后继的前驱为该结点的前驱 */
       if((*pav)[s->kval].first==s) /* s是链表的第一个结点 */
         (*pav)[s->kval].first=s->rlink; /* 表头指向下一个结点 */
     } /* 以下修改结点头部 */
     if((*p-r)%(int)pow(2,(*p)->kval+1)==0) /* p为前块 */
       (*p)->kval++;
     else /* p为后块 */
     {
       s->kval=(*p)->kval+1;
       *p=s; /* p指向新块首地址 */
     }
     s=buddy(*p); /* 下一个伙伴块的起始地址 */
   }
   /* 以下将p插到可利用空间表中 */
   (*p)->tag=0;
   if((*pav)[(*p)->kval].first==NULL) /* 该链表空 */
     (*pav)[(*p)->kval].first=(*p)->llink=(*p)->rlink=*p;
   else /* 插在表头 */
   {
     (*p)->rlink=(*pav)[(*p)->kval].first;
     (*p)->llink=(*p)->rlink->llink;
     (*p)->rlink->llink=*p;
     (*p)->llink->rlink=*p;
     (*pav)[(*p)->kval].first=*p;
   }
   *p=NULL;
 }

 void Print(FreeList p)
 { /* 输出p中所有可利用空间表 */
   int i;
   Space h;
   for(i=0;i<=m;i++)
   {
     if(p[i].first) /* 第i个可利用空间表不空 */
     {
       h=p[i].first; /* h指向链表的第一个结点的头部域(首地址) */
       do
       {
         printf("块的大小=%d 块的首地址=%u ",(int)pow(2,h->kval),h); /* 输出结点信息 */
         printf("块标志=%d(0:空闲 1:占用)\n",h->tag);
         h=h->rlink; /* 指向下一个结点的头部域(首地址) */
       }while(h!=p[i].first); /* 没到循环链表的表尾 */
     }
   }
 }

 void PrintUser(Space p[])
 { /* 输出p数组所指的已分配空间 */
   int i;
   for(i=0;i<N;i++)
     if(p[i]) /* 指针不为0(指向一个占用块) */
     {
       printf("占用块%d的首地址=%u ",i,p[i]); /* 输出结点信息 */
       printf("块的大小=%d",(int)pow(2,p[i]->kval));
       printf(" 块标志=%d(0:空闲 1:占用)\n",p[i]->tag);
     }
 }

 void main()
 {
   int i,n;
   FreeList a;
   Space q[N]={NULL}; /* q数组为占用块的首地址 */
   printf("sizeof(WORD)=%u m=%u (int)pow(2,m)=%u\n",sizeof(WORD),m,(int)pow(2,m));
   for(i=0;i<=m;i++) /* 初始化a */
   {
     a[i].nodesize=(int)pow(2,i);
     a[i].first=NULL;
   }
   r=a[m].first=(WORD*)malloc(a[m].nodesize*sizeof(WORD)); /* 在最大链表中生成一个结点 */
   if(r) /* 生成结点成功 */
   {
     r->llink=r->rlink=r; /* 初始化该结点 */
     r->tag=0;
     r->kval=m;
     Print(a);
     PrintUser(q);
     n=100;
     q[0]=AllocBuddy(&a,n); /* 向a申请100个WORD的内存(实际获得128个WORD) */
     printf("申请%d个字后，可利用空间为:\n",n);
     Print(a);
     PrintUser(q);
     n=200;
     q[1]=AllocBuddy(&a,n); /* 向a申请200个WORD的内存(实际获得256个WORD) */
     printf("申请%d个字又",n);
     n=220;
     q[2]=AllocBuddy(&a,n); /* 向a申请220个WORD的内存(实际获得256个WORD) */
     printf("申请%d个字后，可利用空间为:\n",n);
     Print(a);
     PrintUser(q);
     Reclaim(&a,&q[1]); /* 回收q[1]，伙伴不空闲 */
     printf("回收q[1]后，可利用空间为:\n");
     Print(a);
     PrintUser(q);
     Reclaim(&a,&q[0]); /* 回收q[0]，伙伴空闲 */
     printf("回收q[0]后，可利用空间为:\n");
     Print(a);
     PrintUser(q);
     Reclaim(&a,&q[2]); /* 回收q[2]，伙伴空闲，生成一个大结点 */
     printf("回收q[2]后，可利用空间为:\n");
     Print(a);
     PrintUser(q);
   }
   else
     printf("ERROR\n");
 }

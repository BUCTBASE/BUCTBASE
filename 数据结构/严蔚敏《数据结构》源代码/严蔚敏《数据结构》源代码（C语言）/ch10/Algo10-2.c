 /* algo10-2.c 静态链表 */
 #include"c1.h"
 typedef int InfoType; /* 定义其它数据项的类型 */
 #include"c10-2.h"
 void TableInsert(SLinkListType *SL,RedType D[],int n)
 { /* 由数组D建立n个元素的表插入排序的静态链表SL */
   int i,p,q;
   (*SL).r[0].rc.key=INT_MAX; /* 表头结点记录的关键字取最大整数(非降序链表的表尾) */
   (*SL).r[0].next=0; /* next域为0表示表尾(现为空表，初始化) */
   for(i=0;i<n;i++)
   {
     (*SL).r[i+1].rc=D[i]; /* 将数组D的值赋给静态链表SL */
     q=0;
     p=(*SL).r[0].next;
     while((*SL).r[p].rc.key<=(*SL).r[i+1].rc.key)
     { /* 静态链表向后移 */
       q=p;
       p=(*SL).r[p].next;
     }
     (*SL).r[i+1].next=p; /* 将当前记录插入静态链表 */
     (*SL).r[q].next=i+1;
   }
   (*SL).length=n;
 }

 void Arrange(SLinkListType *SL)
 { /* 根据静态链表SL中各结点的指针值调整记录位置，使得SL中记录按关键字 */
   /* 非递减有序顺序排列 算法10.3 */
   int i,p,q;
   SLNode t;
   p=(*SL).r[0].next; /* p指示第一个记录的当前位置 */
   for(i=1;i<(*SL).length;++i)
   { /* (*SL).r[1..i-1]中记录已按关键字有序排列,第i个记录在SL中的当前位置应不小于i */
     while(p<i)
       p=(*SL).r[p].next; /* 找到第i个记录，并用p指示其在SL中当前位置 */
     q=(*SL).r[p].next; /* q指示尚未调整的表尾 */
     if(p!=i)
     {
       t=(*SL).r[p]; /* 交换记录，使第i个记录到位 */
       (*SL).r[p]=(*SL).r[i];
       (*SL).r[i]=t;
       (*SL).r[i].next=p; /* 指向被移走的记录，使得以后可由while循环找回 */
     }
     p=q; /* p指示尚未调整的表尾，为找第i+1个记录作准备 */
   }
 }

 void Sort(SLinkListType L,int adr[])
 { /* 求得adr[1..L.length]，adr[i]为静态链表L的第i个最小记录的序号 */
   int i=1,p=L.r[0].next;
   while(p)
   {
     adr[i++]=p;
     p=L.r[p].next;
   }
 }

 void Rearrange(SLinkListType *L,int adr[])
 { /* adr给出静态链表L的有序次序，即L.r[adr[i]]是第i小的记录。 */
   /* 本算法按adr重排L.r，使其有序。算法10.18(L的类型有变) */
   int i,j,k;
   for(i=1;i<(*L).length;++i)
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

 void print(SLinkListType L)
 {
   int i;
   for(i=1;i<=L.length;i++)
     printf("key=%d ord=%d next=%d\n",L.r[i].rc.key,L.r[i].rc.otherinfo,L.r[i].next);
 }

 #define N 8
 void main()
 {
   RedType d[N]={{49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8}};
   SLinkListType l1,l2;
   int *adr,i;
   TableInsert(&l1,d,N);
   l2=l1; /* 复制静态链表l2与l1相同 */
   printf("排序前:\n");
   print(l1);
   Arrange(&l1);
   printf("l1排序后:\n");
   print(l1);
   adr=(int*)malloc((l2.length+1)*sizeof(int));
   Sort(l2,adr);
   for(i=1;i<=l2.length;i++)
     printf("adr[%d]=%d ",i,adr[i]);
   printf("\n");
   Rearrange(&l2,adr);
   printf("l2排序后:\n");
   print(l2);
 }

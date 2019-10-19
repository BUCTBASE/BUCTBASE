 /* algo2-8.c 实现算法2.17的程序 */
 #include"c1.h"
 #define N 2
 typedef char ElemType;
 #include"c2-3.h"
 #include"bo2-3.c"
 #include"bo2-32.c"

 void difference(SLinkList space,int *S) /* 算法2.17 */
 { /* 依次输入集合A和B的元素，在一维数组space中建立表示集合(A-B)∪(B-A) */
   /* 的静态链表，S为其头指针。假设备用空间足够大，space[0].cur为备用空间的头指针 */
   int r,p,m,n,i,j,k;
   ElemType b;
   InitSpace(space); /* 初始化备用空间 */
   *S=Malloc(space); /* 生成S的头结点 */
   r=*S; /* r指向S的当前最后结点 */
   printf("请输入集合A和B的元素个数m,n:");
   scanf("%d,%d%*c",&m,&n); /* %*c吃掉回车符 */
   printf("请输入集合A的元素（共%d个）:",m);
   for(j=1;j<=m;j++) /* 建立集合A的链表 */
   {
     i=Malloc(space); /* 分配结点 */
     scanf("%c",&space[i].data); /* 输入A的元素值 */
     space[r].cur=i; /* 插入到表尾 */
     r=i;
   }
   scanf("%*c"); /* %*c吃掉回车符 */
   space[r].cur=0; /* 尾结点的指针为空 */
   printf("请输入集合B的元素（共%d个）:",n);
   for(j=1;j<=n;j++)
   { /* 依次输入B的元素,若不在当前表中,则插入,否则删除 */
     scanf("%c",&b);
     p=*S;
     k=space[*S].cur; /* k指向集合A中的第一个结点 */
     while(k!=space[r].cur&&space[k].data!=b)
     { /* 在当前表中查找 */
       p=k;
       k=space[k].cur;
     }
     if(k==space[r].cur)
     { /* 当前表中不存在该元素，插入在r所指结点之后，且r的位置不变 */
       i=Malloc(space);
       space[i].data=b;
       space[i].cur=space[r].cur;
       space[r].cur=i;
     }
     else /* 该元素已在表中，删除之 */
     {
       space[p].cur=space[k].cur;
       Free(space,k);
       if(r==k)
         r=p; /* 若删除的是尾元素，则需修改尾指针 */
     }
   }
 }

 void visit(ElemType c)
 {
   printf("%c ",c);
 }

 void main()
 {
   int k;
   SLinkList s;
   difference(s,&k);
   ListTraverse(s,k,visit);
 }

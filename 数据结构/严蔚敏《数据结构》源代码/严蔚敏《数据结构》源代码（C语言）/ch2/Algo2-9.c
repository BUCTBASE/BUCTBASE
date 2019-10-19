 /* algo2-9.c 尽量采用bo2-32.c中的基本操作实现算法2.17的功能 */
 #include"c1.h"
 #define N 2
 typedef char ElemType;
 #include"c2-3.h"
 #include"bo2-3.c"
 #include"bo2-32.c"

 void visit(ElemType c)
 {
   printf("%c ",c);
 }

 int difference(SLinkList space) /* 改进算法2.17(尽量利用基本操作实现) */
 { /* 依次输入集合A和B的元素，在一维数组space中建立表示集合(A-B)∪(B-A) */
   /* 的静态链表，并返回其头指针。假设备用空间足够大，space[0].cur为备用空间的头指针 */
   int m,n,i,j,k,S;
   ElemType b,c;
   InitSpace(space); /* 初始化备用空间 */
   S=InitList(space); /* 生成链表S的头结点 */
   printf("请输入集合A和B的元素个数m,n:");
   scanf("%d,%d%*c",&m,&n); /* %*c吃掉回车符 */
   printf("请输入集合A的元素（共%d个）:",m);
   for(j=1;j<=m;j++) /* 建立集合A的链表 */
   {
     scanf("%c",&b); /* 输入A的元素值 */
     ListInsert(space,S,j,b); /* 插入到表尾 */
   }
   scanf("%*c"); /* 吃掉回车符 */
   printf("请输入集合B的元素（共%d个）:",n);
   for(j=1;j<=n;j++)
   { /* 依次输入B的元素,若不在当前表中,则插入,否则删除 */
     scanf("%c",&b);
     k=LocateElem(space,S,b); /* k为b的位序 */
     if(k) /* b在当前表中 */
     {
       PriorElem(space,S,b,&c); /* b的前驱为c */
       i=LocateElem(space,S,c); /* i为c的位序 */
       space[i].cur=space[k].cur; /* 将k的指针赋给i的指针 */
       Free(space,k); /* 将下标为k的空闲结点回收到备用链表 */
     }
     else
       ListInsert(space,S,ListLength(space,S)+1,b); /* 在表尾插入b */
   }
   return S;
 }

 void main()
 {
   int k;
   SLinkList s;
   k=difference(s);
   ListTraverse(s,k,visit);
 }

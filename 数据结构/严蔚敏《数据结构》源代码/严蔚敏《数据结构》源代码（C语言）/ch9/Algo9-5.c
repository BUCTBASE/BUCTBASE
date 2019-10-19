 /* algo9-5.c 检验bo9-3.c的程序 */
 #include"c1.h"
 #define N 5 /* 数据元素个数 */
 typedef char KeyType; /* 设关键字域为字符型 */
 typedef struct
 {
   KeyType key;
   int order;
 }ElemType; /* 数据元素类型 */

 #include"c9.h"
 #include"c9-2.h"
 #include"bo9-3.c"

 void print(ElemType c)
 {
   printf("(%d,%d)",c.key,c.order);
 }

 void main()
 {
   BSTree dt,p;
   Status k;
   int i;
   KeyType j;
   ElemType r[N]={{13,1},{24,2},{37,3},{90,4},{53,5}}; /* (以教科书图9.12为例) */
   InitDSTable(&dt); /* 初始化空树 */
   for(i=0;i<N;i++)
     InsertAVL(&dt,r[i],&k); /* 建平衡二叉树 */
   TraverseDSTable(dt,print); /* 按关键字顺序遍历二叉树 */
   printf("\n请输入待查找的关键字: ");
   scanf("%d",&j);
   p=SearchBST(dt,j); /* 查找给定关键字的记录 */
   if(p)
     print(p->data);
   else
     printf("表中不存在此值");
   printf("\n");
   DestroyDSTable(&dt);
 }

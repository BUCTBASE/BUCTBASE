 /* algo9-6.c 检验bo9-4.c的程序 */
 #include"c1.h"
 #define m 3 /* B树的阶，暂设为3 */
 #define N 16 /* 数据元素个数 */
 #define MAX 5 /* 字符串最大长度+1 */
 typedef int KeyType; /* 设关键字域为整型 */
 typedef struct
 {
   char info[MAX];
 }Others;/* 记录的其它部分 */

 #include"c9-3.h"
 #include"bo9-4.c"

 void print(BTNode c,int i) /* TraverseDSTable()调用的函数 */
 {
   printf("(%d,%s)",c.node[i].key,c.node[i].recptr->others.info);
 }

 void main()
 {
   Record r[N]={{24,"1"},{45,"2"},{53,"3"},{12,"4"},{37,"5"},
                {50,"6"},{61,"7"},{90,"8"},{100,"9"},{70,"10"},
                {3,"11"},{30,"12"},{26,"13"},{85,"14"},{3,"15"},
		{7,"16"}}; /* (以教科书中图9.16为例) */
   BTree t;
   Result s;
   int i;
   InitDSTable(&t);
   for(i=0;i<N;i++)
   {
     s=SearchBTree(t,r[i].key);
     if(!s.tag)
       InsertBTree(&t,&r[i],s.pt,s.i);
   }
   printf("按关键字的顺序遍历B_树:\n");
   TraverseDSTable(t,print);
   printf("\n请输入待查找记录的关键字: ");
   scanf("%d",&i);
   s=SearchBTree(t,i);
   if(s.tag)
     print(*(s.pt),s.i);
   else
     printf("没找到");
   printf("\n");
   DestroyDSTable(&t);
 }

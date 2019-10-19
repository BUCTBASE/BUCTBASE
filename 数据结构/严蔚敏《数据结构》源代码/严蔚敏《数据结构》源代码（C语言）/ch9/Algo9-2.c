 /* algo9-2.c 检验bo9-1.(有序表部分)的程序 */
 #include"c1.h"
 #define N 11 /* 数据元素个数 */
 typedef int KeyType; /* 设关键字域为整型 */
 typedef struct /* 数据元素类型 */
 {
   KeyType key; /* 关键字域 */
   int others; /* 其它部分 */
 }ElemType;
 ElemType r[N]={{5,1},{13,2},{19,3},{21,4},{37,5},{56,6},{64,7},{75,8},
		{80,9},{88,10},{92,11}}; /* 数据元素(以教科书P.219的数据为例),全局变量 */
 #include"c9.h"
 #include"c9-1.h"
 #include"bo9-1.c"

 void print(ElemType c) /* Traverse()调用的函数 */
 {
   printf("(%d %d) ",c.key,c.others);
 }

 void main()
 {
   SSTable st;
   int i;
   KeyType s;
   Creat_Ord(&st,N); /* 由全局数组产生非降序静态查找表st */
   Traverse(st,print); /* 顺序输出非降序静态查找表st */
   printf("\n");
   printf("请输入待查找值的关键字: ");
   scanf("%d",&s);
   i=Search_Bin(st,s); /* 折半查找有序表 */
   if(i)
     printf("(%d %d) %d是第%d个记录的关键字\n",st.elem[i].key,st.elem[i].others,s,i);
   else
     printf("没找到\n");
   Destroy(&st);
 }

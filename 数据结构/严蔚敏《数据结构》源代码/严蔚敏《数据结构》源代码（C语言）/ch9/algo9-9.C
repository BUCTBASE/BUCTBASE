 /* algo9-9.c 检验bo9-7.c的程序 */
 #include"c1.h"
 #define NULLKEY 0 /* 0为无记录标志 */
 #define N 10 /* 数据元素个数 */
 typedef int KeyType; /* 设关键字域为整型 */
 typedef struct
 {
   KeyType key;
   int ord;
 }ElemType; /* 数据元素类型 */

 #include"c9.h"
 #include"c9-6.h"
 #include"bo9-7.c"

 void print(int p,ElemType r)
 {
   printf("address=%d (%d,%d)\n",p,r.key,r.ord);
 }

 void main()
 {
   ElemType r[N]={{17,1},{60,2},{29,3},{38,4},{1,5},{2,6},{3,7},{4,8},{60,9},{13,10}};
   HashTable h;
   int i,p;
   Status j;
   KeyType k;
   InitHashTable(&h);
   for(i=0;i<N-1;i++)
   { /* 插入前N-1个记录 */
     j=InsertHash(&h,r[i]);
     if(j==DUPLICATE)
       printf("表中已有关键字为%d的记录，无法再插入记录(%d,%d)\n",r[i].key,r[i].key,r[i].ord);
   }
   printf("按哈希地址的顺序遍历哈希表:\n");
   TraverseHash(h,print);
   printf("请输入待查找记录的关键字: ");
   scanf("%d",&k);
   j=Find(h,k,&p);
   if(j==SUCCESS)
     print(p,h.elem[p]);
   else
     printf("没找到\n");
   j=InsertHash(&h,r[i]); /* 插入第N个记录 */
   if(j==ERROR) /* 重建哈希表 */
     j=InsertHash(&h,r[i]); /* 重建哈希表后重新插入第N个记录 */
   printf("按哈希地址的顺序遍历重建后的哈希表:\n");
   TraverseHash(h,print);
   printf("请输入待查找记录的关键字: ");
   scanf("%d",&k);
   j=Find(h,k,&p);
   if(j==SUCCESS)
     print(p,h.elem[p]);
   else
     printf("没找到\n");
   DestroyHashTable(&h);
 }

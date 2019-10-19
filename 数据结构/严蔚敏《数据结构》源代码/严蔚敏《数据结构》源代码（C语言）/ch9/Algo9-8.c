 /* algo9-8.c 检验bo9-6.c的程序 */
 #include"c1.h"
 #define N 16 /* 数据元素个数 */
 #define LENGTH 27 /* 结点的最大度+1(大写英文字母) */
 typedef struct
 {
   int ord;
 }Others; /* 记录的其它部分 */
 #define Nil ' ' /* 定义结束符为空格(与教科书不同) */
 #include"c9-5.h"
 #include"bo9-6.c"

 Status pr(Record *r)
 {
   printf("(%s,%d)",r->key.ch,r->others.ord);
   return OK;
 }

 void main()
 {
   TrieTree t;
   int i;
   char s[MAXKEYLEN+1];
   KeysType k;
   Record *p;
   Record r[N]={{{"CAI"},1},{{"CAO"},2},{{"LI"},3},{{"LAN"},4},
                {{"CHA"},5},{{"CHANG"},6},{{"WEN"},7},{{"CHAO"},8},
                {{"YUN"},9},{{"YANG"},10},{{"LONG"},11},{{"WANG"},12},
                {{"ZHAO"},13},{{"LIU"},14},{{"WU"},15},{{"CHEN"},16}};
   /* 数据元素(以教科书式9-24为例) */
   InitDSTable(&t);
   for(i=0;i<N;i++)
   {
     r[i].key.num=strlen(r[i].key.ch)+1;
     r[i].key.ch[r[i].key.num]=Nil; /* 在关键字符串最后加结束符 */
     p=SearchTrie(t,r[i].key);
     if(!p)
       InsertTrie(&t,&r[i]);
   }
   printf("按关键字符串的顺序遍历Trie树(键树):\n");
   TraverseDSTable(t,pr);
   printf("\n请输入待查找记录的关键字符串: ");
   scanf("%s",s);
   k.num=strlen(s)+1;
   strcpy(k.ch,s);
   k.ch[k.num]=Nil; /* 在关键字符串最后加结束符 */
   p=SearchTrie(t,k);
   if(p)
     pr(p);
   else
     printf("没找到");
   printf("\n");
   DestroyDSTable(&t);
 }

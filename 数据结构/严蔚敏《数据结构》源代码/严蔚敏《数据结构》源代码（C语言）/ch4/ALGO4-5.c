 /* algo4-5.c 根据algo4-4.c产生的文件,索引查询图书 */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-5.h"
 #include"bo2-6.c"
 #include"c4-2.h"
 #include"bo4-2.c"

 #define MaxBookNum 10 /* 假设只对10本书建索引表 */
 #define MaxKeyNum 25 /* 索引表的最大容量(关键词的最大数) */
 #define MaxLineLen 51 /* 书目串(书名+书号)buf的最大长度 */

 typedef struct
 {
   HString key; /* 关键词(堆分配类型,c4-2.h) */
   LinkList bnolist; /* 存放书号索引的链表(c2-5.h) */
 }IdxTermType; /* 索引项类型 */

 typedef struct
 {
   IdxTermType item[MaxKeyNum+1];
   int last; /* 关键词的个数 */
 }IdxListType; /* 索引表类型(有序表) */

 typedef struct
 {
   char bookname[MaxLineLen]; /* 书目串 */
   int bookno; /* 书号 */
 }BookTermType; /* 书目项类型 */

 typedef struct BookListType /* 书目表类型(有序表) */
 {
   BookTermType item[MaxBookNum];
   int last; /* 书目的数量 */
 }BookListType; /* 书目表类型(有序表) */

 void main()
 {
   FILE *f; /* 任何时间最多打开一个文件 */
   IdxListType idxlist; /* 索引表 */
   BookListType booklist; /* 书目表 */
   char buf[MaxLineLen+1]; /* 当前书目串(包括'\0') */
   HString ch; /* 索引字符串 */
   int BookNo; /* 书号变量 */
   int i,k,l;
   Link p;
   InitString(&ch); /* 初始化HString类型的变量 */
   f=fopen("BookIdx.txt","r"); /* 打开书名关键词索引表文件 */
   if(!f)
     exit(OVERFLOW);
   fscanf(f,"%d",&idxlist.last); /* 书名关键词个数 */
   for(k=0;k<idxlist.last;k++) /* 把关键词文件的内容拷到idxlist中 */
   {
     fscanf(f,"%s",buf);
     i=0;
     while(buf[i])
       buf[i++]=tolower(buf[i]); /* 字母转为小写 */
     InitString(&idxlist.item[k].key);
     StrAssign(&idxlist.item[k].key,buf);
     InitList(&idxlist.item[k].bnolist); /* 初始化书号链表 bo2-6.c */
     fscanf(f,"%d",&i);
     for(l=0;l<i;l++)
     {
       fscanf(f,"%d",&BookNo);
       if(!MakeNode(&p,BookNo)) /* 分配失败 bo2-6.c */
         exit(OVERFLOW);
       p->next=NULL;
       Append(&idxlist.item[k].bnolist,p); /* 插入新的书号索引 bo2-6.c */
     }
   }
   fclose(f);
   f=fopen("BookInfo.txt","r"); /* 打开书目文件 */
   if(!f)
     exit(FALSE);
   i=0;
   while(!feof(f)) /* 把书目文件的内容拷到booklist中 */
   {
     fgets(buf,MaxLineLen,f);
     booklist.item[i].bookno=(buf[0]-'0')*100+(buf[1]-'0')*10+(buf[2]-'0'); /* 前三位为书号 */
     strcpy(booklist.item[i].bookname,buf);
     i++;
   }
   booklist.last=i;
   printf("请输入书目的关键词(一个)");
   scanf("%s",buf);
   i=0;
   while(buf[i])
     buf[i++]=tolower(buf[i]); /* 字母转为小写 */
   StrAssign(&ch,buf);
   i=0;
   do
   {
     k=StrCompare(ch,idxlist.item[i].key); /* bo4-2.c */
     i++;
   }while(k&&i<=idxlist.last);
   if(!k) /* 索引表中有此关键词 */
   {
     p=idxlist.item[i-1].bnolist.head->next;
     while(p)
     {
       l=0;
       while(l<booklist.last&&p->data!=booklist.item[l].bookno)
         l++;
       if(l<booklist.last)
         printf("%s",booklist.item[l].bookname);
       p=p->next;
     }
   }
   else
     printf("没找到\n");
 }

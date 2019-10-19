 /* algo4-4.c 生成书名关键词索引文件bookidx.txt，算法4.9～4.14 */
 /* 为运行algo4-5.c做准备 */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-5.h"
 #include"bo2-6.c"
 #include"c4-2.h"
 #include"bo4-2.c"

 #define MaxKeyNum 25 /* 索引表的最大容量(关键词的最大数) */
 #define MaxLineLen 51 /* 书目串(书名+书号)buf的最大长度 */
 #define MaxWordNum 10 /* 词表(一本书的关键词)的最大容量 */
 #define MaxNoIdx 10 /* 常用词(仅指大写)的最大数 */
 typedef struct
 {
   char *item[MaxWordNum]; /* 词表(字符串)指针数组 */
   int last; /* 词的数量 */
 }WordListType; /* 词表类型(顺序表) */

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
   char *item[MaxNoIdx]; /* 常用词表指针数组 */
   int last; /* 常用词的数量 */
 }NoIdxType; /* 常用词表类型(有序表) */

 /* 全局变量 */
 char buf[MaxLineLen+1]; /* 当前书目串(包括'\0') */
 WordListType wdlist; /* 暂存一本书的词表 */
 NoIdxType noidx; /* 常用词表 */

 void InitIdxList(IdxListType *idxlist)
 { /* 初始化操作，置索引表idxlist为空表，且在idxliat.item[0]设一空串 */
   (*idxlist).last=0;
   InitString(&(*idxlist).item[0].key); /* bo4-2.c */
   InitList(&(*idxlist).item[0].bnolist); /* bo2-6.c */
 }

 void ExtractKeyWord(int *BookNo)
 { /* 从buf中提取书名关键词到词表wdlist，书号存入BookNo */
   int i,l,f=1; /* f是字符串结束标志 0: 结束 1: 未结束 */
   char *s1,*s2;
   if(buf[0]<'0'||buf[0]>'9') /* buf的首字母不是数字 */
     exit(OVERFLOW);
   for(i=1;i<=wdlist.last;i++) /* 释放上一个书目在词表wdlist的存储空间 */
   {
     free(wdlist.item[i]);
     wdlist.item[i]=NULL;
   }
   wdlist.last=0;
   *BookNo=(buf[0]-'0')*100+(buf[1]-'0')*10+(buf[2]-'0'); /* 前三位为书号 */
   s2=&buf[2]; /* s1指向书号的尾字符 */
   do
   { /* 提取书名关键词到词表wdlist */
     s1=s2+1; /* s1向后移动一个单词 */
     s2=strchr(s1,' '); /* s2指向s1的第一个空格,如没有,返回NULL */
     if(!s2) /* 到串尾 */
     {
       s2=strchr(s1,'\12'); /* s2指向buf的最后一个字符(回车符) */
       f=0;
     }
     l=s2-s1; /* 单词长度 */
     if(s1[0]>='A'&&s1[0]<='Z') /* 单词首字母为大写 */
     { /* 写入词表 */
       wdlist.item[wdlist.last]=(char *)malloc((l+1)*sizeof(char));
       /* 生成串空间(包括'\0') */
       for(i=0;i<l;i++)
         wdlist.item[wdlist.last][i]=s1[i]; /* 写入词表 */
       wdlist.item[wdlist.last][l]=0;
       for(i=0;i<noidx.last;i++) /* 查找是否为常用词 */
         if(!strcmp(wdlist.item[wdlist.last],noidx.item[i]))
           break;
       if(i!=noidx.last) /* 是常用词 */
       {
         free(wdlist.item[wdlist.last]); /* 从词表中删除该词 */
         wdlist.item[wdlist.last]=NULL;
       }
       else
         wdlist.last++; /* 词表长度+1 */
     }
   }while(f);
 }

 void GetWord(int i,HString *wd)
 { /* 用wd返回词表wdlist中第i个关键词 */
   StrAssign(wd,wdlist.item[i]); /* 生成关键字字符串 bo4-2.c */
 }

 int Locate(IdxListType *idxlist,HString wd,Status *b)
 { /* 在索引表idxlist中查询是否存在与wd相等的关键词。若存在,则返回其 */
   /* 在索引表中的位置,且b取值TRUE;否则返回插入位置,且b取值FALSE */
   int i,m;
   for(i=(*idxlist).last;(m=StrCompare((*idxlist).item[i].key,wd))>0;--i); /* bo4-2.c */
   if(m==0) /* 找到 */
   {
     *b=TRUE;
     return i;
   }
   else
   {
     *b=FALSE;
     return i+1;
   }
 }

 void InsertNewKey(IdxListType *idxlist,int i,HString wd)
 { /* 在索引表idxlist的第i项上插入新关键词wd,并初始化书号索引的链表为空表 */
   int j;
   InitList(&(*idxlist).item[(*idxlist).last+1].bnolist); /* bo2-6.c */
   for(j=(*idxlist).last;j>=i;--j) /* 后移索引项 */
     (*idxlist).item[j+1]=(*idxlist).item[j];
   InitString(&(*idxlist).item[i].key); /* bo4-2.c */
   StrCopy(&(*idxlist).item[i].key,wd); /* 串拷贝插入新的索引项 bo4-2.c */
   InitList(&(*idxlist).item[i].bnolist); /* 初始化书号索引表为空表 bo2-6.c */
   (*idxlist).last++;
 }

 void InsertBook(IdxListType *idxlist,int i,int bno)
 { /* 在索引表idxlist的第i项中插入书号为bno的索引 */
   Link p;
   if(!MakeNode(&p,bno)) /* 分配失败 bo2-6.c */
     exit(OVERFLOW);
   p->next=NULL;
   Append(&(*idxlist).item[i].bnolist,p); /* 插入新的书号索引 bo2-6.c */
 }

 void InsIdxList(IdxListType *idxlist,int bno)
 { /* 将书号为bno的关键词插入索引表 */
   int i,j;
   Status b;
   HString wd;
   InitString(&wd); /* bo4-2.c */
   for(i=0;i<wdlist.last;i++)
   {
     GetWord(i,&wd);
     j=Locate(idxlist,wd,&b);
     if(!b)
       InsertNewKey(idxlist,j,wd); /* 插入新的索引项 */
     InsertBook(idxlist,j,bno); /* 插入书号索引 */
   }
 }

 void PutText(FILE *f,IdxListType idxlist)
 { /* 将生成的索引表idxlist输出到文件f */
   int i,j;
   Link p;
   fprintf(f,"%d\n",idxlist.last);
   for(i=1;i<=idxlist.last;i++)
   {
     for(j=0;j<idxlist.item[i].key.length;j++)
       fprintf(f,"%c",idxlist.item[i].key.ch[j]);
     fprintf(f,"\n%d\n",idxlist.item[i].bnolist.len);
     p=idxlist.item[i].bnolist.head;
     for(j=1;j<=idxlist.item[i].bnolist.len;j++)
     {
       p=p->next;
       fprintf(f,"%d ",p->data);
     }
     fprintf(f,"\n");
   }
 }

 void main()
 {
   FILE *f; /* 任何时间最多打开一个文件 */
   IdxListType idxlist; /* 索引表 */
   int BookNo; /* 书号变量 */
   int k,l;
   f=fopen("NoIdx.txt","r"); /* 打开常用词文件 */
   if(!f)
     exit(OVERFLOW);
   fscanf(f,"%d",&noidx.last); /* 常用词个数 */
   for(k=0;k<noidx.last;k++) /* 把常用词文件的内容拷到noidx中 */
   {
     fscanf(f,"%s",buf);
     l=strlen(buf);
     noidx.item[k]=(char*)malloc(l*sizeof(char));
     strcpy(noidx.item[k],buf);
   }
   fclose(f);
   f=fopen("BookInfo.txt","r"); /* 打开书目文件 */
   if(!f)
     exit(FALSE);
   InitIdxList(&idxlist); /* 初始化索引表idxlist为空 */
   wdlist.last=0; /* 词表长度初值为0 */
   while(!feof(f))
   {
     fgets(buf,MaxLineLen,f);
     l=strlen(buf);
     if(l<=1)
       break;
     ExtractKeyWord(&BookNo); /* 从buf中提取关键词到词表，书号存入BookNo */
     InsIdxList(&idxlist,BookNo);
   }
   fclose(f);
   f=fopen("BookIdx.txt","w");
   if(!f)
     exit(INFEASIBLE);
   PutText(f,idxlist); /* 将生成的索引表idxlist输出到文件f */
   fclose(f);
 }

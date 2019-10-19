 /* algo12-1.c 根据事务文件成批地更改主文件并得到一个新的主文件 */
 #include"c1.h"
 typedef struct RedType /* 主文件记录类型 */
 {
   int accounts; /* 帐号 */
   int amount; /* 余额 */
 }RedType; /* 主文件记录类型 */
 typedef struct RcdType /* 事务文件记录类型(比主文件记录类型多了成员code) */
 {
   int accounts; /* 帐号 */
   int amount; /* 存取的数量(存为+,取为-) */
   char code; /* 修改要求(I:插入 U:修改 D:删除) */
 }RcdType; /* 事务文件记录类型(比主文件记录类型多了成员code) */
 #define key accounts
 RedType P(RcdType g)
 { /* 把g加工为q的结构返回 */
   RedType q;
   q.accounts=g.accounts;
   q.amount=g.amount;
   return q;
 }

 void Q(RedType *f,RcdType g)
 { /* 将f和g归并成一个f结构的记录 */
   (*f).amount+=g.amount;
 }

 void MergeFile(FILE *f,FILE *g,FILE *h)
 { /* 由按关键字递增有序的非空顺序文件f和g归并得到新文件h，三个文件均已 */
   /* 打开，其中，f和g为只读文件，文件中各附加一个最大关键字记录， */
   /* 且g文件中对该记录的操作为插入。h为只写文件。算法12.1 */
   RedType fr,fn;
   RcdType gr;
   int i;
   fread(&fr,sizeof(RedType),1,f);
   fread(&gr,sizeof(RcdType),1,g);
   while(!feof(f)||!feof(g))
   {
     if(fr.key<gr.key)
       i=1;
     else if(gr.code=='D'&&fr.key==gr.key)
       i=2;
     else if(gr.code=='I'&&fr.key>gr.key)
       i=3;
     else if(gr.code=='U'&&fr.key==gr.key)
       i=4;
     else
       i=0;
     switch(i)
     {
       case 1: /* 复制“旧”主文件中记录 */
      fwrite(&fr,sizeof(RedType),1,h);
      if(!feof(f))
        fread(&fr,sizeof(RedType),1,f);
       break;
       case 2: /* 删除“旧”主文件中记录，即不复制 */
               if(!feof(f))
                 fread(&fr,sizeof(RedType),1,f);
               if(!feof(g))
                 fread(&gr,sizeof(RcdType),1,g);
               break;
       case 3: /* 插入 */
               fn=P(gr); /* 函数P把gr加工为h的结构 */
               fwrite(&fn,sizeof(RedType),1,h);
               if(!feof(g))
	            fread(&gr,sizeof(RcdType),1,g);
               break;
       case 4: /* 更改“旧”主文件中记录 */
               Q(&fr,gr); /* 函数Q将fr和gr归并成一个h结构的记录 */
               fwrite(&fr,sizeof(RedType),1,h);
               if(!feof(f))
	            fread(&fr,sizeof(RedType),1,f);
               if(!feof(g))
	            fread(&gr,sizeof(RcdType),1,g);
               break;
       default:exit(ERROR); /* 其它均为出错情况 */
     }
   }
 }

 void print(RedType t)
 {
   printf("%6d%4d\n",t.accounts,t.amount);
 }

 void printc(RcdType t)
 {
   printf("%6d%6d%8c\n",t.accounts,t.amount,t.code);
 }

 void main()
 {
   RedType c,a[8]={{1,50},{5,78},{12,100},{14,95},{15,360},{18,200},{20,510},{INT_MAX,0}}; /* 主文件数据 */
   RcdType d,b[6]={{8,100,'I'},{12,-25,'U'},{14,38,'U'},{18,-200,'D'},{21,60,'I'},{INT_MAX,0,'U'}}; /* 已排序的事务文件数据 */
   FILE *f,*g,*h;
   int j;
   f=fopen("old","wb"); /* 以写的方式打开主文件old */
   fwrite(a,sizeof(RedType),8,f); /* 将数组a中的数据写入文件old */
   fclose(f); /* 关闭文件old，形成主文件 */
   f=fopen("change","wb"); /* 以写的方式打开事务文件change */
   fwrite(b,sizeof(RcdType),6,f); /* 将数组b中的数据写入文件change */
   fclose(f); /* 关闭文件change，形成已排序的事务文件 */
   f=fopen("old","rb"); /* 以读的方式打开主文件old */
   printf("主文件内容:\n");
   printf("  帐号 余额\n");
   do
   {
     j=fread(&c,sizeof(RedType),1,f);
     if(j==1)
       print(c); /* 输出r的内容 */
   }while(j==1);
   rewind(f); /* 使f的指针重新返回文件的起始位置，以便重新读入内存 */
   g=fopen("change","rb"); /* 以读的方式打开已排序的事务文件change */
   printf("已排序的事务文件内容:\n");
   printf("  帐号 存取数量 修改要求\n");
   do
   {
     j=fread(&d,sizeof(RcdType),1,g);
     if(j==1)
       printc(d); /* 输出r的内容 */
   }while(j==1);
   rewind(g); /* 使g的指针重新返回文件的起始位置，以便重新读入内存 */
   h=fopen("new","wb"); /* 以写的方式打开新主文件new */
   MergeFile(f,g,h); /* 生成新主文件 */
   fclose(f); /* 关闭文件old */
   fclose(g); /* 关闭文件change */
   fclose(h); /* 关闭文件new */
   f=fopen("new","rb"); /* 以读的方式打开新主文件new */
   printf("新主文件内容:\n");
   printf("  帐号 余额\n");
   do
   {
     j=fread(&c,sizeof(RedType),1,f);
     if(j==1)
       print(c); /* 输出r的内容 */
   }while(j==1);
   fclose(f); /* 关闭文件new */
 }

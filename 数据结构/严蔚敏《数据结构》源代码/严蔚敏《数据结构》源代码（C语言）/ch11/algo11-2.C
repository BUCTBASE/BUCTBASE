 /* algo11-2.c 通过置换－选择排序产生不等长的初始归并段文件 */
 #include"c1.h"
 typedef int InfoType; /* 定义其它数据项的类型 */
 #include"c10-1.h" /* 定义KeyType、RedType及SqList */
 #define MAXKEY INT_MAX
 #define RUNEND_SYMBOL INT_MAX
 #define w 6 /* 内存工作区可容纳的记录个数 */
 #define M 10 /* 设输出M个数据换行 */
 #define N 24 /* 设大文件有N个数据 */

 typedef int LoserTree[w]; /* 败者树是完全二叉树且不含叶子，可采用顺序存储结构 */
 typedef struct
 {
   RedType rec; /* 记录 */
   KeyType key; /* 从记录中抽取的关键字 */
   int rnum; /* 所属归并段的段号 */
 }RedNode,WorkArea[w]; /* 内存工作区，容量为w */

 void Select_MiniMax(LoserTree ls,WorkArea wa,int q) /* 算法11.6 */
 { /* 从wa[q]起到败者树的根比较选择MINIMAX记录，并由q指示它所在的归并段 */
   int p,s,t;
   for(t=(w+q)/2,p=ls[t];t>0;t=t/2,p=ls[t])
     if(wa[p].rnum<wa[q].rnum||wa[p].rnum==wa[q].rnum&&wa[p].key<wa[q].key)
     {
       s=q;
       q=ls[t]; /* q指示新的胜利者 */
       ls[t]=s;
     }
   ls[0]=q;
 }

 void Construct_Loser(LoserTree ls,WorkArea wa,FILE *fi)
 { /* 输入w个记录到内存工作区wa,建得败者树ls,选出关键字最小的记录并由s指示 */
   /* 其在wa中的位置。算法11.7 */
   int i;
   for(i=0;i<w;++i)
     wa[i].rnum=wa[i].key=ls[i]=0; /* 工作区初始化 */
   for(i=w-1;i>=0;--i)
   {
     fread(&wa[i].rec,sizeof(RedType),1,fi); /* 输入一个记录 */
     wa[i].key=wa[i].rec.key; /* 提取关键字 */
     wa[i].rnum=1; /* 其段号为＂1＂ */
     Select_MiniMax(ls,wa,i); /* 调整败者 */
   }
 }

 void get_run(LoserTree ls,WorkArea wa,int rc,int *rmax,FILE *fi,FILE *fo)
 { /* 求得一个初始归并段，fi为输入文件指针，fo为输出文件指针。算法11.5 */
   int q;
   KeyType minimax;
   while(wa[ls[0]].rnum==rc) /* 选得的MINIMAX记录属当前段时 */
   {
     q=ls[0]; /* q指示MINIMAX记录在wa中的位置 */
     minimax=wa[q].key;
     fwrite(&wa[q].rec,sizeof(RedType),1,fo); /* 将刚选得的MINIMAX记录写入输出文件 */
     fread(&wa[q].rec,sizeof(RedType),1,fi); /* 从输入文件读入下一记录(改) */
     if(feof(fi))
     { /* 输入文件结束，虚设记录（属＂rmax+1＂段） */
       wa[q].rnum=*rmax+1;
       wa[q].key=MAXKEY;
     }
     else
     { /* 输入文件非空时 */
       wa[q].key=wa[q].rec.key; /* 提取关键字 */
       if(wa[q].key<minimax)
       { /* 新读入的记录属下一段 */
         *rmax=rc+1;
	 wa[q].rnum=*rmax;
       }
       else /* 新读入的记录属当前段 */
	 wa[q].rnum=rc;
     }
     Select_MiniMax(ls,wa,q); /* 选择新的MINIMAX记录 */
   }
 }

 void Replace_Selection(LoserTree ls,WorkArea wa,FILE *fi,FILE *fo)
 { /* 在败者树ls和内存工作区wa上用置换－选择排序求初始归并段，fi为输入文件 */
   /* (只读文件)指针,fo为输出文件(只写文件)指针,两个文件均已打开。算法11.4 */
   int rc,rmax;
   RedType j;
   j.key=RUNEND_SYMBOL;
   Construct_Loser(ls,wa,fi); /* 初建败者树 */
   rc=rmax=1; /* rc指示当前生成的初始归并段的段号，rmax指示wa中关键字所属初始归并段的最大段号 */
   while(rc<=rmax) /* ＂rc=rmax+1＂标志输入文件的置换－选择排序已完成 */
   {
     get_run(ls,wa,rc,&rmax,fi,fo); /* 求得一个初始归并段 */
     j.otherinfo=rc;
     fwrite(&j,sizeof(RedType),1,fo); /* 将段结束标志写入输出文件 */
     rc=wa[ls[0]].rnum; /* 设置下一段的段号 */
   }
 }

 void print(RedType t)
 {
   printf("(%d,%d)",t.key,t.otherinfo);
 }

 void main()
 {
   RedType b,a[N]={{51,1},{49,2},{39,3},{46,4},{38,5},{29,6},{14,7},{61,8},{15,9},{30,10},{1,11},{48,12},{52,13},{3,14},{63,15},{27,16},{4,17},{13,18},{89,19},{24,20},{46,21},{58,22},{33,23},{76,24}};
   FILE *fi,*fo;
   LoserTree ls;
   WorkArea wa;
   int i,k,j=RUNEND_SYMBOL;
   char s[3],fname[4];
   fo=fopen("ori","wb"); /* 以写的方式打开大文件ori */
   fwrite(a,sizeof(RedType),N,fo); /* 将数组a写入大文件ori */
   fclose(fo);
   fi=fopen("ori","rb"); /* 以读的方式重新打开大文件ori */
   printf("大文件的记录为:\n");
   for(i=1;i<=N;i++)
   {
     fread(&b,sizeof(RedType),1,fi); /* 依次将大文件ori的数据读入b */
     print(b); /* 输出b的内容 */
     if(i%M==0)
       printf("\n");
   }
   printf("\n");
   rewind(fi); /* 使fi的指针重新返回大文件ori的起始位置，以便重新读入内存，产生有序的子文件 */
   fo=fopen("out","wb"); /* 以写的方式打开初始归并段文件out */
   Replace_Selection(ls,wa,fi,fo); /* 用置换－选择排序求初始归并段 */
   fclose(fo);
   fclose(fi);
   fi=fopen("out","rb"); /* 以读的方式重新打开初始归并段文件out */
   printf("初始归并段文件的记录为:\n");
   i=1;
   do
   {
     k=fread(&b,sizeof(RedType),1,fi); /* 依次将大文件out的数据读入b */
     if(k==1)
     {
       print(b); /* 输出b的内容 */
       if(i++%M==0)
         printf("\n");
     }
   }while(k==1);
   printf("\n");
   rewind(fi); /* 使fi的指针重新返回大文件ori的起始位置，以便重新读入内存，产生有序的子文件 */
   k=0;
   while(!feof(fi)) /* 按段输出初始归并段文件out */
   {
     itoa(k,s,10); /* 依次生成文件名f0,f1,… */
     strcpy(fname,"f");
     strcat(fname,s);
     fo=fopen(fname,"wb"); /* 依次以写的方式打开文件f0,f1,… */
     do
     {
       i=fread(&b,sizeof(RedType),1,fi);
       if(i==1) /* fread()调用成功 */
       {
	 fwrite(&b,sizeof(RedType),1,fo); /* 将b写入文件f0,f1,… */
         if(b.key==j) /* 1个归并段结束 */
         {
           k++;
           fclose(fo);
           break;
         }
       }
     }while(i==1);
   };
   fclose(fi);
   printf("共产生%d个初始归并段文件\n",k);
 }

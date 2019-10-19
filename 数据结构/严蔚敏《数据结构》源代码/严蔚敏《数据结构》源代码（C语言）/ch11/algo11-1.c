 /* algo11-1.c 调用bo11-1.c的程序 */
 #include"c1.h"
 typedef int InfoType; /* 定义其它数据项的类型 */
 #include"c9.h"
 #include"c10-1.h" /* 定义KeyType、RedType及SqList */
 #include"bo10-1.c"
 #define k 5 /* k路归并 */
 #include"bo11-1.c"
 #define N 3 /* 设每小个文件有N个数据(可将整个文件一次读入内存的称为小文件) */
 #define M 10 /* 设输出M个数据换行 */

 void print(RedType t)
 {
   printf("(%d,%d)",t.key,t.otherinfo);
 }

 void main()
 {
   RedType a[k*N]={{16,1},{15,2},{10,3},{20,4},{9,5},{18,6},{22,7},{20,8},{40,9},{15,10},{25,11},{6,12},{12,13},{48,14},{37,15}}; /* 有k*N个记录的数组 */
   RedType r,t={MAXKEY}; /* 小文件尾部的结束标志 */
   SqList l;
   int i,j;
   char fname[k][3],fori[4]="ori",fout[4]="out",s[3];
   LoserTree ls;
   /* 由数组a创造1个大文件(不能将整个文件一次读入内存的称为大文件) */
   fp[k]=fopen(fori,"wb"); /* 以写的方式打开大文件fori */
   fwrite(a,sizeof(RedType),k*N,fp[k]); /* 将数组a中的数据写入文件fori中(表示1个大文件) */
   fclose(fp[k]); /* 关闭文件fori */
   fp[k]=fopen(fori,"rb"); /* 以读的方式打开大文件fori */
   printf("大文件的记录为:\n");
   for(i=1;i<=N*k;i++)
   {
     fread(&r,sizeof(RedType),1,fp[k]); /* 依次将大文件fori的数据读入r */
     print(r); /* 输出r的内容 */
     if(i%M==0)
       printf("\n");
   }
   printf("\n");
   rewind(fp[k]); /* 使fp[k]的指针重新返回大文件fori的起始位置，以便重新读入内存，产生有序的子文件 */
   for(i=0;i<k;i++) /* 将大文件fori的数据分成k组，每组N个数据 */
   { /* 排序后分别存到小文件f0,f1,…中 */
     fread(&l.r[1],sizeof(RedType),N,fp[k]); /* 将大文件fori的N个数据读入l */
     l.length=N;
     InsertSort(&l); /* 对l进行内部排序 */
     itoa(i,s,10); /* 生成k个文件名f0,f1,f2,… */
     strcpy(fname[i],"f");
     strcat(fname[i],s);
     fp[i]=fopen(fname[i],"wb"); /* 以写的方式打开文件f0,f1,… */
     fwrite(&l.r[1],sizeof(RedType),N,fp[i]); /* 将排序后的N个数据分别写入f0,f1,… */
     fwrite(&t,sizeof(RedType),1,fp[i]); /* 将文件结束标志分别写入f0,f1,… */
     fclose(fp[i]); /* 关闭文件f0,f1,… */
   }
   fclose(fp[k]); /* 关闭大文件fori */
   for(i=0;i<k;i++)
   { /* 依次打开f0,f1,f2,…,k个文件 */
     itoa(i,s,10); /* 生成k个文件名f0,f1,f2,… */
     strcpy(fname[i],"f");
     strcat(fname[i],s);
     fp[i]=fopen(fname[i],"rb"); /* 以读的方式打开文件f0,f1,… */
     printf("有序子文件f%d的记录为:\n",i);
     for(j=0;j<=N;j++)
     {
       fread(&r,sizeof(RedType),1,fp[i]); /* 依次将f0,f1,…的数据读入r */
       print(r); /* 输出r的内容 */
     }
     printf("\n");
     rewind(fp[i]); /* 使fp[i]的指针重新返回f0,f1,…的起始位置，以便重新读入内存 */
   }
   fp[k]=fopen(fout,"wb"); /* 以写的方式打开大文件fout */
   K_Merge(ls,b); /* 利用败者树ls将k个输入归并段中的记录归并到输出归并段，即大文件fout */
   for(i=0;i<k;i++)
     fclose(fp[i]); /* 关闭文件f0,f1,… */
   fclose(fp[k]); /* 关闭文件fout */
   fp[k]=fopen(fout,"rb"); /* 以读的方式打开大文件fout验证排序 */
   printf("排序后的大文件的记录为:\n");
   for(i=1;i<=N*k+1;i++)
   {
     fread(&t,sizeof(RedType),1,fp[k]);
     print(t);
     if(i%M==0)
       printf("\n");
   }
   printf("\n");
   fclose(fp[k]); /* 关闭文件fout */
 }

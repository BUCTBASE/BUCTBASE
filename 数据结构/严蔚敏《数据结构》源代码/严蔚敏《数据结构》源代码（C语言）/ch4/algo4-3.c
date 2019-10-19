 /* algo4-3.c 文本行编辑 */
 #include"c1.h"
 #include"c4-2.h" /* 采用串的堆分配存储结构 */
 #include"bo4-2.c" /* 串的堆分配基本操作 */

 #define MAX_LEN 25 /* 文件最大行数 */
 #define LINE_LEN 75 /* 每行字符数最大值+1 */
 #define NAME_LEN 20 /* 文件名最大长度(包括盘符、路径)+1 */

 /* 全局变量 */
 HString T[MAX_LEN];
 char str[LINE_LEN],filename[NAME_LEN]="";
 FILE *fp;
 int n=0; /* 文件行数 */

 void Open()
 { /* 打开文件(新或旧) */
   int i;
   if(filename[0]) /* 文件已打开 */
     printf("已存在打开的文件\n");
   else
   {
     printf("请输入文件名(可包括盘符、路径，不超过%d个字符): ",NAME_LEN-1);
     scanf("%s%*c",filename);
     fp=fopen(filename,"r");
     if(fp) /* 已存在此文件 */
     {
       do
       {
         fgets(str,LINE_LEN,fp);
         i=strlen(str);
         str[i-1]=0; /* 将10强制改为0 */
         i--;
         if(i>0)
         {
           StrAssign(&T[n],str);
           n++;
           if(n>MAX_LEN)
           {
             printf("文件太大\n");
             return;
           }
         }
       }while(i>0);
       fclose(fp);
     }
     else
       printf("新文件\n");
   }
 }

 void List()
 { /* 显示文件内容 */
   int i;
   for(i=0;i<n;i++)
   {
     printf("%d: ",i+1);
     StrPrint(T[i]);
   }
   getchar();
 }

 void Insert()
 { /* 插入行 */
   int i,l,m;
   printf("在第l行前插m行,请输入l m: ");
   scanf("%d%d%*c",&l,&m);
   if(n+m>MAX_LEN)
   {
     printf("插入行太多\n");
     return;
   }
   if(n>=l-1&&l>0)
   {
     for(i=n-1;i>=l-1;i--)
       T[i+m]=T[i];
     n+=m;
     printf("请顺序输入待插入内容:\n");
     for(i=l-1;i<l-1+m;i++)
     {
       gets(str);
       InitString(&T[i]);
       StrAssign(&T[i],str);
     }
   }
   else
     printf("行超出范围\n");
 }

 void Delete()
 { /* 删除行 */
   int i,l,m;
   printf("从第l行起删除m行,请输入l m: ");
   scanf("%d%d%*c",&l,&m);
   if(n>=l+m-1&&l>0)
   {
     for(i=l-1+m;i<n;i++)
       T[i-m]=T[i];
     for(i=n-m;i<n;i++)
       InitString(&T[i]);
     n-=m;
   }
   else
     printf("行超出范围\n");
 }

 void Copy()
 { /* 拷贝行 */
   int i,l,m,k;
   printf("把第l行开始的m行插在原k行之前,请输入l m k: ");
   scanf("%d%d%d%*c",&l,&m,&k);
   if(n+m>MAX_LEN)
   {
     printf("拷贝行太多\n");
     return;
   }
   if(n>=k-1&&n>=l-1+m&&(k>=l+m||k<=l))
   {
     for(i=n-1;i>=k-1;i--)
       T[i+m]=T[i];
     n+=m;
     if(k<=l)
       l+=m;
     for(i=l-1;i<l-1+m;i++)
     {
       InitString(&T[i+k-l]);
       StrCopy(&T[i+k-l],T[i]);
     }
   }
   else
     printf("行超出范围\n");
 }

 void Modify()
 { /* 修改行 */
   int i;
   printf("请输入待修改的行号: ");
   scanf("%d%*c",&i);
   if(i>0&&i<=n) /* 行号合法 */
   {
     printf("%d: ",i);
     StrPrint(T[i-1]);
     printf("请输入新内容: ");
     gets(str);
     StrAssign(&T[i-1],str);
   }
   else
     printf("行号超出范围\n");
 }

 void Search()
 { /* 查找字符串 */
   int i,k,f=1; /* f为继续查找标志 */
   char b;
   HString s;
   printf("请输入待查找的字符串: ");
   scanf("%s%*c",str);
   InitString(&s);
   StrAssign(&s,str);
   for(i=0;i<n&&f;i++) /* 逐行查找 */
   {
     k=1; /* 由每行第1个字符起查找 */
     while(k)
     {
       k=Index(T[i],s,k); /* 由本行的第k个字符开始查找 */
       if(k) /* 找到 */
       {
         printf("第%d行: ",i+1);
         StrPrint(T[i]);
         printf("第%d个字符处找到。继续查找吗(Y/N)? ",k);
         b=getchar();
         getchar();
         if(b!='Y'&&b!='y') /* 中断查找 */
         {
           f=0;
           break;
         }
         else
           k++;
       }
     }
   }
   if(f)
     printf("没找到\n");
 }

 void Replace1()
 { /* 替换字符串 */
   int i,k,f=1; /* f为继续替换标志 */
   char b;
   HString s,t;
   printf("请输入待替换的字符串: ");
   scanf("%s%*c",str);
   InitString(&s);
   StrAssign(&s,str);
   printf("替换为: ");
   scanf("%s%*c",str);
   InitString(&t);
   StrAssign(&t,str);
   for(i=0;i<n&&f;i++) /* 逐行查找、替换 */
   {
     k=1; /* 由每行第1个字符起查找 */
     while(k)
     {
       k=Index(T[i],s,k); /* 由本行的第k个字符开始查找 */
       if(k) /* 找到 */
       {
         printf("第%d行: ",i+1);
         StrPrint(T[i]);
         printf("第%d个字符处找到。是否替换(Y/N)? ",k);
         b=getchar();
         getchar();
         if(b=='Y'||b=='y')
         {
           StrDelete(&T[i],k,StrLength(s));
           StrInsert(&T[i],k,t);
         }
         printf("继续替换吗(Y/N)?");
         b=getchar();
         getchar();
         if(b!='Y'&&b!='y') /* 中断查找、替换 */
         {
           f=0;
           break;
         }
         else
           k+=StrLength(t);
       }
     }
   }
   if(f)
     printf("没找到\n");
 }

 void Save()
 { /* 存盘 */
   int i;
   getchar();
   fp=fopen(filename,"w");
   if(fp)
   {
     for(i=0;i<n;i++)
     {
       T[i].ch[T[i].length]=0;
       fputs(T[i].ch,fp);
       fputc(10,fp);
     }
     fputc(10,fp);
     fclose(fp);
   }
   else
     printf("存盘失败\n");
 }

 void main()
 {
   Status s=TRUE;
   int i,k;
   for(i=0;i<MAX_LEN;i++) /* 初始化串 */
     InitString(&T[i]);
   while(s)
   {
     printf("请选择: 1.打开文件(新或旧)  2.显示文件内容\n");
     printf("        3.插入行  4.删除行  5.拷贝行  6.修改行\n");
     printf("        7.查找字符串        8.替换字符串\n");
     printf("        9.存盘退出          0.放弃编辑\n");
     scanf("%d",&k);
     switch(k)
     {
       case 1: Open();
               break;
       case 2: List();
               break;
       case 3: Insert();
               break;
       case 4: Delete();
               break;
       case 5: Copy();
               break;
       case 6: Modify();
               break;
       case 7: Search();
               break;
       case 8: Replace1();
               break;
       case 9: Save();
       case 0: s=FALSE;
     }
   }
 }

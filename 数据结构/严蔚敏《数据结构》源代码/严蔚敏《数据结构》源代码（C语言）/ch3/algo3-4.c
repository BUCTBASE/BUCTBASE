 /* algo3-4.c 行编辑程序,实现算法3.2 */
 typedef char SElemType;
 #include"c1.h"
 #include"c3-1.h"
 #include"bo3-1.c"
 FILE *fp;

 Status copy(SElemType c)
 { /* 将字符c送至fp所指的文件中 */
   fputc(c,fp);
   return OK;
 }

 void LineEdit()
 { /* 利用字符栈s，从终端接收一行并送至调用过程的数据区。算法3.2 */
   SqStack s;
   char ch,c;
   InitStack(&s);
   printf("请输入一个文本文件,^Z结束输入:\n");
   ch=getchar();
   while(ch!=EOF)
   { /* EOF为^Z键，全文结束符 */
     while(ch!=EOF&&ch!='\n')
     {
       switch(ch)
       {
         case '#':Pop(&s,&c);
                  break; /* 仅当栈非空时退栈 */
         case '@':ClearStack(&s);
                  break; /* 重置s为空栈 */
         default :Push(&s,ch); /* 有效字符进栈 */
       }
       ch=getchar(); /* 从终端接收下一个字符 */
     }
     StackTraverse(s,copy); /* 将从栈底到栈顶的栈内字符传送至文件 */
     ClearStack(&s); /* 重置s为空栈 */
     fputc('\n',fp);
     if(ch!=EOF)
       ch=getchar();
   }
   DestroyStack(&s);
 }

 void main()
 {
   fp=fopen("ED.DAT","w"); /* 在当前目录下建立ED.DAT文件，用于写数据， */
   if(fp)                  /* 如已有同名文件则先删除原文件 */
   {
     LineEdit();
     fclose(fp); /* 关闭fp所指的文件 */
   }
   else
     printf("建立文件失败!\n");
 }


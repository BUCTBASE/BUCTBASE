 /* main4-3.c 检验bo4-3.c的主程序 */
 char blank='#'; /* 全局变量,用于填补空余 */
 #include"c1.h"
 #include"c4-3.h"
 #include"bo4-3.c"
 void main()
 {
   char *s1="ABCDEFGHI",*s2="12345",*s3="",*s4="asd#tr",*s5="ABCD";
   Status k;
   int pos,len;
   LString t1,t2,t3,t4;
   InitString(&t1);
   InitString(&t2);
   printf("初始化串t1后，串t1空否？%d(1:空 0:否) 串长=%d\n",StrEmpty(t1),StrLength(t1));
   k=StrAssign(&t1,s3);
   if(k==OK)
   {
     printf("串t1为: ");
     StrPrint(t1);
   }
   else
     printf("出错\n"); /* 不能生成空串 */
   k=StrAssign(&t1,s4);
   if(k==OK)
   {
     printf("串t1为: ");
     StrPrint(t1);
   }
   else
     printf("出错\n"); /* 不能生成含有变量blank所代表的字符的串 */
   k=StrAssign(&t1,s1);
   if(k==OK)
   {
     printf("串t1为: ");
     StrPrint(t1);
   }
   else
     printf("出错\n");
   printf("串t1空否？%d(1:空 0:否) 串长=%d\n",StrEmpty(t1),StrLength(t1));
   StrAssign(&t2,s2);
   printf("串t2为: ");
   StrPrint(t2);
   StrCopy(&t3,t1);
   printf("由串t1拷贝得到串t3,串t3为: ");
   StrPrint(t3);
   InitString(&t4);
   StrAssign(&t4,s5);
   printf("串t4为: ");
   StrPrint(t4);
   Replace(&t3,t4,t2);
   printf("用t2取代串t3中的t4串后，串t3为: ");
   StrPrint(t3);
   ClearString(&t1);
   printf("清空串t1后，串t1空否？%d(1:空 0:否) 串长=%d\n",StrEmpty(t1),StrLength(t1));
   Concat(&t1,t2,t3);
   printf("串t1(=t2+t3)为: ");
   StrPrint(t1);
   Zip(&t1);
   printf("去除不必要的占位符后，串t1为: ");
   StrPrint(t1);
   pos=Index(t1,t3,1);
   printf("pos=%d\n",pos);
   printf("在串t1的第pos个字符之前插入串t2，请输入pos: ");
   scanf("%d",&pos);
   k=StrInsert(&t1,pos,t2);
   if(k)
   {
     printf("插入串t2后，串t1为: ");
     StrPrint(t1);
   }
   else
     printf("插入失败！\n");
   printf("求从t1的第pos个字符起,长度为len的子串t2,请输入pos,len: ");
   scanf("%d,%d",&pos,&len);
   SubString(&t2,t1,pos,len);
   printf("串t2为: ");
   StrPrint(t2);
   printf("StrCompare(t1,t2)=%d\n",StrCompare(t1,t2));
   printf("删除串t1中的子字符串：从第pos个字符起删除len个字符。请输入pos,len：");
   scanf("%d,%d",&pos,&len);
   k=StrDelete(&t1,pos,len);
   if(k)
   {
     printf("从第%d位置起删除%d个元素后串t1为:",pos,len);
     StrPrint(t1);
   }
 }
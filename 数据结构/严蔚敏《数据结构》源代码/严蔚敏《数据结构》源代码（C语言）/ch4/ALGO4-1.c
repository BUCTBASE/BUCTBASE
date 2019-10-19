 /* algo4-1.c 实现算法4.6、4.7的程序 */
 #include"c1.h"
 #include"c4-1.h"
 #include"bo4-1.c"

 void get_next(SString T,int next[])
 { /* 求模式串T的next函数值并存入数组next 算法 4.7 */
   int i=1,j=0;
   next[1]=0;
   while(i<T[0])
     if(j==0||T[i]==T[j])
     {
       ++i;
       ++j;
       next[i]=j;
     }
     else
       j=next[j];
 }

 int Index_KMP(SString S,SString T,int pos,int next[])
 { /* 利用模式串T的next函数求T在主串S中第pos个字符之后的位置的KMP算法。 */
   /* 其中,T非空,1≤pos≤StrLength(S)。算法 4.6 */
   int i=pos,j=1;
   while(i<=S[0]&&j<=T[0])
     if(j==0||S[i]==T[j]) /* 继续比较后继字符 */
     {
       ++i;
       ++j;
     }
     else /* 模式串向右移动 */
       j=next[j];
   if(j>T[0]) /* 匹配成功 */
     return i-T[0];
   else
     return 0;
 }

 void main()
 {
   int i,j,*p;
   SString s1,s2; /* 以教科书中图4.5为例 */
   StrAssign(s1,"acabaabaabcacaabc");
   printf("主串为: ");
   StrPrint(s1);
   StrAssign(s2,"abaabcac");
   printf("子串为: ");
   StrPrint(s2);
   i=StrLength(s2);
   p=(int*)malloc((i+1)*sizeof(int)); /* 生成s2的next数组 */
   get_next(s2,p);
   printf("子串的next函数为: ");
   for(j=1;j<=i;j++)
     printf("%d ",*(p+j));
   printf("\n");
   i=Index_KMP(s1,s2,1,p);
   if(i)
     printf("主串和子串在第%d个字符处首次匹配\n",i);
   else
     printf("主串和子串匹配不成功\n");
 }
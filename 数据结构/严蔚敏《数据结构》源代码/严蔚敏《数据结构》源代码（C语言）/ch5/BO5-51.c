 /* bo5-51.c 广义表的书写形式串为SString类型 */
 #include"c4-1.h" /* 定义SString类型 */
 #include"bo4-1.c" /* SString类型的基本操作 */
 void sever(SString str,SString hstr) /* 算法5.8  SString是数组，不需引用类型 */
 { /* 将非空串str分割成两部分:hsub为第一个','之前的子串,str为之后的子串 */
   int n,k,i; /* k记尚未配对的左括号个数 */
   SString ch,c1,c2,c3;
   n=StrLength(str);
   StrAssign(c1,",");
   StrAssign(c2,"(");
   StrAssign(c3,")");
   SubString(ch,str,1,1);
   for(i=1,k=0;i<=n&&StrCompare(ch,c1)||k!=0;++i)
   { /* 搜索最外层的第一个逗号 */
     SubString(ch,str,i,1);
     if(!StrCompare(ch,c2))
       ++k;
     else if(!StrCompare(ch,c3))
       --k;
   }
   if(i<=n)
   {
     SubString(hstr,str,1,i-2);
     SubString(str,str,i,n-i+1);
   }
   else
   {
     StrCopy(hstr,str);
     ClearString(str);
   }
 }

 Status CreateGList(GList *L,SString S) /* 算法5.7 */
 { /* 采用头尾链表存储结构,由广义表的书写形式串S创建广义表L。设emp="()" */
   SString sub,hsub,emp;
   GList p,q;
   StrAssign(emp,"()");
   if(!StrCompare(S,emp))
     *L=NULL; /* 创建空表 */
   else
   {
     *L=(GList)malloc(sizeof(GLNode));
     if(!*L) /* 建表结点 */
       exit(OVERFLOW);
     if(StrLength(S)==1) /* S为单原子 */
     {
       (*L)->tag=ATOM;
       (*L)->a.atom=S[1]; /* 创建单原子广义表 */
     }
     else
     {
       (*L)->tag=LIST;
       p=*L;
       SubString(sub,S,2,StrLength(S)-2); /* 脱外层括号 */
       do
       { /* 重复建n个子表 */
         sever(sub,hsub); /* 从sub中分离出表头串hsub */
         CreateGList(&p->a.ptr.hp,hsub);
         q=p;
         if(!StrEmpty(sub)) /* 表尾不空 */
         {
           p=(GLNode *)malloc(sizeof(GLNode));
           if(!p)
             exit(OVERFLOW);
           p->tag=LIST;
           q->a.ptr.tp=p;
         }
       }while(!StrEmpty(sub));
       q->a.ptr.tp=NULL;
     }
   }
   return OK;
 }


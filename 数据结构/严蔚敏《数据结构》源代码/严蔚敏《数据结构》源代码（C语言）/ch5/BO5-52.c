 /* bo5-52.c 广义表的书写形式串为HString类型 */
 #include"c4-2.h" /* 定义HString类型 */
 #include"bo4-2.c" /* HString类型的基本操作 */
 Status sever(HString *str,HString *hstr)
 { /* 将非空串str分割成两部分:hstr为第一个','之前的子串,str为之后的子串 */
   int n,i=1,k=0; /* k记尚未配对的左括号个数 */
   HString ch,c1,c2,c3;
   InitString(&ch); /* 初始化HString类型的变量 */
   InitString(&c1);
   InitString(&c2);
   InitString(&c3);
   StrAssign(&c1,",");
   StrAssign(&c2,"(");
   StrAssign(&c3,")");
   n=StrLength(*str);
   do
   {
     SubString(&ch,*str,i,1);
     if(!StrCompare(ch,c2))
       ++k;
     else if(!StrCompare(ch,c3))
       --k;
     ++i;
   }while(i<=n&&StrCompare(ch,c1)||k!=0);
   if(i<=n)
   {
     StrCopy(&ch,*str);
     SubString(hstr,ch,1,i-2);
     SubString(str,ch,i,n-i+1);
   }
   else
   {
     StrCopy(hstr,*str);
     ClearString(str);
   }
   return OK;
 }

 Status CreateGList(GList *L,HString S)
 { /* 采用头尾链表存储结构,由广义表的书写形式串S创建广义表L。设emp="()" */
   HString emp,sub,hsub;
   GList p,q;
   InitString(&emp);
   InitString(&sub);
   InitString(&hsub);
   StrAssign(&emp,"()");
   if(!StrCompare(S,emp)) /* 创建空表 */
     *L=NULL;
   else
   {
     *L=(GList)malloc(sizeof(GLNode));
     if(!*L) /* 建表结点不成功 */
       exit(OVERFLOW);
     if(StrLength(S)==1) /* 创建单原子广义表 */
     {
       (*L)->tag=ATOM;
       (*L)->a.atom=S.ch[0];
     }
     else
     {
       (*L)->tag=LIST;
       p=*L;
       SubString(&sub,S,2,StrLength(S)-2); /* 脱外层括号 */
       do /* 重复建n个子表 */
       {
         sever(&sub,&hsub); /* 从sub中分离出表头串hsub */
         CreateGList(&p->a.ptr.hp,hsub);
         q=p;
         if(!StrEmpty(sub)) /* 表尾不空 */
         {
           p=(GList)malloc(sizeof(GLNode));
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

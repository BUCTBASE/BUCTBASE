 /* algo2-11.c 实现算法2.20、2.21的程序 */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-5.h"
 #include"bo2-6.c"

 Status ListInsert_L(LinkList *L,int i,ElemType e) /* 算法2.20 */
 { /* 在带头结点的单链线性表L的第i个元素之前插入元素e */
   Link h,s;
   if(!LocatePos(*L,i-1,&h))
     return ERROR; /* i值不合法 */
   if(!MakeNode(&s,e))
     return ERROR; /* 结点分配失败 */
   InsFirst(L,h,s); /*对于从第i个结点开始的链表,第i-1个结点是它的头结点 */
   return OK;
 }

 Status MergeList_L(LinkList La,LinkList Lb,LinkList *Lc,int(*compare)(ElemType,ElemType))
 { /* 已知单链线性表La和Lb的元素按值非递减排列。归并La和Lb得到新的单链 */
   /* 线性表Lc，Lc的元素也按值非递减排列。（不改变La、Lb）算法2.21 */
   Link ha,hb,pa,pb,q;
   ElemType a,b;
   if(!InitList(Lc))
     return ERROR; /* 存储空间分配失败 */
   ha=GetHead(La); /* ha和hb分别指向La和Lb的头结点 */
   hb=GetHead(Lb);
   pa=NextPos(ha); /* pa和pb分别指向La和Lb的第一个结点 */
   pb=NextPos(hb);
   while(!ListEmpty(La)&&!ListEmpty(Lb)) /* La和Lb均非空 */
   {
     a=GetCurElem(pa); /* a和b为两表中当前比较元素 */
     b=GetCurElem(pb);
     if(compare(a,b)<=0)
     {
       DelFirst(&La,ha,&q);
       InsFirst(Lc,(*Lc).tail,q);
       pa=NextPos(ha);
     }
     else /* a>b */
     {
       DelFirst(&Lb,hb,&q);
       InsFirst(Lc,(*Lc).tail,q);
       pb=NextPos(hb);
     }
   }
   if(!ListEmpty(La))
     Append(Lc,pa);
   else
     Append(Lc,pb);
   FreeNode(&ha);
   FreeNode(&hb);
   return OK;
 }

 int comp(ElemType c1,ElemType c2)
 {
   return c1-c2;
 }

 void visit(ElemType c)
 {
   printf("%d ",c); /* 整型 */
 }

 void main()
 {
   LinkList La,Lb,Lc;
   int j;
   InitList(&La);
   for(j=1;j<=5;j++)
     ListInsert_L(&La,j,j); /* 顺序插入 1 2 3 4 5 */
   printf("La=");
   ListTraverse(La,visit);
   InitList(&Lb);
   for(j=1;j<=5;j++)
     ListInsert_L(&Lb,j,2*j); /* 顺序插入 2 4 6 8 10 */
   printf("Lb=");
   ListTraverse(Lb,visit);
   InitList(&Lc);
   MergeList_L(La,Lb,&Lc,comp); /* 归并La和Lb，产生Lc */
   printf("Lc=");
   ListTraverse(Lc,visit);
   DestroyList(&Lc);
 }

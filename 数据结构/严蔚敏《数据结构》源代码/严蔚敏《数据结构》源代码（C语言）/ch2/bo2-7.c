 /* bo2-7.c 多项式(存储结构由c2-6.h定义)的基本操作及算法2.22、2.23等 */
 #include"c2-5.h"
 #include"bo2-6.c"
 typedef LinkList polynomial;
 #define DestroyPolyn DestroyList /* 与bo2-6.cpp中的函数同义不同名 */
 #define PolynLength ListLength /* 与bo2-6.cpp中的函数同义不同名 */

 Status OrderInsertMerge(LinkList *L,ElemType e,int(* compare)(term,term))
 { /* 按有序判定函数compare()的约定，将值为e的结点插入或合并到升序链表L的适当位置 */
   Position q,s;
   if(LocateElemP(*L,e,&q,compare)) /* L中存在该指数项 */
   {
     q->data.coef+=e.coef; /* 改变当前结点系数的值 */
     if(!q->data.coef) /* 系数为0 */
     { /* 删除多项式L中当前结点 */
       s=PriorPos(*L,q); /* s为当前结点的前驱 */
       if(!s) /* q无前驱 */
         s=(*L).head;
       DelFirst(L,s,&q);
       FreeNode(&q);
     }
     return OK;
   }
   else /* 生成该指数项并插入链表 */
     if(MakeNode(&s,e)) /* 生成结点成功 */
     {
       InsFirst(L,q,s);
       return OK;
     }
     else /* 生成结点失败 */
       return ERROR;
 }

 int cmp(term a,term b) /* CreatPolyn()的实参 */
 { /* 依a的指数值<、=或>b的指数值，分别返回-1、0或+1 */
   if(a.expn==b.expn)
     return 0;
   else
     return (a.expn-b.expn)/abs(a.expn-b.expn);
 }

 void CreatPolyn(polynomial *P,int m) /* 算法2.22 */
 { /* 输入m项的系数和指数，建立表示一元多项式的有序链表P */
   Position q,s;
   term e;
   int i;
   InitList(P);
   printf("请依次输入%d个系数，指数：\n",m);
   for(i=1;i<=m;++i)
   { /* 依次输入m个非零项（可按任意顺序） */
     scanf("%f,%d",&e.coef,&e.expn);
     if(!LocateElemP(*P,e,&q,cmp)) /* 当前链表中不存在该指数项,cmp是实参 */
       if(MakeNode(&s,e)) /* 生成结点并插入链表 */
         InsFirst(P,q,s);
   }
 }

 void PrintPolyn(polynomial P)
 { /* 打印输出一元多项式P */
   Link q;
   q=P.head->next; /* q指向第一个结点 */
   printf("  系数    指数\n");
   while(q)
   {
     printf("%f  %d\n",q->data.coef,q->data.expn);
     q=q->next;
   }
 }

 void AddPolyn(polynomial *Pa,polynomial *Pb) /* 算法2.23 */
 { /* 多项式加法:Pa=Pa+Pb,并销毁一元多项式Pb */
   Position ha,hb,qa,qb;
   term a,b;
   ha=GetHead(*Pa);
   hb=GetHead(*Pb); /* ha和hb分别指向Pa和Pb的头结点 */
   qa=NextPos(ha);
   qb=NextPos(hb); /* qa和qb分别指向Pa和Pb中当前结点（现为第一个结点） */
   while(!ListEmpty(*Pa)&&!ListEmpty(*Pb)&&qa)
   { /* Pa和Pb均非空且ha没指向尾结点(qa!=0) */
     a=GetCurElem(qa);
     b=GetCurElem(qb); /* a和b为两表中当前比较元素 */
     switch(cmp(a,b))
     {
       case -1:ha=qa; /* 多项式Pa中当前结点的指数值小 */
               qa=NextPos(ha); /* ha和qa均向后移一个结点 */
               break;
       case 0: qa->data.coef+=qb->data.coef;
               /* 两者的指数值相等,修改Pa当前结点的系数值 */
               if(qa->data.coef==0) /* 删除多项式Pa中当前结点 */
               {
                 DelFirst(Pa,ha,&qa);
                 FreeNode(&qa);
               }
               else
                 ha=qa;
               DelFirst(Pb,hb,&qb);
               FreeNode(&qb);
               qb=NextPos(hb);
               qa=NextPos(ha);
               break;
       case 1: DelFirst(Pb,hb,&qb); /* 多项式Pb中当前结点的指数值小 */
               InsFirst(Pa,ha,qb);
               ha=ha->next;
               qb=NextPos(hb);
     }
   }
   if(!ListEmpty(*Pb))
   {
     (*Pb).tail=hb;
     Append(Pa,qb); /* 链接Pb中剩余结点 */
   }
   DestroyPolyn(Pb); /* 销毁Pb */
 }

 void AddPolyn1(polynomial *Pa,polynomial *Pb)
 { /* 另一种多项式加法的算法:Pa=Pa+Pb,并销毁一元多项式Pb */
   Position qb;
   term b;
   qb=GetHead(*Pb); /* qb指向Pb的头结点 */
   qb=qb->next; /* qb指向Pb的第一个结点 */
   while(qb)
   {
     b=GetCurElem(qb);
     OrderInsertMerge(Pa,b,cmp);
     qb=qb->next;
   }
   DestroyPolyn(Pb); /* 销毁Pb */
 }

 void Opposite(polynomial Pa)
 { /* 一元多项式系数取反 */
   Position p;
   p=Pa.head;
   while(p->next)
   {
     p=p->next;
     p->data.coef*=-1;
   }
 }

 void SubtractPolyn(polynomial *Pa,polynomial *Pb)
 { /* 多项式减法:Pa=Pa-Pb,并销毁一元多项式Pb */
   Opposite(*Pb);
   AddPolyn(Pa,Pb);
 }

 void MultiplyPolyn(polynomial *Pa,polynomial *Pb)
 { /* 多项式乘法:Pa=PaPb,并销毁一元多项式Pb */
   polynomial Pc;
   Position qa,qb;
   term a,b,c;
   InitList(&Pc);
   qa=GetHead(*Pa);
   qa=qa->next;
   while(qa)
   {
     a=GetCurElem(qa);
     qb=GetHead(*Pb);
     qb=qb->next;
     while(qb)
     {
       b=GetCurElem(qb);
       c.coef=a.coef*b.coef;
       c.expn=a.expn+b.expn;
       OrderInsertMerge(&Pc,c,cmp);
       qb=qb->next;
     }
     qa=qa->next;
   }
   DestroyPolyn(Pb); /* 销毁Pb */
   ClearList(Pa); /* 将Pa重置为空表 */
   (*Pa).head=Pc.head;
   (*Pa).tail=Pc.tail;
   (*Pa).len=Pc.len;
 }

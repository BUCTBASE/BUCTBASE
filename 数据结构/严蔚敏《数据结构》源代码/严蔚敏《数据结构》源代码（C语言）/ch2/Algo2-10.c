 /* algo2-10.c 两个仅设表尾指针的循环链表的合并（教科书图2.13） */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-2.h"
 #include"bo2-4.c"

 void MergeList_CL(LinkList *La,LinkList Lb)
 {
   LinkList p=Lb->next;
   Lb->next=(*La)->next;
   (*La)->next=p->next;
   free(p);
   *La=Lb;
 }

 void visit(ElemType c)
 {
   printf("%d ",c);
 }

 void main()
 {
   int n=5,i;
   LinkList La,Lb;
   InitList_CL(&La);
   for(i=1;i<=n;i++)
     ListInsert_CL(&La,i,i);
   printf("La="); /* 输出链表La的内容 */
   ListTraverse_CL(La,visit);
   InitList_CL(&Lb);
   for(i=1;i<=n;i++)
     ListInsert_CL(&Lb,1,i*2);
   printf("Lb="); /* 输出链表Lb的内容 */
   ListTraverse_CL(Lb,visit);
   MergeList_CL(&La,Lb);
   printf("La+Lb="); /* 输出合并后的链表的内容 */
   ListTraverse_CL(La,visit);
 }

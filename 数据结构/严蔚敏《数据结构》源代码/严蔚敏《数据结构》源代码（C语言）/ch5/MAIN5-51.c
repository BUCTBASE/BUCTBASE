 /* main5-51.c 检验bo5-5.c和bo5-51.c(字符串为SString类型)的主程序 */
 #include"c1.h"
 typedef char AtomType; /* 定义原子类型为字符型 */
 #include"c5-5.h" /* 定义广义表的头尾链表存储 */
 #include"bo5-5.c"
 #include"bo5-51.c"

 void visit(AtomType e)
 {
   printf("%c ", e);
 }

 void main()
 {
   char p[80];
   SString t;
   GList l,m;
   InitGList(&l);
   InitGList(&m);
   printf("空广义表l的深度=%d l是否空？%d(1:是 0:否)\n",GListDepth(l),GListEmpty(l));
   printf("请输入广义表l(书写形式：空表:(),单原子:a,其它:(a,(b),b)):\n");
   gets(p);
   StrAssign(t,p);
   CreateGList(&l,t);
   printf("广义表l的长度=%d\n",GListLength(l));
   printf("广义表l的深度=%d l是否空？%d(1:是 0:否)\n",GListDepth(l),GListEmpty(l));
   printf("遍历广义表l：\n");
   Traverse_GL(l,visit);
   printf("\n复制广义表m=l\n");
   CopyGList(&m,l);
   printf("广义表m的长度=%d\n",GListLength(m));
   printf("广义表m的深度=%d\n",GListDepth(m));
   printf("遍历广义表m：\n");
   Traverse_GL(m,visit);
   DestroyGList(&m);
   m=GetHead(l);
   printf("\nm是l的表头，遍历广义表m：\n");
   Traverse_GL(m,visit);
   DestroyGList(&m);
   m=GetTail(l);
   printf("\nm是l的表尾，遍历广义表m：\n");
   Traverse_GL(m,visit);
   InsertFirst_GL(&m,l);
   printf("\n插入l为m的表头，遍历广义表m：\n");
   Traverse_GL(m,visit);
   printf("\n删除m的表头，遍历广义表m：\n");
   DestroyGList(&l);
   DeleteFirst_GL(&m,&l);
   Traverse_GL(m,visit);
   printf("\n");
   DestroyGList(&m);
 }

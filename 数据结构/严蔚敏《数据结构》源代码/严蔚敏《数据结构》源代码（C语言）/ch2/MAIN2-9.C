 /* main2-9.c 检验bo2-9.c的主程序(除输出语句外，和main2-8.c很像) */
 #include"c1.h"
 typedef int ElemType;
 #include"c2-2.h" /* 此句和main2-8.c不同 */
 #include"bo2-2.c" /* 加此句 */
 #include"bo2-9.c" /* 此句和main2-8.c不同 */

 void visit(ElemType c) /* ListTraverse()调用的函数(类型要一致) */
 {
   printf("%d ",c);
 }

 void main()
 {
   LinkList L; /* 此句和main2-8.c不同 */
   ElemType d,e;
   Status i;
   int n;
   printf("按非降序建立n个元素的线性表L,请输入元素个数n: ");
   scanf("%d",&n);
   CreatAscend(&L,n);
   printf("依次输出L的元素：");
   ListTraverse(L,visit);
   InsertAscend(L,10); /* 按非降序插入元素10 */
   printf("按非降序插入元素10后，线性表L为：");
   ListTraverse(L,visit);
   HeadInsert(L,12); /* 在L的头部插入12 */
   EndInsert(L,9); /* 在L的尾部插入9 */
   printf("在L的头部插入12，尾部插入9后，线性表L为：");
   ListTraverse(L,visit);
   i=GetFirstElem(L,&e); /* 此句加 */
   printf("第1个元素是: %d\n",e); /* 此句加 */
   printf("请输入要删除的元素的值: ");
   scanf("%d",&e);
   i=DeleteElem(L,e);
   if(i)
     printf("成功删除%d!\n",e);
   else
     printf("不存在元素%d!\n",e);
   printf("线性表L为：");
   ListTraverse(L,visit);
   printf("请输入要取代的元素的序号 元素的新值: ");
   scanf("%d%d",&n,&e);
   ReplaceElem(L,n,e);
   printf("线性表L为：");
   ListTraverse(L,visit);
   DestroyList(&L);
   printf("销毁L后,按非升序重新建立n个元素的线性表L,请输入元素个数n(>2): ");
   scanf("%d",&n);
   CreatDescend(&L,n);
   printf("依次输出L的元素：");
   ListTraverse(L,visit);
   InsertDescend(L,10); /* 按非升序插入元素10 */
   printf("按非升序插入元素10后，线性表L为：");
   ListTraverse(L,visit);
   printf("请输入要删除的元素的值: ");
   scanf("%d",&e);
   i=DeleteElem(L,e);
   if(i)
     printf("成功删除%d!\n",e);
   else
     printf("不存在元素%d!\n",e);
   printf("线性表L为：");
   ListTraverse(L,visit);
   DeleteFirst(L,&e);
   DeleteTail(L,&d);
   printf("删除表头元素%d和表尾元素%d后,线性表L为：",e,d);
   ListTraverse(L,visit);
 }
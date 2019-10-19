 /* main6-2.c 检验bo6-2.c的主程序,利用条件编译选择数据类型(另一种方法) */
 #define CHAR /* 字符型 */
 /* #define INT /* 整型（二者选一） */
 #include"c1.h"
 #ifdef CHAR
   typedef char TElemType;
   TElemType Nil=' '; /* 字符型以空格符为空 */
 #endif
 #ifdef INT
   typedef int TElemType;
   TElemType Nil=0; /* 整型以0为空 */
 #endif
 #include"c6-2.h"
 #include"bo6-2.c"

 Status visitT(TElemType e)
 {
 #ifdef CHAR
   printf("%c ",e);
 #endif
 #ifdef INT
   printf("%d ",e);
 #endif
   return OK;
 }

 void main()
 {
   int i;
   BiTree T,p,c;
   TElemType e1,e2;
   InitBiTree(&T);
   printf("构造空二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
   e1=Root(T);
   if(e1!=Nil)
 #ifdef CHAR
     printf("二叉树的根为: %c\n",e1);
 #endif
 #ifdef INT
     printf("二叉树的根为: %d\n",e1);
 #endif
   else
     printf("树空，无根\n");
 #ifdef CHAR
   printf("请先序输入二叉树(如:ab三个空格表示a为根结点,b为左子树的二叉树)\n");
 #endif
 #ifdef INT
   printf("请先序输入二叉树(如:1 2 0 0 0表示1为根结点,2为左子树的二叉树)\n");
 #endif
   CreateBiTree(&T);
   printf("建立二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",BiTreeEmpty(T),BiTreeDepth(T));
   e1=Root(T);
   if(e1!=Nil)
 #ifdef CHAR
     printf("二叉树的根为: %c\n",e1);
 #endif
 #ifdef INT
     printf("二叉树的根为: %d\n",e1);
 #endif
   else
     printf("树空，无根\n");
   printf("中序递归遍历二叉树:\n");
   InOrderTraverse(T,visitT);
   printf("\n中序非递归遍历二叉树:\n");
   InOrderTraverse1(T,visitT);
   printf("中序非递归遍历二叉树(另一种方法):\n");
   InOrderTraverse2(T,visitT);
   printf("后序递归遍历二叉树:\n");
   PostOrderTraverse(T,visitT);
   printf("\n层序遍历二叉树:\n");
   LevelOrderTraverse(T,visitT);
   printf("请输入一个结点的值: ");
 #ifdef CHAR
   scanf("%*c%c",&e1);
 #endif
 #ifdef INT
   scanf("%d",&e1);
 #endif
   p=Point(T,e1); /* p为e1的指针 */
 #ifdef CHAR
   printf("结点的值为%c\n",Value(p));
 #endif
 #ifdef INT
   printf("结点的值为%d\n",Value(p));
 #endif
   printf("欲改变此结点的值，请输入新值: ");
 #ifdef CHAR
   scanf("%*c%c%*c",&e2);
 #endif
 #ifdef INT
   scanf("%d",&e2);
 #endif
   Assign(p,e2);
   printf("层序遍历二叉树:\n");
   LevelOrderTraverse(T,visitT);
   e1=Parent(T,e2);
   if(e1!=Nil)
 #ifdef CHAR
     printf("%c的双亲是%c\n",e2,e1);
 #endif
 #ifdef INT
     printf("%d的双亲是%d\n",e2,e1);
 #endif
   else
 #ifdef CHAR
     printf("%c没有双亲\n",e2);
 #endif
 #ifdef INT
     printf("%d没有双亲\n",e2);
 #endif
   e1=LeftChild(T,e2);
   if(e1!=Nil)
 #ifdef CHAR
     printf("%c的左孩子是%c\n",e2,e1);
 #endif
 #ifdef INT
     printf("%d的左孩子是%d\n",e2,e1);
 #endif
   else
 #ifdef CHAR
     printf("%c没有左孩子\n",e2);
 #endif
 #ifdef INT
     printf("%d没有左孩子\n",e2);
 #endif
   e1=RightChild(T,e2);
   if(e1!=Nil)
 #ifdef CHAR
     printf("%c的右孩子是%c\n",e2,e1);
 #endif
 #ifdef INT
     printf("%d的右孩子是%d\n",e2,e1);
 #endif
   else
 #ifdef CHAR
     printf("%c没有右孩子\n",e2);
 #endif
 #ifdef INT
     printf("%d没有右孩子\n",e2);
 #endif
   e1=LeftSibling(T,e2);
   if(e1!=Nil)
 #ifdef CHAR
     printf("%c的左兄弟是%c\n",e2,e1);
 #endif
 #ifdef INT
     printf("%d的左兄弟是%d\n",e2,e1);
 #endif
   else
 #ifdef CHAR
     printf("%c没有左兄弟\n",e2);
 #endif
 #ifdef INT
     printf("%d没有左兄弟\n",e2);
 #endif
   e1=RightSibling(T,e2);
   if(e1!=Nil)
 #ifdef CHAR
     printf("%c的右兄弟是%c\n",e2,e1);
 #endif
 #ifdef INT
     printf("%d的右兄弟是%d\n",e2,e1);
 #endif
   else
 #ifdef CHAR
     printf("%c没有右兄弟\n",e2);
 #endif
 #ifdef INT
     printf("%d没有右兄弟\n",e2);
 #endif
   InitBiTree(&c);
   printf("构造一个右子树为空的二叉树c:\n");
 #ifdef CHAR
   printf("请先序输入二叉树(如:ab三个空格表示a为根结点,b为左子树的二叉树)\n");
 #endif
 #ifdef INT
   printf("请先序输入二叉树(如:1 2 0 0 0表示1为根结点,2为左子树的二叉树)\n");
 #endif
   CreateBiTree(&c);
   printf("先序递归遍历二叉树c:\n");
   PreOrderTraverse(c,visitT);
   printf("\n树c插到树T中,请输入树T中树c的双亲结点 c为左(0)或右(1)子树: ");
 #ifdef CHAR
   scanf("%*c%c%d",&e1,&i);
 #endif
 #ifdef INT
   scanf("%d%d",&e1,&i);
 #endif
   p=Point(T,e1); /* p是T中树c的双亲结点指针 */
   InsertChild(p,i,c);
   printf("先序递归遍历二叉树:\n");
   PreOrderTraverse(T,visitT);
   printf("\n删除子树,请输入待删除子树的双亲结点  左(0)或右(1)子树: ");
 #ifdef CHAR
   scanf("%*c%c%d",&e1,&i);
 #endif
 #ifdef INT
   scanf("%d%d",&e1,&i);
 #endif
   p=Point(T,e1);
   DeleteChild(p,i);
   printf("先序递归遍历二叉树:\n");
   PreOrderTraverse(T,visitT);
   printf("\n");
   DestroyBiTree(&T);
 }
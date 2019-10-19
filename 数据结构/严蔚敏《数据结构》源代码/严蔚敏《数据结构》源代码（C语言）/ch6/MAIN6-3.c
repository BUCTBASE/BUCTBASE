 /* main6-3.c 检验bo6-3.c的主程序 */
 #define CHAR 1 /* 字符型 */
 /*#define CHAR 0 /* 整型(二者选一) */
 #if CHAR
   typedef char TElemType;
   TElemType Nil=' '; /* 字符型以空格符为空 */
 #else
   typedef int TElemType;
   TElemType Nil=0; /* 整型以0为空 */
 #endif
 #include"c1.h"
 #include"c6-3.h"
 #include"bo6-3.c"

 Status vi(TElemType c)
 {
 #if CHAR
   printf("%c ",c);
 #else
   printf("%d ",c);
 #endif
   return OK;
 }

 void main()
 {
   BiThrTree H,T;
 #if CHAR
   printf("请按先序输入二叉树(如:ab三个空格表示a为根结点,b为左子树的二叉树)\n");
 #else
   printf("请按先序输入二叉树(如:1 2 0 0 0表示1为根结点,2为左子树的二叉树)\n");
 #endif
   CreateBiThrTree(&T); /* 按先序产生二叉树 */
   InOrderThreading(&H,T); /* 中序遍历，并中序线索化二叉树 */
   printf("中序遍历(输出)二叉线索树:\n");
   InOrderTraverse_Thr(H,vi); /* 中序遍历(输出)二叉线索树 */
   printf("\n");
 }

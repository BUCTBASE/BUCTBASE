 /* c6-6.h 二叉树的三叉链表存储表示 */
 typedef struct BiTPNode
 {
   TElemType data;
   struct BiTPNode *parent,*lchild,*rchild; /* 双亲、左右孩子指针 */
 }BiTPNode,*BiPTree;

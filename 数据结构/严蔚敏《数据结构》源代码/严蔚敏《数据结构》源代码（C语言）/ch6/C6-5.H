 /* c6-5.h 树的二叉链表(孩子－兄弟)存储表示 */
 typedef struct CSNode
 {
   TElemType data;
   struct CSNode *firstchild,*nextsibling;
 }CSNode,*CSTree;

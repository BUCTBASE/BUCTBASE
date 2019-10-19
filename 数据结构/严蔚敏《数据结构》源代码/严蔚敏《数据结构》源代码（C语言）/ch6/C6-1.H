 /* c6-1.h 二叉树的顺序存储表示 */
 #define MAX_TREE_SIZE 100 /* 二叉树的最大结点数 */
 typedef TElemType SqBiTree[MAX_TREE_SIZE]; /* 0号单元存储根结点 */

 typedef struct
 {
   int level,order; /* 结点的层,本层序号(按满二叉树计算) */
 }position;

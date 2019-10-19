 /* c9-3.h B树的结点类型 */
 typedef struct
 {
   KeyType key; /* 关键字 */
   Others others; /* 其它部分(由主程定义) */
 }Record; /* 记录类型 */

 typedef struct BTNode
 {
   int keynum; /* 结点中关键字个数，即结点的大小 */
   struct BTNode *parent; /* 指向双亲结点 */
   struct Node /* 结点向量类型 */
   {
     KeyType key; /* 关键字向量 */
     struct BTNode *ptr; /* 子树指针向量 */
     Record *recptr; /* 记录指针向量 */
   }node[m+1]; /* key,recptr的0号单元未用 */
 }BTNode,*BTree; /* B树结点和B树的类型 */

 typedef struct
 {
   BTNode *pt; /* 指向找到的结点 */
   int i; /* 1..m，在结点中的关键字序号 */
   int tag; /* 1:查找成功，O:查找失败 */
 }Result; /* B树的查找结果类型 */

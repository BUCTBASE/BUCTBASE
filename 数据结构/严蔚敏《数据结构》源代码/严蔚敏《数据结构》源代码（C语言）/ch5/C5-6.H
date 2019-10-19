 /* c5-6.h 广义表的扩展线性链表存储表示 */
 typedef enum{ATOM,LIST}ElemTag; /* ATOM==0:原子,LIST==1:子表 */
 typedef struct GLNode
 {
   ElemTag tag; /* 公共部分,用于区分原子结点和表结点 */
   union /* 原子结点和表结点的联合部分 */
   {
     AtomType atom; /* 原子结点的值域 */
     struct GLNode *hp; /* 表结点的表头指针 */
   }a;
   struct GLNode *tp; /* 相当于线性链表的next,指向下一个元素结点 */
 }*GList,GLNode; /* 广义表类型GList是一种扩展的线性链表 */

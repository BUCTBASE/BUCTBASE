 /* c2-4.h 线性表的双向链表存储结构 */
 typedef struct DuLNode
 {
   ElemType data;
   struct DuLNode *prior,*next;
 }DuLNode,*DuLinkList;

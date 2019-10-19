 /* c8-3.h 加标志域的广义表的头尾链表存储表示(由c5-5.h改) */
 typedef enum{ATOM,LIST}ElemTag; /* ATOM==0:原子,LIST==1:子表 */
 typedef struct GLNode
 {
   int mark; /* 加此域，其余同c5-5.h */
   ElemTag tag; /* 公共部分,用于区分原子结点和表结点 */
   union /* 原子结点和表结点的联合部分 */
   {
     AtomType atom; /* atom是原子结点的值域,AtomType由用户定义 */
     struct
     {
       struct GLNode *hp,*tp;
     }ptr; /* ptr是表结点的指针域,prt.hp和ptr.tp分别指向表头和表尾 */
   }a;
 }*GList,GLNode; /* 广义表类型 */

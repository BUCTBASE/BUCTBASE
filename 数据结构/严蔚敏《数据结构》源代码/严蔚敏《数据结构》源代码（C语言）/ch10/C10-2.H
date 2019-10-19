 /* c10-2.h 静态链表类型 */
 #define SIZE 100 /* 静态链表容量 */
 typedef int KeyType; /* 定义关键字类型为整型 */

 typedef struct
 {
   KeyType key; /* 关键字项 */
   InfoType otherinfo; /* 其它数据项，具体类型在主程中定义 */
 }RedType; /* 记录类型 */

 typedef struct
 {
   RedType rc; /* 记录项 */
   int next; /* 指针项 */
 }SLNode; /* 表结点类型 */

 typedef struct
 {
   SLNode r[SIZE]; /* 0号单元为表头结点 */
   int length; /* 链表当前长度 */
 }SLinkListType; /* 静态链表类型 */

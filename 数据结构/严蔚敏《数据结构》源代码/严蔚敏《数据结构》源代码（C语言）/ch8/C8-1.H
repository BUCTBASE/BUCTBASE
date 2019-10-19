 /* c8-1.h 边界标识法可利用空间表的结点结构 */
 /* head和foot分别是可利用空间表中结点的第一个字和最后一个字(WORD) */

 typedef struct WORD /* 字类型 */
 {
   union
   {
     struct WORD *llink; /* 头部域，指向前驱结点 */
     struct WORD *uplink; /* 底部域，指向本结点头部 */
   }a;
   int tag; /* 块标志，0：空闲，1：占用，头部和尾部均有 */
   int size; /* 头部域，块大小 */
   struct WORD *rlink; /* 头部域，指向后继结点 */
 }WORD,head,foot,*Space; /* *Space：可利用空间指针类型 */

 #define FootLoc(p) (p)+(p)->size-1 /* 带参数的宏定义，指向p所指结点的底部(最后一个字) */
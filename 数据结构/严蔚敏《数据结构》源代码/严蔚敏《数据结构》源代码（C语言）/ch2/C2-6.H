 /* c2-6.h 抽象数据类型Polynomial的实现 */
 typedef struct /* 项的表示,多项式的项作为LinkList的数据元素 */
 {
   float coef; /* 系数 */
   int expn; /* 指数 */
 }term,ElemType;
 /* 两个类型名:term用于本ADT,ElemType为LinkList的数据对象名 */
 /* c6-7.h 赫夫曼树和赫夫曼编码的存储表示 */
 typedef struct
 {
   unsigned int weight;
   unsigned int parent,lchild,rchild;
 }HTNode,*HuffmanTree; /* 动态分配数组存储赫夫曼树 */
 typedef char **HuffmanCode; /* 动态分配数组存储赫夫曼编码表 */

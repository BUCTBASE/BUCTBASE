 /* c4-3.h 串的块链存储表示 */
 #define CHUNKSIZE 4 /* 可由用户定义的块大小 */
 typedef struct Chunk
 {
   char ch[CHUNKSIZE];
   struct Chunk *next;
 }Chunk;
 typedef struct
 {
   Chunk *head,*tail; /* 串的头和尾指针 */
   int curlen; /* 串的当前长度 */
 }LString;
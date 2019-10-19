 /* c4-1.h 串的定长顺序存储表示 */
 #define MAXSTRLEN 40 /* 用户可在255以内定义最大串长（1个字节） */
 typedef char SString[MAXSTRLEN+1]; /* 0号单元存放串的长度 */

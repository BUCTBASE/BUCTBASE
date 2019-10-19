 /* bo9-7.c 哈希函数的基本操作 */
 Status InitHashTable(HashTable *H)
 { /* 操作结果: 构造一个空的哈希表 */
   int i;
   (*H).count=0; /* 当前元素个数为0 */
   (*H).sizeindex=0; /* 初始存储容量为hashsize[0] */
   m=hashsize[0];
   (*H).elem=(ElemType*)malloc(m*sizeof(ElemType));
   if(!(*H).elem)
     exit(OVERFLOW); /* 存储分配失败 */
   for(i=0;i<m;i++)
     (*H).elem[i].key=NULLKEY; /* 未填记录的标志 */
   return OK;
 }

 void DestroyHashTable(HashTable *H)
 { /* 初始条件: 哈希表H存在。操作结果: 销毁哈希表H */
   free((*H).elem);
   (*H).elem=NULL;
   (*H).count=0;
   (*H).sizeindex=0;
 }

 unsigned Hash(KeyType K)
 { /* 一个简单的哈希函数(m为表长，全局变量) */
   return K%m;
 }

 void collision(int *p,int d) /* 线性探测再散列 */
 { /* 开放定址法处理冲突 */
   *p=(*p+d)%m;
 }

 Status SearchHash(HashTable H,KeyType K,int *p,int *c)
 { /* 在开放定址哈希表H中查找关键码为K的元素,若查找成功,以p指示待查数据 */
   /* 元素在表中位置,并返回SUCCESS;否则,以p指示插入位置,并返回UNSUCCESS */
   /* c用以计冲突次数，其初值置零，供建表插入时参考。算法9.17 */
   *p=Hash(K); /* 求得哈希地址 */
   while(H.elem[*p].key!=NULLKEY&&!EQ(K,H.elem[*p].key))
   { /* 该位置中填有记录．并且关键字不相等 */
     (*c)++;
     if(*c<m)
       collision(p,*c); /* 求得下一探查地址p */
     else
       break;
   }
   if EQ(K,H.elem[*p].key)
     return SUCCESS; /* 查找成功，p返回待查数据元素位置 */
   else
     return UNSUCCESS; /* 查找不成功(H.elem[p].key==NULLKEY)，p返回的是插入位置 */
 }

 Status InsertHash(HashTable *,ElemType); /* 对函数的声明 */
 void RecreateHashTable(HashTable *H) /* 重建哈希表 */
 { /* 重建哈希表 */
   int i,count=(*H).count;
   ElemType *p,*elem=(ElemType*)malloc(count*sizeof(ElemType));
   p=elem;
   printf("重建哈希表\n");
   for(i=0;i<m;i++) /* 保存原有的数据到elem中 */
     if(((*H).elem+i)->key!=NULLKEY) /* 该单元有数据 */
       *p++=*((*H).elem+i);
   (*H).count=0;
   (*H).sizeindex++; /* 增大存储容量 */
   m=hashsize[(*H).sizeindex];
   p=(ElemType*)realloc((*H).elem,m*sizeof(ElemType));
   if(!p)
     exit(OVERFLOW); /* 存储分配失败 */
   (*H).elem=p;
   for(i=0;i<m;i++)
     (*H).elem[i].key=NULLKEY; /* 未填记录的标志(初始化) */
   for(p=elem;p<elem+count;p++) /* 将原有的数据按照新的表长插入到重建的哈希表中 */
     InsertHash(H,*p);
 }

 Status InsertHash(HashTable *H,ElemType e)
 { /* 查找不成功时插入数据元素e到开放定址哈希表H中，并返回OK； */
   /* 若冲突次数过大，则重建哈希表。算法9.18 */
   int c,p;
   c=0;
   if(SearchHash(*H,e.key,&p,&c)) /* 表中已有与e有相同关键字的元素 */
     return DUPLICATE;
   else if(c<hashsize[(*H).sizeindex]/2) /* 冲突次数c未达到上限,(c的阀值可调) */
   { /* 插入e */
     (*H).elem[p]=e;
     ++(*H).count;
     return OK;
   }
   else
     RecreateHashTable(H); /* 重建哈希表 */
   return ERROR;
 }

 void TraverseHash(HashTable H,void(*Vi)(int,ElemType))
 { /* 按哈希地址的顺序遍历哈希表 */
   int i;
   printf("哈希地址0～%d\n",m-1);
   for(i=0;i<m;i++)
     if(H.elem[i].key!=NULLKEY) /* 有数据 */
       Vi(i,H.elem[i]);
 }

 Status Find(HashTable H,KeyType K,int *p)
 { /* 在开放定址哈希表H中查找关键码为K的元素,若查找成功,以p指示待查数据 */
   /* 元素在表中位置,并返回SUCCESS;否则,返回UNSUCCESS */
   int c=0;
   *p=Hash(K); /* 求得哈希地址 */
   while(H.elem[*p].key!=NULLKEY&&!EQ(K,H.elem[*p].key))
   { /* 该位置中填有记录．并且关键字不相等 */
     c++;
     if(c<m)
       collision(p,c); /* 求得下一探查地址p */
     else
       return UNSUCCESS; /* 查找不成功(H.elem[p].key==NULLKEY) */
   }
   if EQ(K,H.elem[*p].key)
     return SUCCESS; /* 查找成功，p返回待查数据元素位置 */
   else
     return UNSUCCESS; /* 查找不成功(H.elem[p].key==NULLKEY) */
 }

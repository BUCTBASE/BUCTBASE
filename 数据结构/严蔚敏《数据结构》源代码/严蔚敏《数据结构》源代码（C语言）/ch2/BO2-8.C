 /* bo2-8.c 顺序表示的线性表(存储结构由c2-1.h定义)的扩展操作(10个) */
 #include"bo2-1.c"
 void InsertAscend(SqList *L,ElemType e)
 { /* 初始条件：按非降序排列的顺序线性表L已存在 */
   /* 操作结果：在L中按非降序插入新的数据元素e，L的长度加1 */
   ElemType *newbase,*p;
   int k;
   if((*L).length>=(*L).listsize) /* 当前存储空间已满,增加分配 */
   {
     newbase=(ElemType *)realloc((*L).elem,((*L).listsize+LISTINCREMENT)*sizeof(ElemType));
     if(!newbase)
       exit(OVERFLOW); /* 存储分配失败 */
     (*L).elem=newbase; /* 新基址 */
     (*L).listsize+=LISTINCREMENT; /* 增加存储容量 */
   }
   p=(*L).elem;
   for(k=1;k<=(*L).length;k++)
     if(e>*p)
       p++;
     else
       break;
   ListInsert(L,k,e); /* 函数在bo2-1.c中 */
 }

 void InsertDescend(SqList *L,ElemType e)
 { /* 初始条件：按非升序排列的顺序线性表L已存在 */
   /* 操作结果：在L中按非升序插入新的数据元素e，L的长度加1 */
   ElemType *newbase,*p;
   int k;
   if((*L).length>=(*L).listsize) /* 当前存储空间已满,增加分配 */
   {
     newbase=(ElemType *)realloc((*L).elem,((*L).listsize+LISTINCREMENT)*sizeof(ElemType));
     if(!newbase)
       exit(OVERFLOW); /* 存储分配失败 */
     (*L).elem=newbase; /* 新基址 */
     (*L).listsize+=LISTINCREMENT; /* 增加存储容量 */
   }
   p=(*L).elem;
   for(k=1;k<=(*L).length;k++)
     if(e<*p)
       p++;
     else
       break;
   ListInsert(L,k,e); /* 函数在bo2-1.c中 */
 }

 Status HeadInsert(SqList *L,ElemType e)
 { /* 初始条件：顺序线性表L已存在。操作结果：在L的头部插入新的数据元素e，L的长度加1 */
   ElemType *p,*q,*newbase;
   if((*L).length>=(*L).listsize)
   {
     newbase=(ElemType *)realloc((*L).elem,((*L).listsize+LISTINCREMENT)*sizeof(ElemType));
     if(!newbase)
       exit(OVERFLOW);
     (*L).elem=newbase;
     (*L).listsize+=LISTINCREMENT;
   }
   q=(*L).elem;
   for(p=(*L).elem+(*L).length-1;p>=q;--p)
     *(p+1)=*p;
   *q=e;
   (*L).length++;
   return OK;
 }

 Status EndInsert(SqList *L,ElemType e)
 { /* 初始条件：顺序线性表L已存在。操作结果：在L的尾部插入新的数据元素e，L的长度加1 */
   ElemType *q,*newbase;
   if((*L).length>=(*L).listsize) /* 当前存储空间已满,增加分配 */
   {
     newbase=(ElemType *)realloc((*L).elem,((*L).listsize+LISTINCREMENT)*sizeof(ElemType));
     if(!newbase)
       exit(OVERFLOW); /* 存储分配失败 */
     (*L).elem=newbase; /* 新基址 */
     (*L).listsize+=LISTINCREMENT; /* 增加存储容量 */
   }
   q=(*L).elem+(*L).length; /* q为插入位置 */
   *q=e;
   (*L).length++;
   return OK;
 }

 Status DeleteFirst(SqList *L,ElemType *e)
 { /* 初始条件：顺序线性表L已存在，且有不少于1个元素 */
   /* 操作结果：删除L的第一个数据元素，并由e返回其值，L的长度减1 */
   ElemType *p,*q;
   if(ListEmpty(*L)) /* 空表无法删除 */
     return ERROR;
   p=(*L).elem; /* p指向第一个元素 */
   *e=*p;
   q=(*L).elem+(*L).length-1; /* q指向最后一个元素 */
   for(++p;p<=q;++p)
     *(p-1)=*p; /* 从第2个元素起，所有元素向前移动一个位置 */
   (*L).length--; /* 当前长度减1 */
   return OK;
 }

 Status DeleteTail(SqList *L,ElemType *e)
 { /* 初始条件：顺序线性表L已存在，且有不少于1个元素 */
   /* 操作结果：删除L的最后一个数据元素，并用e返回其值，L的长度减1 */
   ElemType *p;
   if(!(*L).length) /* 空表 */
     return ERROR;
   p=(*L).elem+(*L).length-1; /* 最后一个数据元素的位置 */
   *e=*p; /* 被删除元素的值赋给e */
   (*L).length--; /* 表长减1 */
   return OK;
 }

 Status DeleteElem(SqList *L,ElemType e)
 { /* 删除表中值为e的元素，并返回TRUE；如无此元素，则返回FALSE */
   int i=0,j;
   while(i<(*L).length&&e!=*((*L).elem+i))
     i++;
   if(i==(*L).length) /* 没找到 */
     return FALSE;
   else
   {
     for(j=i;j<(*L).length;j++)
       *((*L).elem+j)=*((*L).elem+j+1); /* 后面的元素依次前移 */
     (*L).length--; /* 当前长度减1 */
     return TRUE;
   }
 }

 Status ReplaceElem(SqList L,int i,ElemType e)
 { /* 用e取代表L中第i个元素的值 */
   if(i<1||i>L.length) /* i值不合法 */
     exit(ERROR);
   *(L.elem+i-1)=e;
   return OK;
 }

 Status CreatAscend(SqList *L,int n)
 { /* 按非降序建立n个元素的线性表 */
   int i,j;
   ElemType e;
   InitList(L);
   printf("请输入%d个元素:\n",n);
   scanf("%d",&e);
   ListInsert(L,1,e); /* 在空表中插入第1个元素 */
   for(i=1;i<n;i++)
   {
     scanf("%d",&e);
     for(j=0;j<(*L).length;j++)
       if(e<=*((*L).elem+j))
         break;
     ListInsert(L,j+1,e); /* 插于表中 */
   }
   return TRUE;
 }

 Status CreatDescend(SqList *L,int n)
 { /* 按非升序建立n个元素的线性表 */
   int i,j;
   ElemType e;
   InitList(L);
   printf("请输入%d个元素:\n",n);
   scanf("%d",&e);
   ListInsert(L,1,e); /* 在空表中插入第1个元素 */
   for(i=1;i<n;i++)
   {
     scanf("%d",&e);
     for(j=0;j<(*L).length;j++)
       if(e>=*((*L).elem+j))
         break;
     ListInsert(L,j+1,e); /* 插于表中 */
   }
   return TRUE;
 }


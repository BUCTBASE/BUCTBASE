 /* algo2-6.c 利用单链表结构处理教科书图2.1(学生健康登记表) */
 #include"c1.h"
 #define NAMELEN 8 /* 姓名最大长度 */
 #define CLASSLEN 4 /* 班级名最大长度 */
 struct stud /* 记录的结构 */
 {
   char name[NAMELEN+1];
   long num;
   char sex;
   int age;
   char Class[CLASSLEN+1];
   int health;
 };
 typedef struct stud ElemType; /* 链表结点元素类型为结构体 */
 #include"c2-2.h"
 char sta[3][9]={"健康  ","一般  ","神经衰弱"}; /* 健康状况(3类) */
 FILE *fp;

 Status InitList(LinkList *L) /* 拷自bo2-2.c */
 { /* 操作结果：构造一个空的线性表L */
   *L=(LinkList)malloc(sizeof(struct LNode)); /* 产生头结点,并使L指向此头结点 */
   if(!*L) /* 存储分配失败 */
     exit(OVERFLOW);
   (*L)->next=NULL; /* 指针域为空 */
   return OK;
 }

 Status ListTraverse(LinkList L,void(*vi)(ElemType)) /* 拷自bo2-2.c */
 { /* 初始条件：线性表L已存在 */
   /* 操作结果:依次对L的每个数据元素调用函数vi()。一旦vi()失败,则操作失败 */
   LinkList p=L->next;
   while(p)
   {
     vi(p->data);
     p=p->next;
   }
   printf("\n");
   return OK;
 }

 void InsertAscend(LinkList L,ElemType e) /* 此函数是由bo2-9.c中的同名函数改写 */
 { /* 按学号非降序插入 */
   LinkList q=L,p=L->next;
   while(p&&e.num>p->data.num)
   {
     q=p;
     p=p->next;
   }
   q->next=(LinkList)malloc(sizeof(struct LNode)); /* 插在q后 */
   q->next->data=e;
   q->next->next=p;
 }

 void Print(struct stud e)
 { /* 显示记录e的内容 */
   printf("%-8s %6ld",e.name,e.num);
   if(e.sex=='m')
     printf(" 男");
   else
     printf(" 女");
   printf("%5d  %-4s",e.age,e.Class);
   printf("%9s\n",sta[e.health]);
 }

 void ReadIn(struct stud *e)
 { /* 由键盘输入结点信息 */
   printf("请输入姓名(<=%d个字符): ",NAMELEN);
   scanf("%s",e->name);
   printf("请输入学号: ");
   scanf("%ld",&e->num);
   printf("请输入性别(m:男 f:女): ");
   scanf("%*c%c",&e->sex);
   printf("请输入年龄: ");
   scanf("%d",&e->age);
   printf("请输入班级(<=%d个字符): ",CLASSLEN);
   scanf("%s",e->Class);
   printf("请输入健康状况(0:%s 1:%s 2:%s):",sta[0],sta[1],sta[2]);
   scanf("%d",&e->health);
 }

 void WriteToFile(struct stud e)
 { /* 将结点信息写入fp指定的文件 */
   fwrite(&e,sizeof(struct stud),1,fp);
 }

 Status ReadFromFile(struct stud *e)
 { /* 由fp指定的文件读取结点信息到e */
   int i;
   i=fread(e,sizeof(struct stud),1,fp);
   if(i==1) /* 读取文件成功 */
     return OK;
   else
     return ERROR;
 }

 Status FindFromNum(LinkList L,long num,LinkList *p,LinkList *q)
 { /* 查找表中学号为num的结点,如找到,q指向此结点,p指向q的前驱, */
   /* 并返回TRUE;如无此元素,则返回FALSE */
   *p=L;
   while(*p)
   {
     *q=(*p)->next;
     if(*q&&(*q)->data.num>num) /* 因为是按学号非降序排列 */
       break;
     if(*q&&(*q)->data.num==num) /* 找到该学号 */
       return TRUE;
     *p=*q;
   }
   return FALSE;
 }

 Status FindFromName(LinkList L,char name[],LinkList *p,LinkList *q)
 { /* 查找表中姓名为name的结点,如找到,q指向此结点,p指向q的前驱, */
   /* 并返回TRUE;如无此元素,则返回FALSE */
   *p=L;
   while(*p)
   {
     *q=(*p)->next;
     if(*q&&!strcmp((*q)->data.name,name)) /* 找到该姓名 */
       return TRUE;
     *p=*q;
   }
   return FALSE;
 }

 Status DeleteElemNum(LinkList L,long num)
 { /* 删除表中学号为num的元素，并返回TRUE；如无此元素，则返回FALSE */
   LinkList p,q;
   if(FindFromNum(L,num,&p,&q)) /* 找到此结点,且q指向其,p指向其前驱 */
   {
     p->next=q->next;
     free(q);
     return TRUE;
   }
   return FALSE;
 }

 Status DeleteElemName(LinkList L,char name[])
 { /* 删除表中姓名为name的元素，并返回TRUE；如无此元素，则返回FALSE */
   LinkList p,q;
   if(FindFromName(L,name,&p,&q)) /* 找到此结点,且q指向其,p指向其前驱 */
   {
     p->next=q->next;
     free(q);
     return TRUE;
   }
   return FALSE;
 }

 void Modify(ElemType *e)
 { /* 修改结点内容 */
   char s[80];
   Print(*e); /* 显示原内容 */
   printf("请输入待修改项的内容，不修改的项按回车键保持原值:\n");
   printf("请输入姓名(<=%d个字符): ",NAMELEN);
   gets(s);
   if(strlen(s))
     strcpy(e->name,s);
   printf("请输入学号: ");
   gets(s);
   if(strlen(s))
     e->num=atol(s);
   printf("请输入性别(m:男 f:女): ");
   gets(s);
   if(strlen(s))
     e->sex=s[0];
   printf("请输入年龄: ");
   gets(s);
   if(strlen(s))
     e->age=atoi(s);
   printf("请输入班级(<=%d个字符): ",CLASSLEN);
   gets(s);
   if(strlen(s))
     strcpy(e->Class,s);
   printf("请输入健康状况(0:%s 1:%s 2:%s):",sta[0],sta[1],sta[2]);
   gets(s);
   if(strlen(s))
     e->health=atoi(s); /* 修改完毕 */
 }

 #define N 4 /* student记录的个数 */
 void main()
 {
   struct stud student[N]={{"王小林",790631,'m',18,"计91",0},
                           {"陈红",790632,'f',20,"计91",1},
                           {"刘建平",790633,'m',21,"计91",0},
                           {"张立立",790634,'m',17,"计91",2}}; /* 表的初始记录 */
   int i,j,flag=1;
   long num;
   char filename[13],name[NAMELEN+1];
   ElemType e;
   LinkList T,p,q;
   InitList(&T); /* 初始化链表 */
   while(flag)
   {
     printf("1:将结构体数组student中的记录按学号非降序插入链表\n");
     printf("2:将文件中的记录按学号非降序插入链表\n");
     printf("3:键盘输入新记录，并将其按学号非降序插入链表\n");
     printf("4:删除链表中第一个有给定学号的记录\n");
     printf("5:删除链表中第一个有给定姓名的记录\n");
     printf("6:修改链表中第一个有给定学号的记录\n");
     printf("7:修改链表中第一个有给定姓名的记录\n");
     printf("8:查找链表中第一个有给定学号的记录\n");
     printf("9:查找链表中第一个有给定姓名的记录\n");
     printf("10:显示所有记录 11:将链表中的所有记录存入文件 12:结束\n");
     printf("请选择操作命令: ");
     scanf("%d",&i);
     switch(i)
     {
       case 1: for(j=0;j<N;j++)
                 InsertAscend(T,student[j]);
               break;
       case 2: printf("请输入文件名: ");
               scanf("%s",filename);
               if((fp=fopen(filename,"rb"))==NULL)
                 printf("打开文件失败!\n");
               else
               {
                 while(ReadFromFile(&e))
                   InsertAscend(T,e);
                 fclose(fp);
               }
               break;
       case 3: ReadIn(&e);
               InsertAscend(T,e);
               break;
       case 4: printf("请输入待删除记录的学号: ");
               scanf("%ld",&num);
               if(!DeleteElemNum(T,num))
                 printf("没有学号为%ld的记录\n",num);
               break;
       case 5: printf("请输入待删除记录的姓名: ");
               scanf("%s",name);
               if(!DeleteElemName(T,name))
                 printf("没有姓名为%s的记录\n",name);
               break;
       case 6: printf("请输入待修改记录的学号: ");
               scanf("%ld%*c",&num); /* %*c吃掉回车符 */
               if(!FindFromNum(T,num,&p,&q))
                 printf("没有学号为%ld的记录\n",num);
               else
               {
                 Modify(&q->data);
                 if(q->data.num!=num) /* 学号被修改 */
                 {
                   p->next=q->next; /* 把q所指的结点从L中删除 */
                   InsertAscend(T,q->data); /* 把元素插入L */
                   free(q); /* 删除q */
                 }
               }
               break;
       case 7: printf("请输入待修改记录的姓名: ");
               scanf("%s%*c",name); /* %*c吃掉回车符 */
               if(!FindFromName(T,name,&p,&q))
                 printf("没有姓名为%s的记录\n",name);
               else
               {
                 num=q->data.num; /* 学号存入num */
                 Modify(&q->data);
                 if(q->data.num!=num) /* 学号被修改 */
                 {
                   p->next=q->next; /* 把q所指的结点从L中删除 */
                   InsertAscend(T,q->data); /* 把元素插入L */
                   free(q); /* 删除q */
                 }
               }
               break;
       case 8: printf("请输入待查找记录的学号: ");
               scanf("%ld",&num);
               if(!FindFromNum(T,num,&p,&q))
                 printf("没有学号为%ld的记录\n",num);
               else
                 Print(q->data);
               break;
       case 9: printf("请输入待查找记录的姓名: ");
               scanf("%s",name);
               if(!FindFromName(T,name,&p,&q))
                 printf("没有姓名为%s的记录\n",name);
               else
               Print(q->data);
               break;
       case 10:printf("  姓名    学号 性别 年龄 班级 健康状况\n");
               ListTraverse(T,Print);
               break;
       case 11:printf("请输入文件名: ");
               scanf("%s",filename);
               if((fp=fopen(filename,"wb"))==NULL)
                 printf("打开文件失败!\n");
               else
                 ListTraverse(T,WriteToFile);
               fclose(fp);
               break;
       case 12:flag=0;
     }
   }
 }


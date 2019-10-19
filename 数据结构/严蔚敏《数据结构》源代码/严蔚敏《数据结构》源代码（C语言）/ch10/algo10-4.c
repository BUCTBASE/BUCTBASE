 /* algo10-4.c 调用起泡排序(在教科书1.4.3 算法效率的度量中)的程序 */
 #include"c1.h"
 #define N 8
 void bubble_sort(int a[],int n)
 { /* 将a中整数序列重新排列成自小至大有序的整数序列(起泡排序) */
   int i,j,t;
   Status change;
   for(i=n-1,change=TRUE;i>1&&change;--i)
   {
     change=FALSE;
     for(j=0;j<i;++j)
       if(a[j]>a[j+1])
       {
         t=a[j];
         a[j]=a[j+1];
         a[j+1]=t;
         change=TRUE;
       }
   }
 }

 void print(int r[],int n)
 {
   int i;
   for(i=0;i<n;i++)
     printf("%d ",r[i]);
   printf("\n");
 }

 void main()
 {
   int d[N]={49,38,65,97,76,13,27,49};
   printf("排序前:\n");
   print(d,N);
   bubble_sort(d,N);
   printf("排序后:\n");
   print(d,N);
 }

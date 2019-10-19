 /* algo3-8.c 用递归调用求Ackerman(m,n)的值 */
 #include<stdio.h>
 int ack(int m,int n)
 {
   int z;
   if(m==0)
     z=n+1;
   else if(n==0)
     z=ack(m-1,1);
   else
     z=ack(m-1,ack(m,n-1));
   return z;
 }

 void main()
 {
   int m,n;
   printf("Please input m,n:");
   scanf("%d,%d",&m,&n);
   printf("Ack(%d,%d)=%d\n",m,n,ack(m,n));
 }

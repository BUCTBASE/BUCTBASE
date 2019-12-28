#include<stdio.h>

void main()
{
   int i,j,k,n;
   for(n=100;n<=999;n++)
   {
	   i=n/100;
	   j=n/10%10;
	   k=n%10;
	   if(n==(i*i*i+j*j*j+k*k*k))
		   printf("%d\n",n);
   }
}
void popo(int a[], int n)
{
	int i,j,t;
	for(j=1;j<n;j++)
	   for(i=0;i<n-j;i++)
		   if(a[i]>a[i+1])
		   {
			   t=a[i];
			   a[i]=a[i+1];
			   a[i+1]=t;
		   }
}
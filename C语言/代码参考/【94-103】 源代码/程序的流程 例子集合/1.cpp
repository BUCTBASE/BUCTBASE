# include <stdio.h>

int main(void)
{
	int  a=4, b=3, c=5, t=0;
	if(a<b) 
	{
		t=a;  
		a=b;  
		b=t;
	}
	
	if(a<c)
	{
		t=a;
		a=c;
		c=t;
	}
	printf("%d,  %d,  %d   %d\n", a, b, c, t);

	return 0;
}

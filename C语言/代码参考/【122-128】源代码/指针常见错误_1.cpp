# include <stdio.h>

int main(void)
{
	int * p;
	static int i = 5;

	*p = i;
	printf("%d\n", *p);

	return 0;
}
# include <stdio.h>

void f(int * p)
{
	*p = 10; // i = 10;
}

int main(void)
{
	int i = 5;

	f(&i);
	printf("i = %d\n", i);

	return 0;
}
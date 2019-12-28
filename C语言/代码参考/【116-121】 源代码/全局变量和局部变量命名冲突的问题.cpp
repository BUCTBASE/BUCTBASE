# include <stdio.h>

int i = 99;

void f(int i)
{
	printf("i = %d\n", i);
}

int main(void)
{
	f(8);

	return 0;
}
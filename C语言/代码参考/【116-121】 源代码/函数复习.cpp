# include <stdio.h>

void f(int i);

void g(void)
{
	f(5);
}

void f(int i)
{
//	int i = 99;
	
	printf("i = %d\n", i);
	return ;
}

int main(void)
{	
	int i = 10;
	
	g();

	return 0;
}
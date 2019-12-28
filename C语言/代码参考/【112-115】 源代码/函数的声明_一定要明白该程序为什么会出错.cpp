# include <stdio.h>

void f(int); //函数声明， 分号不能丢掉

int main(void)
{
	f();

	return 0;
}

void f(void)
{
	printf("哈哈!\n");
}

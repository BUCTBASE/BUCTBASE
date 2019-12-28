# include <stdio.h>

int main(void)
{
	if (3 > 2)
		printf("AAAA\n");
	else if (3 > 1)
		printf("BBBB\n");
	else
		printf("CCCC\n");

	return 0;
}
/*
	在Vc++6.0中的输出结果是:
---------------
AAAA
---------------
	总结:
if (表达式1)
	A;
else if (表达式2)
	B;
else if (表达式3)
	C;
else
	D;

即便表达式1和2都成立，也只会执行A语句

*/
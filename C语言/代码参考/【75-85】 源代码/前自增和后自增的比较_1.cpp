# include <stdio.h>

int main(void)
{
	int i;
	int j;
	int k;
	int m;

	i = j = 3; //等价于 i = 3;  j = 3;
	k = i++;
	m = ++j;

	printf("i = %d, j = %d, k = %d, m = %d\n", i, j, k, m);

	return 0;
}
/*
	在Vc++6.0中的输出结果是:
----------------------
i = 4, j = 4, k = 3, m = 4
----------------------
	总结:
		前自增整体表达式的值是i加1之后的值
		后自增整体表达式的值是i加1之前的值
*/

/*
	2009年10月23日9:41:49
	本程序不对， 因为循环中更新的变量不能定义成浮点型
*/

# include <stdio.h>

int main(void)
{
	float i;
	float sum = 0;  

	for (i=1.0; i<=100; ++i)
	{
		sum = sum + 1/i;
	}
	printf("sum = %f\n", sum);  

	return 0;
}
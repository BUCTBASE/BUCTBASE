/*
	2009年10月21日15:51:16
	求1到100之间所有的能被3整除的数字之和
*/

# include <stdio.h>

int main(void)
{
	int i;
	int sum = 0;  // =0不能省

	for (i=3; i<=100; ++i)
	{
		if (i%3 == 0)//如果 i能被3整除
			sum = sum + i;
		printf("sum = %d\n", sum);
	}
	
	return 0;
}
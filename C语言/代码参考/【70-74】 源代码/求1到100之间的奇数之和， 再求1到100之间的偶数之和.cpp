# include <stdio.h>

int main(void)
{
	int i;
	int sum1 = 0;  //奇数和
	int sum2 = 0;  //偶数和
	
	for (i=1; i<101; ++i)
	{
		if (i%2 == 1)
		{
			sum1 += i;
		}
		else
		{
			sum2 += i;
		}
	}
	printf("奇数和 = %d\n", sum1);
	printf("偶数和 = %d\n", sum2);
	
	return 0;
}
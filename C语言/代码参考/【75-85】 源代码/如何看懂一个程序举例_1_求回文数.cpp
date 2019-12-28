# include <stdio.h>

int main(void)
{
	int val; //存放待判断的数字
	int m;
	int sum = 0;

	printf("请输入您需要判断的数字:  ");
	scanf("%d", &val);
	
	m = val;
	while (m)
	{
		sum = sum * 10 + m%10;
		m /= 10;
	}

	if (sum == val)
		printf("Yes!\n");
	else
		printf("No!\n");

	return 0;
}
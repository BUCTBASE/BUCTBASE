# include <stdio.h>

int main(void)
{
	int i;
	float sum = 0;

	for (i=1; i<=100; ++i)
	{
		sum = sum + 1.0/i;   //是OK的 推荐使用
			//sum = sum + (float)(1/i); 这样写是不对的 
			//也可以这样写:  sum = sum + 1 / (float)(i);   不推荐
	}
	printf("sum = %f\n", sum);  //float必须用%f输出

	return 0;
}
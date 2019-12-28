/*
	2009年10月21日15:47:19
	求1到100之间所有的奇数之和
*/

# include <stdio.h>

int main(void)
{
	int i;
	int sum = 0;  //=0不能省

	for (i=1; i<100; i+=2) //i+=2; 等价于 i = i + 2;  但通常都写i+=2 不写i = i+2
	{
		sum = sum + i;
		//printf("今天我很高兴!\n");
	}

	printf("i = %d\n", i);
	printf("sum = %d\n", sum);

	return 0;
}
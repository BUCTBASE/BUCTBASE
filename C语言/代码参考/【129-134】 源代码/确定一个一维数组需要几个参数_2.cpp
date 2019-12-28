/*
	2009年11月14日10:45:51
	一定要明白 10行的pArr[3] 和17行 19行的a[3] 是同一个变量
*/

# include <stdio.h>

void f(int * pArr, int len)
{
	pArr[3] = 88;  //10行
}

int main(void)
{
	int a[6] = {1,2,3,4,5,6};
	
	printf("%d\n", a[3]);  //17行
	f(a, 6);
	printf("%d\n", a[3]);  //  19行

	return 0;
}
/*
	在Vc++6.0中的输出结果是:
---------------------------
4
88
Press any key to continue
---------------------------
*/
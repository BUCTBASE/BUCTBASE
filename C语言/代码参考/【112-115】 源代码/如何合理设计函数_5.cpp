/*
	2009年11月4日11:56:29
	用两个函数来实现求1到某个数字之间所有的素数，并将其输出
	本程序 和 如何合理设计函数_4.cpp 相比较
	代码量更少，可重用性更高
*/


# include <stdio.h>

//本函数的功能是: 判断m是否是素数，是返回true，不是返回false
bool IsPrime(int m)
{
	int i;
		
	for (i=2; i<m; ++i)
	{
		if (0 == m%i)
			break;
	}
	if (i == m)
		return true;
	else
		return false;

}

//本函数的功能是把1到n之间所有的素数在显示器上输出
void TraverseVal(int n)
{
	int i;

	for (i=2; i<=n; ++i)
	{
		if ( IsPrime(i) )
			printf("%d\n", i);
	}
}

int main(void)
{
	int val;
 
	scanf("%d", &val);
	TraverseVal(val);

	return 0;
}
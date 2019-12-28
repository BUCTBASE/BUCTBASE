/*
	2009年11月6日9:33:02
	一定要明白该程序为什么是错的，
	也要明白把9到12行代码放在14行后面，为什么程序就OK了
*/

# include <stdio.h>



int k = 1000;  //14行
void g()  //9
{
	printf("k = %d\n", k);
} //12

void f(void)
{
	g();
	printf("k = %d\n", k);
}

int main(void)
{
	f();
	return 0;
}
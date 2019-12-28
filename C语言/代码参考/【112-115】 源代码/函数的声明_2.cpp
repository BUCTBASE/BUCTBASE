/*
	2009年11月4日11:01:35
	一定要明白该程序为什么是错误的
	一定要明白该程序第9行生效之后程序为什么就正确了
*/

# include <stdio.h>

//void f(void);  //9行

void g(void)
{
	f();  //因为函数f的定义放在了调用f语句的后面，所有语法出错
}

void f(void)
{
	printf("哈哈!\n");
}

int main(void)
{
	g();

	return 0;
}



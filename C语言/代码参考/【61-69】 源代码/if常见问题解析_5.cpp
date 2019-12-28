# include <stdio.h>

int main(void)
{
	if (1 > 2)
		printf("AAAA\n");
	else if (1 > 5)
		printf("BBBB\n");
	else (5 > 10);  //无实际意义的语句
		printf("CCCC\n");

		/*
			else (5 > 10);  //无实际意义的语句
				printf("CCCC\n");
		
			等价于
			else 
				(5 > 10);  //无实际意义的语句
			printf("CCCC\n");
		*/


	return 0;
}
/*
	总结:
if (表达式1)
	A;
else if (表达式2)
	B;
else if (表达式3)
	C;
else (表达式4);  
	D;

这样写语法不会出错，但逻辑上是错误的

else (表达式4);  
	D;
等价于
else 
	(表达式4);  
D;

*/

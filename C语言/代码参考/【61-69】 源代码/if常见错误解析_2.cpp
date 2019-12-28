# include <stdio.h>

int main(void)
{
	if (3 > 2) //4行  如果这里加分号，则会导致程序编译到6行时就会出错
		printf("哈哈!\n");
	else  //6行
		printf("嘿嘿!\n");

	return 0;
}
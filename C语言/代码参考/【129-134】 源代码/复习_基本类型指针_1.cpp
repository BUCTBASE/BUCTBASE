# include <stdio.h>

int main(void)
{
	int * p;//等价于 int *p; 也等价于 int* p;
	int i = 5;
	char ch = 'A';

	p = &i;  // *p 以p的内容为地址的变量
	*p = 99;
	printf("i = %d, *p = %d\n", i, *p);
	
	//p = &ch;
	//p = ch; //error
	//p = 5;  //error

	return 0;
}
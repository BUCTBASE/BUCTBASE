# include <stdio.h>

int main(void)
{
	int * p; //p是变量的名字, int * 表示p变量存放的是int类型变量的地址
	int i = 3;

	p = &i;  //OK
	//p = i; //error，因为类型不一致，p只能存放int类型变量的地址，不能存放int类型变量的值
	//p = 55; //error 原因同上

	return 0;
}
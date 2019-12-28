# include <stdio.h>
# include <malloc.h>

void f(int * q)
{
	//*p = 200; //error
	//q = 200;
	//**q = 200;  //error
	*q = 200;
	//free(q);  //把q所指向的内存释放掉  本语句必须的注释掉，否则会导致第20行的代码出错
}

int main(void)
{
	int * p = (int *)malloc(sizeof(int)); //sizeof(int)返回值是int所占的字节数
	*p = 10;

	printf("%d\n", *p);  //10
	f(p);  //p是int *类型
	printf("%d\n", *p);  //200    第20行

	return 0;
}
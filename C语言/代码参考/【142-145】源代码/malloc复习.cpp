# include <stdio.h>
# include <malloc.h>

int main(void)
{
//	int k;
	int * p = (int *)malloc(4);  
		/*
			malloc函数的返回值是void *
			void * 也叫干地址  所谓干地址就是无实际意义的地址
		*/

	free(p); //把p指向的内存释放

	return 0;
}
# include <stdio.h>

//f函数可以输出任何一个一维数组的内容
void f(int * pArr, int len)
{
	int i;

	for (i=0; i<len; ++i)
		printf("%d  ", *(pArr+i) );  //*pArr *(pArr+1) *(pArr+2) 
	printf("\n");
}

int main(void)
{
	int a[5] = {1,2,3,4,5};
	int b[6] = {-1,-2,-3,4,5,-6};
	int c[100] = {1, 99, 22, 33};

	f(a, 5);  //a是 int *
	f(b, 6);
	f(c, 100);

	return 0;
}
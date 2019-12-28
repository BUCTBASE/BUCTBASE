# include <stdio.h>

void OutArr(int * pArr, int len)
{
	//pArr[2] = 10; //pArr[2] == *(pArr+2) == *(a+2) == a[2]
	int i;
	
	for (i=0; i<len; ++i)
		printf("%d\n", pArr[i]);
}

int main(void)
{
	int a[5] = {1,2,3,4,5};

//	printf("%d\n", a[2]);
	OutArr(a, 5);
//	printf("%d\n", a[2]);
//	a = &a[2]; //error  因为a是常量

//	printf("%#X, %#X\n", a, &a[0]);
//	a ==  &a[0]

	return 0;
}
# include <stdio.h>

int main(void)
{
	int a[5] = {1, 2, 3, 4, 5};
		//a是数组的名字， 5表示数组元素的个数 ，并且这5过热元素分别用a[0] a[1] ...a[4]
	int i;

	for (i=0; i<5; ++i)
		printf("%d\n", a[i]);

	printf("%d\n", a[100]);

	return 0;
}

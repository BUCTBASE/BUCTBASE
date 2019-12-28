# include <stdio.h>

int main(void)
{
	int a[5];
	int i;
	
	scanf("%d", &a[0]);
	printf("a[0] = %d\n", a[0]);

	scanf("%d", &a[3]);
	printf("a[3] = %d\n", a[3]);

	for (i=0; i<5; ++i)
		printf("%d ", a[i]);

	return 0;
}
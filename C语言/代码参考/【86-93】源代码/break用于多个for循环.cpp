# include <stdio.h>

int main(void)
{
	int i, j;

	for (i=0; i<3; ++i)
	{
		for (j=1; j<4; ++j)
			break;  //break只能终止距离它最近的循环
		printf("同志们好!\n");
	}

	return 0;
}
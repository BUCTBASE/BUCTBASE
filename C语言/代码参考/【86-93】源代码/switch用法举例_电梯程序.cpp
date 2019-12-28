# include <stdio.h>

int main(void)
{
	int val;

	printf("请输入您要进入的楼层: ");
	scanf("%d", &val);

	switch (val)
	{
	case 1:
		printf("1层开!\n");
		break;
	case 2:
		printf("2层开!\n");
		//break;
	case 3:
		printf("3层开!\n");
		break;
    default:
		printf("没有盖到这一层!\n");
		break;
	}

	return 0;
}
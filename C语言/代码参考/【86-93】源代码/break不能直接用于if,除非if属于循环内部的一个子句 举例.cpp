# include <stdio.h>

int main(void)
{
	int i;
/*
	switch (2)
	{
	case 2:
		printf("哈哈!\n");
		break;  //OK, break可以用于switch
	}

*/
	
	for (i=0; i<3; ++i )
	{
		if (3 > 2)
			break;  //break虽然是if内部的语句，但break终止的确是外部的for循环
		printf("嘿嘿!\n");
	}

	return 0;
}
# include <stdio.h>

int main(void)
{ 
	int a=1,b;
	
	for(b=1; b<=10; b++)
	{
		if(a >= 8)
			break;  //会跳到18行
		if(1 == a%2)
		{
			a += 5;
			continue;   //会跳到7行执行b++
		}
		a -= 3;
	}
	printf("b = %d\n",b);
}

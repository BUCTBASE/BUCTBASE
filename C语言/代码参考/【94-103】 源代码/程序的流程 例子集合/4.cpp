# include <stdio.h>

int main(void)
{
    int  i=0, s=0;
	
	do
	{ 
		if(i%2)
		{
			i++;
			continue;  //会跳到11行去执行
		}
		i++;
		s+=i;  // s = s + i;
	}while(i < 5);  //11行
	
	printf("%d\n",s);   
	
	return 0;
}

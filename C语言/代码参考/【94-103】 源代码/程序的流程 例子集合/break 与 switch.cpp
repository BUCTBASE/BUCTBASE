# include <stdio.h>

int main()
{ 
	int x=1, y=0, a=0, b=0;

	switch(x) // 第一个switch 
	{  
	case 1:  
		switch(y)  // 第二个switch 
		{  
		case 0:  
			a++; 
			break;  
		case 1:  
			b++; 
			break;
		}
		break;  
	case 2: 
		a++;    
		b++;
		break;  
	}
	
	printf("%d %d\n",a,b); //26行
	
	return 0;
}

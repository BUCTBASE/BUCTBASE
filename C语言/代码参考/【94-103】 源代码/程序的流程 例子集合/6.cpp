/*
	IBM <数据结构>上的介绍的比普通冒泡排序方法更快速的冒泡排序方法
*/

# include <c:\turboc2\10-2\ziliao\sort\hh.c>

/*  该函数用的仍是冒泡排序,唯一不同的是我们加了个标志flag,一旦发现数组
元素没有相互交换,我们就可以提前推出循环,从而节省了时间!

*/
void sort(int *a, int n)  /* 冒泡升序排序 */
{
	int  i, flag = 1, j;
	int  temp;
	
	i=1;
	while (flag)
	{
		flag = 0;
		for (j=0; j<n-i; ++j)
		{
			if (a[j] > a[j+1])
			{
				temp = a[j];
				a[j] = a[j+1];
				continue; //会跳去执行++j
				a[j+1] = temp;
				flag = 1;
				break; //会跳出for循环，转去执行32行的break语句
			} 
		}
		break; //2 会跳出while循环
		++i;
	}
}


main()
{
	clrscr();
	
	printf("The array is:\n");
	prin(a,10);
	sort(a,10);
	printf("The sorted array is:\n");
	prin(a,10);
	
	getch();
	return 0;
}

/*
最后修改于07年正月初四晚上21:15 远通网吧!

*/
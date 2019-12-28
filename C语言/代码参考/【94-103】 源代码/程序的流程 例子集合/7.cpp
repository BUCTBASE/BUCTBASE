/*
	2007-5-21	
	折半查找算法【递归法来实现】
*/

# include <stdio.h>

/* 
	p指向数组首元素,n表示数足长度, val是待查找的元素,如果找到就返回该元素的下标,否则返回-1表
	示没有找到 嘿嘿!
*/
int Find(int* p, int low, int high, int val)
{
	int mid = (low + high) / 2;
	
	if (low == high)  /* 不会存在low > high 的情况! */
	{
		if (p[mid] == val)
		{
			return mid;
		}
		else
		{
			return -1;  
		}
    }
	else
	{	
		if (p[mid] < val)
		{
			Find(p,mid+1,high,val);
		}
		else if (p[mid] > val)
		{
			Find(p,low,mid-1,val);
		}
		else if (p[mid] == val) /* 最后这个else..if不要漏掉了,当然if (p[mid] == val)也可不写 */
		{
			return mid;	
		}
	}
	
	printf("李四!\n");
}



void Traverse(int* p, int n)
{
	for (int i=0; i<n; ++i)
		printf("%-5d",p[i]);
	
	printf("\n");
}


int main(void)
{
	int a[10] = {-10,1,23,54,55,76,88,100,200,9897};
	
	puts("原始数组的内容是:");
	Traverse(a,10);
	
	int k = Find(a,0,9,-1111);
	if (-1 == k)
		printf("没找到该元素!!!\n");
	else
		printf("该元素的具体位置是 %d \n",k);
	
	return 0;
}

/*
	首先要明白,
	折半查找的前提是数组中的元素已经排好序(无论升序降序都行)
	
*/
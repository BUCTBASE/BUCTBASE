# include <stdio.h>

int main(void)
{
	float score; //score分数

	printf("请输入您的考试成绩: ");
	scanf("%f", &score);

	if (score > 100)
		printf("这是做梦!\n");
	else if (score>=90 && score<=100) //不能写成 90<=score<=100
		printf("优秀!\n");
	else if (score>=80 && score<90)
		printf("良好!\n");
	else if (score>=60 && score<80)
		printf("及格!\n");
	else if (score>=0 && score<60)  //if不能省，否则会出错
		printf("不及格! 继续努力!\n");
	
	
	return 0;
}
/*
总结
if (表达式1)
	A;
else if (表达式2)
	B;
else if (表达式3)
	C;
else (表达式4)  //7行
	D;

这样写是不对的，正确的写法是：
	要么去掉7行的(表达式4)
	要么在7行的else 后面加if 

*/
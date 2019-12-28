#include <stdio.h>
void main()
{    char str[30],new_str[30];
     int i,j;
     char c;
     printf("Input a string:\n");
     gets(str);
     printf("Input a random character:\n");
     c=getchar();
     printf("Delete the input character from the string:\n");
       for(i=0,j=0;str[i]!='\0';i++)
          	if(str[i]!=c)   
		new_str[ j++ ]=str[i];     
       new_str[j]='\0';        /*新串加字符串结束标志*/
       printf("The new string is:\n %s\n",new_str);
}

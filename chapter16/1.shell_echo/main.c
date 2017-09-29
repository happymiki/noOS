#include <stdio.h>
#include <string.h>

/* 命令行长度 */
#define MAX_LINE_LENGTH		256

int main(void)
{
	/* 用来存放用户输入的命令内容 */
	char str[MAX_LINE_LENGTH];
	
	while (1)
	{
		/* 打印命令行提示符,注意不能加换行 */
		printf("CML#");
		
		/* 清除str数组以存放新的字符串 */
		memset(str,0,sizeof(str));
		
		/* shell第一步：获取用户输入的命令 */
		scanf("%s",str);
		
		/* shell第二步：解析用户输入的命令 */
		
		
		/* shell第三步：处理用户输入命令 */
		printf("%s\n",str);
	}
	
	
	return 0;
}

























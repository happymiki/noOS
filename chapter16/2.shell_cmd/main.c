#include <stdio.h>
#include <string.h>

/* 命令行长度 */
#define MAX_LINE_LENGTH		256


/* 宏定义一些标准命令 */
#define led					"led"
#define lcd 				"lcd"
#define pwm					"pwm"

/* 当前系统定义的命令数 */
#define CMD_NUM			3

char g_cmdset[CMD_NUM][MAX_LINE_LENGTH];

static void init_cmd_set(void);

int main(void)
{
	/* 用来存放用户输入的命令内容 */
	char str[MAX_LINE_LENGTH];
	
	int i;
	
	init_cmd_set();
	
	while (1)
	{
		/* 打印命令行提示符,注意不能加换行 */
		printf("CML#");
		
		/* 清除str数组以存放新的字符串 */
		memset(str,0,sizeof(str));
		
		/* shell第一步：获取用户输入的命令 */
		scanf("%s",str);
		
		/* shell第二步：解析用户输入的命令 */
		for (i=0; i<CMD_NUM; i++)
		{
			if (!strcmp(str,g_cmdset[i]))
			{
				/* 相等，找到了命令，就去执行这个命令所对应的动作 */
				printf("您输入的命令数：%s，是合法的\n",str);
				break; 
			}
		}
		if (i >= CMD_NUM)
		{
			/* 找完了命令集都没找到命令 */
			printf("%s不是一个内部合法命令，请重新输入\n",str);
		}
		
		/* shell第三步：处理用户输入命令 */
		//printf("%s\n",str);
	}
	
	
	return 0;
}


/* 初始化命令列表 */
static void init_cmd_set(void)
{
	/* 全部清零 */
	memset(g_cmdset,0,sizeof(g_cmdset));
	
	strcpy(g_cmdset[0],led);
	strcpy(g_cmdset[1],lcd);
	strcpy(g_cmdset[2],pwm);
	
	
}





















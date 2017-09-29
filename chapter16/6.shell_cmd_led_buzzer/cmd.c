// 命令解析和命令执行相关的函数
#include "shell.h"

char g_cmdset[CMD_NUM][MAX_LINE_LENGTH];	// 命令集，主命令
char cmd[MAX_CMD_PART][MAX_LEN_PART];		// 当前解析的命令
int cmd_index = -1;					// 存储解析到的命令是第几个主命令


// 初始化命令列表
void init_cmd_set(void)
{
	memset((char *)g_cmdset, 0, sizeof(g_cmdset));		// 先全部清零
	strcpy(g_cmdset[0], led);
	strcpy(g_cmdset[1], lcd);
	strcpy(g_cmdset[2], pwm);
	
	memset((char *)cmd, 0, sizeof(g_cmdset));
}

/********************** 命令处理函数 ***********************/
/************led命令处理方法**************/
// 命令未找到的处理
void do_cmd_notfound(void)
{
	puts(cmd[0]);
	puts("不是一个内部合法命令，请重新输入\n");
	puts("\n");
}
// led的处理方法
void do_cmd_led(void)
{
	int flag = -1;
	//puts("led cmd");
	//puts("\n");
	// 真正的led命令实现
	// led目前支持的命令led on | led off
	// cmd[0]里面是led，cmd[1]里面是on或off
	
	if (!strcmp(cmd[1],"on"))
	{
		// led on
		flag = 1;
		led_on();
	}
	if (!strcmp(cmd[1],"off"))
	{ 
		// led off
		flag = 1;
		led_off();
	}
	if (-1 == flag)
	{
		puts("command error,try:led on | led off");
		puts("\n");
	}
	// ****还可以继续扩展****
}

/************buzzer命令处理方法**************/
// buzzer的处理方法
void do_cmd_buzzer(void)
{
	int flag = -1;
	//puts("led cmd");
	//puts("\n");
	// 真正的led命令实现
	// buzzer目前支持的命令buzzer on | buzzer off
	// cmd[0]里面是buzzer，cmd[1]里面是on或off
	
	if (!strcmp(cmd[1],"on"))
	{
		// led on
		flag = 1;
		buzzer_on();
	}
	if (!strcmp(cmd[1],"off"))
	{ 
		// led off
		flag = 1;
		buzzer_off();
	}
	if (-1 == flag)
	{
		puts("command error,try:buzzer on | buzzer off");
		puts("\n");
	}
	// ****还可以继续扩展
}

/************lcd命令处理方法**************/





/********************** 命令解析、执行框架 ***********************/

// 解析命令
void cmd_parser(char *str)
{
	int i;
	
	// 1.先将用户输入的次命令分割放入cmd中
	cmdsplit(cmd,str);
	
	// 2.将cmd中的第一个字符串和主命令g_cmdset比较
	
	
	cmd_index = -1;
	
	for (i=0; i<CMD_NUM; i++)
	{
		// 次命令中的第一个字符串也就是主命令
		if (!strcmp(cmd[0], g_cmdset[i]))
		{
			// 相等，找到了这个命令，就去执行这个命令所对应的动作。
			puts("您输入的命令是：");
			puts(str);
			puts("\n");
			cmd_index = i;
			
			
			break;
		}	
	}
		/*
		if (i >= CMD_NUM)
		{
			// 找遍了命令集都没找到这个命令
			cmd_index = -1;
		}
		*/
}

// 执行命令
void cmd_exec(void)
{
	switch (cmd_index)
	{
		case 0:		//led
			do_cmd_led();
			break;
		case 1:		// lcd
			
		case 2:		// buzzer
			
		default:
			do_cmd_notfound();
			break;
	}
}














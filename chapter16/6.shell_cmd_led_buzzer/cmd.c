// �������������ִ����صĺ���
#include "shell.h"

char g_cmdset[CMD_NUM][MAX_LINE_LENGTH];	// �����������
char cmd[MAX_CMD_PART][MAX_LEN_PART];		// ��ǰ����������
int cmd_index = -1;					// �洢�������������ǵڼ���������


// ��ʼ�������б�
void init_cmd_set(void)
{
	memset((char *)g_cmdset, 0, sizeof(g_cmdset));		// ��ȫ������
	strcpy(g_cmdset[0], led);
	strcpy(g_cmdset[1], lcd);
	strcpy(g_cmdset[2], pwm);
	
	memset((char *)cmd, 0, sizeof(g_cmdset));
}

/********************** ������� ***********************/
/************led�������**************/
// ����δ�ҵ��Ĵ���
void do_cmd_notfound(void)
{
	puts(cmd[0]);
	puts("����һ���ڲ��Ϸ��������������\n");
	puts("\n");
}
// led�Ĵ�����
void do_cmd_led(void)
{
	int flag = -1;
	//puts("led cmd");
	//puts("\n");
	// ������led����ʵ��
	// ledĿǰ֧�ֵ�����led on | led off
	// cmd[0]������led��cmd[1]������on��off
	
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
	// ****�����Լ�����չ****
}

/************buzzer�������**************/
// buzzer�Ĵ�����
void do_cmd_buzzer(void)
{
	int flag = -1;
	//puts("led cmd");
	//puts("\n");
	// ������led����ʵ��
	// buzzerĿǰ֧�ֵ�����buzzer on | buzzer off
	// cmd[0]������buzzer��cmd[1]������on��off
	
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
	// ****�����Լ�����չ
}

/************lcd�������**************/





/********************** ���������ִ�п�� ***********************/

// ��������
void cmd_parser(char *str)
{
	int i;
	
	// 1.�Ƚ��û�����Ĵ�����ָ����cmd��
	cmdsplit(cmd,str);
	
	// 2.��cmd�еĵ�һ���ַ�����������g_cmdset�Ƚ�
	
	
	cmd_index = -1;
	
	for (i=0; i<CMD_NUM; i++)
	{
		// �������еĵ�һ���ַ���Ҳ����������
		if (!strcmp(cmd[0], g_cmdset[i]))
		{
			// ��ȣ��ҵ�����������ȥִ�������������Ӧ�Ķ�����
			puts("������������ǣ�");
			puts(str);
			puts("\n");
			cmd_index = i;
			
			
			break;
		}	
	}
		/*
		if (i >= CMD_NUM)
		{
			// �ұ��������û�ҵ��������
			cmd_index = -1;
		}
		*/
}

// ִ������
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














#include <stdio.h>
#include <string.h>

/* �����г��� */
#define MAX_LINE_LENGTH		256

int main(void)
{
	/* ��������û�������������� */
	char str[MAX_LINE_LENGTH];
	
	while (1)
	{
		/* ��ӡ��������ʾ��,ע�ⲻ�ܼӻ��� */
		printf("CML#");
		
		/* ���str�����Դ���µ��ַ��� */
		memset(str,0,sizeof(str));
		
		/* shell��һ������ȡ�û���������� */
		scanf("%s",str);
		
		/* shell�ڶ����������û���������� */
		
		
		/* shell�������������û��������� */
		printf("%s\n",str);
	}
	
	
	return 0;
}

























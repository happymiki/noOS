#include "stdio.h"

void uart_init(void);

int main(void)
{
	//���ô��ڳ�ʼ��������ʼ������
	uart_init(); 
	printf("I LOVE U");
	/*
	while(1)
	{
		uart_putchar('a');
		delay();
	}
	*/
	return 0;
}
























#include "stdio.h"

void uart_init(void);

int main(void)
{
	//调用串口初始化函数初始化串口
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
























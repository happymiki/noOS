#include "stdio.h"

void uart_init(void);

void key_init(void);
void key_polling(void);

int main(void)
{
	//调用串口初始化函数初始化串口
	uart_init(); 
	//key_init();
	printf("init successful\r\n");
	//key_polling();
	/*
	while(1)
	{
		uart_putchar('a');
		delay();
	}
	*/
	return 0;
}
























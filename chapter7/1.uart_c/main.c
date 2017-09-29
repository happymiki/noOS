

void main(void)
{
	//调用串口初始化函数初始化串口
	uart_init();
	
	while(1)
	{
		uart_putchar('a');
		delay();
	}
}


























void main(void)
{
	//���ô��ڳ�ʼ��������ʼ������
	uart_init();
	
	while(1)
	{
		uart_putchar('a');
		delay();
	}
}
























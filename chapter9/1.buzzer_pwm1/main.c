#include "stdio.h"

void uart_init(void);
void timer2_pwm_init(void);


int main(void)
{
	/* ���ô��ڳ�ʼ��������ʼ������ */
	uart_init(); 
	timer2_pwm_init();
	
	while(1);
	
	return 0;
}
























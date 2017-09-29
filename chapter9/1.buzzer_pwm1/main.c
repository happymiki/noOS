#include "stdio.h"

void uart_init(void);
void timer2_pwm_init(void);


int main(void)
{
	/* 调用串口初始化函数初始化串口 */
	uart_init(); 
	timer2_pwm_init();
	
	while(1);
	
	return 0;
}
























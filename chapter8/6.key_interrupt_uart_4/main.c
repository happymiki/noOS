#include "stdio.h"
#include "interrupt.h"
#include "key.h"
#include "uart.h"

#define KEY_EINT2		NUM_EINT2		// LEFT
#define KEY_EINT3		NUM_EINT3		// DOWN
#define KEY_EINT16_19	NUM_EINT16_31	// 其余4个共用

void delay(void)
{
	volatile unsigned int i = 1000000;
		while (i--);
}

int main(void)
{
	//调用串口初始化函数初始化串口
	uart_init(); 
	
	// 以中断方式来处理按键的初始化
	key_init_interrupt();

	// 如果程序要使用中断，就要调用中断初始化来初步初始化中断控制器
	system_init_exception();
	
	printf("init successful\r\n");
	
	// 绑定isr到中断控制器硬件
	intc_setvectaddr(KEY_EINT2,isr_eint2);
	intc_setvectaddr(KEY_EINT3,isr_eint3);
	intc_setvectaddr(KEY_EINT16_19,isr_eint16_19);
	
	// 使能中断
	intc_enable(KEY_EINT2);
	intc_enable(KEY_EINT3);
	intc_enable(KEY_EINT16_19);
	
	// 加个心跳
	while (1)
	{
		printf("I LOVE U\r\n");
		delay();
	}
	return 0;
} 
























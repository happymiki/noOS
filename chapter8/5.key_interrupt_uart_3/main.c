#include "stdio.h"
#include "interrupt.h"

#define KEY_INTNUM	NUM_EINT9

void uart_init(void);
void key_init(void);
void key_polling(void);

void key_isr();

int main(void)
{
	//调用串口初始化函数初始化串口
	uart_init(); 
	key_init();
	printf("init successful\r\n");

	// 如果程序要使用中断，就要调用中断初始化来初步初始化中断控制器
	system_init_exception();
	
	// 绑定isr到中断控制器硬件
	intc_setvectaddr(KEY_INTNUM,key_isr);
	
	
	return 0;
}

void key_isr()
{
	
}






















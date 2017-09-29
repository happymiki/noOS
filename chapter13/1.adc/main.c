#include "stdio.h"
#include "interrupt.h"
#include "uart.h"
#include "adc.h"

void delay(void)
{
	volatile unsigned int i = 1000000;
		while (i--);
}

int main(void)
{
	//调用串口初始化函数初始化串口
	uart_init(); 
	
	// 如果程序要使用中断，就要调用中断初始化来初步初始化中断控制器
	//system_init_exception();
	
	adc_init();
	
	printf("****************adc test************\r\n");
	
	adc_test();
	// 绑定isr到中断控制器硬件
	//intc_setvectaddr(NUM_WDT,isr_wdt);
	
	// 使能中断   
	//intc_enable(NUM_WDT);
	
	while (1);
	
	return 0;
} 
























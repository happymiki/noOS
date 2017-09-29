#include "stdio.h"
#include "interrupt.h"
#include "wdt.h"
#include "uart.h"


void delay(void)
{
	volatile unsigned int i = 1000000;
		while (i--);
}

int main(void)
{
	//���ô��ڳ�ʼ��������ʼ������ 
	uart_init(); 
	
	// ���жϷ�ʽ�������Ź��ĳ�ʼ��
	wdt_init_reset();

	// �������Ҫʹ���жϣ���Ҫ�����жϳ�ʼ����������ʼ���жϿ�����
	system_init_exception();
	
	printf("init successful\r\n");
	
	// ��isr���жϿ�����Ӳ��
	intc_setvectaddr(NUM_WDT,isr_wdt);
	
	// ʹ���ж�   
	intc_enable(NUM_WDT);
	
	while (1);
	
	return 0;
} 
























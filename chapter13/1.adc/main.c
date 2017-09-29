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
	//���ô��ڳ�ʼ��������ʼ������
	uart_init(); 
	
	// �������Ҫʹ���жϣ���Ҫ�����жϳ�ʼ����������ʼ���жϿ�����
	//system_init_exception();
	
	adc_init();
	
	printf("****************adc test************\r\n");
	
	adc_test();
	// ��isr���жϿ�����Ӳ��
	//intc_setvectaddr(NUM_WDT,isr_wdt);
	
	// ʹ���ж�   
	//intc_enable(NUM_WDT);
	
	while (1);
	
	return 0;
} 
























#include "stdio.h"
#include "interrupt.h"
#include "key.h"
#include "uart.h"

#define KEY_EINT2		NUM_EINT2		// LEFT
#define KEY_EINT3		NUM_EINT3		// DOWN
#define KEY_EINT16_19	NUM_EINT16_31	// ����4������

void delay(void)
{
	volatile unsigned int i = 1000000;
		while (i--);
}

int main(void)
{
	//���ô��ڳ�ʼ��������ʼ������
	uart_init(); 
	
	// ���жϷ�ʽ���������ĳ�ʼ��
	key_init_interrupt();

	// �������Ҫʹ���жϣ���Ҫ�����жϳ�ʼ����������ʼ���жϿ�����
	system_init_exception();
	
	printf("init successful\r\n");
	
	// ��isr���жϿ�����Ӳ��
	intc_setvectaddr(KEY_EINT2,isr_eint2);
	intc_setvectaddr(KEY_EINT3,isr_eint3);
	intc_setvectaddr(KEY_EINT16_19,isr_eint16_19);
	
	// ʹ���ж�
	intc_enable(KEY_EINT2);
	intc_enable(KEY_EINT3);
	intc_enable(KEY_EINT16_19);
	
	// �Ӹ�����
	while (1)
	{
		printf("I LOVE U\r\n");
		delay();
	}
	return 0;
} 
























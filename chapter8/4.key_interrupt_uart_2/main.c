#include "stdio.h"
#include "interrupt.h"

#define KEY_INTNUM	NUM_EINT9

void uart_init(void);
void key_init(void);
void key_polling(void);

void key_isr();

int main(void)
{
	//���ô��ڳ�ʼ��������ʼ������
	uart_init(); 
	key_init();
	printf("init successful\r\n");

	// �������Ҫʹ���жϣ���Ҫ�����жϳ�ʼ����������ʼ���жϿ�����
	system_init_exception();
	
	// ��isr���жϿ�����Ӳ��
	intc_setvectaddr(KEY_INTNUM,key_isr);
	
	
	return 0;
}

void key_isr()
{
	
}






















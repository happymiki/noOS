/*
 *�ļ����� led.s
 *��  �ߣ� CML
 *��  ���� ��ʾ��࿪��icache
 */
 


#define WTCON     0xE2700000

#define SVC_STACK 0xD0037D80 
.global _start		// ��_start�������Ը�Ϊ�ⲿ�����������ļ��ܹ�����
 _start:

	// ��1�����رտ��Ź�����WTCON��bit5д��0���ɣ�
	ldr r0, =WTCON
	ldr r1, =0x0
	str r1, [r0]
	
	// ��2��������SVCջ
	ldr sp, =SVC_STACK 
	
	// ��3���������icache
	mrc p15,0,r0,c1,c0,0;	// ����cp15��c1��r0��
	bic r0, r0, #(0<<12)	// bit12��0 ��icache
	//orr r0, r0, #(1<<12)	// bit12��1 ��icache
	mcr p15,0,r0,c1,c0,0;
	
	// ֮����Ե���c���Գ���
	
	bl led_blink		// led_blink��c�����еĺ���

// ���������ѭ�����ܶ�
	b .
 
 
 
 
 
 
 
 
 
 
 
 
 
/*
 * �ļ�����	start.s	
 * ���ߣ�	����ʦ
 * ������	��ʾ����
 */

#define WTCON		0xE2700000

#define SVC_STACK	0xd0037d80
#define IRQ_STACK	0xd0037f80


.global _start					// ��_start�������Ը�Ϊ�ⲿ�����������ļ��Ϳ��Կ���_start��
.global IRQ_handle	

_start:

	// ��0��������������
	
	/* д��1 */
	ldr r0, =0xE010E81C
	ldr r1, =0x301
	str r1,[r0]

	// ��1�����ؿ��Ź�����WTCON��bit5д��0���ɣ�
	ldr r0, =WTCON
	ldr r1, =0x0
	str r1, [r0]
	
	// ��2������ʼ��ʱ��
	bl clock_init
	
	// ��3��������SVCջ
	ldr sp, =SVC_STACK
	
	// ��4������/��icache
	mrc p15,0,r0,c1,c0,0;			// ����cp15��c1��r0��
	//bic r0, r0, #(1<<12)			// bit12 ��0  ��icache
	orr r0, r0, #(1<<12)			// bit12 ��1  ��icache
	mcr p15,0,r0,c1,c0,0;

	bl main
		
// ������������ѭ�����ܶ�
	b .
	
// �������ຯ�������ж�ģʽ�µ��ֳ������ͻָ�,���ҵ����������жϴ�������
IRQ_handle:
	// ��һ��������IRQģʽ�µ�ջ
	ldr sp, =IRQ_STACK
	
	// �ڶ���������LR
	// ��Ϊarm����ˮ�ߣ�����pc��ֵ�������ִ�еĴ���+8
	sub lr,lr,#4
	
	// ������������r0-r12��irqģʽ�µ�ջ����
	stmfd sp!, {r0-r12, lr}
	
	// ���Ĳ��������жϴ�������
	bl irq_handler

	// ���岽��������ɿ�ʼ�ָ��ֳ�����ʵ�����жϷ��أ��ؼ��ǽ�r0-r12��pc��cpsrһ��ָ�
	ldmfd sp!, {r0-r12, pc}^







	
	
	
	
	
	
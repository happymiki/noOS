/*
 * �ļ�����	led.s	
 * ���ߣ�	����ʦ
 * ������	��ʾ�ض�λ����SRAM�ڲ��ض�λ��
 */

#define WTCON		0xE2700000

#define SVC_STACK	0xd0037d80

.global _start		// ��_start�������Ը�Ϊ�ⲿ�����������ļ��Ϳ��Կ���_start��
_start:

	// ��0��������������
	// д��1
	//ldr r0, =0xE010E81C
	//ldr r1, =0x301
	//str r1, [r0]
	// д��2
	//ldr r0, =0xE010E81C
	//ldr r1, [r0]
	//orr r1, r1, #0x300
	//orr r1, r1, #0x01
	//str r1, [r0]
	// д��3
	ldr r0, =0xE010E81C
	ldr r1, [r0]
	ldr r2, =0x301
	orr r1, r1, r2
	str r1, [r0]

	// ��1�����ؿ��Ź�����WTCON��bit5д��0���ɣ�
	ldr r0, =WTCON
	ldr r1, =0x0
	str r1, [r0]
	
	// ��2��������SVCջ
	ldr sp, =SVC_STACK
	
	// ��3������/��icache
	mrc p15,0,r0,c1,c0,0;			// ����cp15��c1��r0��
	//bic r0, r0, #(1<<12)			// bit12 ��0  ��icache
	orr r0, r0, #(1<<12)			// bit12 ��1  ��icache
	mcr p15,0,r0,c1,c0,0;

	// ��4������ʼ��ddr
	bl sdram_asm_init
	

	// ��5�����ض�λ����SD����45������ʼ������32���������ݵ�DDR��0x23E00000
	bl copy_bl2_2_ddr

	
	
// ������������ѭ�����ܶ�
	b .
	


	
	

	
	
	
	
	
	
	
	
	
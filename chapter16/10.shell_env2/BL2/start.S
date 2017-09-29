/*
 * �ļ�����	led.s	
 * ���ߣ�	����ʦ
 * ������	��ʾ�ض�λ����SRAM�ڲ��ض�λ��
 */

#define WTCON		0xE2700000

#define SVC_STACK	0xd0037d80
#define IRQ_STACK	0xd0037f80

.global _start	
.global IRQ_handle					// ��_start�������Ը�Ϊ�ⲿ�����������ļ��Ϳ��Կ���_start��
_start:

// ��������bss������ʽ��ʼ��Ϊ0��û����ʽ��ʼ���ģ�ȫ�ֱ���û�г�ʼ��Ϊ0
// ����ǰ���C���Թ���C����ʱ����
clean_bss:
	ldr r0, =bss_start					
	ldr r1, =bss_end
	cmp r0, r1				// ���r0����r1��˵��bss��Ϊ�գ�ֱ����ȥ
	beq run_on_dram			// ���bss��֮��ĵ�ַ
	mov r2, #0
clear_loop:
	str r2, [r0], #4		// �Ƚ�r2�е�ֵ����r0��ָ����ڴ��ַ��r0�е�ֵ��Ϊ�ڴ��ַ����
	cmp r0, r1				// Ȼ��r0 = r0 + 4
	bne clear_loop

run_on_dram:	
	// ����ת��led_blink��ʼ�ڶ��׶�
	ldr pc, =main				// ldrָ��ʵ�ֳ���ת
	
	
// ������������ѭ�����ܶ�
	b .
	
IRQ_handle:
	// ����IRQģʽ�µ�ջ
	ldr sp, =IRQ_STACK
	// ����LR
	// ��ΪARM����ˮ�ߣ�����PC��ֵ�������ִ�еĴ���+8��
	sub lr, lr, #4
	// ����r0-r12��lr��irqģʽ�µ�ջ����
	stmfd sp!, {r0-r12, lr}
	// �ڴ˵���������isr�������ж�
	bl irq_handler
	// ������ɿ�ʼ�ָ��ֳ�,��ʵ�������жϷ��أ��ؼ��ǽ�r0-r12��pc��cpsrһ��ظ�
	ldmfd sp!, {r0-r12, pc}^	
	
	
	

	
	
	
	
	
	
	
	
	
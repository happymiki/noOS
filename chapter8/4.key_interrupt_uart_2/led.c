#define GPJ0CON   0xE0200240
#define GPJ0DAT   0xE0200244

#define rGPJ0CON *((volatile unsigned int *)GPJ0CON)
#define rGPJ0DAT *((volatile unsigned int *)GPJ0DAT)

//�ú���ʵ��led��˸
void led_blink(void)
{	
	rGPJ0CON = 0x11111111;
	
	while (1)
	{
		//led��
		rGPJ0DAT = ((0<<3) | (0<<4) | (0<<5));
		//��ʱ
		delay();
		//led��
		rGPJ0DAT = ((1<<3) | (1<<4) | (1<<5));
		//��ʱ
		delay();
	}
	return 0;
}

// ����1��led
void led1(void)
{
	rGPJ0CON = 0x11111111;
	rGPJ0DAT = ((0<<3) | (1<<4) | (1<<5));
}

// ����2��led
void led2(void)
{
	rGPJ0CON = 0x11111111;
	rGPJ0DAT = ((1<<3) | (0<<4) | (1<<5));
}

// ����3��led
void led3(void)
{
	rGPJ0CON = 0x11111111;
	rGPJ0DAT = ((1<<3) | (1<<4) | (0<<5));
}

// ����12��led
void led4(void)
{
	rGPJ0CON = 0x11111111;
	rGPJ0DAT = ((0<<3) | (0<<4) | (1<<5));
}

// ����23��led
void led5(void)
{
	rGPJ0CON = 0x11111111;
	rGPJ0DAT = ((1<<3) | (0<<4) | (0<<5));
}

// ����123��led
void led6(void)
{
	rGPJ0CON = 0x11111111;
	rGPJ0DAT = ((0<<3) | (0<<4) | (0<<5));
}
void led_off(void)
{
	rGPJ0CON = 0x11111111;
	rGPJ0DAT = ((1<<3) | (1<<4) | (1<<5));
}


void delay(void)
{
	volatile unsigned int i = 100000;		//volatile �ñ�������Ҫ�Ż��� 
	while (i--);							//���ÿ��ȡ��������ԭʼֵ
}

#if 0
	// ��һ������0x11111111д��0xE0200240(GPJ0CON)λ�ã���������������Ϊ��������벻��
	ldr r0, =0x11111111			// �ӡ�=�������õ���ldrαָ���Ҫ�������ж��������
	ldr r1, =GPJ0CON			// �Ϸ����������ǷǷ���������һ�㶼��ldrαָ��
	str r0, [r1]				// �Ĵ������Ѱַ�����ܣ���r0�е���д�뵽r1�е���Ϊ��ַ���ڴ���ȥ

flag:
	// �ڶ�����������һ��
	//ldr r0, =((0<<3) | (1<<4) | (1<<5))	//�൱��0b00000000��
	ldr r0, = ~(1<<3)
	ldr r1, =GPI0DAT
	str r0, [r1]				// ��0д��GPJ0DAT�Ĵ����жϣ����ż�����͵�ƽ��LED����
	//��ʱ
	bl delay					// ʹ��bl���к�������
	
	//�������������ڶ���
	ldr r0, = ~(1<<4)
	ldr r1, =GPI0DAT
	str r0, [r1]				// ��0д��GPJ0DAT�Ĵ����жϣ����ż�����͵�ƽ��LED����
	//��ʱ
	bl delay					// ʹ��bl���к�������

	//���Ĳ�������������
	ldr r0, = ~(1<<5)
	ldr r1, =GPI0DAT
	str r0, [r1]				// ��0д��GPJ0DAT�Ĵ����жϣ����ż�����͵�ƽ��LED����
	//��ʱ
	bl delay					// ʹ��bl���к�������

	b flag

delay:
	ldr r2, =10000000
	ldr r3, =0x0
delay_loop:	
	sub r2, r2, #1 				//r2 = r2 - 1
	
	cmp r2,r3 					//cmp��Ӱ��CPSR�Ĵ�����Z��־λ�����r2����r3����Z=1����һ���е�eq�ͻ����
	bne delay_loop
	mov pc, lr					//�������÷���
#endif
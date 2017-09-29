
#define 	GPD0CON  	(0XE02000A0)
#define 	TCFG0		(0XE2500000)	
#define 	TCFG1  		(0XE2500004)
#define 	CON			(0XE2500008)	
#define   	TCNTB2		(0XE2500024)
#define   	TCMPB2		(0XE2500028)


#define 	rGPD0CON	(*(volatile unsigned int *)GPD0CON)
#define 	rTCFG0		(*(volatile unsigned int *)TCFG0)
#define 	rTCFG1		(*(volatile unsigned int *)TCFG1)
#define 	rCON		(*(volatile unsigned int *)CON)
#define 	rTCNTB2		(*(volatile unsigned int *)TCNTB2)
#define 	rTCMPB2		(*(volatile unsigned int *)TCMPB2)

/* ��ʼ��PWM timer2,ʹ�����һ��PWM���Σ�Ƶ��Ϊ2kHZ,duty��ռ�ձȣ�Ϊ50% */
void timer2_pwm_init(void)
{
	/* ����GPD0_2���ţ���������ΪXpwmTOUT_2 */
	rGPD0CON &= ~(0xf<<8);		/* ���� */
	rGPD0CON |= (2<<8);			/* ��ֵ */
	
	/* ����PWM��ʱ�������ɼĴ�����ʹ�乤�� */ 
	/* ����Ԥ��Ƶ���ļĴ��� */
	rTCFG0 &= ~(0xff<<8);		/* ���� */
	rTCFG0 |= (65<<8);			/* prescaler1 = 65,Ԥ��Ƶ֮��Ƶ��Ϊ1Hz */
	
	/* ���÷�Ƶ���ļĴ��� */
	rTCFG1 &= ~(0xf<<8);		/* ���� */
	rTCFG1 |= (1<<8);			/* MUX2����Ϊ1/2��Ƶ����Ƶ��ʱ������Ϊ500kHz */
	
	/* ʱ�����ú�֮��ʱ������Ϊ500kHz����Ӧ��ʱ������Ϊ2us��Ҳ����ÿ��2us��һ����
	   ���Ҫ����ʱ����x����TCNTB��Ӧ��д��x/2us */
	
	rCON |= (1<<15);		/* ʹ��Auto Reload������������װ�ض�ʱ�����ܷ���PWM���� */
	rTCNTB2 = 250;			/* 0.5ms/2us = 500us/2us = 250 */
	rTCMPB2 = 125;			/* duty = 50% */
	
	/* ��һ����Ҫ�ֹ���TCNTB�е�ֵˢ�µ�TCNT��ȥ���Ժ�Ϳ���auto-reload�� */
	rCON |= (1<<13);		/* ���Զ�ˢ�¹��� */
	rCON &= ~(1<<13);		/* �ر��Զ�ˢ�¹��� */
	
	rCON |= (1<<12);		/* ��timer2��ʱ����Ҫ�Ȱ������Ķ����úò��ܿ� */  
	
}

void buzzer_init(void)
{
	rGPD0CON &= ~(0xf<<0);
	rGPD0CON |= (1<<8);		// ���ó�outputģʽ
	rGPD0DAT |= (1<<2);		// ����ߵ�ƽ
}

void buzzer_on(void)
{
	//rGPD0CON &= ~(0xf<<8);		/* ���� */
	//rGPD0CON |= (2<<8);			/* ��ֵ */	
	rGPD0DAT |= (1<<2);
}


// �ط���������TCON�أ�GPIO��
void buzzer_off(void)
{
	//rGPD0CON &= ~(0xf<<8);		/* ���� */
	//rGPD0CON |= (0<<8);			/* ��ֵ */	
	rGPD0DAT &= ~(1<<2);
}

 




















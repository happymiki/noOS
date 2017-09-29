
#define		WTCON		(0xE2700000)
#define		WTDAT		(0xE2700004)
#define		WTCNT		(0xE2700008)
#define		WTCLRINT	(0xE270000C)

#define 	rWTCON		(*(volatile unsigned int *)WTCON)
#define 	rWTDAT		(*(volatile unsigned int *)WTDAT)
#define 	rWTCNT		(*(volatile unsigned int *)WTCNT)
#define 	rWTCLRINT	(*(volatile unsigned int *)WTCLRINT)



/* WDT���жϴ������ */
void isr_wdt(void)
{
	static int i = 0; 
	/* ���Ź���ʱ��ʱ�䵽��һ����������������� */
	printf("wdt interrupt.i = %d...\r\n",i++);
	
	/* ���ж� */
	intc_clearvectaddr();		/* ϵͳ���ж� */
	rWTCLRINT = 1;				/* ���Ź����ж� */
}
/* ��ʼ��WDT��ʹ֮���Բ����ж� */
void wdt_init_interrupt(void)
{
	/* ��һ��������Ԥ��Ƶ�� */
	rWTCON &= ~(0xff<<8);
	rWTCON |= (65<<8);		/* 1MHz */

	/* �ڶ��������÷�Ƶ�� */
	rWTCON &= ~(3<<3);
	rWTCON |= (3<<3);		/* 1/128 MHz��T = 128us */
	
	/* �������������жϺ͸�λ�Ŀ��أ�ʹ���жϣ���ֹ��λ */
	rWTCON |= (1<<2);		/* enable wdt interrupt */
	rWTCON &= ~(1<<0);		/* disable wdt reset */

	/* ���Ĳ������ö�ʱʱ�� */
	/* WDT��ʱ�ļ������������ն�ʱʱ��Ϊ�����ֵ*ʱ������ */
	rWTDAT = 10000;			/* ��ʱ1.28s */
	rWTCNT = 10000;			/* ��ʱ1.28s */

	/* ��ʵWTDAT�е�ֵ�ǲ����Զ�ˢ��WTCNT��ȥ���������ʾ����WTCON�е�ֵ������ֵ����
		Ĭ��ֵ��Ȼ�������Ĭ��ֵ��ʼ�������������ʱ��ȽϾã������ʾ��������WTCNT
		��WTDATһ����ֵ�����һ�ζ�ʱ��ֵ�ͺͺ���һ����*/
	//rWTDAT = 10000;			/* ��ʱ1.28s */
	//rWTCNT = 10000;			/* ��ʱ1.28s */
	
	/* ��ʵWTDAT�е�ֵ�ǲ����Զ�ˢ��WTCNT��ȥ���������ʾ����WTCON�е�ֵ������ֵ����
		Ĭ��ֵ��Ȼ�������Ĭ��ֵ��ʼ�������������ʱ��ȽϾã������ʾ��������WTCNT
		��WTDATһ����ֵ�����һ�ζ�ʱ��ֵ�ͺͺ���һ����*/
	rWTDAT = 10000;			/* ��ʱ1.28s */
	//rWTCNT = 10000;			/* ��ʱ1.28s */
	/* ���岽���Ȱ����мĴ������ú�֮��ſ����Ź� */
	rWTCON |= (1<<5);		/* enable wdt */
	
}



















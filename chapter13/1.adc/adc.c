#include "adc.h"

/* ��һ����ʱҪȷʵ����ʱ
   �ڶ�����ʱʱ��������*/
   
static void delay(void)
{
	volatile unsigned int i,j;
	
	for (i=0; i<8000; i++)
		for (j=0; j<1000; j++);
	
}

/* ��ʼ��ADC������ */
void adc_init(void)
{
	/* resolution set to 12bit */
	rTSADCCON0 |= (1<<16);
	
	/* enable clock prescaler */
	rTSADCCON0 |= (1<<14);
	
	/* convertor clock = 66/66M = 1MHZ ,MSPS = 200KHZ */
	rTSADCCON0 &= ~(0xFF<<6);
	rTSADCCON0 |= (65<<6);
	
	/* nornal aperation mode */
	rTSADCCON0 &= ~(1<<2);

	/* disable strat by read */
	rTSADCCON0 &= ~(1<<1);
	
	/* MUX set ADCIN0 */
	rADCMUX &= ~(0x0f<<0);
}


/* ����ADC,���ѭ�����ADC���õ�ADCת����ֵ����ӡ���� */
void adc_test(void)
{
	unsigned int val = 0;
	while (1)
	{
		/* ��һ�����ֹ�����ADCת�� */
		rTSADCCON0 |= (1<<0);
		
		/* �ڶ������ȴ�ADCת����� */
		while (!(rTSADCCON0 & (1<<15)));
		
		/* ����������ȡADC����ֵ */
		val = rTSDATX0;
		printf("X: bit14 = %d.\r\n",(val & (1<<14)));
		printf("X: adc value = %d\r\n",(val & (0xFFF<<0)));

		val = rTSDATY0;
		printf("Y: bit14 = %d.\r\n",(val & (1<<14)));
		printf("Y: adc value = %d\r\n",(val & (0xFFF<<0)));
		
		/* ���Ĳ���������ʾADC��ֵ */
		
		
		/* ���岽����ʱ */
		delay();
	}
	
}



















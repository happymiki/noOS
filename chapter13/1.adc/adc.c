#include "adc.h"

/* 第一：延时要确实能延时
   第二：延时时间必须合适*/
   
static void delay(void)
{
	volatile unsigned int i,j;
	
	for (i=0; i<8000; i++)
		for (j=0; j<1000; j++);
	
}

/* 初始化ADC控制器 */
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


/* 测试ADC,完成循环检测ADC并得到ADC转换数值，打印出来 */
void adc_test(void)
{
	unsigned int val = 0;
	while (1)
	{
		/* 第一步：手工开启ADC转换 */
		rTSADCCON0 |= (1<<0);
		
		/* 第二步：等待ADC转换完毕 */
		while (!(rTSADCCON0 & (1<<15)));
		
		/* 第三步：读取ADC的数值 */
		val = rTSDATX0;
		printf("X: bit14 = %d.\r\n",(val & (1<<14)));
		printf("X: adc value = %d\r\n",(val & (0xFFF<<0)));

		val = rTSDATY0;
		printf("Y: bit14 = %d.\r\n",(val & (1<<14)));
		printf("Y: adc value = %d\r\n",(val & (0xFFF<<0)));
		
		/* 第四步：处理、显示ADC数值 */
		
		
		/* 第五步：延时 */
		delay();
	}
	
}



















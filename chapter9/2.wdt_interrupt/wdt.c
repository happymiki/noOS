
#define		WTCON		(0xE2700000)
#define		WTDAT		(0xE2700004)
#define		WTCNT		(0xE2700008)
#define		WTCLRINT	(0xE270000C)

#define 	rWTCON		(*(volatile unsigned int *)WTCON)
#define 	rWTDAT		(*(volatile unsigned int *)WTDAT)
#define 	rWTCNT		(*(volatile unsigned int *)WTCNT)
#define 	rWTCLRINT	(*(volatile unsigned int *)WTCLRINT)



/* WDT的中断处理程序 */
void isr_wdt(void)
{
	static int i = 0; 
	/* 看门狗定时器时间到了一个做的有意义的事情 */
	printf("wdt interrupt.i = %d...\r\n",i++);
	
	/* 清中断 */
	intc_clearvectaddr();		/* 系统清中断 */
	rWTCLRINT = 1;				/* 看门狗清中断 */
}
/* 初始化WDT，使之可以产生中断 */
void wdt_init_interrupt(void)
{
	/* 第一步：设置预分频器 */
	rWTCON &= ~(0xff<<8);
	rWTCON |= (65<<8);		/* 1MHz */

	/* 第二步：设置分频器 */
	rWTCON &= ~(3<<3);
	rWTCON |= (3<<3);		/* 1/128 MHz，T = 128us */
	
	/* 第三步：设置中断和复位的开关：使能中断，禁止复位 */
	rWTCON |= (1<<2);		/* enable wdt interrupt */
	rWTCON &= ~(1<<0);		/* disable wdt reset */

	/* 第四步：设置定时时间 */
	/* WDT定时的计数个数，最终定时时间为这里的值*时钟周期 */
	rWTDAT = 10000;			/* 定时1.28s */
	rWTCNT = 10000;			/* 定时1.28s */

	/* 其实WTDAT中的值是不会自动刷到WTCNT中去，如果不显示设置WTCON中的值，它的值就是
		默认值，然后以这个默认值开始计数，所以这个时间比较久，如果显示的设置了WTCNT
		和WTDAT一样的值，则第一次定时的值就和后面一样了*/
	//rWTDAT = 10000;			/* 定时1.28s */
	//rWTCNT = 10000;			/* 定时1.28s */
	
	/* 其实WTDAT中的值是不会自动刷到WTCNT中去，如果不显示设置WTCON中的值，它的值就是
		默认值，然后以这个默认值开始计数，所以这个时间比较久，如果显示的设置了WTCNT
		和WTDAT一样的值，则第一次定时的值就和后面一样了*/
	rWTDAT = 10000;			/* 定时1.28s */
	//rWTCNT = 10000;			/* 定时1.28s */
	/* 第五步：先把所有寄存器设置好之后才开看门狗 */
	rWTCON |= (1<<5);		/* enable wdt */
	
}



















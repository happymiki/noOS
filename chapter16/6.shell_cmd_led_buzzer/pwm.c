
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

/* 初始化PWM timer2,使其输出一个PWM波形，频率为2kHZ,duty（占空比）为50% */
void timer2_pwm_init(void)
{
	/* 设置GPD0_2引脚，将其配置为XpwmTOUT_2 */
	rGPD0CON &= ~(0xf<<8);		/* 清零 */
	rGPD0CON |= (2<<8);			/* 赋值 */
	
	/* 设置PWM定时器的若干寄存器，使其工作 */ 
	/* 设置预分频器的寄存器 */
	rTCFG0 &= ~(0xff<<8);		/* 清零 */
	rTCFG0 |= (65<<8);			/* prescaler1 = 65,预分频之后频率为1Hz */
	
	/* 设置分频器的寄存器 */
	rTCFG1 &= ~(0xf<<8);		/* 清零 */
	rTCFG1 |= (1<<8);			/* MUX2设置为1/2分频，分频后时钟周期为500kHz */
	
	/* 时钟设置好之后，时钟周期为500kHz，对应的时钟周期为2us，也就是每隔2us计一次数
	   如果要定的时间是x，则TCNTB中应该写入x/2us */
	
	rCON |= (1<<15);		/* 使能Auto Reload，反复进行重装载定时，才能发出PWM波形 */
	rTCNTB2 = 250;			/* 0.5ms/2us = 500us/2us = 250 */
	rTCMPB2 = 125;			/* duty = 50% */
	
	/* 第一次需要手工将TCNTB中的值刷新到TCNT中去，以后就可以auto-reload了 */
	rCON |= (1<<13);		/* 打开自动刷新功能 */
	rCON &= ~(1<<13);		/* 关闭自动刷新功能 */
	
	rCON |= (1<<12);		/* 开timer2定时器，要先把其他的都设置好才能开 */  
	
}

void buzzer_init(void)
{
	rGPD0CON &= ~(0xf<<0);
	rGPD0CON |= (1<<8);		// 设置成output模式
	rGPD0DAT |= (1<<2);		// 输出高电平
}

void buzzer_on(void)
{
	//rGPD0CON &= ~(0xf<<8);		/* 清零 */
	//rGPD0CON |= (2<<8);			/* 赋值 */	
	rGPD0DAT |= (1<<2);
}


// 关蜂鸣器，在TCON关，GPIO关
void buzzer_off(void)
{
	//rGPD0CON &= ~(0xf<<8);		/* 清零 */
	//rGPD0CON |= (0<<8);			/* 赋值 */	
	rGPD0DAT &= ~(1<<2);
}

 




















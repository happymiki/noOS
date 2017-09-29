#include "rtc.h"

#define 	RTC_BASE	 (0xE2800000)
#define		rINTP      	 (*((volatile unsigned long *)(RTC_BASE + 0x30)))
#define		rRTCCON    	 (*((volatile unsigned long *)(RTC_BASE + 0x40)))
#define		rTICCNT    	 (*((volatile unsigned long *)(RTC_BASE + 0x44)))
#define		rRTCALM    	 (*((volatile unsigned long *)(RTC_BASE + 0x50)))
#define		rALMSEC    	 (*((volatile unsigned long *)(RTC_BASE + 0x54)))
#define		rALMMIN    	 (*((volatile unsigned long *)(RTC_BASE + 0x58)))
#define		rALMHOUR  	 (*((volatile unsigned long *)(RTC_BASE + 0x5c)))
#define		rALMDATE     (*((volatile unsigned long *)(RTC_BASE + 0x60)))
#define		rALMMON    	 (*((volatile unsigned long *)(RTC_BASE + 0x64)))
#define		rALMYEAR  	 (*((volatile unsigned long *)(RTC_BASE + 0x68)))
#define		rRTCRST      (*((volatile unsigned long *)(RTC_BASE + 0x6c)))
#define		rBCDSEC    	 (*((volatile unsigned long *)(RTC_BASE + 0x70)))
#define		rBCDMIN   	 (*((volatile unsigned long *)(RTC_BASE + 0x74)))
#define		rBCDHOUR     (*((volatile unsigned long *)(RTC_BASE + 0x78)))
#define		rBCDDATE     (*((volatile unsigned long *)(RTC_BASE + 0x7c)))
#define		rBCDDAY      (*((volatile unsigned long *)(RTC_BASE + 0x80)))
#define		rBCDMON      (*((volatile unsigned long *)(RTC_BASE + 0x84)))
#define		rBCDYEAR     (*((volatile unsigned long *)(RTC_BASE + 0x88)))
#define		rCURTICCNT   (*((volatile unsigned long *)(RTC_BASE + 0x90)))
#define		rRTCLVD    	 (*((volatile unsigned long *)(RTC_BASE + 0x94)))



/* 函数功能：把十进制的num转成BCD码，譬如把56转成0x56 */
static unsigned int num_to_bcd (unsigned int num)
{
	unsigned int shi,ge,bcd;
	
	/* 第一步：把56拆分成5和6 */
	shi = num / 10;
	ge = num % 10;
	
	/* 第二步：把5和6组合成0x56 */
	bcd = ((shi<<4) | ge);
	
	return bcd;
}

/* 函数功能：把十进制的BCD转成十进制，譬如把0x56转成56 */
static unsigned int bcd_to_num (unsigned int bcd)
{
	unsigned int shi,ge,num;
	
	/* 第一步：把0x56拆分成5和6 */
	shi = (bcd & (0xf0))>>4;
	ge = bcd & (0x0f);
	
	/* 第二步：把5和6组合成56 */
	num = (shi*10) + ge;
	
	return num;
}


void rtc_set_time(const RTC_TIME *rtc)
{
	unsigned int year_base = 2000;
	/* 第一步：打开RTC的读写开关 */
	rRTCCON |= (1<<0); 
	
	/* 第二步：写RTC的时间寄存器 */
	rBCDYEAR = num_to_bcd(rtc->year - year_base);
	rBCDMON = num_to_bcd(rtc->month);
	rBCDDATE = num_to_bcd(rtc->date);
	rBCDHOUR = num_to_bcd(rtc->hour);
	rBCDMIN = num_to_bcd(rtc->minute);
	rBCDSEC = num_to_bcd(rtc->second);
	rBCDDAY = num_to_bcd(rtc->day);
	
	/* 最后一步：关闭RTC的读写开关 */
	rRTCCON &= ~(1<<0);
}


void rtc_get_time(RTC_TIME *rtc)
{
	unsigned int year_base = 2000;
	/* 第一步：打开RTC的读写开关 */
	rRTCCON |= (1<<0); 
	
	/* 第二步：读RTC的时间寄存器 */
	rtc->year = bcd_to_num(rBCDYEAR) + year_base;
	rtc->month = bcd_to_num(rBCDMON);
	rtc->date = bcd_to_num(rBCDDATE);
	rtc->hour = bcd_to_num(rBCDHOUR);
	rtc->minute = bcd_to_num(rBCDMIN);
	rtc->second = bcd_to_num(rBCDSEC);
	rtc->day = bcd_to_num(rBCDDAY);
	
	/* 最后一步：关闭RTC的读写开关 */
	rRTCCON &= ~(1<<0);
}

void rtc_set_alarm(void)
{
	rALMSEC = num_to_bcd(23);
	
	rRTCALM |= 1<<0;
	rRTCALM |= 1<<6;
}

void isr_rtc_alarm(void)
{
	static int i = 0;
	
	/*  */
	printf("rtc alarm i=%d...\r\n",i++);
	
	/* 清中断 */
	rINTP |= (1<<1);
	
	intc_clearvectaddr();
	
	
}





















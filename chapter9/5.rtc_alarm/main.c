#include "stdio.h"
#include "interrupt.h"
#include "wdt.h"
#include "uart.h"
#include "rtc.h"

void delay(void)
{
	volatile int i,j;
	for (i=0; i<1000; i++)
		for (j=0; j<2000; j++);
}

int main(void)
{
	RTC_TIME tWrite =
	{
		.year = 2016,
		.month = 3,
		.date = 23,
		.hour = 19,
		.minute = 20,
		.second = 20,
		.day = 4,
	};
	RTC_TIME tRead;
	/* 调用串口初始化函数初始化串口 */
	uart_init(); 
	

	system_init_exception();
	rtc_set_alarm();
	
	intc_setvectaddr(NUM_RTC_ALARM,isr_rtc_alarm);
	
	intc_enable(NUM_RTC_ALARM);
	
	
	printf("init successful\r\n");
	
	printf("---rtc set time test---\r\n");
	
	rtc_set_time(&tWrite);
		
	while (1)
	{
		rtc_get_time(&tRead);
		printf("The time read is:%d:%d:%d:%d:%d:%d:%d.\r\n",\
		tRead.year,tRead.month,tRead.date,tRead.hour,\
		tRead.minute,tRead.second,tRead.day);
		
		delay();
	}
	
	return 0;
} 
























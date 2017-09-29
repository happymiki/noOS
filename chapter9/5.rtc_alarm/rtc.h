#ifndef __RTC_H__
#define __RTC_H__



typedef struct rtc_time
{
	unsigned int year;
	unsigned int month;
	unsigned int date;		// ¼¸ºÅ
	unsigned int hour;
	unsigned int minute;
	unsigned int second;
	unsigned int day;		// ÐÇÆÚ¼¸
}RTC_TIME;

void rtc_set_time(const RTC_TIME *rtc);
void rtc_get_time(RTC_TIME *rtc);
void isr_rtc_alarm(void);
void rtc_set_alarm(void);











#endif
#include "interrupt.h"
#include "stdio.h"

void reset_exception(void);
void undef_exception(void);
void soft_int_exception(void);
void prefetch_exception(void);
void data_exception(void);
void irq_handler(void);

void system_init_exception(void)
{
	r_exception_reset 	 = (unsigned int)reset_exception;
	r_exception_undef 	 = (unsigned int)undef_exception;
	r_exception_soft_int = (unsigned int)soft_int_exception;
	r_exception_prefetch = (unsigned int)prefetch_exception;
	r_exception_data 	 = (unsigned int)data_exception;
	r_exception_irq 	 = (unsigned int)IRQ_handle;
	r_exception_fiq 	 = (unsigned int)IRQ_handle;
}

void reset_exception(void) 
{
	printf("reset_exception.\r\n");
}

void undef_exception(void) 
{
	printf("undef_exception.\r\n");
}

void soft_int_exception(void) 
{
	printf("soft_int_exception.\r\n");
}

void prefetch_exception(void) 
{
	printf("prefetch_exception.\r\n");
}  

void data_exception(void) 
{
	printf("data_exception.\r\n");
}
 
// 真正的中断处理程序，只考虑中断处理，不考虑保护和恢复现场
void irq_handler(void)
{
	//printf("irq_handler.\r\n");
	// SoC支持很多个中断（2440有30多个，210有100多个）.
	// 这么多中断第一阶段走的是一条路，都会进入irq_handler
	// 识别究竟哪一个发生了中断，调用相应的中断处理程序
}


















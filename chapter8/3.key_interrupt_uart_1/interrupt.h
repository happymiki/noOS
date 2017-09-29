#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

/******************************异常基地址************************************/
#define exception_vector_table_base		(0xD0037400)	

/*****************************各类异常地址***********************************/
#define exception_reset					(exception_vector_table_base + 0x00)
#define exception_undef					(exception_vector_table_base + 0x04)
#define exception_soft_int				(exception_vector_table_base + 0x08)
#define exception_prefetch				(exception_vector_table_base + 0x0c)
#define exception_data		 			(exception_vector_table_base + 0x10)
#define exception_irq					(exception_vector_table_base + 0x18)
#define exception_fiq					(exception_vector_table_base + 0x1c)

#define r_exception_reset				(*(volatile unsigned int *)exception_reset)
#define r_exception_undef				(*(volatile unsigned int *)exception_undef)
#define r_exception_soft_int			(*(volatile unsigned int *)exception_soft_int)
#define r_exception_prefetch			(*(volatile unsigned int *)exception_prefetch)
#define r_exception_data				(*(volatile unsigned int *)exception_data) 
#define r_exception_irq					(*(vola tile unsigned int *)exception_irq)
#define r_exception_fiq					(*(volatile unsigned int *)exception_fiq)



#endif








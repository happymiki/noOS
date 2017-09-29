/*******************************包含头文件******************************/
#include "stdio.h"
#include "interrupt.h"
#include "key.h"
#include "led.h"
/*******************************GPIO寄存器地址宏定义******************************/
#define GPH0CON		0xE0200C00
#define GPH0DAT		0xE0200C04

#define GPH2CON		0xE0200C40
#define GPH2DAT		0xE0200C44

/*******************************GPIO寄存器操作宏定义******************************/
#define rGPH0CON	(*(volatile unsigned int *)GPH0CON)
#define rGPH0DAT	(*(volatile unsigned int *)GPH0DAT)

#define rGPH2CON	(*(volatile unsigned int *)GPH2CON)
#define rGPH2DAT	(*(volatile unsigned int *)GPH2DAT)

/*******************************外部中断相关寄存器地址宏定义*********************/
// 中断控制寄存器
#define EXT_INT_0_CON 	0xE0200E00
#define EXT_INT_2_CON 	0xE0200E08

// 中断的使能/禁止开关寄存器
#define EXT_INT_0_MASK  0xE0200F00
#define EXT_INT_2_MASK  0xE0200F08

// 中断挂起寄存器
#define EXT_INT_0_PEND  0xE0200F40
#define EXT_INT_2_PEND  0xE0200F48 

/*******************************外部中断相关寄存器地址宏定义*********************/
#define rEXT_INT_0_CON	(*(volatile unsigned int *)EXT_INT_0_CON)
#define rEXT_INT_2_CON	(*(volatile unsigned int *)EXT_INT_2_CON)

#define rEXT_INT_0_MASK	(*(volatile unsigned int *)EXT_INT_0_MASK)
#define rEXT_INT_2_MASK	(*(volatile unsigned int *)EXT_INT_2_MASK)

#define rEXT_INT_0_PEND	(*(volatile unsigned int *)EXT_INT_0_PEND)
#define rEXT_INT_2_PEND	(*(volatile unsigned int *)EXT_INT_2_PEND)

/**********************中断方式处理按键函数定义******************************/
void key_init_interrupt(void)
{
	// 1、设置外部中断对应的GPIO模式
	// GPH0_2 GPH0_3设置为外部中断模式
	rGPH0CON |= (0xff<<8); 
	// GPH2_0123共4个引脚设置为外部中断模式
	rGPH2CON |= (0xffff<<0);	
	
	// 2、中断触发模式设置:下降沿触发
	rEXT_INT_0_CON &= ~(0xff<<8);			// bit8~bit15全部清零
	rEXT_INT_0_CON |= ((2<<8) | (2<<12));	// 2:0010 把EXT_INT2和EXT_INT3设置为下降沿触发
	
	rEXT_INT_2_CON &= ~(0xffff<<0);
	rEXT_INT_2_CON |= ((2<<0) | (2<<4) | (2<<8) | (2<<12));
	
	// 3、中断的允许
	rEXT_INT_0_MASK &= ~(3<<2);				// 外部中断允许
	rEXT_INT_2_MASK &= ~(0x0f<<0);
	
	// 4、清挂起,写1,不是写0
	rEXT_INT_0_PEND |= (3<<2);
	rEXT_INT_2_PEND |= (0x0f<<0);
}

// EINT2通道对应的按键，就是GPH0_2引脚对应的按键，就是开发板上的LEFT的那个按键
void isr_eint2(void)
{
	// 1、中断处理代码，真正干活的代码
	printf("isr_eint2 LEFT.\r\n");
	
	// 2、清除中断挂起
	rEXT_INT_0_PEND |= (1<<2);
	intc_clearvectaddr();
}

// EINT3通道对应的按键，就是GPH0_3引脚对应的按键，就是开发板上的DOWN的那个按键
void isr_eint3(void)
{
	// 1、中断处理代码，真正干活的代码
	printf("isr_eint3 DOWN.\r\n");
	
	// 2、清除中断挂起
	rEXT_INT_0_PEND |= (1<<3);
	intc_clearvectaddr();
}

// EINT16-19通道对应的按键，就是GPH2_0-3引脚对应的按键，就是开发板上的 的那个按键
void isr_eint16_19(void)
{
	// 1、中断处理代码，真正干活的代码
	// 因为EINT16-31是共享中断，所以要在这里再次区分具体是哪个子中断
	if (rEXT_INT_2_PEND & (1<<0))
	{
		printf("eint16.\r\n");
	}
	if (rEXT_INT_2_PEND & (1<<1))
	{
		printf("eint17.\r\n");
	}
	if (rEXT_INT_2_PEND & (1<<2))
	{
		printf("eint18.\r\n");
	}
	if (rEXT_INT_2_PEND & (1<<3))
	{
		printf("eint19.\r\n");
	}
	
	// 2、清除中断挂起
	rEXT_INT_2_PEND |= (0x0f<<3);
	intc_clearvectaddr();
}

/**********************轮询方式处理案件函数定义******************************/
// 延时函数
static void delay20ms(void)
{
	 int i,j;
	 for (i=0; i<1000; i++) 
		 for(j=0; j<1000; j++);
}
// 初始化按键
void key_init(void)
{
	// 设置GPH0CON和GPH2CON寄存器，设置为输入模式
	// GPH0CON的bit8～15全部设置为0，即可
	rGPH0CON &= ~(0xff<<8); 
	// GPH2CON的bit0～15全部设置为0，即可
	rGPH2CON &= ~(0xffff<<0);
	
}

// 轮询查看按键
void key_polling(void)
{
	// 依次读出每个GPIO的值，判断其值为0（按下）还是1（弹起）。
	// 反复循环判断
	while (1)
	{
		// 按键1
		if (0 == (rGPH0DAT & (1<<2)))
		{
			delay20ms();
			if (0 == (rGPH0DAT & (1<<2)))
			{
				//延时，消抖
				
				// 为0，说明按下
				led1();
				printf("key LEFT\r\n");
			}
		}
		// 按键2
		else if (0 == (rGPH0DAT & (1<<3)))
		{
			// 为0，说明按下
			led2();
			printf("key DOWN\r\n");
		}
		// 按键3
		else if (0 == (rGPH2DAT & (1<<0)))
		{
			// 为0，说明按下
			led3();
			printf("key UP\r\n");
		}
		// 按键4
		else if (0 == (rGPH2DAT & (1<<1)))
		{
			// 为0，说明按下
			led4();
			printf("key RIGHT\r\n");
		}
		// 按键5
		else if (0 == (rGPH2DAT & (1<<2)))
		{
			// 为0，说明按下
			led5();
			printf("key BACK\r\n");
		}
		// 按键6
		else if (0 == (rGPH2DAT & (1<<3)))
		{
			// 为0，说明按下
			led6();
			printf("key MENU\r\n");
		}
		else 
		{
			led_off();
		}
	
	}
}


















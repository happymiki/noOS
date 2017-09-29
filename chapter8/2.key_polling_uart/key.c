/*******************************包含头文件******************************/
#include "stdio.h"

/*******************************GPIO寄存器地址定义******************************/
#define GPH0CON		0xE0200C00
#define GPH0DAT		0xE0200C04

#define GPH2CON		0xE0200C40
#define GPH2DAT		0xE0200C44

/*******************************GPIO寄存器操作定义******************************/
#define rGPH0CON	(*(volatile unsigned int *)GPH0CON)
#define rGPH0DAT	(*(volatile unsigned int *)GPH0DAT)

#define rGPH2CON	(*(volatile unsigned int *)GPH2CON)
#define rGPH2DAT	(*(volatile unsigned int *)GPH2DAT)

/*******************************函数定义******************************/
// 延时函数
void delay20ms(void)
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
	// GPH2CON的bit8～15全部设置为0，即可
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


















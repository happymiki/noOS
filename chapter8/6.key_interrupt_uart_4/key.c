/*******************************����ͷ�ļ�******************************/
#include "stdio.h"
#include "interrupt.h"
#include "key.h"
#include "led.h"
/*******************************GPIO�Ĵ�����ַ�궨��******************************/
#define GPH0CON		0xE0200C00
#define GPH0DAT		0xE0200C04

#define GPH2CON		0xE0200C40
#define GPH2DAT		0xE0200C44

/*******************************GPIO�Ĵ��������궨��******************************/
#define rGPH0CON	(*(volatile unsigned int *)GPH0CON)
#define rGPH0DAT	(*(volatile unsigned int *)GPH0DAT)

#define rGPH2CON	(*(volatile unsigned int *)GPH2CON)
#define rGPH2DAT	(*(volatile unsigned int *)GPH2DAT)

/*******************************�ⲿ�ж���ؼĴ�����ַ�궨��*********************/
// �жϿ��ƼĴ���
#define EXT_INT_0_CON 	0xE0200E00
#define EXT_INT_2_CON 	0xE0200E08

// �жϵ�ʹ��/��ֹ���ؼĴ���
#define EXT_INT_0_MASK  0xE0200F00
#define EXT_INT_2_MASK  0xE0200F08

// �жϹ���Ĵ���
#define EXT_INT_0_PEND  0xE0200F40
#define EXT_INT_2_PEND  0xE0200F48 

/*******************************�ⲿ�ж���ؼĴ�����ַ�궨��*********************/
#define rEXT_INT_0_CON	(*(volatile unsigned int *)EXT_INT_0_CON)
#define rEXT_INT_2_CON	(*(volatile unsigned int *)EXT_INT_2_CON)

#define rEXT_INT_0_MASK	(*(volatile unsigned int *)EXT_INT_0_MASK)
#define rEXT_INT_2_MASK	(*(volatile unsigned int *)EXT_INT_2_MASK)

#define rEXT_INT_0_PEND	(*(volatile unsigned int *)EXT_INT_0_PEND)
#define rEXT_INT_2_PEND	(*(volatile unsigned int *)EXT_INT_2_PEND)

/**********************�жϷ�ʽ��������������******************************/
void key_init_interrupt(void)
{
	// 1�������ⲿ�ж϶�Ӧ��GPIOģʽ
	// GPH0_2 GPH0_3����Ϊ�ⲿ�ж�ģʽ
	rGPH0CON |= (0xff<<8); 
	// GPH2_0123��4����������Ϊ�ⲿ�ж�ģʽ
	rGPH2CON |= (0xffff<<0);	
	
	// 2���жϴ���ģʽ����:�½��ش���
	rEXT_INT_0_CON &= ~(0xff<<8);			// bit8~bit15ȫ������
	rEXT_INT_0_CON |= ((2<<8) | (2<<12));	// 2:0010 ��EXT_INT2��EXT_INT3����Ϊ�½��ش���
	
	rEXT_INT_2_CON &= ~(0xffff<<0);
	rEXT_INT_2_CON |= ((2<<0) | (2<<4) | (2<<8) | (2<<12));
	
	// 3���жϵ�����
	rEXT_INT_0_MASK &= ~(3<<2);				// �ⲿ�ж�����
	rEXT_INT_2_MASK &= ~(0x0f<<0);
	
	// 4�������,д1,����д0
	rEXT_INT_0_PEND |= (3<<2);
	rEXT_INT_2_PEND |= (0x0f<<0);
}

// EINT2ͨ����Ӧ�İ���������GPH0_2���Ŷ�Ӧ�İ��������ǿ������ϵ�LEFT���Ǹ�����
void isr_eint2(void)
{
	// 1���жϴ�����룬�����ɻ�Ĵ���
	printf("isr_eint2 LEFT.\r\n");
	
	// 2������жϹ���
	rEXT_INT_0_PEND |= (1<<2);
	intc_clearvectaddr();
}

// EINT3ͨ����Ӧ�İ���������GPH0_3���Ŷ�Ӧ�İ��������ǿ������ϵ�DOWN���Ǹ�����
void isr_eint3(void)
{
	// 1���жϴ�����룬�����ɻ�Ĵ���
	printf("isr_eint3 DOWN.\r\n");
	
	// 2������жϹ���
	rEXT_INT_0_PEND |= (1<<3);
	intc_clearvectaddr();
}

// EINT16-19ͨ����Ӧ�İ���������GPH2_0-3���Ŷ�Ӧ�İ��������ǿ������ϵ� ���Ǹ�����
void isr_eint16_19(void)
{
	// 1���жϴ�����룬�����ɻ�Ĵ���
	// ��ΪEINT16-31�ǹ����жϣ�����Ҫ�������ٴ����־������ĸ����ж�
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
	
	// 2������жϹ���
	rEXT_INT_2_PEND |= (0x0f<<3);
	intc_clearvectaddr();
}

/**********************��ѯ��ʽ��������������******************************/
// ��ʱ����
static void delay20ms(void)
{
	 int i,j;
	 for (i=0; i<1000; i++) 
		 for(j=0; j<1000; j++);
}
// ��ʼ������
void key_init(void)
{
	// ����GPH0CON��GPH2CON�Ĵ���������Ϊ����ģʽ
	// GPH0CON��bit8��15ȫ������Ϊ0������
	rGPH0CON &= ~(0xff<<8); 
	// GPH2CON��bit0��15ȫ������Ϊ0������
	rGPH2CON &= ~(0xffff<<0);
	
}

// ��ѯ�鿴����
void key_polling(void)
{
	// ���ζ���ÿ��GPIO��ֵ���ж���ֵΪ0�����£�����1�����𣩡�
	// ����ѭ���ж�
	while (1)
	{
		// ����1
		if (0 == (rGPH0DAT & (1<<2)))
		{
			delay20ms();
			if (0 == (rGPH0DAT & (1<<2)))
			{
				//��ʱ������
				
				// Ϊ0��˵������
				led1();
				printf("key LEFT\r\n");
			}
		}
		// ����2
		else if (0 == (rGPH0DAT & (1<<3)))
		{
			// Ϊ0��˵������
			led2();
			printf("key DOWN\r\n");
		}
		// ����3
		else if (0 == (rGPH2DAT & (1<<0)))
		{
			// Ϊ0��˵������
			led3();
			printf("key UP\r\n");
		}
		// ����4
		else if (0 == (rGPH2DAT & (1<<1)))
		{
			// Ϊ0��˵������
			led4();
			printf("key RIGHT\r\n");
		}
		// ����5
		else if (0 == (rGPH2DAT & (1<<2)))
		{
			// Ϊ0��˵������
			led5();
			printf("key BACK\r\n");
		}
		// ����6
		else if (0 == (rGPH2DAT & (1<<3)))
		{
			// Ϊ0��˵������
			led6();
			printf("key MENU\r\n");
		}
		else 
		{
			led_off();
		}
	
	}
}


















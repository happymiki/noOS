/*******************************GPIO�Ĵ�����ַ����******************************/
#define GPH0CON		0xE0200C00
#define GPH0DAT		0xE0200C04

#define GPH2CON		0xE0200C40
#define GPH2DAT		0xE0200C44

/*******************************GPIO�Ĵ�����������******************************/
#define rGPH0CON	(*(volatile unsigned int *)GPH0CON)
#define rGPH0DAT	(*(volatile unsigned int *)GPH0DAT)

#define rGPH2CON	(*(volatile unsigned int *)GPH2CON)
#define rGPH2DAT	(*(volatile unsigned int *)GPH2DAT)

/*******************************��������******************************/
// ��ʼ������
void key_init(void)
{
	// ����GPH0CON��GPH2CON�Ĵ���������Ϊ����ģʽ
	// GPH0CON��bit8��15ȫ������Ϊ0������
	rGPH0CON &= ~(0xff<<8); 
	// GPH2CON��bit8��15ȫ������Ϊ0������
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
			// Ϊ0��˵������
			led1();
		}
		// ����2
		else if (0 == (rGPH0DAT & (1<<3)))
		{
			// Ϊ0��˵������
			led2();
		}
		// ����3
		else if (0 == (rGPH2DAT & (1<<0)))
		{
			// Ϊ0��˵������
			led3();
		}
		// ����4
		else if (0 == (rGPH2DAT & (1<<1)))
		{
			// Ϊ0��˵������
			led4();
		}
		// ����5
		else if (0 == (rGPH2DAT & (1<<2)))
		{
			// Ϊ0��˵������
			led5();
		}
		// ����6
		else if (0 == (rGPH2DAT & (1<<3)))
		{
			// Ϊ0��˵������
			led6();
		}
		else 
		{
			led_off();
		}
	
	}
}


















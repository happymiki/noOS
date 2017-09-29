#define GPJ0CON   0xE0200240
#define GPJ0DAT   0xE0200244

#define rGPJ0CON *((volatile unsigned int *)GPJ0CON)
#define rGPJ0DAT *((volatile unsigned int *)GPJ0DAT)

//该函数实现led闪烁
void led_blink(void)
{	
	rGPJ0CON = 0x11111111;
	
	while (1)
	{
		//led亮
		rGPJ0DAT = ((0<<3) | (0<<4) | (0<<5));
		//延时
		delay();
		//led灭
		rGPJ0DAT = ((1<<3) | (1<<4) | (1<<5));
		//延时
		delay();
	}
	return 0;
}

// 亮第1个led
void led1(void)
{
	rGPJ0CON = 0x11111111;
	rGPJ0DAT = ((0<<3) | (1<<4) | (1<<5));
}

// 亮第2个led
void led2(void)
{
	rGPJ0CON = 0x11111111;
	rGPJ0DAT = ((1<<3) | (0<<4) | (1<<5));
}

// 亮第3个led
void led3(void)
{
	rGPJ0CON = 0x11111111;
	rGPJ0DAT = ((1<<3) | (1<<4) | (0<<5));
}

// 亮第12个led
void led4(void)
{
	rGPJ0CON = 0x11111111;
	rGPJ0DAT = ((0<<3) | (0<<4) | (1<<5));
}

// 亮第23个led
void led5(void)
{
	rGPJ0CON = 0x11111111;
	rGPJ0DAT = ((1<<3) | (0<<4) | (0<<5));
}

// 亮第123个led
void led6(void)
{
	rGPJ0CON = 0x11111111;
	rGPJ0DAT = ((0<<3) | (0<<4) | (0<<5));
}
void led_off(void)
{
	rGPJ0CON = 0x11111111;
	rGPJ0DAT = ((1<<3) | (1<<4) | (1<<5));
}


void delay(void)
{
	volatile unsigned int i = 100000;		//volatile 让编译器不要优化， 
	while (i--);							//这才每次取的数都是原始值
}

#if 0
	// 第一步：把0x11111111写入0xE0200240(GPJ0CON)位置，把所有引脚设置为输出，代码不变
	ldr r0, =0x11111111			// 从“=”看出用的是ldr伪指令，需要编译器判断这个数是
	ldr r1, =GPJ0CON			// 合法立即数还是非法立即数。一般都用ldr伪指令
	str r0, [r1]				// 寄存器间接寻址，功能：把r0中的数写入到r1中的数为地址的内存中去

flag:
	// 第二步：点亮第一个
	//ldr r0, =((0<<3) | (1<<4) | (1<<5))	//相当于0b00000000，
	ldr r0, = ~(1<<3)
	ldr r1, =GPI0DAT
	str r0, [r1]				// 把0写入GPJ0DAT寄存器中断，引脚即输出低电平，LED点亮
	//延时
	bl delay					// 使用bl进行函数调用
	
	//第三步：点亮第二个
	ldr r0, = ~(1<<4)
	ldr r1, =GPI0DAT
	str r0, [r1]				// 把0写入GPJ0DAT寄存器中断，引脚即输出低电平，LED点亮
	//延时
	bl delay					// 使用bl进行函数调用

	//第四步：点亮第三个
	ldr r0, = ~(1<<5)
	ldr r1, =GPI0DAT
	str r0, [r1]				// 把0写入GPJ0DAT寄存器中断，引脚即输出低电平，LED点亮
	//延时
	bl delay					// 使用bl进行函数调用

	b flag

delay:
	ldr r2, =10000000
	ldr r3, =0x0
delay_loop:	
	sub r2, r2, #1 				//r2 = r2 - 1
	
	cmp r2,r3 					//cmp会影响CPSR寄存器的Z标志位，如果r2等于r3，则Z=1，下一句中的eq就会成立
	bne delay_loop
	mov pc, lr					//函数调用返回
#endif
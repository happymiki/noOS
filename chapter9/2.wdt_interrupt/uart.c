#include "uart.h"
/***********************各个寄存器地址宏定义**********************/

// GPA0控制寄存器地址宏定义
#define GPA0CON 	0xE0200000	

// UART配置寄存器地址宏定义
#define ULCON0		0xE2900000
#define UCON0		0xE2900004
#define UFCON0		0xE2900008
#define UMCON0		0xE290000C
#define UBRDIV0		0xE2900028
#define UDIVSLOT0	0xE290002C

// UART状态查看寄存器地址宏定义
#define UTRSTAT0 	0xE2900010
#define UTXH0		0xE2900020
#define URXH0		0xE2900024 

/************************各个寄存器操作宏定义***********************/

// GPA0控制寄存器操作宏定义
#define rGPA0CON 	(*(volatile unsigned int *)GPA0CON)

// UART配置寄存器操作宏定义
#define rULCON0		(*(volatile unsigned int *)ULCON0)
#define rUCON0		(*(volatile unsigned int *)UCON0)
#define rUFCON0		(*(volatile unsigned int *)UFCON0)
#define rUMCON0		(*(volatile unsigned int *)UMCON0)
#define rUBRDIV0	(*(volatile unsigned int *)UBRDIV0)
#define rUDIVSLOT0	(*(volatile unsigned int *)UDIVSLOT0)

// UART状态查看寄存器操作宏定义
#define rUTRSTAT0	(*(volatile unsigned int *)UTRSTAT0)
#define rUTXH0		(*(volatile unsigned int *)UTXH0)
#define rURXH0		(*(volatile unsigned int *)URXH0)

/****************************函数定义*********************************/
// 串口初始化程序
void uart_init(void)
{
	// 初始化TX和RX对应的GPIO引脚
	rGPA0CON &= ~(0xff<<0); 		// 把寄存器的bit0～7全部清零
	rGPA0CON |= 0x00000022;		// 0b0010，TX,RX
	
	// 串口配置寄存器初始化
	rULCON0  = 0x3;				//0校验位，8数据位，1停止位	
	rUCON0   = 0x5;				//发送和接收为polling mode
	rUFCON0  = 0;				//禁止FIFO模式
	rUMCON0  = 0;				//禁止流控（AFC）
	
	// 波特率设置：DIV_VAL = (PCLK/(bps x 16))-1
	// PCLK_PSYS用66MHz算得rUBRDIV0为34余0.8，rUDIVSLOT0为0xDFDD。
	// PCLK_PSYS用66.7MHz算得rUBRDIV0为35余0.18，rUDIVSLOT0为0x0888。
	// DIV_VAL = (66700000/(115200*16))-1 = 35.18
	rUBRDIV0   = 34;
	// （rUDIVSLOT0中的1的个数）/16 = 上一步计算的余数 = 0.18
	// rUDIVSLOT0中的1的个数 = 16*0.18 = 2.88 = 3
	rUDIVSLOT0 = 0xDFDD;		// 3个1，查表210芯片datasheet得知
	
}

// 串口发送程序，发送一个字节
void putc(char ch)
{
	// 串口发送一个字符，其实把1个字节写入发送缓冲区
	// 因为串口控制器发送1个字节的速度远远低于CPU的速度，
	// 所以cpu发送一个字节时必须确认串口控制器当前缓冲区为空
	// 就是串口发完了上一个字节,看发送状态寄存器bit2
	// 如果缓冲区非空则位为0，此时应该循环，直到位为1
	while (!(rUTRSTAT0 & (1<<1)));
	rUTXH0 = ch;
}

// 串口接收程序，轮询方式，接收一个字节
char getc(void)
{
	while (!(rUTRSTAT0 & (1<<0)));
	return (rURXH0 & 0x0f);
}




















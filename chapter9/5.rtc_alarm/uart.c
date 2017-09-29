#include "uart.h"
/***********************�����Ĵ�����ַ�궨��**********************/

// GPA0���ƼĴ�����ַ�궨��
#define GPA0CON 	0xE0200000	

// UART���üĴ�����ַ�궨��
#define ULCON0		0xE2900000
#define UCON0		0xE2900004
#define UFCON0		0xE2900008
#define UMCON0		0xE290000C
#define UBRDIV0		0xE2900028
#define UDIVSLOT0	0xE290002C

// UART״̬�鿴�Ĵ�����ַ�궨��
#define UTRSTAT0 	0xE2900010
#define UTXH0		0xE2900020
#define URXH0		0xE2900024 

/************************�����Ĵ��������궨��***********************/

// GPA0���ƼĴ��������궨��
#define rGPA0CON 	(*(volatile unsigned int *)GPA0CON)

// UART���üĴ��������궨��
#define rULCON0		(*(volatile unsigned int *)ULCON0)
#define rUCON0		(*(volatile unsigned int *)UCON0)
#define rUFCON0		(*(volatile unsigned int *)UFCON0)
#define rUMCON0		(*(volatile unsigned int *)UMCON0)
#define rUBRDIV0	(*(volatile unsigned int *)UBRDIV0)
#define rUDIVSLOT0	(*(volatile unsigned int *)UDIVSLOT0)

// UART״̬�鿴�Ĵ��������궨��
#define rUTRSTAT0	(*(volatile unsigned int *)UTRSTAT0)
#define rUTXH0		(*(volatile unsigned int *)UTXH0)
#define rURXH0		(*(volatile unsigned int *)URXH0)

/****************************��������*********************************/
// ���ڳ�ʼ������
void uart_init(void)
{
	// ��ʼ��TX��RX��Ӧ��GPIO����
	rGPA0CON &= ~(0xff<<0); 		// �ѼĴ�����bit0��7ȫ������
	rGPA0CON |= 0x00000022;		// 0b0010��TX,RX
	
	// �������üĴ�����ʼ��
	rULCON0  = 0x3;				//0У��λ��8����λ��1ֹͣλ	
	rUCON0   = 0x5;				//���ͺͽ���Ϊpolling mode
	rUFCON0  = 0;				//��ֹFIFOģʽ
	rUMCON0  = 0;				//��ֹ���أ�AFC��
	
	// ���������ã�DIV_VAL = (PCLK/(bps x 16))-1
	// PCLK_PSYS��66MHz���rUBRDIV0Ϊ34��0.8��rUDIVSLOT0Ϊ0xDFDD��
	// PCLK_PSYS��66.7MHz���rUBRDIV0Ϊ35��0.18��rUDIVSLOT0Ϊ0x0888��
	// DIV_VAL = (66700000/(115200*16))-1 = 35.18
	rUBRDIV0   = 34;
	// ��rUDIVSLOT0�е�1�ĸ�����/16 = ��һ����������� = 0.18
	// rUDIVSLOT0�е�1�ĸ��� = 16*0.18 = 2.88 = 3
	rUDIVSLOT0 = 0xDFDD;		// 3��1�����210оƬdatasheet��֪
	
}

// ���ڷ��ͳ��򣬷���һ���ֽ�
void putc(char ch)
{
	// ���ڷ���һ���ַ�����ʵ��1���ֽ�д�뷢�ͻ�����
	// ��Ϊ���ڿ���������1���ֽڵ��ٶ�ԶԶ����CPU���ٶȣ�
	// ����cpu����һ���ֽ�ʱ����ȷ�ϴ��ڿ�������ǰ������Ϊ��
	// ���Ǵ��ڷ�������һ���ֽ�,������״̬�Ĵ���bit2
	// ����������ǿ���λΪ0����ʱӦ��ѭ����ֱ��λΪ1
	while (!(rUTRSTAT0 & (1<<1)));
	rUTXH0 = ch;
}

// ���ڽ��ճ�����ѯ��ʽ������һ���ֽ�
char getc(void)
{
	while (!(rUTRSTAT0 & (1<<0)));
	return (rURXH0 & 0x0f);
}




















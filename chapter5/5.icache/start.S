/*
 *文件名： led.s
 *作  者： CML
 *描  述： 演示汇编开关icache
 */
 


#define WTCON     0xE2700000

#define SVC_STACK 0xD0037D80 
.global _start		// 把_start链接属性改为外部，这样其他文件能够看见
 _start:

	// 第1步：关闭看门狗（向WTCON的bit5写入0即可）
	ldr r0, =WTCON
	ldr r1, =0x0
	str r1, [r0]
	
	// 第2步：设置SVC栈
	ldr sp, =SVC_STACK 
	
	// 第3步：开或关icache
	mrc p15,0,r0,c1,c0,0;	// 读出cp15的c1到r0中
	bic r0, r0, #(0<<12)	// bit12置0 关icache
	//orr r0, r0, #(1<<12)	// bit12置1 开icache
	mcr p15,0,r0,c1,c0,0;
	
	// 之后可以调用c语言程序
	
	bl led_blink		// led_blink是c语言中的函数

// 汇编最后的死循环不能丢
	b .
 
 
 
 
 
 
 
 
 
 
 
 
 
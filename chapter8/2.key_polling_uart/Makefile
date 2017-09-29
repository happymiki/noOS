CC 		= arm-linux-gcc
LD      = arm-linux-ld
OBJCPOY = arm-linux-objcopy
OBJDUMP = arm-linux-objdump
AR		= arm-linux-ar
INCDIR 	:= $(shell pwd )
# C预处理的flag，flag就是编译器可选的选项
CPPFLAGS	:= -nostdlib -nostdinc -I$(INCDIR)/include

# C编译器的flag
CFLAGS		:= -Wall -O2 -fno-builtin

# 导出这些变量到全局，给子文件夹下的Makefile使用
export CC LD OBJCPOY OBJDUMP AR CPPFLAGS CFLAGS


objs := start.o led.o clock.o uart.o main.o key.o
objs += lib/libc.a

uart.bin: $(objs)
	${LD} -Tlink.lds -o uart.elf $^
	${OBJCPOY} -O binary uart.elf uart.bin
	${OBJDUMP} -D uart.elf > uart_elf.dis
	gcc mkv210_image.c -o mkx210
	./mkx210 uart.bin 210.bin
	
lib/libc.a:
	cd lib; make; cd ..
	
%.o : %.S
	${CC} $(CPPFLAGS) $(CFLAGS) -o $@ $< -c 

%.o : %.c
	${CC} $(CPPFLAGS) $(CFLAGS) -o $@ $< -c 

clean:
	rm *.o *.elf *.bin *.dis mkx210 -f
	cd lib; make clean; cd ..

	
	
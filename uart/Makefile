objs := head.o init.o serial.o main.o

COMPILER=arm-none-eabi-
OTHER_COMPIILER=${COMPILER)

uart.bin: $(objs)
	${COMPILER}ld -Tuart.lds -o uart_elf $^
	${COMPILER}objcopy -O binary -S uart_elf $@
	${COMPILER}objdump -D -m arm uart_elf > uart.dis
	
%.o:%.c
	${COMPILER}gcc -Wall -O2 -c -o $@ $<

%.o:%.S
	${COMPILER}gcc -Wall -O2 -c -o $@ $<

clean:
	rm -f uart.bin uart_elf uart.dis *.o		
	

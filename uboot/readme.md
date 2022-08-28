Thanks for following link to explain start.S 
https://blog.51cto.com/sviews/671827

But it didn't explain why using following line at start.S
		ldr r0, =0x33000000					//@ check link file for exact location

at uboot.lds
	. = 0x33000000;
	.text :{
		start/built-in.o
		*(.text)
	}	
Above lines in uboot.lds will make sure folder start's files (extension .S and .c) will be build
at start location 0x33000000

When mini2440 boots up if from NOR flash, it will copy first 4k code to RAM location 0x0000000
, then execute from there.

Our bootloader will looks like exceed this 4k range, so at at link file, we put start/built-in.o at top of .text section.
this will make sure no matter the bootloader size, start/built-in.o code will be run first.

start.S will initialize clock, read code from NAND, copy them(100k?) to ram, location is 0x33000000
at following line in start.S
		ldr pc, =main

it will load 'main' symbol's location which should be something like 0x33000xxx, then run from there.

Therefore, link file will have to link all code start from 0x33000000, main symbol will set to 0x33000xxx


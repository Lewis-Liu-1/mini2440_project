# mini2440_project

This project will explain mini2440 bootloader, from start to boot Linux kernel

## What is mini2440
Mini2440 is a SOC board made by friendly arm, following link has more information
http://www.friendlyarm.net/products/mini2440

It has LCD, Camera GPIO, serial, MIC input, speaker connection, SD slot, make it perfect start point for Linux learning.

It has a boot selection switch, you can first power up from NOR flash, load program to NAND flash, swith to NAND flash boot, test your program, without worrying above mess up with NAND flash.


## Getting Started

* When mini2440 boots up if from NOR flash, it will copy first 4k code to RAM location 0x0000000
, then execute from there.

* Our bootloader will looks like exceed this 4k range, so at link file uboot.lds, we put start/built-in.o at top of .text section.

```
	. = 0x33000000;
	.text :{
		start/built-in.o
		*(.text)
	}	
```

this will make sure no matter the bootloader size, start/built-in.o code will be run first.

* start.S will initialize clock, read code from NAND, copy them(100k?) to ram, location is 0x33000000

```
ldr r0, =0x33000000					//@ check link file for exact location
```

* Once nand has copy all the code to RAM, our application will from main
```
	ldr pc, =main<br/>
```
it will load 'main' symbol's location which should be something like 0x33000xxx, then run from there.

Therefore, link file will have to link all code start from 0x33000000, main symbol will set to 0x33000xxx


## Help


## Authors


## Version History

* 0.1
    * Initial Release

## License


## Acknowledgments

* [mini2440 bootloader](https://blog.51cto.com/sviews/671827)

# mini2440_project

Thanks for following link to explain start.S <br/>
https://blog.51cto.com/sviews/671827<br/>
<br/>
But it didn't explain why using following line at start.S<br/>
<code>
	ldr r0, =0x33000000					//@ check link file for exact location
</code>

at uboot.lds<br/>
<code>
	. = 0x33000000;<br/>
	.text :{<br/>
		start/built-in.o<br/>
		*(.text)<br/>
	}	<br/>
</code>
Above lines in uboot.lds will make sure folder start's files (extension .S and .c) will be build<br/>
at start location 0x33000000<br/>
<br/>
When mini2440 boots up if from NOR flash, it will copy first 4k code to RAM location 0x0000000<br/>
, then execute from there.<br/><br/>

Our bootloader will looks like exceed this 4k range, so at at link file, we put start/built-in.o at top of .text section.<br/>
this will make sure no matter the bootloader size, start/built-in.o code will be run first.<br/>
<br/>
start.S will initialize clock, read code from NAND, copy them(100k?) to ram, location is 0x33000000<br/>
at following line in start.S<br/>
	<code>
	ldr pc, =main<br/>
	</code>
it will load 'main' symbol's location which should be something like 0x33000xxx, then run from there.<br/>
<br/>
Therefore, link file will have to link all code start from 0x33000000, main symbol will set to 0x33000xxx<br/>


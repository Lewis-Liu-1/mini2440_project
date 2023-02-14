# Find project at github
u-boot-2014.04-mini2440-master

# Install toolchain 
```  
  tar xvzf arm-linux-gcc-4.4.3.tgz –C /
  gedit /root/.bashrc
  edit ~/.bashrc
  export PATH=$PATH:/opt/FriendlyARM/toolschain/4.4.3/bin
```
  
# build uboot
```
  make mini2440_config
  make
  make CROSS_COMPILE=arm-linux-
  sudo apt-get install zlib1g:i386
  make CROSS_COMPILE=arm-linux-
```
# Install uboot to mini2440
boot from NOR flash
[q] select q, into supervivi screen
```
Supervivi> load ram 0x32000000 242332 u
USB host is connected. Waiting a download.
```
From PC
```
sudo ./s3c2410_boot_usb u-boot.bin 
```
```
Now, Downloading [ADDRESS:32000000h,TOTAL:242342]
RECEIVED FILE SIZE:  242342 (236KB/S, 1S)
Downloaded file at 0x32000000, size = 242332 bytes
Supervivi> go 0x32000000
```

```nand scrub```
press n and enter

```nand createbbt```
press n and enter

```nand write 0x31000000 u-boot```


Now boot from NAND flash

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
ldr pc, =main
```
it will load 'main' symbol's location which should be something like 0x33000xxx, then run from there.

Therefore, link file will have to link all code start from 0x33000000, main symbol will set to 0x33000xxx

## Compile and Load
run make from uboot directory
```
make
```
* From mini2440 set SW2 to NOR position
* From PC, connect USB-A (next to speaker on mini2440) to PC usb slot
* Run picocom
```
picocom /dev/ttyUSB0 -b 115200
```
* Power up mini2440 by flip siwtch S1
once you have seen following print out
```##### FriendlyARM BIOS 2.0 for 2440 #####
[x] format NAND FLASH for Linux
[v] Download vivi 
[k] Download linux kernel 
[y] Download root_yaffs image 
[a] Absolute User Application
[n] Download Nboot for WinCE 
[l] Download WinCE boot-logo
[w] Download WinCE NK.bin 
[d] Download & Run 
[z] Download zImage into RAM 
[g] Boot linux from RAM 
[f] Format the nand flash 
[b] Boot the system 
[s] Set the boot parameters 
[u] Backup NAND Flash to HOST through USB(upload) 
[r] Restore NAND Flash from HOST through USB 
[q] Goto shell of vivi 
[i] Version: 1138-2K
Enter your selection:
```
press 'a' key at PC's keyboard

```
Enter your selection: a
USB host is connected. Waiting a download.
```
* From PC, at uboot folder

```
make install
```
At picocom terminal
```
Now, Downloading [ADDRESS:30000000h,TOTAL:1538]
RECEIVED FILE SIZE:    1538 (1KB/S, 1S)
Downloaded file at 0x30000000, size = 1528 bytes
Write to flash ok: skipped size = 0x0, size = 0x5f8
```
* Set SW2 switch to NAND position, power off and on mini2440
should see following print out on picocom terminal

```
**********mini-boot for mini2440**********
```
First step 'Hello world' has achieved.

** Tag v1.0 contains above code 

## Boot Linux Kernel by using above boot loader
* Now we will read Linux kernel from NAND, save it to ram location 0x30008000
* As our current bootloader running at 0x33000000, we should not mess up with ram data.
* from mini2440 find zimage_xx binaries, write to NAND by using boot from NOR flash option
```
[k] Download linux kernel 
```
* from PC, run following command

```
sudo ./s3c2410_boot_usb zImage_W35 
```
zimage will be write to NAND kernel location.

Now run following command from uboot folder on PC
```
make
make install
```
Set switch to NAND position, power off and on, now Linux will boot from NAND.

```
**********mini-boot for mini2440**********
now booting linux from nand flash ...
g_page_type: 2
Use default linux command line
load Image of Linux...

Ok
Uncompressing Linux................................................................................................................................................... done, booting the kernel.
Linux version 2.6.32.2-FriendlyARM (root@localhost.localdomain) (gcc version 4.4.3 (ctng-1.6.1) ) #18 Wed Apr 13 20:06:31 HKT 2011
CPU: ARM920T [41129200] revision 0 (ARMv4T), cr=c0007177
CPU: VIVT data cache, VIVT instruction cache
Machine: FriendlyARM Mini2440 development board
ATAG_INITRD is deprecated; please update your bootloader.
Memory policy: ECC disabled, Data cache writeback
CPU S3C2440A (id 0x32440001)
S3C24XX Clocks, (c) 2004 Simtec Electronics
S3C244X: core 400.000 MHz, memory 100.000 MHz, peripheral 50.000 MHz
CLOCK: Slow mode (1.500 MHz), fast, MPLL on, UPLL on
Built 1 zonelists in Zone order, mobility grouping on.  Total pages: 16256
Kernel command line: root=/dev/mtdblock3 console=ttySAC0,115200 mem=64M init=/linuxrc
PID hash table entries: 256 (order: -2, 1024 bytes)
Dentry cache hash table entries: 8192 (order: 3, 32768 bytes)
Inode-cache hash table entries: 4096 (order: 2, 16384 bytes)
Memory: 64MB = 64MB total
Memory: 60084KB available (4176K code, 451K data, 156K init, 0K highmem)
SLUB: Genslabs=11, HWalign=32, Order=0-3, MinObjects=0, CPUs=1, Nodes=1
Hierarchical RCU implementation.
```
Tag v2.0 will contains above code

## Help


## Authors


## Version History

* 0.1
    * Initial Release

## License


## Acknowledgments

* [mini2440 bootloader](https://blog.51cto.com/sviews/671827)

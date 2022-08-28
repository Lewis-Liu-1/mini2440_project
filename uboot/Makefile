APP=uboot

CROSS_COMPILE = arm-none-linux-gnueabi-
#arm-lwm-linux-gnueabi-
CC		= $(CROSS_COMPILE)gcc
LD		= $(CROSS_COMPILE)ld
AR		= $(CROSS_COMPILE)ar

OBJCOPY	= $(CROSS_COMPILE)objcopy
OBJDUMP	= $(CROSS_COMPILE)objdump

INCLUDEDIR	:= $(shell pwd)/include
CFLAGS		:= -Wall -O2 -nostdlib
CPPFLAGS	:= -nostdinc -fno-builtin -I$(INCLUDEDIR)

BUILT_IN_OBJ = built-in.o

export CC LD AR OBJCOPY OBJDUMP INCLUDEDIR CFLAGS CPPFLAGS

export BUILT_IN_OBJ 

SUBDIRS =  start main
# device lib app main
SUBOBJS := $(foreach n, $(SUBDIRS), $(n)/$(BUILT_IN_OBJ))

all: $(APP).bin $(APP).dis

$(APP).bin : $(APP).elf
	${OBJCOPY} -O binary -S $^ $@
$(APP).dis : $(APP).elf
	${OBJDUMP} -D -m arm $^ > $@
$(APP).elf : $(SUBOBJS)
	${LD} -T$(APP).lds -o $@ $^
	
$(SUBOBJS) : $(SUBDIRS)
	
.PHONY : $(SUBDIRS)
$(SUBDIRS) :
	@make -C $@ all
	
.PHONE : clean
clean:
	rm -f $(APP).dis $(APP).bin $(APP).elf *.o
	@for subdir in $(SUBDIRS); do \
	(make clean -C $$subdir); \
	done
	
install:
	sudo ../tool/s3c2410_boot_usb uboot.bin
objs := boot_linux.o nand_app.o head.o

all: $(BUILT_IN_OBJ)
	
$(BUILT_IN_OBJ): $(objs)
	$(LD) -r $(LDFLAGS) -o $@ $^

%.o:%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

%.o:%.S
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o

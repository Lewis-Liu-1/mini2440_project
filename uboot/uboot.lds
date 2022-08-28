ENTRY(_start)
SECTIONS
{
	. = 0x33000000;
	.text :{
		start/built-in.o
		*(.text)
	}	
	. = ALIGN(32);
	.data :{
		*(.data)
	}
	. = ALIGN(32);
	.bss :{
		*(.bss)
	}
}

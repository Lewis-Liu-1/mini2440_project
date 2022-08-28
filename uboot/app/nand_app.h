#define uint32_t unsigned int
#define uint16_t unsigned short
#define uint8_t  unsigned char

struct zboot_first_sector {
	unsigned char  dont_care[0x20];
	unsigned int   magic;
	unsigned char  os_type;
	unsigned char  has_nand_bios;
	unsigned short logo_pos;
	unsigned int   os_start;
	unsigned int   os_length;
	unsigned int   os_ram_start;
	unsigned char  linux_cmd[512 - 0x34];
}  __attribute__((packed));

#define g_magic			(first_sector.magic)
#define g_os_type		(first_sector.os_type)
#define g_has_nand_bios		(first_sector.has_nand_bios)
#define g_logo_pos		(first_sector.logo_pos)
#define g_os_start		(first_sector.os_start)
#define g_os_length		(first_sector.os_length)
#define g_os_ram_start		(first_sector.os_ram_start)
#define g_linux_cmd_line	(first_sector.linux_cmd)

extern struct zboot_first_sector first_sector;

#define OS_LINUX 0x02
#define PAGE_UNKNOWN 0
#define PAGE512      1
#define PAGE2048     2

#define BYTE_SECTOR_SHIFT   (g_page_type == PAGE512 ? 9 : 11)
#define SECTOR_BLOCK_SHIFT  (g_page_type == PAGE512 ? 5 : 6)

#define SECTOR_SIZE (1 << BYTE_SECTOR_SHIFT)
#define BLOCK_SIZE  (SECTOR_SIZE << SECTOR_BLOCK_SHIFT)

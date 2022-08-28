/*GPIO registers*/
#define GPBCON (*(volatile unsigned long *)0x56000010)
#define GPBDAT (*(volatile unsigned long *)0x56000014)

#define GPHCON (*(volatile unsigned long *)0x56000070)
#define GPHDAT (*(volatile unsigned long *)0x56000074)
#define GPHUP (*(volatile unsigned long *)0x56000078)

/*UART registers*/
#define ULCON0 (*(volatile unsigned long *)0x50000000)
#define UCON0 (*(volatile unsigned long *)0x50000004)
#define UFCON0 (*(volatile unsigned long *)0x50000008)
#define UMCON0 (*(volatile unsigned long *)0x5000000c)
#define UTRSTAT0 (*(volatile unsigned long *)0x50000010)
#define UTXH0 (*(volatile unsigned char *)0x50000020)
#define URXH0 (*(volatile unsigned char *)0x50000024)
#define UBRDIV0 (*(volatile unsigned long *)0x50000028)

unsigned char mac_addr[6] = {0x22, 0x44, 0x66, 0x88, 0x00, 0x22};
unsigned char ip_addr[4] = {192, 168, 0, 230};
unsigned char host_ip_addr[4] = {192, 168, 0, 231};
unsigned char host_mac_addr[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

unsigned char send_buffer[1024];
unsigned char recv_buffer[1024];
unsigned long send_packet_len;
unsigned long recv_packet_len;

void tftp_select(void);

#define TXD0READY (1 << 2)
#define RXD0READY (1)

void init_uart(void)
{
    GPHCON |= 0xa0; // GPH2,GPH3 used as TXD0,RXD0
    GPHUP = 0x0c;   // GPH2,GPH3禁止上拉

    ULCON0 = 0x03; // 8N1，8位数据，一位停止位，无奇偶校验
    UCON0 = 0x05;  //使用查询方式，时钟采用PCLK
    UFCON0 = 0x00; //不使用FIFO
    UMCON0 = 0x00; //不使用流控
    UBRDIV0 = 26;  //波特率为115200
}

void putc(unsigned char c)
{
    while (!(UTRSTAT0 & TXD0READY))
        ;
    UTXH0 = c;
}

void myprintf(char *str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        putc(str[i]);
        i++;
    }
}

int main(void)
{
    int num;
    init_uart(); //波特率为115200，8位数据，一位停止位，无奇偶校验，无流控

    myprintf("\n**********mini-boot for mini2440**********\n\r");
    while (1)
        ;
}
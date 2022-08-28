#include "s3c2440.h"
#include "stdio.h"
#include "serial.h"
#include "mini-boot.h"
#include "configs.h"

int main(void)
{
	//波特率为115200，8位数据，一位停止位，无奇偶校验，无流控
	init_uart();
	printf("\r\n**********mini-boot for mini2440**********\r\n");
	printf("now booting linux from nand flash ...\n\r");
	boot_linux();
	return 0;
}


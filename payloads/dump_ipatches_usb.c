#include <stdint.h>
#include "printf.h"
#include "tegra_uart.h"
#include "common.h"
#include "bootrom_usb_helper.h"

#define BOOTROM_START			0xfff00000

#if defined(T30)
    #define IROM_SIZE (48 * 1024)
#elif defined(T114)
    #define IROM_SIZE (64 * 1024)
#else
    #error No SoC specified
#endif

/* ipatch hardware */
#define IPATCH_BASE					(0x6001dc00)
#define IPATCH_SELECT				(0x0)
#define IPATCH_REGS					(0x4)

void dump_memory(uint8_t *src, uint32_t size);

void main()
{
	char buf[4096];
	//volatile uint32_t reg = 0;
	//sprintf(buf, "hello there %d; 0x%08x; %s\n", 420, 0x69, "Nope");
	//usb_transfer_data(buf, strlen(buf));

	//sprintf(buf, "Select: 0x%08x; Reg 1: 0x%08x", reg_read(IPATCH_BASE, IPATCH_SELECT), reg_read(IPATCH_BASE, IPATCH_REGS));
	//usb_transfer_data(buf, strlen(buf));
	
	
	uint32_t ipatch_select = reg_read(IPATCH_BASE, IPATCH_SELECT);
	
	int32_t counter = 0;
	while (ipatch_select & 0x1) {
		volatile uint32_t reg = reg_read(IPATCH_BASE, IPATCH_REGS + counter*4);
		//sprintf(buf, "Patch %d: 0x%08x;\n", counter, reg);
		//usb_transfer_data(buf, strlen(buf));
		
		sprintf(buf, "Patch %d; Address 0x%08x: 0x%04x;\n", counter, 0xfff00000 | ((reg >> 16)<<1), reg & 0xffff);
		usb_transfer_data(buf, strlen(buf));
		
		counter++;
		ipatch_select >>= 1;
	}
	

	while(1);
}

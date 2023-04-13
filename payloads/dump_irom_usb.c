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

#define IPATCH_BASE					(0x6001dc00)
#define IPATCH_SELECT				(0x0)

void dump_memory(uint8_t *src, uint32_t size);

void main()
{
	reg_write(IPATCH_BASE, IPATCH_SELECT, 0x0);
	usb_transfer_data((void*)BOOTROM_START, IROM_SIZE);

	while(1);
}

#include <stdint.h>
#include "common.h"

#define PINMUX_BASE					(0x70003000)
/* uart-a tx */
#define PINMUX_AUX_SDMMC3_DAT1_0 			(0x39c)
/* uart-a rx */
#define PINMUX_AUX_SDMMC3_CMD_0			(0x394)

#define BOOTROM_START			0xfff00000
#define BOOTROM_SIZE_T114		0x10000

void send_zero();
void send_one();
void send_byte(uint8_t b);

void main()
{
	send_byte(0x55);
	send_byte(0x55);
	send_byte(0x55);
	send_byte(0x55);
	
	uint8_t *irom_base = (uint8_t*)BOOTROM_START;
	for (uint32_t i = 0; i < BOOTROM_SIZE_T114; i++) {
		send_byte(irom_base[i]);
		
		// give uart some time to synchronize in case timing is a bit of.
		for (int i = 0; i < 216000000 / 216 / 55 * 4; i++) {;}
	}
	
	// incdicate clear end of the bootrom
	uint8_t counter = 0;
	for (uint8_t i = 0; i < 256 ; i++){
		send_byte(counter);
		for (int i = 0; i < 6000000; i++) {;}
	}
	
	while(1) { ; }
}

/**
 * This send at ~600 Baud
 */
void send_byte(uint8_t b) {
	// start bit
	send_zero();
	for (int i = 0; i < 216000000 / 216 / 55; i++) {;}
	
	// data - LSB first
	for (uint32_t i = 0; i < 8; i++) {
		if (b & 1) {
			send_one();
		} else {
			send_zero();
		}
		b >>= 1;
		for (int i = 0; i < 216000000 / 216 / 55; i++) {;}
	}
	
	// 1 stop bit
	send_one();
	for (int i = 0; i < 216000000 / 216 / 55; i++) {;}
}

void send_zero() {
	reg_write(PINMUX_BASE, PINMUX_AUX_SDMMC3_DAT1_0, 0b00000100); /* tx */
	reg_write(PINMUX_BASE, PINMUX_AUX_SDMMC3_CMD_0, 0b00100100); /* rx */
}

void send_one() {
	reg_write(PINMUX_BASE, PINMUX_AUX_SDMMC3_DAT1_0, 0b00000110); /* tx */
	reg_write(PINMUX_BASE, PINMUX_AUX_SDMMC3_CMD_0, 0b00100110); /* rx */
}

#include "bootrom_usb_helper.h"



void usb_transfer_data(void* data, uint32_t size) {
	uint32_t ret = 0;
	
	void (*write_ep1)(uint32_t*, uint32_t, uint32_t*) = (void (*)(uint32_t*, uint32_t, uint32_t*))write_ep1_in_sync;
	write_ep1(data, size, &ret);

	void (*usb_reset)(uint32_t, uint32_t) = (void (*)(uint32_t, uint32_t))usb_reset_ep1;
	usb_reset(0, 1);

}

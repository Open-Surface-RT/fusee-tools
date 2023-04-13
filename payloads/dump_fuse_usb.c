#include <stdint.h>
#include "size.h"
#include "bootrom_usb_helper.h"
/*
#if defined(T30)
    #define write_ep1_in_sync (0xFFF05092 + 1)
    #define usb_reset_ep1 (0xFFF04996 + 1)
    #define IROM_SIZE (48 * 1024)
#elif defined(T114)
    #define write_ep1_in_sync (0xfff06ccc + 1)
    #define usb_reset_ep1 (0xfff0679e + 1)
    #define IROM_SIZE (64 * 1024)
#else
    #error No SoC specified
#endif
*/

#if defined(T30)
    #define write_ep1_in_sync (0xFFF05092 + 1)
    #define usb_reset_ep1 (0xFFF04996 + 1)
    #define IROM_SIZE (48 * 1024)
#elif defined(T114)
    #define write_ep1_in_sync (0xfff06ccc + 1)
    #define usb_reset_ep1 (0xfff0679e + 1)
    #define IROM_SIZE (64 * 1024)
#else
    #error No SoC specified
#endif

// Tegra common
#define IROM_START 0xfff00000U


#define IPATCH_BASE 0x6001dc00U


#define FUSE_BASE 0x7000f800U

//void transfer_data(void *data, uint32_t size);

int main() {
	
	char str[] = "Hello, this is a message from Surface 2 :)";
	
	usb_transfer_data(str, sizeof(str));
	
	usb_transfer_data((void*)FUSE_BASE, SZ_1K);
/*
	for (int i = 0; i < 2; i++) {
		transfer_data((uint32_t*)(IROM_START+i*0x1000), 0x1000);
	}	
*/	
	
	while(1);
	
	return 0;
}

/*
void transfer_data(void* data, uint32_t size) {
	uint32_t ret = 0;
	
	void (*write_ep1)(uint32_t*, uint32_t, uint32_t*) = (void (*)(uint32_t*, uint32_t, uint32_t*))write_ep1_in_sync;
	write_ep1(data, size, &ret);

	void (*usb_reset)(uint32_t, uint32_t) = (void (*)(uint32_t, uint32_t))usb_reset_ep1;
	usb_reset(0, 1);

}
*/

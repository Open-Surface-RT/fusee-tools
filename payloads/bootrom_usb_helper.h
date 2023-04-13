#ifndef BOOTROM_USB_H
#define BOOTROM_USB_H

#include "size.h"
#include <stdint.h>

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

void usb_transfer_data(void *data, uint32_t size);


#endif

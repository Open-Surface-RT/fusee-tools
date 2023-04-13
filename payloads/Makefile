CROSS_COMPILE = arm-none-eabi-

# Use our cross-compile prefix to set up our basic cross compile environment.
CC      = $(CROSS_COMPILE)gcc
LD      = $(CROSS_COMPILE)ld
OBJCOPY = $(CROSS_COMPILE)objcopy

CFLAGS = \
	-mtune=arm7tdmi \
	-mlittle-endian \
	-fno-stack-protector \
	-fno-common \
	-fno-builtin \
	-ffreestanding \
	-std=gnu99 \
	-Werror \
	-Wall \
	-Wno-error=unused-function \
	-fomit-frame-pointer \
	-g \
	-O0

LDFLAGS = -nostdlib -L /usr/lib/gcc/arm-none-eabi/9.2.1 -lgcc
#-Map=$(basename $@).map

OBJS = tegra_uart.o printf.o

#OBJS_T20	= T20_bootrom_usb_helper.o
OBJS_T30	= T30_bootrom_usb_helper.o
OBJS_T114	= T114_bootrom_usb_helper.o
#OBJS_T124	= T124_bootrom_usb_helper.o

#T20_ENTRY_POINT_ADDRESS	:= 0x40008000
T30_ENTRY_POINT_ADDRESS	:= 0x4000A000
T114_ENTRY_POINT_ADDRESS	:= 0x4000E000
#T124_ENTRY_POINT_ADDRESS	:= 0x4000E000


all: 	T30_dump_fuse_usb.bin		T114_dump_fuse_usb.bin		\
	T30_dump_ipatches_usb.bin	T114_dump_ipatches_usb.bin	\
	T30_dump_irom_usb.bin		T114_dump_irom_usb.bin		\
	T30_patch_irom.bin		T114_patch_irom.bin		\
	T30_dump_irom_uart.bin		T114_dump_irom_uart.bin	\


T30_%.bin: T30_%.elf
	$(OBJCOPY) -v -O binary $< $@

T30_%.elf: T30_%.o $(OBJS) $(OBJS_T30)
	$(LD) $^ -T common.lds --defsym LOAD_ADDR=$(T30_ENTRY_POINT_ADDRESS) $(LDFLAGS) -o $@

T30_%.o: CFLAGS += -DT30
T30_%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@



T114_%.bin: T114_%.elf
	$(OBJCOPY) -v -O binary $< $@

T114_%.elf: T114_%.o $(OBJS) $(OBJS_T114)
	$(LD) $^ -T common.lds --defsym LOAD_ADDR=$(T114_ENTRY_POINT_ADDRESS) $(LDFLAGS) -o $@

T114_%.o: CFLAGS += -DT114
T114_%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm -f *.o *.elf *.bin *.map

.PHONY: all clean

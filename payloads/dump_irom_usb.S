// USB IROM dumper

#define T114

#if defined(T30)
    #define write_ep1_in_sync (0xFFF05092 + 1)
    #define usb_reset_ep1 (0xFFF04996 + 1)
    #define IROM_SIZE (48 * 1024)
#elif defined(T114)
    #define write_ep1_in_sync (0xfff06ccc + 1)
    #define usb_reset_ep1 (0xfff0679e + 1)
    #define IROM_SIZE (64 * 1024)
#endif

// Tegra common
#define IROM_START 0xfff00000

// Options
#define SAY_HELLO
#define DUMP_IROM

    .globl _start

    .section ".text"
_start:

#ifdef SAY_HELLO
    ldr r0, =hello_str
    mov r1, #hello_str_len
    sub r2, sp, #4
    sub sp, sp, #4
    ldr ip, =write_ep1_in_sync
    mov lr, pc
    bx ip
    add sp, sp, #4
    mov r0, #0
    mov r1, #1
    ldr ip, =usb_reset_ep1
    mov lr, pc
    bx ip
#endif

#ifdef DUMP_IROM
    // TODO A loop is needed here. IROM_SIZE
    // Currently you can set to 0xFFF0:0000, 0xFFF0:1000, 0xFFF0:2000, ... and dump parts of the IROM.
    ldr r0, =#0xFFF00000
    ldr r1, =#0x1000
    sub r2, sp, #4
    sub sp, sp, #4
    ldr ip, =write_ep1_in_sync
    mov lr, pc
    bx ip
    add sp, sp, #4
    mov r0, #0
    mov r1, #1
    ldr ip, =usb_reset_ep1
    mov lr, pc
    bx ip
#endif

L_spin:
    b L_spin


#ifdef SAY_HELLO
    .globl  hello_str
    .type   hello_str, %object
    .size   hello_str, Lhello_str_end - hello_str
    .align 4
hello_str:
    .asciz "hello, world\n"
Lhello_str_end:
    .equ    hello_str_len, . - hello_str
#endif

    .ltorg

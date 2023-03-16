// USB AES-SBK dumper

#define T114

#if defined(T30)
    #error Not ready for T30
    #define write_ep1_in_sync (0xFFF05092 + 1)
    #define usb_reset_ep1 (0xFFF04996 + 1)
    #define get_security_mode // TODO
#elif defined(T114)
    #define write_ep1_in_sync (0xfff06ccc + 1)
    #define usb_reset_ep1 (0xfff0679e + 1)
    #define get_security_mode (0xfff0228c + 1)
#endif

// Tegra common
#define FUSE_PRIVATE_KEY0 0x7000F9A4
#define FUSE_PRIVATE_KEY4 0x7000F9B4
#define SBK_DUMP_SIZE (FUSE_PRIVATE_KEY4 - FUSE_PRIVATE_KEY0 + 4)

// Options
#define SAY_HELLO
#define DUMP_SBK
//#define DUMP_SECURE_MODE

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

#ifdef DUMP_SBK
    sub sp, sp, #SBK_DUMP_SIZE
    mov r0, sp
    ldr r1, =#FUSE_PRIVATE_KEY0
    mov r2, #SBK_DUMP_SIZE
    bl copy
    mov r0, sp
    mov r1, #SBK_DUMP_SIZE
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

#ifdef DUMP_SECURE_MODE
    sub sp, sp, #4
    mov r0, sp
    // call bootrom function
    ldr ip, =get_security_mode
    mov lr, pc
    bx ip
    
    mov r0, sp
    mov r1, #4
    sub sp, sp, #4
    mov r2, sp
    ldr ip, =write_ep1_in_sync
    mov lr, pc
    bx ip
    add sp, sp, #8
#endif

L_spin:
    b L_spin


#if defined(DUMP_SBK)
//
// Simple block copy.
//   r0 = destination address
//   r1 = source address
//   r2 = length in bytes
// Destroys r0-r3.
//
    .globl copy
copy:

    // Copy the word...
    ldr r3, [r1], #4
    str r3, [r0], #4

    // And continue while we have words left to copy.
    subs r2, r2, #4
    bne copy

    // Once we're done, return.
    bx lr
#endif

    .global x32_to_str
    .type   x32_to_str, %function
x32_to_str:
    add r2, r0, #8
.Lnibble_loop:
    mov r3, r1, lsr #28
    cmp r3, #9
    addls   r3, r3, #48
    addhi   r3, r3, #55
    strb    r3, [r0]
    add r0, r0, #1
    cmp r0, r2
    mov r1, r1, asl #4
    bne .Lnibble_loop
    bx  lr

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

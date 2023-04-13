#ifndef PRINTF_H
#define PRINTF_H

#include <stdint.h>

typedef unsigned long size_t;


typedef long ssize_t;
/*
#ifdef __64BIT__
typedef unsigned long long uintmax_t;
typedef long long intmax_t;
#else
typedef unsigned int uintmax_t;
typedef int intmax_t;
#endif
*/

typedef unsigned char u_char;

typedef unsigned int u_int;
typedef unsigned long u_long;
typedef unsigned short u_short;
typedef unsigned long long u_quad_t;
typedef long long quad_t;
//typedef unsigned long uintptr_t;
typedef long ptrdiff_t;


size_t strlen(const char *s);

void printf(const char *fmt, ...);
void sprintf(char *buffer, const char *fmt, ...);

#endif

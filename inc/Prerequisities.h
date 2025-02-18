#pragma once

 // String types.

/** @brief string */
typedef char* s;

/** @brief const string */
typedef const char* cs;

// Unsigned int types.

/** @brief Unsigned 8-bit integer */
typedef unsigned char u8;

/** @brief Unsigned 16-bit integer */
typedef unsigned short u16;

/** @brief Unsigned 32-bit integer */
typedef unsigned int u32;

/** @brief Unsigned 64-bit integer */
typedef unsigned long long u64;

// Signed int types.

/** @brief Signed 8-bit integer */
typedef signed char i8;

/** @brief Signed 16-bit integer */
typedef signed short i16;

/** @brief Signed 32-bit integer */
typedef signed int i32;

/** @brief Signed 64-bit integer */
typedef signed long long i64;

// Floating point types

/** @brief 32-bit floating point number */
typedef float f32;

/** @brief 64-bit floating point number */
typedef double f64;

// Boolean types

/** @brief 32-bit boolean type, used for APIs which require it */
typedef int b32;

/** @brief 8-bit boolean type */
typedef char b8;

/** @brief 8-bit bool */
typedef union vb8 {
  u8 data;
  struct {
    u8 b0 : 1;  // bit 0
    u8 b1 : 1;  // bit 1
    u8 b2 : 1;  // bit 2
    u8 b3 : 1;  // bit 3
    u8 b4 : 1;  // bit 4
    u8 b5 : 1;  // bit 5
    u8 b6 : 1;  // bit 6
    u8 b7 : 1;  // bit 7
  };
} vb8;

/** @brief 16-bit bool */
typedef union vb16 {
  u16 data;
  struct {
    u16 b0  : 1;  // bit 0
    u16 b1  : 1;  // bit 1
    u16 b2  : 1;  // bit 2
    u16 b3  : 1;  // bit 3
    u16 b4  : 1;  // bit 4
    u16 b5  : 1;  // bit 5
    u16 b6  : 1;  // bit 6
    u16 b7  : 1;  // bit 7
    u16 b8  : 1;  // bit 8
    u16 b9  : 1;  // bit 9
    u16 b10 : 1;  // bit 10
    u16 b11 : 1;  // bit 11
    u16 b12 : 1;  // bit 12
    u16 b13 : 1;  // bit 13
    u16 b14 : 1;  // bit 14
    u16 b15 : 1;  // bit 15
  };
} vb16;

/** @brief 32-bit bool */
typedef union vb32 {
  u32 data;
  struct {
    u32 b0  : 1;  // bit 0
    u32 b1  : 1;  // bit 1
    u32 b2  : 1;  // bit 2
    u32 b3  : 1;  // bit 3
    u32 b4  : 1;  // bit 4
    u32 b5  : 1;  // bit 5
    u32 b6  : 1;  // bit 6
    u32 b7  : 1;  // bit 7
    u32 b8  : 1;  // bit 8
    u32 b9  : 1;  // bit 9
    u32 b10 : 1;  // bit 10
    u32 b11 : 1;  // bit 11
    u32 b12 : 1;  // bit 12
    u32 b13 : 1;  // bit 13
    u32 b14 : 1;  // bit 14
    u32 b15 : 1;  // bit 15
    u32 b16 : 1;  // bit 16
    u32 b17 : 1;  // bit 17
    u32 b18 : 1;  // bit 18
    u32 b19 : 1;  // bit 19
    u32 b20 : 1;  // bit 20
    u32 b21 : 1;  // bit 21
    u32 b22 : 1;  // bit 22
    u32 b23 : 1;  // bit 23
    u32 b24 : 1;  // bit 24
    u32 b25 : 1;  // bit 25
    u32 b26 : 1;  // bit 26
    u32 b27 : 1;  // bit 27
    u32 b28 : 1;  // bit 28
    u32 b29 : 1;  // bit 29
    u32 b30 : 1;  // bit 30
    u32 b31 : 1;  // bit 31
  };
} vb32;

/** @brief 64-bit bool */
typedef union vb64 {
    u64 data;
    struct {
        u64 b0  : 1;  // bit 0
        u64 b1  : 1;  // bit 1
        u64 b2  : 1;  // bit 2
        u64 b3  : 1;  // bit 3
        u64 b4  : 1;  // bit 4
        u64 b5  : 1;  // bit 5
        u64 b6  : 1;  // bit 6
        u64 b7  : 1;  // bit 7
        u64 b8  : 1;  // bit 8
        u64 b9  : 1;  // bit 9
        u64 b10 : 1;  // bit 10
        u64 b11 : 1;  // bit 11
        u64 b12 : 1;  // bit 12
        u64 b13 : 1;  // bit 13
        u64 b14 : 1;  // bit 14
        u64 b15 : 1;  // bit 15
        u64 b16 : 1;  // bit 16
        u64 b17 : 1;  // bit 17
        u64 b18 : 1;  // bit 18
        u64 b19 : 1;  // bit 19
        u64 b20 : 1;  // bit 20
        u64 b21 : 1;  // bit 21
        u64 b22 : 1;  // bit 22
        u64 b23 : 1;  // bit 23
        u64 b24 : 1;  // bit 24
        u64 b25 : 1;  // bit 25
        u64 b26 : 1;  // bit 26
        u64 b27 : 1;  // bit 27
        u64 b28 : 1;  // bit 28
        u64 b29 : 1;  // bit 29
        u64 b30 : 1;  // bit 30
        u64 b31 : 1;  // bit 31
        u64 b32 : 1;  // bit 32
        u64 b33 : 1;  // bit 33
        u64 b34 : 1;  // bit 34
        u64 b35 : 1;  // bit 35
        u64 b36 : 1;  // bit 36
        u64 b37 : 1;  // bit 37
        u64 b38 : 1;  // bit 38
        u64 b39 : 1;  // bit 39
        u64 b40 : 1;  // bit 40
        u64 b41 : 1;  // bit 41
        u64 b42 : 1;  // bit 42
        u64 b43 : 1;  // bit 43
        u64 b44 : 1;  // bit 44
        u64 b45 : 1;  // bit 45
        u64 b46 : 1;  // bit 46
        u64 b47 : 1;  // bit 47
        u64 b48 : 1;  // bit 48
        u64 b49 : 1;  // bit 49
        u64 b50 : 1;  // bit 50
        u64 b51 : 1;  // bit 51
        u64 b52 : 1;  // bit 52
        u64 b53 : 1;  // bit 53
        u64 b54 : 1;  // bit 54
        u64 b55 : 1;  // bit 55
        u64 b56 : 1;  // bit 56
        u64 b57 : 1;  // bit 57
        u64 b58 : 1;  // bit 58
        u64 b59 : 1;  // bit 59
        u64 b60 : 1;  // bit 60
        u64 b61 : 1;  // bit 61
        u64 b62 : 1;  // bit 62
        u64 b63 : 1;  // bit 63
    };
} vb64;

#define var decltype(auto)

#include <memory>
#include <iostream>
#include <stdexcept>
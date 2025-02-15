#ifndef STD_TYPES_H
#define STD_TYPES_H

/* Standard data types */
typedef unsigned char       uint8_t;    /* 8-bit unsigned integer */
typedef unsigned short      uint16_t;   /* 16-bit unsigned integer */
typedef unsigned int        uint32_t;   /* 32-bit unsigned integer */
typedef unsigned long long uint64_t;   /* 64-bit unsigned integer */

typedef signed char         int8_t;     /* 8-bit signed integer */
typedef signed short        int16_t;    /* 16-bit signed integer */
typedef signed int          int32_t;    /* 32-bit signed integer */
typedef signed long long   int64_t;    /* 64-bit signed integer */


/* Floating point types */
typedef float               float32_t;  /* 32-bit floating point */
typedef double              float64_t;  /* 64-bit floating point */

/* Boolean type */
typedef enum 
{FALSE = 0,
 TRUE = 1
 }boolean;

/* Null pointer definition */
#define NULL_PTR            ((void*)0)

#define NULL (void *) 0

#endif /* STD_TYPES_H */

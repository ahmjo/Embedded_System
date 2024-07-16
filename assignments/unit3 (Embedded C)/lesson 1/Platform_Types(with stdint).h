#ifndef Platfprm_Types.h
#define Platfprm_Types.h

#include "stdbool.h"
#include "stdint.h"

#define CPU_TYPE         CPU_TYPE_32
#define CPU_BIT_ORDER    MSB_FIRST
#define CPU_BYTE_ORDER   HIGH_BYTE_FIRST

#ifndef _bool
#define _bool            unsigned char
#ifndef FALSE
#define FALSE            (boolean)false
#endif
#ifndef TRUE
#define TRUE             (boolean)true
#endif

typedef _bool            boolean;
typedef int8_t           sint8;
typedef uint8_t          uint8;
typedef char             char_t;
typedef int16_t          sint16;
typedef uint16_t         uint16;
typedef int32_t          sint32;
typedef uint32_t         uint32;
typedef int64_t          sint64;
typedef uint64_t         uint64;

typedef volatile  int8_t    vint8_t;
typedef volatile  uint8_t   vuint8_t;
typedef volatile  int16_t   vint16_t;
typedef volatile  uint16_t  vuint16_t;
typedef volatile  int32_t   vint32_t;
typedef volatile  uint32_t  vuint32_t;
typedef volatile  int64_t   vint64_t;
typedef volatile  uint64_t  vuint64_t;        

#endif
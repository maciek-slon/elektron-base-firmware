 #ifdef INTTYPES
 #else
 //#include <stdint.h>
 #define INTTYPES
 /*unsigned types*/
 typedef unsigned char uint8_t;
 typedef unsigned int  uint16_t;
 typedef unsigned long uint32_t;
 typedef unsigned long long uint64_t;
 /*signed types*/
 typedef signed char int8_t;
 typedef signed int  int16_t;
 typedef signed long int32_t;
 typedef signed long long int64_t;
 #endif

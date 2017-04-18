/*
 * iso16284_pbf.h: Packed Binary Format(TM) header file by ISO 16284:2001(E) STD
 * Written by Park, JaeHo(jrogue@huvitz.com)
 * Last Modification Date: 2003/12/08(Mon)
 */

#ifndef _ISO16284_PBF_H
#define _ISO16284_PBF_H

// integers are defined to be 16-bit quantities.
typedef unsigned int INT_U32;
typedef signed int INT_S32;
typedef unsigned short INT_U16;
typedef signed short INT_S16;
typedef unsigned char INT_U8;
typedef signed char INT_S8;

INT_S16 packit(INT_S16 *src, INT_U8 *dst, INT_S16 num);
INT_S16 unpackit(INT_S16 *dst, INT_U8 *src, INT_S16 n);

#endif


/*!
 * \file common_macro.h
 * \brief
 *
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : 수  3월 21 09:45:39 KST 2007
 *
*/
#ifndef _COMMON_MACRO_H_
#define _COMMON_MACRO_H_

#include <printf_func.h>

// ASSERT macro 정의 
#undef ASSERT

#ifdef _USE_ASSERT_
#define ASSERT( x ) \
	do {  \
		if ( !(x) ) { \
			SSL_PRINTF("%s(%d):%s:ASSERT FAIL. System Down!!!\n", __FILE__, __LINE__, __func__); \
			while (1); \
		}  \
	} while (0)

#define MASSERT( x, m ) \
	do {  \
		if ( !(x) ) { \
			SSL_PRINTF(m); \
			SSL_PRINTF("%s(%d):%s:ASSERT FAIL. System Down!!!\n", __FILE__, __LINE__, __func__); \
			while (1); \
		}  \
	} while (0)


#elif defined(_USE_LOOSE_ASSERT_) 
#define ASSERT( x ) \
	do {  \
		if ( !(x) ) { \
			SSL_PRINTF("%s(%d):%s:ASSERT FAIL.\n", __FILE__, __LINE__, __func__); \
		}  \
	} while (0)

#define MASSERT( x, m ) \
	do {  \
		if ( !(x) ) { \
			SSL_PRINTF(m); \
			SSL_PRINTF("%s(%d):%s:ASSERT FAIL.\n", __FILE__, __LINE__, __func__); \
		}  \
	} while (0)
#else
#define ASSERT( x ) 
#define MASSERT( x, m ) 
#endif 



#undef DCODE

#ifdef _DEBUG_
#define DCODE( x ) x
#else 
#define DCODE( x ) 
#endif // _DEBUG_

#ifndef PRINTF
#define PRINTF SSL_PRINTF
#endif 

#endif
/********** end of file **********/

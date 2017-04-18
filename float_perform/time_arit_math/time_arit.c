/*
 * Copyright (c) 2014-2015, Nicolas Limare <nicolas@limare.net>
 * All rights reserved.
 *
 * This program is free software: you can use, modify and/or
 * redistribute it under the terms of the simplified BSD
 * License. You should have received a copy of this license along
 * this program. If not, see
 * <http://www.opensource.org/licenses/bsd-license.html>.
 */

/**
 * @file time_arit.c
 * @brief timing arithmetic and math operations
 *
 * @author Nicolas Limare <nicolas@limare.net>
 */

#include "xutils.inc.c"

#define USE_TIMING
#include "timing.h"

#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <limits.h>

typedef int8_t int8;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef float flt32;
typedef double flt64;

#ifdef NOFLT80
#define RUNFLT80 0
typedef float flt80;
#else
#define RUNFLT80 1
typedef __float80 flt80;
#endif

#ifdef NOFLT128
#define RUNFLT128 0
typedef float flt128;
#else
#define RUNFLT128 1
typedef __float128 flt128;
#endif

/**
 * floating-point comparison, for qsort()
 */
static int cmpf(const void * a, const void * b) {
    float fa = * (float *) a;
    float fb = * (float *) b;
    return (fa > fb) - (fa < fb);
}

/* single type macro */
#define TIME(OP, TYPE, T) {						\
	float cpuclock[nbrun];						\
	volatile TYPE * a = (TYPE *) _a;				\
	volatile TYPE * b = (TYPE *) _b;				\
	volatile TYPE * c = (TYPE *) _c;				\
	const size_t nbops = memsize / sizeof(TYPE);			\
	for (int n = 0; n < nbrun; n++) {				\
	    TIMING_CPUCLOCK_START(0);					\
	    for (int i = 0; i < nbops; i++)				\
		OP;							\
	    TIMING_CPUCLOCK_TOGGLE(0);					\
	    cpuclock[n] = TIMING_CPUCLOCK_S(0);				\
	}								\
	qsort(cpuclock, nbrun, sizeof(float), &cmpf);			\
	T = nbops / 1E6 / cpuclock[nbrun/2];				\
    }

/* multi int type macro */
#define ITIME(OP) {						\
	float t1, t2, t3, t4;					\
	TIME(OP, int8, t1);					\
	TIME(OP, int16, t2);					\
	TIME(OP, int32, t3);					\
	TIME(OP, int64, t4);					\
	printf("'%s',\t %6.1f,\t %6.1f,\t %6.1f,\t %6.1f\n",	\
	       #OP, t1, t2, t3, t4);				\
    }


/* multi flt type macro */
#define FTIME(OP) {						\
	float t1, t2, t3=0, t4=0;				\
	TIME(OP, flt32, t1);					\
	TIME(OP, flt64, t2);					\
	if (RUNFLT80) TIME(OP, flt80, t3);			\
	if (RUNFLT128) TIME(OP, flt128, t4);			\
	printf("'%s',\t %6.1f,\t %6.1f,\t %6.1f,\t %6.1f\n",	\
	       #OP, t1, t2, t3, t4);				\
    }

#ifndef MEMSIZE
#define MEMSIZE 10000000
#endif

#ifndef NBRUN
#define NBRUN 32
#endif

int main(void) {
    const size_t memsize = MEMSIZE;
    const int nbrun = NBRUN;
    // "volatile" avoids optimizing out
    volatile unsigned char *_a, *_b, *_c;

    _a = xmalloc(memsize);
    _b = xmalloc(memsize);
    _c = xmalloc(memsize);

    /* initialization */
    srand(0);
    for (size_t i = 0; i < memsize; i++) {
        _a[i] = rand() % (UCHAR_MAX - 1) + 1; // no zero div
        _b[i] = rand() % (UCHAR_MAX - 1) + 1; // no zero div
    }
    INFO("%zu Kbytes, median of %d trials",
         memsize / 1000, nbrun);

    INFO("Integer Arithmetics");
    ITIME(c[i]=a[i]+b[i]);
    ITIME(c[i]=a[i]&b[i]);
    ITIME(c[i]=a[i]|b[i]);
    ITIME(c[i]=a[i]^b[i]);
    ITIME(c[i]=a[i]*b[i]);
    ITIME(c[i]=a[i]/b[i]);
    ITIME(c[i]=a[i]%b[i]);

    INFO("Floating-point Arithmetics");
    FTIME(c[i]=a[i]+b[i]);
    FTIME(c[i]=a[i]*b[i]);
    FTIME(c[i]=a[i]/b[i]);

    xfree((void *) _a);
    xfree((void *) _b);
    xfree((void *) _c);

    return EXIT_SUCCESS;
}

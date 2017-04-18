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
 * @file time_math.c
 * @brief timing arithmetic and math operations
 *
 * @author Nicolas Limare <nicolas@limare.net>
 */

#include "xutils.inc.c"

#define USE_TIMING
#include "timing.h"

#include <stdlib.h>
#include <stdint.h>
#include <tgmath.h>
#include <limits.h>

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
	volatile TYPE * a = (TYPE *) a_ ## TYPE;			\
	volatile TYPE * b = (TYPE *) b_ ## TYPE;			\
	volatile TYPE * c = (TYPE *) c_ ## TYPE;			\
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
    volatile flt32 *a_flt32, *b_flt32, *c_flt32;
    volatile flt64 *a_flt64, *b_flt64, *c_flt64;
    volatile flt80 *a_flt80, *b_flt80, *c_flt80;
    volatile flt128 *a_flt128, *b_flt128, *c_flt128;

    a_flt32 = (flt32*) xmalloc(memsize);
    b_flt32 = (flt32*) xmalloc(memsize);
    c_flt32 = (flt32*) xmalloc(memsize);
    a_flt64 = (flt64*) xmalloc(memsize);
    b_flt64 = (flt64*) xmalloc(memsize);
    c_flt64 = (flt64*) xmalloc(memsize);
#ifndef NOFLT80
    a_flt80 = (flt80*) xmalloc(memsize);
    b_flt80 = (flt80*) xmalloc(memsize);
    c_flt80 = (flt80*) xmalloc(memsize);
#endif
#ifndef NOFLT128
    a_flt128 = (flt128*) xmalloc(memsize);
    b_flt128 = (flt128*) xmalloc(memsize);
    c_flt128 = (flt128*) xmalloc(memsize);
#endif

    INFO("# %zu Kbytes, median of %d trials",
         memsize / 1000, nbrun);

    /* initialization */
    srand(0);
    for (size_t i = 0; i < memsize / sizeof(flt32); i++) {
        a_flt32[i] = ((flt32) rand() + 1.) / ((flt32) UCHAR_MAX + 1.); // ]0..1]
        b_flt32[i] = ((flt32) rand() + 1.) / ((flt32) UCHAR_MAX + 1.); // ]0..1]
    }
    for (size_t i = 0; i < memsize / sizeof(flt64); i++) {
        a_flt64[i] = (flt64) a_flt32[i];
        b_flt64[i] = (flt64) b_flt32[i];
    }
#ifndef NOFLT80
    for (size_t i = 0; i < memsize / sizeof(flt80); i++) {
        a_flt80[i] = (flt80) a_flt32[i];
        b_flt80[i] = (flt80) b_flt32[i];
    }
#endif
#ifndef NOFLT128
    for (size_t i = 0; i < memsize / sizeof(flt128); i++) {
        a_flt128[i] = (flt128) a_flt32[i];
        b_flt128[i] = (flt128) b_flt32[i];
    }
#endif

    INFO("Single-Instruction Functions");
    FTIME(c[i]=a[i]+b[i]);
    FTIME(c[i]=a[i]*b[i]);
    FTIME(c[i]=a[i]/b[i]);
    FTIME(c[i]=fabs(a[i]));
    FTIME(c[i]=sqrt(a[i]));

    INFO("Fast Functions");
    FTIME(c[i]=exp(a[i]));
    FTIME(c[i]=asin(a[i])); // idem acos
    FTIME(c[i]=atan(a[i]));
    FTIME(c[i]=sinh(a[i])); // idem cosh
    FTIME(c[i]=tanh(a[i]));

    INFO("Slow Functions");
    FTIME(c[i]=log(a[i]));
    FTIME(c[i]=log10(a[i]));
    FTIME(c[i]=pow(a[i],b[i]));
    FTIME(c[i]=sin(a[i])); // idem cos
    FTIME(c[i]=tan(a[i]));

    xfree((void *) a_flt32);
    xfree((void *) b_flt32);
    xfree((void *) c_flt32);
    xfree((void *) a_flt64);
    xfree((void *) b_flt64);
    xfree((void *) c_flt64);
#ifndef NOFLT80
    xfree((void *) a_flt80);
    xfree((void *) b_flt80);
    xfree((void *) c_flt80);
#endif
#ifndef NOFLT128
    xfree((void *) a_flt128);
    xfree((void *) b_flt128);
    xfree((void *) c_flt128);
#endif

    return EXIT_SUCCESS;
}

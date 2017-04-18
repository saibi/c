# Overview

This code contains small timing routines to measure the performance of
the CPU on repeated arithmetic operations and math functions. Its goal
is to provide a first approximation of the speed one can expect, and
to compare different operations, precision, and processors.

Results are collected on two web pages.
* http://limare.perso.math.cnrs.fr/notes/2014/12/12_arit_speed/
* http://limare.perso.math.cnrs.fr/notes/2014/12/16_math_speed/

# Requirements

A C99 compiler is the only hard requirement. Aligned memory allocation
(for SIMD) is only available for POSIX systems.
The makefile also uses `taskset` and `sed` to run the programs and
format the results.

# Usage

`make` will compile and run the code and format the
results. Otherwise, you can manually compile and execute the two
programs `time_arit` and `time_math`.

On non-POSIX systems, disable the aligned memory allocation by
uncommenting `-DNOMEMALIGN` in the makefile.

On systems without 80 bits and 128 bits floating-point support (such
as ARM processors), disable these measures by defining the `NOFLT80`
and `NOFLT128` macros (uncomment `-DNOFLT80 -DNOFLT128` in the makefile).

# Notes

Results should be more reproducible on an idle system without
hyperthreading and adaptive clock frequency.
-> http://limare.perso.math.cnrs.fr/notes/2014/11/26_ht_freq_scal/

Mobile processors (on laptops) often show unstable results, possibly
because of aggressive hardware throttling and heat control.

# Contribute

If you have an interesting CPU not included in the web pages yet,
please run this code and send me the results. I would like to receive
the output of at least three successive runs (`make; make; make`),
with these system info:

* CPU reference    : cat /proc/cpuinfo
* compiler version : c99 --version
* libc version     : strings /usr/lib/*/libc.a | grep GLIBC
* system distribution and version

# Contact

Nicolas Limare <nicolas@limare.net>

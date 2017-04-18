#include <stdio.h>
#include <stdlib.h>



#ifndef _GCC_ 
#ifdef __NOT_80x86__
/// arm std2.5 에는 swab() 함수 제공하지 않는다.
/// SDT 로 컴파일이 가능 하도록 
/// newlib 소스에서 swab() 소스를 가져옴
static void swab(unsigned char * b1, unsigned char * b2, int length)
{
	const unsigned char *from = b1;
  	unsigned char *to = b2;
  	int ptr;
	for (ptr = 1; ptr < length; ptr += 2) {
		unsigned char p = from[ptr];
		unsigned char q = from[ptr-1];

		to[ptr-1] = p;
		to[ptr  ] = q;
	}
	if (ptr == length) /* I.e., if length is odd, */
		to[ptr-1] = 0;   /* then pad with a NUL. */
}
#endif 
#endif 

typedef unsigned int U16;
typedef int S16;
typedef unsigned char U8;


static U8 *outftp;
static S16 ftpn = 0;

static void pack(U16 i, S16 n)
{
#ifdef __NOT_80x86__
	if (n == 4) {
		swab(outftp, outftp, 2);
	}
#endif
	if (!(ftpn & 1)) {
		if (n > 1) {
			*outftp++ = (i & 0xff);
			if (n > 2) {
				*outftp++ = (i & 0xff00) >> 8;
			}
		} else {
			*outftp = i << 4;
		}
	} else {
		if (n > 1) {
			if (n == 2) {
				*outftp++ |= (i & 0xf0) >> 4;
				*outftp = (i & 0x0f) << 4;
			} else {
				*outftp++ |= (i & 0x00f0) >> 4;
				*outftp++ = (i & 0x000f) << 4 | (i & 0xf000) >> 12;
				*outftp = (i & 0x0f00) >> 4;
			}
		} else {
			*outftp++ |= (i & 0x0f);
		}
	}
	ftpn += n;
}

static S16 packit(S16 *src, U8 *dst, S16 num)
{
	S16 i;
	S16 state = 16;
	S16 dr, d2r, dr1 = 0;

	outftp = dst;
	for (ftpn = 0, i = 0; i < num; i++) {
		if (!i) {
			dr = src[i];
		} else {
			dr = src[i] - src[i - 1];
		}
		d2r = dr - dr1;
		switch (state) {
		case 16:
			if (dr < 128 && dr > - 128) {
				state = 8;
				pack(0x8000, 4);
				pack(dr, 2);
			} else {
				pack(src[i], 4);
			}
			break;
		case 8:
			if (dr >= 128 || dr <= -127) {
				state = 16;
				pack(0x81, 2);
				pack(src[i], 4);
			} else {
				if (d2r < 8 && d2r > -8) {
					state = 4;
					pack(0x80, 2);
					pack(d2r, 1);
				} else {
					pack(dr, 2);
				}
			}
			break;
		case 4:
			if (d2r >= 8 || d2r <= -8) {
				pack(0x8, 1);
				if (dr >=128 || dr <= -127) {
					state = 16;
					pack(0x81, 2);
					pack(src[i], 4);
				} else {
					state = 8;
					pack(dr, 2);
				}
			} else {
				pack(d2r, 1);
			}
			break;
		default:
			return -99;
		}
		dr1 = dr;
	}
	return ((ftpn + 1) >> 1);
}


// CPE-4000 version
static int unpack(S16 i)
{
	int j = 0;

	if (!(ftpn & 1)) {
		switch (i) {
		case 1:
			j = (*outftp & 0xf0) >> 4;
			if (j > 8) { // 9
				j = - (16 - j);
			}
			break;
		case 2:
			j = *outftp++;
			if (j > 128) { // 129
				j = - (256 - j);
			}
			break;
		case 4:
			j = *outftp++;
			j |= ((int)(*outftp++)) << 8;
			break;
		}
	} else {
		j = ((*outftp++) & 0x0f);
		switch (i) {
		case 1:
			if (j > 8) { // 9
				j = - (16 - j);
			}
			break;
		case 2:
			j <<= 4;
			j |= (*outftp & 0xf0) >> 4;
			if (j > 128) { // 129
				j = - (256 - j);
			}
			break;
		case 4:
			j <<= 4;
			j |= (*outftp & 0xf0) >> 4;
			j |= ((int) (*outftp++ & 0x0f)) << 12;
			j |= (*outftp & 0xf0) << 4;
			break;
		}
	}
	ftpn += i;

#ifdef __NOT_80x86__
	if (i == 4) {
		swab((char *)j, (char *)j, 2);
	}
#endif
	return (int) j;
}

static S16 unpackit(S16 *dst, U8 *src, S16 n)
{
	S16 state = 16, size = 4;
	S16 i, dr=0, d2r=0, dr1 = 0;
	S16 x;

	outftp = src;
	ftpn = 0;
	for (i = 0; i < n; i++) {
		AGAIN:
		x = unpack(size);
		switch (state) {
		case 16:
			if (x == 0x8000) {
				state = 8;
				size = 2;
				goto AGAIN;
			}
			dst[i] = x;
			if (i) {
				dr1 = x - dst[i - 1];
			} else {
				dr1 = x;
			}
			break;
		case 8:
			if ((x & 0xff) == 0x80) {
				state = 4;
				size = 1;
				goto AGAIN;
			}
			if ((x & 0xff) == 0x81) {
				state = 16;
				size = 4;
				goto AGAIN;
			}
			dr = x;
			if (i) {
				dst[i] = dst[i - 1] + dr;
			} else {
				dst[i] = dr;
			}
			dr1 = dr;
			break;
		case 4:
			if ((x & 0x0f) == 0x8) {
				state = 8;
				size = 2;
				goto AGAIN;
			}
			d2r = x;
			dr = dr1 + d2r;
			dst[i] = dst[i - 1] + dr;
			dr1 = dr;
			break;
		}

		printf("[%d] %d,  src(%02x, %d)\n", i, dst[i], *outftp, *outftp);
	}

	return (outftp - src);
	//return i; // modified code
}



#if 0
/// VCA DCS version
/*
unpack() function
INPUTS: i - The number of nibbles to unpack from the packed data stream.
OUTPUTS: The 16-bit integer value of the packed data
GLOBALS: None
STATICS: outftp
Returns the next nibble, byte, or word of packed data based on the size which is passed. Since byte order for words is different on Z8002, it swaps the order of the bytes before returning a word value.
unpack() is local to this module, called by unpackit() 
*/
static S16 unpack(S16 i)
{
	U16 j = 0;

	if (!(ftpn & 1)) { // on an even boundary 
		switch (i) {
		case 1:
			j = (*outftp & 0xf0) >> 4; // pull from high nibble first
			if (j > 7) {
				j |= 0xfff0;
			}
			break;
		case 2:
			j = *outftp++; // pull a whole byte
			if (j > 127) {
				j |= 0xff00;
			}
			break;
		case 4:
			j = *outftp++; // pull first low byte
			j |= ((int)(*outftp++)) << 8;  // or in high byte
			break;
		}
	} else { // starting in the middle of the byte
		j = ((*outftp++) & 0x0f); // pull from low nibble first
		switch (i) {
		case 1:
			if (j > 7) {
				j |= 0xfff0; // extend sign
			}
			break;
		case 2:
			j <<= 4; // shift up a nibble 
			j |= (*outftp & 0xf0) >> 4; // and grab low nibble from high nibble
			if (j > 127) {
				j |= 0xff00; // extend sign
			}
			break;
		case 4:
			j <<= 4; // shift what we have up to be nibble 3
			j |= (*outftp & 0xf0) >> 4; // add in nibble 4 to get low byte complete
			j |= ((int) (*outftp++ & 0x0f)) << 12; // add in nibble 1
			j |= (*outftp & 0xf0) << 4; // add in nibble 2
			break;
		}
	}
	ftpn += i;

#ifdef __NOT_80x86__
	if (i == 4) {
		swab((char *)j, (char *)j, 2);
	}
#endif
	return (S16) j;
}


/*
unpackit() function
INPUTS: src - Pointer to an input buffer containing packed data. 
	dst - Pointer to an output buffer to fill. 
	n - Number of integers to unpack
OUTPUTS: Unpacked data in the output buffer (dst). Returns number of unpacked bytes.
GLOBALS: None
STATICS: outftp
Unpacks the packed data from src into dst. Calls unpackit().
*/
static S16 unpackit(S16 *dst, U8 *src, S16 n)
{
	S16 state = 16, size = 4;
	S16 i, dr=0, d2r=0, dr1 = 0, x;

	outftp = src;
	ftpn = 0;
	for (i = 0; i < n; i++) {
		AGAIN:
		x = unpack(size);
		switch (state) {
		case 16:
			if (x == 0x8000) {
				state = 8;
				size = 2;
				goto AGAIN;
			}
			dst[i] = x;
			if (i) {
				dr1 = x - dst[i - 1];
			} else {
				dr1 = x;
			}
			break;
		case 8:
			if ((x & 0xff) == 0x80) {
				state = 4;
				size = 1;
				goto AGAIN;
			}
			if ((x & 0xff) == 0x81) {
				state = 16;
				size = 4;
				goto AGAIN;
			}
			dr = x;
			if (i) {
				dst[i] = dst[i - 1] + dr;
			} else {
				dst[i] = dr;
			}
			dr1 = dr;
			break;
		case 4:
			if ((x & 0x0f) == 0x8) {
				state = 8;
				size = 2;
				goto AGAIN;
			}
			d2r = x;
			dr = dr1 + d2r;
			dst[i] = dst[i - 1] + dr;
			dr1 = dr;
			break;
		}
	}
	return (outftp - src);
}
#endif 

#define MAX_COUNT 500
U8 buf[] = { 
#if 0
	0xaf, 0x09, 0x00, 0x80, 0x68, 0x16, 0xb2, 0x81, 0x5a, 0x09, 0xcd,
	0x08, 0x00, 0x80, 0x8c, 0xa3, 0xbb, 0xd8, 0xf3, 0x11, 0x32, 0x53,
	0x70, 0x81, 0x12, 0x09, 0xa7, 0x09, 0x27, 0x0a, 0x00, 0x80, 0x2e,
	0xbe, 0x80, 0x4b, 0xc8, 0xc3, 0xb9, 0xb1, 0x80, 0xd8, 0xb8, 0xc8,
	0xdd, 0xf2, 0x05, 0x1b, 0x2a, 0x32, 0x80, 0x6b, 0x83, 0xc4, 0xd5, 0xe0,
#endif 

207, 
8, 
0, 
128, 
251, 
128, 
96, 
0, 
17, 
242, 
241, 
242, 
0, 
16, 
31, 
47, 
32, 
242, 
15, 
254, 
238, 
253, 
255, 
253, 
29, 
15, 
225, 
209, 
255, 
15, 
241, 
225, 
240, 
241, 
240, 
241, 
240, 
31, 
241, 
31, 
63, 
32, 
243, 
15, 
32, 
2, 
241, 
1, 
0, 
47, 
3, 
211, 
255, 
32, 
31, 
16, 
1, 
0, 
31, 
16, 
31, 
47, 
31, 
16, 
1, 
0, 
0, 
19, 
163, 
16, 
0, 
1, 
1, 
240, 
16, 
242, 
0, 
31, 
16, 
31, 
16, 
31, 
16, 
16, 
1, 
1, 
226, 
17, 
226, 
1, 
242, 
0, 
47, 
3, 
240, 
47, 
73, 
129, 
152, 
13, 
255, 
16, 
241, 
240, 
241, 
240, 
241, 
225, 
255, 
15, 
241, 
209, 
239, 
13, 
29, 
255, 
253, 
254, 
238, 
255, 
2, 
240, 
47, 
47, 
16, 
16, 
2, 
241, 
242, 
241, 
16, 
0, 
104, 
251, 
128, 
96, 
0, 
17, 
242, 
241, 
242, 
0, 
16, 
31, 
47, 
32, 
242, 
15, 
254, 
238, 
253, 
255, 
253, 
29, 
15, 
225, 
209, 
255, 
15, 
241, 
225, 
240, 
241, 
240, 
241, 
240, 
31, 
253, 
143, 
24, 
9, 
92, 
95, 
245, 
194, 
1, 
2, 
240, 
33, 
255, 
63, 
17, 
227, 
255, 
32, 
1, 
15, 
32, 
0, 
16, 
241, 
16, 
0, 
2, 
225, 
1, 
242, 
240, 
19, 
163, 
16, 
0, 
1, 
0, 
31, 
2, 
241, 
242, 
240, 
16, 
1, 
0, 
31, 
16, 
16, 
1, 
243, 
225, 
1, 
1, 
1, 
242, 
0, 
33, 
197, 
255, 
79, 
16, 
17, 
255, 
16, 
241, 
240, 
241, 
240, 
241, 
225, 
255, 
15, 
241, 
209, 
239, 
13, 
29, 
255, 
253, 
254, 
238, 
255, 
2, 
240, 
47, 
47, 
16, 
16, 
2, 
241, 
242, 
241, 
16, 
0, 
0, 
0, 
0, 
0, 
0, 
0, 
0, 
0, 
0, 
0, 
0, 
0, 
0, 
0, 
};

int main(void)
{
	S16 buf_size = 0;
	S16 i;
	S16 dest_list[1440] = { 0, };

	printf("pack/unpack test\n");

	//buf_size = packit(src_list, buf, MAX_COUNT);
	//printf("packed size = %d bytes\n", buf_size);
	//for ( i = 0 ; i < buf_size ; i++ ) {
	//	printf("<%d>", (unsigned)buf[i]);
	//}
	//printf("\n");


	i = unpackit(dest_list, buf, MAX_COUNT);
	printf("unpack = %d bytes\n", i );
	for ( i = 0 ; i < MAX_COUNT ; i++ ) {
		printf("[%d] %d\n", i, dest_list[i]);
	}
	return 0;
}
/********** end of file **********/

#if 0
U8 buf[] = { 

207, 
8, 
0, 
128, 
251, 
128, 
96, 
0, 
17, 
242, 
241, 
242, 
0, 
16, 
31, 
47, 
32, 
242, 
15, 
254, 
238, 
253, 
255, 
253, 
29, 
15, 
225, 
209, 
255, 
15, 
241, 
225, 
240, 
241, 
240, 
241, 
240, 
31, 
241, 
31, 
63, 
32, 
243, 
15, 
32, 
2, 
241, 
1, 
0, 
47, 
3, 
211, 
255, 
32, 
31, 
16, 
1, 
0, 
31, 
16, 
31, 
47, 
31, 
16, 
1, 
0, 
0, 
19, 
163, 
16, 
0, 
1, 
1, 
240, 
16, 
242, 
0, 
31, 
16, 
31, 
16, 
31, 
16, 
16, 
1, 
1, 
226, 
17, 
226, 
1, 
242, 
0, 
47, 
3, 
240, 
47, 
73, 
129, 
152, 
13, 
255, 
16, 
241, 
240, 
241, 
240, 
241, 
225, 
255, 
15, 
241, 
209, 
239, 
13, 
29, 
255, 
253, 
254, 
238, 
255, 
2, 
240, 
47, 
47, 
16, 
16, 
2, 
241, 
242, 
241, 
16, 
0, 
104, 
251, 
128, 
96, 
0, 
17, 
242, 
241, 
242, 
0, 
16, 
31, 
47, 
32, 
242, 
15, 
254, 
238, 
253, 
255, 
253, 
29, 
15, 
225, 
209, 
255, 
15, 
241, 
225, 
240, 
241, 
240, 
241, 
240, 
31, 
253, 
143, 
24, 
9, 
92, 
95, 
245, 
194, 
1, 
2, 
240, 
33, 
255, 
63, 
17, 
227, 
255, 
32, 
1, 
15, 
32, 
0, 
16, 
241, 
16, 
0, 
2, 
225, 
1, 
242, 
240, 
19, 
163, 
16, 
0, 
1, 
0, 
31, 
2, 
241, 
242, 
240, 
16, 
1, 
0, 
31, 
16, 
16, 
1, 
243, 
225, 
1, 
1, 
1, 
242, 
0, 
33, 
197, 
255, 
79, 
16, 
17, 
255, 
16, 
241, 
240, 
241, 
240, 
241, 
225, 
255, 
15, 
241, 
209, 
239, 
13, 
29, 
255, 
253, 
254, 
238, 
255, 
2, 
240, 
47, 
47, 
16, 
16, 
2, 
241, 
242, 
241, 
16, 
0, 
0, 
0, 
0, 
0, 
0, 
0, 
0, 
0, 
0, 
0, 
0, 
0, 
0, 
0, 
};
#endif 

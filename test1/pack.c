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
static S16 unpack(S16 i)
{
	U16 j = 0;

	if (!(ftpn & 1)) {
		switch (i) {
		case 1:
			j = (*outftp & 0xf0) >> 4;
			if (j > 9) {
				j = - (16 - j);
			}
			break;
		case 2:
			j = *outftp++;
			if (j > 129) {
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
			if (j > 9) {
				j = - (16 - j);
			}
			break;
		case 2:
			j <<= 4;
			j |= (*outftp & 0xf0) >> 4;
			if (j > 129) {
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
	return (S16) j;
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

S16 src_list[] = {
	0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 
	100, 110, 120, 130, 140, 150, 160, 170, 180, 190,
	200, 210, 220, 230, 240, 250, 260, 270, 280, 290,
	300, 310, 320, 330, 340, 350, 360, 370, 380, 390,
	400, 410, 420, 430, 440, 450, 460, 470, 480, 490,
	500, 510, 520, 530, 540, 550, 560, 570, 580, 590,




	1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,
	1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,
	1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,
	1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,
	1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,
	1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,
	1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,
	1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,
	1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,
	1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,
	1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,
	1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,
	1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,
	1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,
	1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,
	1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,
	1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,
	1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,
	1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,
	1000,1000,1000,1000,1000,1000,1000,1000,1000,1000,



	2255,2250,2251,2252,2254,2257,2260,2264,2268,2273,2278,2284,2290,2298,2306,
	2314,2323,2332,2343,2354,2366,2379,2390,2398,2403,2405,2405,2402,2397,2391,
	2381,2370,2357,2343,2327,2310,2292,2273,2253,2232,2210,2189,2165,2141,2118,
	2093,2069,2044,2018,1992,1967,1941,1915,1888,1862,1836,1813,1789,1767,1746,
	1727,1708,1689,1672,1654,1639,1623,1608,1594,1580,1568,1555,1543,1533,1522,
	1512,1502,1494,1485,1476,1469,1462,1455,1449,1442,1437,1431,1427,1422,1417,
	1414,1411,1408,1405,1403,1401,1400,1398,1398,1397,1400,1397,1398,1398,1400,
	1402,1403,1406,1409,1412,1414,1418,1421,1427,1431,1437,1442,1449,1455,1461,
	1469,1476,1485,1493,1502,1512,1522,1533,1544,1557,1568,1581,1595,1608,1623,
	1639,1654,1671,1688,1708,1727,1746,1768,1789,1813,1836,1862,1888,1915,1941,
	1967,1993,2018,2044,2069,2093,2118,2142,2165,2189,2210,2232,2253,2273,2292,
	2310,2327,2343,2357,2370,2381,2391,2397,2402,2405,2405,2403,2398,2390,2379,
	2366,2354,2343,2332,2323,2314,2306,2298,2290,2284,2278,2273,2268,2263,2260,
	2257,2254,2252,2251,2250,2255,2250,2251,2252,2254,2257,2260,2264,2268,2273,
	2278,2284,2290,2298,2306,2314,2323,2332,2343,2354,2366,2379,2390,2398,2403,
	2406,2405,2402,2397,2391,2381,2370,2357,2343,2327,2310,2292,2273,2253,2232,
	2210,2189,2165,2141,2118,2093,2069,2044,2018,1992,1967,1941,1915,1888,1862,
	1836,1814,1789,1768,1746,1729,1707,1689,1672,1654,1639,1623,1608,1595,1581,
	1569,1556,1544,1533,1521,1512,1502,1494,1485,1477,1469,1461,1456,1449,1442,
	1437,1431,1427,1422,1418,1414,1410,1409,1406,1403,1401,1399,1398,1398,1397,
	1400,1397,1398,1399,1400,1402,1403,1405,1408,1411,1414,1418,1422,1427,1431,
	1437,1442,1449,1455,1462,1469,1476,1485,1493,1502,1512,1522,1533,1543,1556,
	1568,1580,1594,1608,1623,1638,1654,1672,1688,1708,1729,1746,1768,1789,1813,
	1837,1862,1888,1915,1941,1967,1993,2018,2044,2069,2093,2118,2142,2165,2189,
	2210,2232,2253,2273,2292,2310,2327,2343,2357,2370,2381,2391,2397,2402,2405,
	2405,2403,2398,2390,2379,2366,2354,2343,2332,2323,2314,2306,2297,2290,2284,
	2278,2273,2268,2264,2260,2257,2254,2252,2251,2250
};

#define MAX_COUNT 1440

int main(void)
{
	U8 buf[] = { 
		'}',8,0,128,1,128,3,31,31,31,1,241,0,0,241,0,0,15,16,0,241,31,31,241,1,241,240,1,15,31,31,31,1,240,1,241,241,15,0,31,31,1,240,0,0,1,240,241,0,15,0,31,0,15,31,0,241,15,27,158,16,240,31,0,0,15,31,31,0,0,240,15,16,0,240,241,240,31,31,0,0,1,225,0,0,240,0,31,0,1,225,0,0,15,'.',0,31,16,0,241,0,240,16,0,0,241,241,241,241,241,15,31,'.',16,0,241,241,241,241,241,0,0,0,31,241,31,0,1,240,16,241,241,0,242,255,16,241,0,0,0,31,1,241,255,'/',31,31,31,16,241,15,31,16,15,16,1,240,241,1,240,0,1,255,'/',0,1,241,241,241,0,241,240,16,0,0,241,0,0,0,27,158,'/',31,0,1,241,241,240,31,31,16,15,16,241,0,0,0,15,27,145,241,15,0,31,0,31,16,241,241,241,1,255,31,'/',0,0,0,0,0,0,31,0,16,15,1,240,31,31,1,0,0,241,15,16,242,240,0,0,15,'/',0,27,158,27,145,241,241,241,240,31,31,31,16,15,31,16,241,241,241,241,0,241,241,15,16,241,241,0,15,16,241,241,15,16,241,241,0,241,240,2,240,240,1,0,225,1,241,225,31,0,241,0,15,16,15,16,0,240,31,1,241,240,1,240,15,'/',15,16,0,241,0,240,16,240,0,31,16,240,1,240,1,15,241,31,31,0,1,255,27,145,240,0,0,0,31,241,15,16,0,0,0,241,0,0,0,15,16,0,15,16,0,241,0,27,158,27,145,255,27,145,240,0,0,241,0,1,255,27,145,240,1,225,31,0,0,1,255,16,1,241,15,0,31,0,31,1,240,1,241,15,31,31,31,16,241,242,225,241,241,0,15,31,16,241,242,224,1,0,15,16,0,0,241,0,241,0,240,16,15,31,16,241,241,240,1,15,0,'.',31,0,16,240,1,240,31,0,241,31,15,16,0,0,0,0,241,241,241,240,31,27,158,'/',16,240,1,226,240,241,31,241,240,16,241,240,31,16,240,15,16,0,0,0,15,16,241,240,31,31,31,16,240,31,242,241,15,1,255,27,145,240,0,31,0,0,0,0,31,0,0,0,1,225,0,0,0,1,240,241,15,'/',0,31,0,242,255,27,145,240,0,31,0,27,158,16,0,0,1,241,255,'/',0,31,1,241,240,1,241,240,31,16,241,15,1,241,15,31,16,241,0,241,0,241,241,15,16,15,31,16,241,0,15,16,15,16,0,241,31,241,241,15,27,145,255,'/',0,0,0,0,1,14,27,145,240,31,1,240,31,242,240,31,1,241,15,1,0,241,241,241,0,15,16,15,16,0,15,27,145,240,0,0,0,0,0,1,225,0,31,31,31,0,1,241,241,241,241,240,31,31,16,15,16,0,241,0,241,0,15,16,1,225,0,0,0,0,0,0,1,240,31,241,31,31,0,0,2,224,1,0,15,31,31,16,241,241,0,0,15,16,0,0,31,241,31,0,0,0,1,241,240,16,240,31,31,1,240,16,241,27,158,31,2,240,15,16,15,'/',0,31,0,242,240,1,240,16,241,226,241,0,241,242,225,241,0,241,241,242,240,0,0,0,31,0,31,0,1,240,31,1,240,31,16,240,31,16,0,0,15,16,0,241,0,0,27,147,



#if 0
		0, 128, 0, 25, 128, 0, 0, 0, 0, 0, 
		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 

		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 

		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 

		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 

		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 
	
		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 

		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 

		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 

		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 

		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 

		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 

		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 

		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 

		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 

		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,
#endif 
	};
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
		printf("%d,", dest_list[i]);
	}
	return 0;
}
/********** end of file **********/
#if 0

static unsigned char *outftp;
static int ftpn = 0;



/*
pack() function
INPUTS: i - The value to be packed into the output stream. 
	n - The number of nibbles it should take up.
OUTPUTS: Deposits the packed data into the output buffer pointed to by outftp and updates outftp as needed.
GLOBALS: None
STATICS: outftp, ftpn
Packs nibbles into *outftp and increments the nibble counter ftpn by the number of nibbles packed.
pack()is private to this module, called by packit() 
*/
static void pack(unsigned int i, int n)
{
#ifdef __NOT_80x86__
	if (n == 4) {
		swab(outftp, outftp, 2); // put into 80x86 order
	}
#endif
	if (!(ftpn & 1)) { // on an even nibble boundary? 
		if (n > 1) {
			*outftp++ = (i & 0xff);
			if (n > 2) {
				*outftp++ = (i & 0xff00) >> 8;
			}
		} else {
			*outftp = i << 4; // pack high nibble first 
		}
	} else {
		if (n > 1) {
			if (n == 2) {
				*outftp++ |= (i & 0xf0) >> 4; // fill in low nibble with high nibble of next byte
				*outftp = (i & 0x0f) << 4; // fill in high nibble with low nibble
			} else {
				*outftp++ |= (i & 0x00f0) >> 4; // fill in nibble 3
				*outftp++ = (i & 0x000f) << 4 | (i & 0xf000) >> 12; // nibbles 4 and 1
				*outftp = (i & 0x0f00) >> 4; // and nibble 2
			}
		} else {
			*outftp++ |= (i & 0x0f); // fill in low nibble
		}
	}
	ftpn += n;
}

/*
packit() function
INPUTS: src - Pointer to integers to pack. 
	dst - Buffer to contain packed data. 
	num - Number of integers to pack.
OUTPUTS: Deposits packed data in output buffer (dst), and returns number of bytes actually packed. 
GLOBALS: None 
STATICS: outftp, ftpn
Packs the integer data into the output buffer. 
Calls pack() 
*/
static int packit(int *src, unsigned char *dst, int num)
{
	int i;
	int state = 16;
	int dr, d2r, dr1 = 0;

	outftp = dst;
	for (ftpn = 0, i = 0; i < num; i++) {
		if (!i) {
			dr = src[i];
		} else {
			dr = src[i] - src[i - 1];
		}
		d2r = dr - dr1;
		switch (state) {
		case 16: // Note this was originally, incorrectly, (dr<128 && dr>-128)
			if (dr < 128 && dr > -127) {
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

/*
unpack() function
INPUTS: i - The number of nibbles to unpack from the packed data stream.
OUTPUTS: The 16-bit integer value of the packed data
GLOBALS: None
STATICS: outftp
Returns the next nibble, byte, or word of packed data based on the size which is passed. Since byte order for words is different on Z8002, it swaps the order of the bytes before returning a word value.
unpack() is local to this module, called by unpackit() 
*/
static int unpack(int i)
{
	unsigned int j = 0;

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
	return (int) j;
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
static int unpackit(int *dst, unsigned char *src, int n)
{
	int state = 16, size = 4;
	int i, dr=0, d2r=0, dr1 = 0, x;

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

	printf("DEBUG %s(%d) : src = %p, outftp = %p\n", __FILE__, __LINE__, src, outftp);

   	// org : bytes
	//return (outftp - src);

	// return count
	return i;
}
#endif 

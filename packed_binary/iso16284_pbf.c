/*
 * iso16284_pbf.c: Packed Binary Format(TM) by ISO 16284:2001(E) STD
 * Written by Park, JaeHo(jrogue@huvitz.com)
 * Last Modification Date: 2004/4/3(Sat)
 */

#include "iso16284_pbf.h"

#ifndef _GCC_ 
#ifdef __BIG_ENDIAN__
/// arm std2.5 에는 swab() 함수 제공하지 않는다.
/// SDT 로 컴파일이 가능 하도록 
/// newlib 소스에서 swab() 소스를 가져옴
static void swab(unsigned char * b1, unsigned char * b2, INT_S16 length)
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


static INT_U8 *outftp;
static INT_S16 ftpn = 0;

// VCA DCS V3.08 Annex B sample code
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
static void pack(INT_U16 i, INT_S16 n)
{
#ifdef __BIG_ENDIAN__
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
INT_S16 packit(INT_S16 *src, INT_U8 *dst, INT_S16 num)
{
	INT_S16 i;
	INT_S16 state = 16;
	INT_S16 dr, d2r, dr1 = 0;

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

// Huvitz CPE-4000 code 
// unpack (modified by saibi)
static INT_S32 unpack(INT_S32 i)
{
	INT_S32 j = 0;

	if (!(ftpn & 1)) {
		switch (i) {
		case 1:
			j = (*outftp & 0xf0) >> 4;
			if (j > 7) {
				j = - (16 - j);
			}
			break;
		case 2:
			j = *outftp++;
			if (j > 127) {
				j = - (256 - j);
			}
			break;
		case 4:
			j = *outftp++;
			j |= ((INT_S32)(*outftp++)) << 8;
			break;
		}
	} else {
		j = ((*outftp++) & 0x0f);
		switch (i) {
		case 1:
			if (j > 7) {
				j = - (16 - j);
			}
			break;
		case 2:
			j <<= 4;
			j |= (*outftp & 0xf0) >> 4;
			if (j > 127) {
				j = - (256 - j);
			}
			break;
		case 4:
			j <<= 4;
			j |= (*outftp & 0xf0) >> 4;
			j |= ((INT_S32) (*outftp++ & 0x0f)) << 12;
			j |= (*outftp & 0xf0) << 4;
			break;
		}
	}
	ftpn += i;

#ifdef __BIG_ENDIAN__
	if (i == 4) {
		swab((INT_U8*)j, (INT_U8*)j, 2);
	}
#endif
	return (INT_S32) j;
}

// CPE-4000 unpackit modified by saibi
INT_S16 unpackit(INT_S16 *dst, INT_U8 *src, INT_S16 n)
{
	INT_S32 state = 16, size = 4;
	INT_S32 i, dr=0, d2r=0, dr1 = 0;
	INT_S32 x;

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
	return ( (ftpn+1) >> 1 );
	//return (outftp - src);
	//return i;
}
/********** end of file **********/

#if 0
// VCA DCS V3.08 Annex B sample code
/*
unpack() function
INPUTS: i - The number of nibbles to unpack from the packed data stream.
OUTPUTS: The 16-bit integer value of the packed data
GLOBALS: None
STATICS: outftp
Returns the next nibble, byte, or word of packed data based on the size which is passed. Since byte order for words is different on Z8002, it swaps the order of the bytes before returning a word value.
unpack() is local to this module, called by unpackit() 
*/
static INT_S16 unpack(INT_S16 i)
{
	INT_U16 j = 0;

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
			j |= ((INT_S16)(*outftp++)) << 8;  // or in high byte
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
			j |= ((INT_S16) (*outftp++ & 0x0f)) << 12; // add in nibble 1
			j |= (*outftp & 0xf0) << 4; // add in nibble 2
			break;
		}
	}
	ftpn += i;

#ifdef __BIG_ENDIAN__
	if (i == 4) {
		swab((INT_U8*)j, (INT_U8*)j, 2);
	}
#endif
	return (INT_S16) j;
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
INT_S16 unpackit(INT_S16 *dst, INT_U8 *src, INT_S16 n)
{
	INT_S16 state = 16, size = 4;
	INT_S16 i, dr=0, d2r=0, dr1 = 0, x;

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

	//Uart_Printf("DEBUG %s(%d) : src = %p, outftp = %p\n", __FILE__, __LINE__, src, outftp);

	return ( (ftpn+1) >> 1 );
}



// CPE-4000 org code
static int unpack(int i)
{
	unsigned int j = 0;

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

#ifdef __BIG_ENDIAN__
	if (i == 4) {
		swab((unsigned char *)j, (unsigned char *)j, 2);
	}
#endif
	return (int) j;
}



// Huvitz CPE-4000 code 
static void pack(INT_U16 i, INT_S16 n)
{
#ifdef __BIG_ENDIAN__
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

INT_S16 packit(INT_S16 *src, INT_U8 *dst, INT_S16 num)
{
	INT_S16 i;
	INT_S16 state = 16;
	INT_S16 dr, d2r, dr1 = 0;

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
			if (dr < 128 && dr >= -128) {
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
#endif 

/*!
 * \file bin2bhc.c
 * \brief
 *
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : 월 6 01  대한민국 표준시 2009
 *
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

/// checksum 계산 
/// \param buf 
/// \param size
/// \return checksum
static int calc_checksum(unsigned char *buf, int size)
{
	unsigned short checksum = 0;
	int i;

	for ( i = 0; i < size ; i++) {
		checksum += buf[i];
	}
	return checksum;
}


/// file 읽기 (GB 이상의 큰 파일 처리 못함)
/// \param fd file descriptor
/// \param buf (out) 파일 내용이 저장될 버퍼 (충분히 메모리 확보해야한다)
/// \param size
/// \return file size
/// \return 음수 에러 
static int read_file(int fd, unsigned char *buf, int size)
{
	int rd_idx = 0;
	int ret;

	while( rd_idx < size ) {
		ret = read(fd, &buf[rd_idx], size);
		if ( ret <= 0 ) {
			break;
		}
		rd_idx += ret;
		size -= ret;
	}
	if ( ret < 0 ) {
		return ret;
	}
	return rd_idx;
}

/// file 쓰기 (GB 이상의 큰 파일 처리 못함)
/// \param fd file descriptor
/// \param buf (in) 쓸 파일 내용
/// \param size
/// \return file size
/// \return 음수 에러 
static int write_file(int fd, unsigned char *buf, int size)
{
	int wr_idx = 0;
	int ret;

	while( wr_idx < size ) {
		ret = write(fd, &buf[wr_idx], size);
		if ( ret <= 0 ) {
			break;
		}
		wr_idx += ret;
		size -= ret;
	}
	if ( ret < 0 ) {
		return ret;
	}
	return wr_idx;
}

/// .bhc 파일 이름 생성 
/// \param 원본 파일 이름 
/// \return .bhc 파일 이름 
static char *make_outfile(char *in)
{
	static char tmp[1024];
	char *p;

	strncpy(tmp, in, sizeof(tmp));

	if ( (p = strrchr(tmp, '.')) == NULL ) {
		strcat(tmp, ".bhc");
	} else {
		*p = 0;
		strcat(tmp, ".bhc");
	}
	return tmp;
}



/// 메인 프로그램
int main(int argc, char *argv[])
{
	int fd;
	unsigned char *buf;
	struct stat sb;
	unsigned int new_sz;
	unsigned short new_checksum;
	char *nf;

	printf("Converting .bin -> .bhc \n");

	// parameter check
	if ( argc < 2 ) {
		printf("usage : %s filename\n", argv[0]);
		exit(1);
	}

	// 원본 파일 열기
	fd = open(argv[1], O_RDONLY);
	if ( fd < 0 ) {
		printf("file open error %s.\n", argv[1]);
		exit(2);
	}

	// 사이즈 정보 얻기
	if ( fstat(fd, &sb) < 0 ) {
		printf("stat error %s\n", argv[1]);
		exit(3);
	}

	// 메모리 확보
	buf = (unsigned char *)malloc( sb.st_size + 1);
	if ( buf == NULL ) {
		printf("memory error.\n");
		exit(4);
	}

	// 파일 읽음 
	if ( read_file(fd, buf, sb.st_size) < 0 ) {
		printf("read error %s\n", argv[1]);
		exit(5);
	}
	close(fd);


	// 저장할 size 및 checksum 계산  
	new_sz = sb.st_size + sizeof(int) + sizeof(short); // 4bytes(total size) +원본사이즈 + 2bytes(checksum)
	new_checksum = calc_checksum(buf, sb.st_size); // check 계산

	printf("file %s, size = %d, out_size = %d, crc = %x\n", argv[1], (int)sb.st_size, new_sz, new_checksum);

	// 변환 파일 생성 
	fd = creat( (nf = make_outfile(argv[1])), S_IRWXU | S_IRWXG | S_IRWXO); 
	if ( fd < 0 ) {
		printf("file creation error %s.\n", nf);
		exit(6);
	}

	// 파일 기록 (total size = 4 + 원본 사이즈 + 2 )
	if ( write(fd, &new_sz, sizeof(int)) < 0 ) {
		printf("write error. (size)\n");
		exit(7);
	}

	// 파일 기록 (내용)
	if ( write_file(fd, buf, sb.st_size) < 0 ) {
		printf("write error %s\n", nf);
		exit(8);
	}

	// 파일 기록 (checksum)
	if ( write(fd, &new_checksum, sizeof(short)) < 0 ) {
		printf("write error. (checksum)\n");
		exit(9);
	}
	close(fd);

	printf("%s created.\n", nf);
	exit(0);
}
/********** end of file **********/

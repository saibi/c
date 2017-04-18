/*!
  \file file.c
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Wed Dec 08 19:11:20 KST 2010

*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include <file.h>

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

/// bin 파일을 읽는다
/// 내부에서 malloc 으로 메모리를 할당한후 파일 내용을 저장해서 p_buf 에 돌려준다
/// .bhc 변환을 쉽게 하기위해 파일 버퍼 보다 6 바이트 크게 할당된다. 
/// p_buf - 4 에 size 를 입력할 수 있고 buffer size 끝에 2 bytes check sum 을 입력할 수 있다.
/// \param path
/// \param p_buf (out)
/// \return file_size
/// \return error
int read_bin_file(char *path, unsigned char **p_buf)
{
	int fd;
	struct stat sb;
	int ret;

	unsigned char *buf;

	fd = open(path, O_RDONLY);
	if ( fd < 0 ) {
		perror("read_file() : open error");
		return -1;
	}

	if ( fstat(fd, &sb) < 0 ) {
		perror("read_file() : stat error");
		close(fd);
		return -2;
	}

	buf = (unsigned char *)malloc(sb.st_size + 8);
	if ( buf == NULL ) {
		perror("read_file() : alloc error");
		close(fd);
		return -3;
	}

	ret = read_file(fd, &buf[4], sb.st_size);
	close (fd);
	if ( ret < 0 ) {
		perror("read_file() : read error");
		return -4;
	}
	if ( ret != sb.st_size ) {
		perror("read_file() : size error");
		return -5;
	}

	*p_buf =  &buf[4];
	return ret;
}
/********** end of file **********/

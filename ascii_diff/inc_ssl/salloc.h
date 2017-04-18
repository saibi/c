/*!
 * \file salloc.h
 * \brief
 * simple memory allocation
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : 월  4월 03 13:53:01 KST 2006
 *
*/

#ifndef _SALLOC_H_
#define _SALLOC_H_


#define SALLOC_MAGIC 0x20118279 // 20070209 휴대폰 바꿨다.

/// simple allocation stub structure
struct salloc_stub {
	unsigned int magic;
	unsigned int size;
	unsigned int id; // 메모리 누수 추적을 위한 id
	struct salloc_stub *next, *prev;
};


int init_salloc(void *start_address, unsigned int pool_size);
void * salloc(unsigned int req_size);
int sfree(void *req_mem);
void *srealloc(void *req_addr, unsigned int resize);
void * scalloc(unsigned int req_size);
void * salloc_get_next_address(void);

// 이름 변경 strdup 이 표준 library 함수 이름이라서 앞에 s 하나 더 붙임
char * sstrdup(char *src);

// _DEBUG_ 모드로 컴파일할 경우 아래 함수 사용 가능 
void stat_salloc(void);
void show_salloc_addr(void);
void show_salloc_list(int);

#endif // _SALLOC_H_
/********** end of file **********/

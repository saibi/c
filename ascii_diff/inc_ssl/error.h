/*!
 * \file error.h
 * \brief
 *
 * error code 
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : 월  6월 12 20:31:10 KST 2006
 *
*/

#ifndef _ERROR_H_
#define _ERROR_H_

#define ERR_NONE 0

enum error_idx {
	ERR = 100000,
	ERR_MAX, // 최대값 초과
	ERR_MIN, // 최소값 미만
	ERR_MODIFY, // 값 변경 불가
	ERR_MEM, // memory 부족
	ERR_NOMEM, // same as ERR_MEM
	ERR_INVAL, // invalid paramerter, value, 
	ERR_IO, // i/o 실패
	ERR_READ, // read 실패
	ERR_WRITE, // write 실패
	ERR_FULL, // buffer full /

	ERR_IMPL, // not implemented // 11
	ERR_NOENT, // 해당 항목 없음
	ERR_TIMEOUT, // time out
	ERR_NOT_READY, // not ready
	ERR_EOF, // end of file, end of buffer, end of string
	ERR_TYPE, // type mismatch
	ERR_FORMAT, // invalid format
	ERR_OVERFLOW, // over flow
	ERR_EMPTY, // empty 
	ERR_EDGING, // 가공 에러 

	ERR_DUP, // 중복 에러 // 21
	ERR_DIV_BY_ZERO,  // division by zero
	ERR_VERIFY, // verify failed
	ERR_NOT_ORIGIN, // motor 원점 에러
	ERR_STOP, // user stop 
	ERR_PERM, // permission error
	ERR_MAX_EDGING_TIME, // 최대 가공 시간 초과
	ERR_BUSY, // 사용중
	ERR_WPROTECT, // write protected

	MAX_ERR
};


#endif
/********** end of file **********/

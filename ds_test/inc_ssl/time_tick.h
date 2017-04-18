/*!
 * \file time_tick.h
 * \brief
 *
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : 목 4 03  Korea Standard Time 2008
 *
*/
#ifndef _TIME_TICK_H_
#define _TIME_TICK_H_


/// rtc 를 이용한 time loop macro
/// loop seconds 동안 반복 (초단위)
#define TIME_LOOP_START(loop_seconds, tick_func, tick_per_second ) \
	{ \
		unsigned int tl_cur_time = tick_func(); \
		unsigned int end_tick = tl_cur_time + (loop_seconds) * (tick_per_second); \
		while ( tick_func() < (end_tick)  ) {

#define TIME_LOOP_END }}


/// rtc 를 이용한 function time loop macro ( loop 에서 계속 handler function 실행)
/// loop seconds 동안 반복 (초단위)
#define FUNCTION_TIME_LOOP_START(loop_seconds, handler, tick_func, tick_per_second) \
	{ \
		unsigned int tl_cur_time = tick_func(); \
		unsigned int end_tick = tl_cur_time + (loop_seconds) * (tick_per_second); \
		unsigned int cur; \
		while ( (cur = tick_func()) < (end_tick) ) { \
			if ( handler ) { \
				((void (*)(unsigned int))handler)(cur - tl_cur_time); \
			}





int x_tick_per_second(unsigned int *prev,  int xx_per_second, unsigned int cur_tick, int tick_per_second );
int run_per_x_seconds(unsigned int *prev, int second, unsigned int cur_tick, int tick_per_second);


#endif
/********** end of file **********/

/*!
 * \file cmd_q.h
 * \brief
 *
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : ¼ö 6 11  Korea Standard Time 2008
 *
*/
#ifndef _CMD_Q_H_
#define _CMD_Q_H_

struct cmd_ret_stat_rec {
	int cid;
	int ret;

	struct list_head list;
};

#define CMD_Q_FLAG_RETURN_VALUE 0x80000000
#define CMD_Q_FLAG_CID_MASK 0x7fffffff

struct cmd_q_rec {
	int cid;
	unsigned int when;
	int (*func)(char *, void *, void *);
	char *param;
	void *arg1;
	void *arg2;
	struct list_head list;
};


int add_cmd_function(int cid, int when, int (*func)(char *, void *, void *), char *param, void *arg1, void *arg2);
int get_cmd_function_return_value(int cid, int *ret);
int run_cmd_function(void);
void clear_all_cmd_function_return_value(void);

#endif
/********** end of file **********/

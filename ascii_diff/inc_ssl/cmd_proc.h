/*!
 * \file cmd_proc.h
 * \brief
 *
 *
 * created by Kim Youngmin (ymkim@huvitz.com)
 * creation date : 금 4 04  Korea Standard Time 2008
 *
*/
#ifndef _CMD_PROC_H_
#define _CMD_PROC_H_

#include <llist.h>

/// 콘설 명령 처리 모드
#define CMD_MODE_DUMMY_TERMINAL 0x01
#define CMD_MODE_CONTROL_UI 0x02
#define CMD_MODE_ADVANCED 0x04
#define CMD_MODE_DEBUG 0x08
#define CMD_MODE_COMM 0x10
#define CMD_MODE_SU 0x40000000 // super user flag

#define CONSOLE_CMD_COMMENT_CHAR '#'
#define CONSOLE_CMD_COMMENT_CHAR2 '\''
#define CONSOLE_CMD_HISTORY_CHAR '!'
#define CONSOLE_CMD_ARRAY_START_CHAR '['
#define CONSOLE_CMD_ARRAY_END_CHAR ']'
#define CONSOLE_CMD_SEPARATOR_STR ";"


// console 명령 history 지원
#define MAX_CMD_HISTORY 10 // 최대 명령 기억 개수

// command history
struct cmd_history_entry {
	struct list_head list;
	char cmd[ZERO_ARRAY_IDX];
};

// console command
struct console_command {
	int mode;
	char *cmd;
	void (*func)(char *param, void *);
	void *args;
	char *help_str;
};

extern int command_processing_mode;
extern int command_history_count;
extern int command_processing_result;

// function prototypes
void console_command_handler(void);
int process_console_command_ex(char *input_buf, int ignore_perm);
int process_console_command(char *input_buf); // for script 
int queue_console_command(char *cmd);
int add_cmd_list_table(struct console_command *p_list);
void override_console_cmd_arg(int stat, void *args);


void mode_command_handler(char *param, void *args);

#define HAVE_DEBUG_CAP() (command_processing_mode & CMD_MODE_DEBUG)
#define HAVE_ADVANCED_CAP() (command_processing_mode & CMD_MODE_ADVANCED)
#define HAVE_SUPER_USER_CAP() (command_processing_mode & CMD_MODE_SU)

#endif 
/********** end of file **********/

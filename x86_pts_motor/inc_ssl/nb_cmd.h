/*!
  \file nb_cmd.h
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Fri Jul 22 14:54:39 KST 2011

*/
#ifndef _NB_CMD_H_
#define _NB_CMD_H_

#include <llist.h>

#define MAX_NB_CMD_SLOT 5
#define NB_CMD_MAGIC 0x20118279

typedef struct nb_cmd_entry_rec {
	int cmd;
	void *param;
	int flag;

	//struct list_head list; //unused
} NB_CMD_ENTRY;
#define NB_CMD_IMMEDIATE 0x01
#define NB_CMD_FREE 0x02

typedef struct nb_cmd_meta {
	int magic; // to check initialized or not
	int slot_flag[MAX_NB_CMD_SLOT];
	void * handler[MAX_NB_CMD_SLOT];
	NB_CMD_ENTRY current[MAX_NB_CMD_SLOT];
	int slot;

	//struct list_head cmd_list[MAX_NB_CMD_SLOT]; // unused
} NB_CMD;

#define NB_CMD_SLOT_FLAG_ADD 0x01
#define NB_CMD_SLOT_FLAG_BUSY 0x02


int nb_cmd_init(NB_CMD *pnb);
int nb_cmd_add_slot(NB_CMD *pnb, int id, void * handler);
int nb_cmd_run(NB_CMD *pnb, int id, int cmd, void *param, int flag);
int nb_cmd_loop(NB_CMD *pnb);
int nb_cmd_is_busy(NB_CMD *pnb, int id, int *p_cmd);

#endif 
/********** end of file **********/

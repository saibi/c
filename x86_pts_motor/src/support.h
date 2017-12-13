#ifndef _SUPPORT_H_
#define _SUPPORT_H_

int send_cmd(int fd, const char * cmd);
int send_wps_rot(int fd, int count);
int send_msg(int fd, const char * msg);

int make_nm_cmd_packet(char *buf, int buf_size, const char *contents);
int make_nm_msg_packet(char *buf, int buf_size, const char *contents);
void pr_packet(char *buf);

#endif 


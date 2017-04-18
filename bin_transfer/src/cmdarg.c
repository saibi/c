/*!
  \file cmdarg.c
  \brief


  created by Kim Youngmin (ymkim@huvitz.com)
  creation date : Wed Dec 08 20:08:44 KST 2010

*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <cmdarg.h>

char bin_file_path[1024];
char port_path[1024];
char speed_str[1024];

/// usage
static void usage(char *path)
{
	printf("bin file transfer V0.1 for POSIX OS\n");
	printf("%s [-p /dev/ttyXXXX] [-s 115200] binfile\n", path);
	printf("\t-p : serial port device file path\n");
	printf("\t-s : baud rate (115200, 38400, 9600)\n");
}

/// cmd line option 처리
/// \param argc
/// \param argv
/// \return 0 ok
/// \return 음수 error
int proc_cmd_options(int argc, char *argv[])
{
	int opt;

	if ( argc <= 1 ) {
		usage(argv[0]);
		return -1;
	} else {
		while((opt = getopt(argc, argv, "p:s:")) != -1 ) {
			switch(opt) {
				case 'p':
					printf("DEBUG port =  %s\n", optarg);
					strncpy(port_path, optarg, sizeof(port_path));
					break;

				case 's':
					printf("DEBUG speed =  %s\n", optarg);
					strncpy(speed_str, optarg, sizeof(speed_str));
					break;

				case ':':
					//fprintf(stderr, "Option '-%c' needs a path.\n", optopt);
					usage(argv[0]);
					return -2;

				case '?':
					//fprintf(stderr, "No such option '-%c'\n", optopt);
					usage(argv[0]);
					return -3;
			}
		}
		if ( optind < argc ) {
			strncpy(bin_file_path, argv[optind], sizeof(port_path));
			printf("DEBUG bin_file = %s\n", bin_file_path);
		}
	}
	return 0;
}
/********** end of file **********/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>



#define BUF_SIZE 30
void error_handling(char *message);

int main(int argc, char *argv[])
{
	int send_sock;
	struct sockaddr_in broad_adr;
	FILE *fp;
	char buf[BUF_SIZE];
	int so_brd=1;   // SO_BROADCAST의 옵션정보를 1로 변경하기 위한 변수 초기화
	
	if(argc!=3) {
		printf("Usage : %s <Boradcast IP> <PORT>\n", argv[0]);
		exit(1);
	}
  
	send_sock=socket(PF_INET, SOCK_DGRAM, 0);	
	memset(&broad_adr, 0, sizeof(broad_adr));
	broad_adr.sin_family=AF_INET;
	broad_adr.sin_addr.s_addr=inet_addr(argv[1]);   //브로드 캐스트 ip
	broad_adr.sin_port=htons(atoi(argv[2]));        //브로드 캐스트 포트
	
    
    //SO_BROADCAST 옵션 값을 1로 변경해서 브로드캐스트 가능하게 만듬.
	setsockopt(send_sock, SOL_SOCKET, 
		SO_BROADCAST, (void*)&so_brd, sizeof(so_brd));	

    
    if((fp=fopen("news.txt", "r"))==NULL)
		error_handling("fopen() error");

	while(!feof(fp))
	{
		fgets(buf, BUF_SIZE, fp);
        //브로드 캐스트 주소 정보를 토대로 데이터를 송신
		sendto(send_sock, buf, strlen(buf), 
               0, (struct sockaddr*)&broad_adr, sizeof(broad_adr));
        
		sleep(1);
	}

	close(send_sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

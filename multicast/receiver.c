#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[])
{
    int recv_sock;
    int str_len;
    char buf[BUF_SIZE];
    struct sockaddr_in adr;
    struct ip_mreq join_adr;
	
    
    if (argc !=3) {
        printf("usage: %s <group ip> <port> \n" , argv[0]);
        exit(1);
    }
    
    
    //UDP 소켓 생성
    recv_sock = socket(PF_INET, SOCK_DGRAM,0);
    
    //멀티 캐스트 주소 정보 초기화
    memset(&adr, 0, sizeof(adr));
    adr.sin_family = AF_INET;
    adr.sin_addr.s_addr = inet_addr(argv[1]);   //멀티캐스트 ip
    adr.sin_port = htons(atoi(argv[2]));        //멀티캐스트 port
    
    //멀티 캐스트 주소정보를 기반으로 주소 할당
    bind(recv_sock, (struct sockaddr*)&adr, sizeof(adr));
    
    //가입
    join_adr.imr_multiaddr.s_addr = inet_addr(argv[1]); //멀티 캐스트 Ip
    join_adr.imr_interface.s_addr = htonl(INADDR_ANY);  //호스트 ip
    
    //멀티 캐스트 그룹 가입 설정
    setsockopt(recv_sock, IPPROTO_IP, IP_ADD_MEMBERSHIP,(void*)&join_adr, sizeof(join_adr));
    
    
    while (1) {
        
        //브로트 캐스트 된 데이터를 수신
        str_len = recvfrom(recv_sock , buf, BUF_SIZE -1 , 0 , NULL, 0);
        
        //printf("받은 str_len : %d \n" , str_len);
        
        if (str_len == 0) {
            break;
        }
        
       // printf("check - 0 \n");
        
        buf[str_len] = '\0';
        
        //printf("check - 1 \n");
        
        fputs(buf, stdout);
        
        //printf("check - 2 \n");
    }
    

    
    //소켓 연결 종료
    close(recv_sock);
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

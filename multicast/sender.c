#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fcntl.h>         // O_WRONLY
#include <unistd.h>        // write(), close()

#define TTL 64
#define BUF_SIZE 1024
void error_handling(char *message);

int main(int argc, char *argv[])
{
    
    int send_sock;
    struct sockaddr_in mul_adr;
    int time_live = TTL;
    //FILE *fp;
    int fd;
    char buf[BUF_SIZE];
    
    //경로 /멀티캐스트 IP / PORT번호
    if (argc != 3) {
        printf("usage : %s <groupIP> <PORT> \n" , argv[0]);
        exit(1);
    }
    
    //UDP 소켓 생성
    send_sock = socket(PF_INET,SOCK_DGRAM,0);
    
    
    //멀티 캐스트 주소 정보 초기화
    memset(&mul_adr , 0 , sizeof(mul_adr));
    mul_adr.sin_family = AF_INET;
    mul_adr.sin_addr.s_addr = inet_addr(argv[1]);    //멀티캐스트 ip
    mul_adr.sin_port = htons(atoi(argv[2]));         //멀티캐스트 포트
    
    //TTL 설정
    setsockopt(send_sock, IPPROTO_IP,
                 IP_MULTICAST_TTL,(void*)&time_live, sizeof(time_live));
    
    //파일을 읽기 전용으로 열기
//    fp = fopen("news.txt", "r");
//    if (fp == NULL) {
//        error_handling("fopen error");
//    }
//
    
    fd = open("news.txt", O_RDONLY);
    if(fd == -1) {
        error_handling("open error");
    }


    
    //broadcasting
    while (1) {
        
        //파일에서 데이터를 30 바이트 읽어서
        //char *result = fgets(buf, BUF_SIZE , fp);
        
        ssize_t result =  read(fd, buf, BUF_SIZE);
        
        if(result == 0){
            break;
        }
        
        //printf("보낼 데이터 buf : %s \n" , buf);
        
        //멀티캐스트 주소로 데이터 전달
        sendto(send_sock , buf, strlen(buf) , 0, (struct sockaddr*)&mul_adr , sizeof(mul_adr));
        
        //데이터 전송에 시간을 둘려고.
        sleep(1);
    }
    

    
    //fclose(fp);         //파일 닫기
    close(fd);       //low 레벨 파일 닫기
    close(send_sock);   //소켓 연결 종료
    
	
	return 0;
}

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

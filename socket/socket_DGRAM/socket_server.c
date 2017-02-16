/************************************
 * File name   : socket_server.c
 * Author      : SJC
 * Description : socket�����

 * Date        : 2016-8-17 17:00:54
 * Modification:
 *
 * Makefile    : gcc -o server socket_server.c -lm
*****************************************************/

#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
 
#include <netinet/in.h>
#include <sys/socket.h>
#include <signal.h> 
#include <unistd.h> 
#include <sys/types.h>  
  
int main(void)  
{  
    int server_sockfd = -1;  
    int server_len = 0;  
    int client_len = 0;  
    char buffer[512];  
    int result = 0; 
	
    struct sockaddr_in server_addr;  
    struct sockaddr_in client_addr;  
	
    //�������ݱ��׽���  
    server_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	
    //���ü���IP�˿�  
    server_addr.sin_family = AF_INET;  
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);  
    server_addr.sin_port = htons(9739);  
    server_len = sizeof(server_addr); 
	
    //�󶨣��������׽���  
    bind(server_sockfd, (struct sockaddr*)&server_addr, server_len);  
	
    //�����ӽ���ֹͣ���˳��ź�  
    signal(SIGCHLD, SIG_IGN);  
  
  
    while(1)  
    {     
		printf("server waiting......\n");
        //�������ݣ���client_addr������������Դ�����IP�˿�  
        result = recvfrom(server_sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_addr, &client_len);  
        if(fork() == 0)  
        {  
            //�����ӽ�������������  
            buffer[0] += 'a' - 'A';  
            sleep(2); 
			
            //���ʹ���������  
            sendto(server_sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_addr, client_len);  
            printf("%c\n", buffer[0]);  
			
            //ע�⣬һ��Ҫ�ر��ӽ��̣�����������л᲻����   
            exit(0);  
        }  
    }  
    //�ر��׽���  
    close(server_sockfd);  
	
	return 0;
}  
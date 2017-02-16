/************************************
 * File name   : socket_client.c
 * Author      : SJC
 * Description : socket�ͻ���

 * Date        : 2016-8-17 17:05:10
 * Modification:
 *
 * Makefile    : gcc -o client socket_client.c -lm
*****************************************************/
#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>

#include <unistd.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  


 
int main(int agrc, char *argv[])  
{  
    struct sockaddr_in server_addr;  
    int server_len = 0;  
    int sockfd = -1;  
    int result = 0;  
    char c = 'A';  
	
    //ȡ��һ�������ĵ�һ���ַ�  
    if(agrc > 1)  
        c = argv[1][0]; 
	
    //�������ݱ��׽���  
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);  
	
    //���÷�����IP�˿�  
    server_addr.sin_family = AF_INET;  
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  
    server_addr.sin_port = htons(9739);  
    server_len = sizeof(server_addr); 
	
    //���������������  
    sendto(sockfd, &c, sizeof(char), 0, (struct sockaddr*)&server_addr, server_len); 
		
	printf("client waiting......\n");
    //���շ�����������͹��������ݣ����ڲ�����������Դ�����԰Ѻ�����������Ϊ0  
    recvfrom(sockfd, &c, sizeof(char), 0, 0, 0);    //�����ȴ�
    printf("char from server = %c\n", c);  
	
    //�ر��׽���  
    close(sockfd);  
    //exit(0);
	return 0;
}  
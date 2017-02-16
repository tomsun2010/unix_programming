/************************************
 * File name   : socket_server.c
 * Author      : SJC
 * Description : socket�����

 * Date        : 2016-8-17 16:07:06
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
    int client_sockfd = -1;  
    int client_len = 0;  
    struct sockaddr_in server_addr;  
    struct sockaddr_in client_addr; 
	
    //�������׽���  
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);  
	
    //���÷��������յ����ӵ�ַ�ͼ����Ķ˿�  
    server_addr.sin_family = AF_INET;               //ָ�������׽���  
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);//��������IP��ַ������  
    server_addr.sin_port = htons(9736);             //�󶨵�9736�˿�
	
    //�󶨣��������׽���  
    bind(server_sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	
    //�����׽��ֶ��У������׽���  
    listen(server_sockfd, 5); 
	
    //�����ӽ���ֹͣ���˳��ź�  
    signal(SIGCHLD, SIG_IGN);  
      
    while(1)  
    {  
        char ch = '\0';  
        client_len = sizeof(client_addr);  
        printf("Server waiting......\n"); 
		
        //�������ӣ������µ��׽���  
        client_sockfd = accept(server_sockfd, (struct sockaddr*)&client_addr, &client_len);  
  
        if(fork() == 0)  
        {  
            //�ӽ����У���ȡ�ͻ��˷���������Ϣ��������Ϣ���ٷ��͸��ͻ���  
            read(client_sockfd, &ch, 1);  
            sleep(2);  
            ch++;  
            write(client_sockfd, &ch, 1);  
            close(client_sockfd);  
            exit(0);  
        }  
        else  
        {  
            //�������У��ر��׽���  
            close(client_sockfd);  
        }  
    } 
	return 0;
}  
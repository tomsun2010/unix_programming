/************************************
 * File name   : socket_client.c
 * Author      : SJC
 * Description : socket�ͻ���

 * Date        : 2016-8-17 16:07:14
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
#include <arpa/inet.h>  

  
int main(void)  
{  
    
    int len = 0;  
    int result = -1;  
    char ch = 'A'; 
	
	int sockfd = -1;  
	struct sockaddr_in address;  
	
    //�������׽���  
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
    //����Ҫ���ӵķ���������Ϣ  
    address.sin_family = AF_INET;                    //ʹ�������׽���  
    address.sin_addr.s_addr = inet_addr("127.0.0.1");//��������ַ  
    address.sin_port = htons(9736);                  //�������������Ķ˿�  
    len = sizeof(address);
	
    //���ӵ�������  
    result = connect(sockfd, (struct sockaddr*)&address, len);  
    if(result == -1)  
    {  
        perror("ops:client\n");  
        exit(1);  
    }  
	
    //���������������  
    write(sockfd, &ch, 1);  
	
    //�ӷ�������ȡ����  
    read(sockfd, &ch, 1);  
    printf("char form server = %c\n", ch);  
    close(sockfd);  
    //exit(0);  
	return 0;
}  
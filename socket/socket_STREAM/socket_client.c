/************************************
 * File name   : socket_client.c
 * Author      : SJC
 * Description : socket客户端

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
	
    //创建流套接字  
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
	
    //设置要连接的服务器的信息  
    address.sin_family = AF_INET;                    //使用网络套接字  
    address.sin_addr.s_addr = inet_addr("127.0.0.1");//服务器地址  
    address.sin_port = htons(9736);                  //服务器所监听的端口  
    len = sizeof(address);
	
    //连接到服务器  
    result = connect(sockfd, (struct sockaddr*)&address, len);  
    if(result == -1)  
    {  
        perror("ops:client\n");  
        exit(1);  
    }  
	
    //发送请求给服务器  
    write(sockfd, &ch, 1);  
	
    //从服务器获取数据  
    read(sockfd, &ch, 1);  
    printf("char form server = %c\n", ch);  
    close(sockfd);  
    //exit(0);  
	return 0;
}  
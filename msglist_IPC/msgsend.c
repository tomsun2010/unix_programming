/************************************
 * File name   : msgsend.c
 * Author      : SJC
 * Description : 消息队列实现IPC，发送端

 * Date        : 2016-8-18 10:50:29
 * Modification:
 *
 * Makefile    : gcc -o xxx xxx.c -lm
*****************************************************/
#include <stdio.h> 
#include <stdlib.h>   
#include <string.h> 

#include <unistd.h>  
#include <sys/msg.h>  
#include <errno.h>  
  
#define MAX_TEXT 512
//#define BUFSIZ 512   //已经被定义  
struct msg_st  
{  
    long int msg_type;  
    char text[MAX_TEXT];  
};  
  
int main(void)  
{  
    int running = 1;  
    struct msg_st data;  
    char buffer[BUFSIZ] = {};  
    int msgid = -1;  
  
    //建立消息队列  
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);  
    if(msgid == -1)  
    {  
        printf("msgget failed!!!\n");  
        exit(-1);  
    }  
  
    //向消息队列中写消息，直到写入end  
    while(running)  
    {  
        //输入数据  
        printf("Enter some text: ");  
        fgets(buffer, BUFSIZ, stdin);  
        data.msg_type = 1;    //注意2 :设置发送的信息的信息类型为1 
        strcpy(data.text, buffer);  
		
        //向队列发送数据  
        if(msgsnd(msgid, (void*)&data, MAX_TEXT, 0) == -1)  
        {  
            printf("msgsnd failed!!!\n");  
            exit(-1);  
        }  
		
        //输入end结束输入  
        if(strncmp(buffer, "end", 3) == 0) 
        {			
            running = 0;  
		}
        sleep(1);  
    }  
    return 0;  
}  
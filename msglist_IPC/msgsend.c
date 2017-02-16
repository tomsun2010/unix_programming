/************************************
 * File name   : msgsend.c
 * Author      : SJC
 * Description : ��Ϣ����ʵ��IPC�����Ͷ�

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
//#define BUFSIZ 512   //�Ѿ�������  
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
  
    //������Ϣ����  
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);  
    if(msgid == -1)  
    {  
        printf("msgget failed!!!\n");  
        exit(-1);  
    }  
  
    //����Ϣ������д��Ϣ��ֱ��д��end  
    while(running)  
    {  
        //��������  
        printf("Enter some text: ");  
        fgets(buffer, BUFSIZ, stdin);  
        data.msg_type = 1;    //ע��2 :���÷��͵���Ϣ����Ϣ����Ϊ1 
        strcpy(data.text, buffer);  
		
        //����з�������  
        if(msgsnd(msgid, (void*)&data, MAX_TEXT, 0) == -1)  
        {  
            printf("msgsnd failed!!!\n");  
            exit(-1);  
        }  
		
        //����end��������  
        if(strncmp(buffer, "end", 3) == 0) 
        {			
            running = 0;  
		}
        sleep(1);  
    }  
    return 0;  
}  
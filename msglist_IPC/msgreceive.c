/************************************
 * File name   : msgreceive.c
 * Author      : SJC
 * Description : ��Ϣ����ʵ��IPC�����ն�

 * Date        : 2016-8-18 10:42:12
 * Modification:
 *
 * Makefile    : gcc -o xxx xxx.c -lm
*****************************************************/

#include <stdio.h>
#include <stdlib.h>    
#include <string.h>

#include <unistd.h>   
#include <errno.h>  
#include <sys/msg.h>  
 
  
//#define BUFSIZ 512 
struct msg_st  
{  
    long int msg_type;  
    char text[BUFSIZ];  
};  
  
int main(void)  
{  
    int running = 1;  
    int msgid = -1;  
    struct msg_st data;  
    long int msgtype = 0; //ע��1:��ȡ�����е�һ�����õ���Ϣ 
  
    //������Ϣ����  
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);  
    if(msgid == -1)  
    {  
        printf("msgget failed!!!!\n");  
        exit(-1);  
    }
	
    //�Ӷ����л�ȡ��Ϣ��ֱ������end��ϢΪֹ  
    while(running)  
    {  
        if(msgrcv(msgid, (void*)&data, BUFSIZ, msgtype, 0) == -1)  
        {  
            printf("msgrcv failed!!!\n");  
            exit(-1);  
        }  
        printf("You write: %s\n",data.text);
		
        //����end����  
        if(strncmp(data.text, "end", 3) == 0)
		{			
            running = 0;  
		}
    }  
    //ɾ����Ϣ����  
    if(msgctl(msgid, IPC_RMID, 0) == -1)  
    {  
        printf("msgctl(IPC_RMID) failed!!!\n");  
        exit(-1);  
    }  
	
    return 0;  
}  
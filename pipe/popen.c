/************************************
 * File name   : popen.c
 * Author      : SJC
 * Description : 
 * Date        : 2016-8-22 15:34:46
 * Modification:
 *
 * Makefile    : gcc -o xxx xxx.c  
***************************************************/
#include <stdio.h>  
#include <string.h> 
#include <stdlib.h>
#include <unistd.h>  
  
int main(void)  
{  
    FILE *read_fp = NULL;  
    FILE *write_fp = NULL;  
    char buffer[BUFSIZ + 1];  
    int chars_read = 0;  
      
    //��ʼ��������  
    memset(buffer, '\0', sizeof(buffer));  
    //��ls��grep����  
    read_fp = popen("ls -l", "r");  
    write_fp = popen("grep rwxrwxr-x", "w");  
    
	//�������̶��򿪳ɹ�  
    if(read_fp && write_fp)  
    {  
        //��ȡһ�����ݿ�  
        chars_read = fread(buffer, sizeof(char), BUFSIZ, read_fp);  
        while(chars_read > 0)  
        {  
            buffer[chars_read] = '\0';  
            
			//������д��grep����  
            fwrite(buffer, sizeof(char), chars_read, write_fp);  
            
			//�������ݿɶ���ѭ����ȡ���ݣ�ֱ��������������  
            chars_read = fread(buffer, sizeof(char), BUFSIZ, read_fp);  
        }  
        //�ر��ļ���  
        pclose(read_fp);  
        pclose(write_fp);  
        exit(0);  
    }  
    return 0;  
}  
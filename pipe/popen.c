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
      
    //初始化缓冲区  
    memset(buffer, '\0', sizeof(buffer));  
    //打开ls和grep进程  
    read_fp = popen("ls -l", "r");  
    write_fp = popen("grep rwxrwxr-x", "w");  
    
	//两个进程都打开成功  
    if(read_fp && write_fp)  
    {  
        //读取一个数据块  
        chars_read = fread(buffer, sizeof(char), BUFSIZ, read_fp);  
        while(chars_read > 0)  
        {  
            buffer[chars_read] = '\0';  
            
			//把数据写入grep进程  
            fwrite(buffer, sizeof(char), chars_read, write_fp);  
            
			//还有数据可读，循环读取数据，直到读完所有数据  
            chars_read = fread(buffer, sizeof(char), BUFSIZ, read_fp);  
        }  
        //关闭文件流  
        pclose(read_fp);  
        pclose(write_fp);  
        exit(0);  
    }  
    return 0;  
}  
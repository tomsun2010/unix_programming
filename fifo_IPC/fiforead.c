/************************************
 * File name   : fiforead.c
 * Author      : SJC
 * Description : 命名管道实现IPC

 * Date        : 2016-8-18 14:18:14
 *
 * Makefile    : gcc -o xxx xxx.c -lm
*****************************************************/
#include <stdio.h>
#include <string.h>  
#include <stdlib.h>  
 
#include <unistd.h>  
#include <fcntl.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <limits.h>  
 
  
int main()  
{  
    const char *fifo_name = "/tmp/my_fifo";  
    int pipe_fd = -1;  
    int data_fd = -1;  
    int res = -1;  
    int open_mode = O_RDONLY;  
    char buffer[PIPE_BUF + 1] = {};  
    int bytes_read = 0;  
    int bytes_write = 0;  
    //清空缓冲数组  
    memset(buffer, '\0', sizeof(buffer));  
  
    printf("Process %d opening FIFO O_RDONLY\n", getpid());  
    //以只读阻塞方式打开管道文件，注意与fifowrite.c文件中的FIFO同名  
    pipe_fd = open(fifo_name, open_mode);  
    //以只写方式创建保存数据的文件  
    data_fd = open("DataFormFIFO.txt", O_WRONLY|O_CREAT, 0644);  
    printf("Process %d result %d\n",getpid(), pipe_fd);  
  
    if(pipe_fd != -1)  
    {  
        do  
        {  
            //读取FIFO中的数据，并把它保存在文件DataFormFIFO.txt文件中  
            res = read(pipe_fd, buffer, PIPE_BUF);  
            bytes_write = write(data_fd, buffer, res);  
            bytes_read += res;  
        }while(res > 0);  
        close(pipe_fd);  
        close(data_fd);  
    }  
    else
	{		
        exit(-1); 
	}		
  
    printf("Process %d finished, %d bytes read\n", getpid(), bytes_read);  
    return 0;  
}  
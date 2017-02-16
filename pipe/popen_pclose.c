/************************************
 * File name   : popen_pclose.c
 * Author      : SJC
 * Description : 
 * Date        : 2016-8-22 15:01:01
 * Modification:
 *
 * Makefile    : gcc -o xxx xxx.c  
***************************************************/

#include <stdio.h>  // printf popen pclose  
#include <stdlib.h>  
#include <string.h> //strerror
//#include <pthread.h>

//#include <unistd.h>
#include <error.h>  //error
#include <errno.h>  //errno
 
int comm_base_system_cmd(char* cmd)
{
	int	  ret = -1;
    FILE* cmd_fd = NULL;

    cmd_fd = popen(cmd, "r");
    if(cmd_fd == NULL)
    {
        printf("popen %s error : %s [errno = %d]\n", cmd, strerror(errno), errno);
        return -1;
    }

    ret = pclose(cmd_fd);
    cmd_fd = NULL;
	printf("shell ret=%d\r\n", ret);
		
    return ret;
}

int main(void)
{
	comm_base_system_cmd("mkdir tmp");  //在当前路径建立一个目录
	return 0;
}
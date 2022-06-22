/*

NAME
       mkfifo, mkfifoat - make a FIFO special file (a named pipe)

SYNOPSIS
       #include <sys/types.h>
       #include <sys/stat.h>

       int mkfifo(const char *pathname, mode_t mode);

        参数： 
            -pathname:管道名称的的路径
            -mode：文件的权限 和open的mode是一样的
                    是一个八进制的数
            返回值: 成功返回0，失败返回-1，并设置错误号


*/

#include<sys/types.h>
#include<stdio.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<unistd.h>


int main()
{   
    //判断文件是否存在
    int ret=access("fifo1",F_OK);
    if(ret==-1)
    {
            printf("管道不存在，创建管道\n");
            ret=mkfifo("fifo1",0664);
    
        if(ret==-1)
      {
         perror("mkfifo");
         exit(0);
      }
    }
    return 0;
}
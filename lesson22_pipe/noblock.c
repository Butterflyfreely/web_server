/*
       #include <unistd.h>
       
       int pipe(int pipefd[2]);
       //功能：创建一个匿名管道用来进程间通信 
         参数：int pipefd[2] 这个数组是一个传出参数
             pipefd[0] 对应的是管道的读端
             pipefd[1] 对应的是管道的些端
        返回值：
            成功 0
            失败 -1

        管道默认是阻塞的：如果管道中没有数据，read阻塞，如果管道满了，write阻塞
        注意：匿名管道只能用于具有关系的进程间之间的通信（父子进程，兄弟进程）            
*/

//子进程发送数据给父进程，附近还曾读取到数据输出
#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>


/*
    设置管道非阻塞
    int flags=fcntl(fd[0],F_GETTFL);//获取原来的的flag
    flags|=O_NONBLOCK;  //修改flag值
    fcntl(fd[0],F_SETFL,flags); //设置新的flag

*/

int main()
{
    //在fork之前创建管道
    int pipefd[2];
    int ret=pipe(pipefd);
    if(ret==-1)
    {
        perror("pipe");
        exit(0);
    }

    //创建子进程
    pid_t pid=fork();
    if(pid>0)
    {
        //父进程
        printf("i am parent process,pid:%d\n",getpid());
        //char buf[1024]={0};


        //从管道的读端读取数据
        char buf[1024]={0};


        int flags=fcntl(pipefd[0],F_GETFL);//获取原来的的flag
        flags|=O_NONBLOCK;  //修改flag值
        fcntl(pipefd[0],F_SETFL,flags); //设置新的flag


        while(1)
        {
            int len=read(pipefd[0],buf,sizeof(buf));
            printf("parent recv :%s,pid:%d,len=%d\n",buf,getpid(),len);
            memset(buf,0,1024);

            //向管道中写数据
            // char* str="hello,i am parent";
            // write(pipefd[1],str,strlen(str));  
        }
        

    }
    else if(pid==0)
    {
        //子进程   从管道的读取端读取数据
        // sleep(10);
       printf("i am child process,pid:%d\n",getpid());

       //关闭读端
       close(pipefd[0]);
       char buf[1024]={0};
       while(1)
       {
           //向管道中写入数据
           char* str="hello,i am child";
            write(pipefd[1],str,strlen(str));
            sleep(1);

       }
       
        
    }
    //return 0;
}



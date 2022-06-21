       /*
        #include <sys/types.h>
       #include <unistd.h>

       pid_t fork(void);
            函数作用：用于创建子进程
            返回值：
                fork()的返回值会返回两次，一次是在父进程中，一次是在子进程中。
                在父进程中返回创建的子进程ID，
                在子进程中返回0
                如何区分父进程和子进程：通过fork的返回值。
                在父进程中返回-1，表示创建子进程失败，并设置erron
       */
#include <sys/types.h>
#include <unistd.h>
#include<stdio.h>


int main()
{
    //创建子进程
    pid_t pid1=fork();

    //判断是父进程还是子进程
    if(pid1>0)
    {
        printf("pid:%d\n",pid1);
        //如果大于0，返回的是创建的子进程号
        //printf("i am parent process,pid:%d,ppid:%d\n",getpid(),getppid());
        int num=10;
        printf("i am parent process,pid:%d,ppid:%d\n,num=%d",getpid(),getppid(),num);

    }else if(pid1==0){
        //子进程
        //printf("i am son process,pid:%d,ppid:%d\n",getpid(),getppid());        
        int num=11;
        printf("i am son process,pid:%d,ppid:%d\n,num=%d",getpid(),getppid(),num);

        printf("---------------");

        num=12;
        printf("i am son process,pid:%d,ppid:%d\n,num=%d",getpid(),getppid(),num);

    }
    else if(pid1==-1)printf("error");

    // //for循环
    // for(int i=0;i<100;i++)
    // {
    //     printf("\ni:%d,pid:%d",i,getpid());
	//     //sleep(1);
    // }
    // printf("\n");

    return 0;
}

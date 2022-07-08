//#define tickets 100

#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

int tickets=10000;

//创建一个互斥量
pthread_mutex_t mutex;


/*
同一张门票被卖多次的情况：原因->线程同步 
三个线程抢占处处理机，在回调函数中由于A线程还在休眠，此时tickets还未--，这时B线程调用了回调函数，开始休眠，C又来了。
不一会儿三个线程都进来了，tickets分别被输出，然后又--，也可能会出现负数的情况

*/


void *sellticket(void* arg)
{
    //printf("son1 thread id:%d\n",pthread_self());

    //卖票
    //——————————临界区————————————————————————————————————
    //usleep(5000);
    while(1)
    {
            //加锁
             pthread_mutex_lock(&mutex);
             pthread_mutex_lock(&mutex);
        if(tickets>0)
        {
            usleep(20000);
            printf("%ld 正在卖第 %d 张票\n",pthread_self(),tickets);
            tickets--;
        }
        else{
            //解锁
                 pthread_mutex_unlock(&mutex);
            break;
        }
            //解锁
         pthread_mutex_unlock(&mutex);

    }
    //——————————临界区————————————————————————————————————

    return NULL;
}

int main()
{
    //初始化一个互斥量
    pthread_mutex_init(&mutex,NULL);

    //创建三个子线程
    pthread_t tid1;
    pthread_t tid2;
    pthread_t tid3;

    int ret1=pthread_create(&tid1,NULL,sellticket,NULL);
    int ret2=pthread_create(&tid2,NULL,sellticket,NULL);
    int ret3=pthread_create(&tid3,NULL,sellticket,NULL);


    //回收子线程的资源，阻塞
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_join(tid3,NULL);


    //释放互斥量资源
    pthread_mutex_destroy(&mutex);
 
    return 0;
}
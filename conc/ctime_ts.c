#include "common.h"

#define MAXSTR 128


static sem_t mutex;



static void init_ctime_ts(void){
    Sem_init(&mutex,0,1);
}

/* 对线程不安全的函数包装 */
char* ctime_ts(const time_t* timep,char *privatep){
    char* sharep;
    P(&mutex);
    //not thread safe
    sharep=ctime(timep);
    strcpy(privatep,sharep);
    V(&mutex);
    return privatep;
}

int main(int argc, char const *argv[])
{
    char timestr[MAXSTR];
    time_t timeval;

    /* 线程安全的获取当前时间 */
    init_ctime_ts();
    timeval=time(NULL);
    ctime_ts(&timeval,timestr);
    printf("%s", timestr);
    return 0;
}

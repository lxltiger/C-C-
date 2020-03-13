#include "common.h"

#define N 10
/*信号量s是一个全局非负整数，
*P(s):如果s是非0值，s减1返回；如果s为0线程就挂起直到s为非0
*V(s):将s加1，如果有任何线程阻塞等待s变为非0，重启这些线程中的一个
*/
/*相对公平的读写，假设读者的数量为N*/

//读写互斥的锁，初始化为N
sem_t mutex ;

// 写者使用的锁，初始化为1
sem_t mutex_w;



void read(){
	while(1){		
		P(&mutex);
		//read operation
		V(&mutex);
	}
}

void write(){
	while(1){
		//其它写者阻塞
		P(&mutex_w);
		//占用共锁，需要拿到全部，如果有读者在用会阻塞直至所有读者离开
		for (int i = 0; i < N; ++i){
			P(&mutex);
		}
		//拿到mutex锁，释放mutex_w锁，其它写者会从mutex_w继续，但会阻塞在mutex上 ；其它读者也阻塞在mutex上
		V(&mutex_w);
		//write op

		//逐渐释放mutex，此时读者、写者在竞争，都可能拿到，区别是读者拿到一个就可以进行读操作，而写者要拿到全部
		for (int i = 0; i < N; ++i){
			V(&mutex);
		}

	}
}
#include "common.h"


int reader_num;
//写锁
sem_t mutex_w;/*  initially = 1 */
//读者数量更新锁 只有读者使用
sem_t mutex_num;/*  initially = 1 */


/*读者有微弱的优势，只要有读者在读，其它读者可自由读，写者需要等待*/

void read(){

	while(1){
		P(&mutex_num);
		reader_num++;
		if(reader_num==1)
			P(&mutex_w);
		V(&mutex_num);
		//Read operation

		P(&mutex_num);
		reader_num--;
		if(reader_num==0)
			V(&mutex_w);
		V(&mutex_num);
	}

}

// 当多个写者存在  可能使读者饥饿
void write(){
	while(1){
		P(&mutex_w);
		//Write operation
		V(&mutex_w);
	}
}


sem_t mutex_extra;/*初始化为1*/
/*读者占有明显优势*/
void generous_write(){
	while(1){
		//多个写者先阻塞于此
		P(&mutex_extra);
		P(&mutex_w);
		//Write operation

		//释放写锁，让读者优先获取 写者不参与竞争
		V(&mutex_w);
		//再释放额外的锁 
		V(&mutex_extra);

	}
}

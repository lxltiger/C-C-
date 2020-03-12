#include "common.h"
#include "sbuf.h"



void sbuf_init(sbuf_t *sp,int n){
	sp->buf=Calloc(n,sizeof(int));
	sp->n=n;
	sp->front=sp->rear=0;
	Sem_init(sp->mutex,0,1);
	Sem_init(sp->slots,0,n);
	Sem_init(sp->items,0,0);
}


void sbuf_deinit(sbuf_t *sp){
	Free(sp->buf);

}

/*n个slot 所以最多同时允许n个线程执行插入操作 但同一个slot只允许一个线程执行*/
void sbuf_insert(sbuf_t *sp,int item){
	P(&sp->slots);/*wait slot*/
	P(&sp->mutex);/*lock buf*/
	sp->buf[(++sp->rear)%(sp->n)]=item;
	V(&sp->mutex);/*unlock buf*/
	V(&sp->items);/*items 初始化为0，现在通知有可用的items 如果有消费者等待会唤醒它*/
}

int sbuf_remove(sbuf_t *sp){
	int item;
	P(&sp->items);/*wait items*/
	P(&sp->mutex);/*lock buf*/
	item=sp->buf[(sp->front+1)%(sp->n)];
	V(&sp->mutex);/*unlock buf*/
	V(&sp->slots);/*通知有可用的slot*/
	return item;
}
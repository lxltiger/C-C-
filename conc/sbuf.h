#ifndef SBUF_H__
#define SBUF_H__

#include "common.h"

typedef struct {
	int *buf;/*buffer array*/
	int n;/*max num of slot*/
	int front;/*front+1)%n is first item*/
	int rear;/*rear %n last item*/
	sem_t mutex;/*protect access to buf*/
	sem_t slots;/*counts available slot*/
	sem_t items;/*count avaiable items*/

} sbuf_t;


void sbuf_init(sbuf_t *sp,int n);
void sbuf_deinit(sbuf_t *sp);
void sbuf_insert(sbuf_t *sp,int item);
int sbuf_remove(sbuf_t *sp);
#endif


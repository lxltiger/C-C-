#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef void SeqList;
// typedef void SeqListNode;

typedef struct SeqListNode
{
	struct SeqListNode *next;
} SeqListNode;

typedef struct TSeqList
{
	SeqListNode header;
	int length;
}TSeqList;

typedef struct Teacher
{
	SeqListNode node;
	int age;
	char name[32];
}Teacher;


SeqList* SeqList_Create(){

	TSeqList *temp=(TSeqList *)malloc(sizeof(TSeqList));
	if (temp==NULL)
	{
		return NULL;
	}
	memset(temp,0,sizeof(TSeqList));
	// temp->length=0;
	// temp->header=NULL;
	return temp;
}

//释放Create方法分配的资源
void SeqList_Destroy(SeqList* slist){
	if (slist==NULL){
		free(slist);
	}
}

void SeqList_Clear(SeqList* slist){
	if (slist==NULL)
	{
		return;
	}
	TSeqList *list=(TSeqList *)slist;
	list->header.next=NULL;
	list->length=0;
}

int SeqList_Length(SeqList* slist){
	if (slist==NULL)
	{
		return -1;
	}
	TSeqList *list=(TSeqList *)slist;
	
	return list->length;
}

int SeqList_Insert(SeqList* slist, SeqListNode* node, int pos){
	if (slist==NULL||node==NULL||pos<0)
	{
		return -1;
	}

	TSeqList *list=(TSeqList *)slist;
	if(pos>list->length){
		pos=list->length;
	}

	SeqListNode *temp=&(list->header);
	// SeqListNode *header=list->header;
	// 跳到要插入位置的前一个节点，从header起跳，但header不属于list元素
	for (int i = 0; i < pos&&temp->next; ++i)
	{
		temp=temp->next;
	}
	//新插入的节点先连接后面的
	node->next=temp->next;
	//设置上一个节点的下个为新节点
	temp->next=node;
	list->length++;

	return 0;

}

SeqListNode* SeqList_Get(SeqList* slist, int pos){
	if (slist==NULL||pos<0)
	{
		return NULL;
	}

	TSeqList *list=(TSeqList *)slist;
	if(pos>list->length){
		return NULL;
	}
	SeqListNode *temp=&(list->header);
	for (int i = 0; i < pos&&temp->next; ++i)
	{
		temp=temp->next;
	}
	return temp->next;


}

SeqListNode* SeqList_Delete(SeqList* slist, int pos){
	if (slist==NULL||pos<0)
	{
		return NULL;
	}

	TSeqList *list=(TSeqList *)slist;
	if(pos>list->length){
		return NULL;
	}
	SeqListNode *current=&(list->header);
	for (int i = 0; i < pos&&current->next; ++i)
	{
		current=current->next;
	}
	//保存要删除的节点
	SeqListNode *temp=current->next;
	// 上个节点指向下歌
	current->next=temp->next;
	list->length--;
	return temp;

}
void print(SeqList *slist){
	int len=SeqList_Length(slist);
	printf("len=%d\n", len);

	Teacher *temp=NULL;
	/*for (int i = 0; i < len; ++i)
	{
		temp=(Teacher *)SeqList_Get(list,i);
		if(temp){
			printf("age=%d\n", temp->age);
		}

	}*/
	TSeqList *list=(TSeqList *)slist;
	SeqListNode *header=&(list->header);
	SeqListNode *node=NULL;
	while(header->next){
		node=header->next;
		temp=(Teacher *)node;
		printf("head=%p,age=%d\n",header, temp->age);
		header=node;
	}
	puts("\n");

}

/*测试代码*/
int main(int argc, char const *argv[])
{
	/* code */
	Teacher t1,t2,t3,t4;
	t1.age=10;
	t2.age=20;
	t3.age=30;
	t4.age=40;
	SeqList *list=SeqList_Create();
	/*可以随机插入 但不能随机删除*/
	SeqList_Insert(list,(SeqListNode *)(&t1),6);
	SeqList_Insert(list,(SeqListNode *)(&t2),5);
	SeqList_Insert(list,(SeqListNode *)(&t3),4);
	SeqList_Insert(list,(SeqListNode *)(&t4),2);
	
	print(list);

	while(SeqList_Length(list)>0){
		SeqList_Delete(list,SeqList_Length(list)-1);//从尾部删除
		SeqList_Delete(list,0);//从头部删除
		print(list);
	}






	return 0;
}


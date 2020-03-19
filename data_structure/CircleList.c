#include "stdio.h"
#include "stdlib.h"
#include "string.h"


typedef void List;

typedef struct CircleListNode
{
	struct CircleListNode *next;
}CircleListNode;

typedef struct _tag_CircleList
{
	CircleListNode header;
	CircleListNode *slider;
	int length;	
}CircleList;

typedef struct Teacher
{
	CircleListNode *next;
	int age;
	
}Teacher;


List* createCircleList(){
	CircleList *list=(CircleList *)malloc(sizeof(CircleList));
	if (list==NULL)
	{
		return NULL;
	}

	memset(list,0,sizeof(CircleList));
	return list;
}

void destoryCircleList(List *list){
	if (list==NULL)
	{
		return;
	}

	free(list);
	
}

void clearCircleList(List *list){
	if (list==NULL)
	{
		return;
	}

	CircleList *circleList=(CircleList *)list;
	circleList->header.next=NULL;
	circleList->slider=NULL;
	circleList->length=0;
}

int getCircleListLength(List *list){
	if (list==NULL)
	{
		return -1;
	}

	CircleList *circleList=(CircleList *)list;
	return circleList->length;
}

//获取节点
CircleListNode* getCircleListNode(List *list,int pos){
	if(list==NULL||pos<0){
		return NULL;
	}
	CircleList *circleList=(CircleList *)list;
	CircleListNode *current=&(circleList->header);
	//只有链表为空时 current－next才为空 因为时循环链表 总有下一个
	for (int i = 0; i < pos&&current->next; ++i)
	{
		current=current->next;
	}

	return current->next;

}

int insert(List *list,CircleListNode *node,int pos) {
	if(list==NULL||node==NULL||pos<0){
		return -1;
	}

	CircleList *circleList=(CircleList *)list;
	//链表的起始位置 也是存储第一个节点的位置
	CircleListNode *current=&(circleList->header);
	//只有第一次插入时 current－next才为空 因为时循环链表 总有下一个
	for (int i = 0; i < pos&&current->next; ++i)
	{
		current=current->next;
	}

	// 找到要插入位置的前一个节点current后，插入新节点
	node->next=current->next;
	current->next=node;

	if(circleList->length==0){
		circleList->slider=node;
	}
	circleList->length++;
	//如果是头插入法 不能通过pos＝0判断，第一次插入即使pos>0 都是头插法,以后只用pos＝＝0才是头插法
	if(current==(CircleListNode *)circleList){
		CircleListNode *last=getCircleListNode(list,circleList->length-1);
		last->next=current->next;
	}
	return pos;
}

CircleListNode* deleteCircleList(List *list,int pos){
	if(list==NULL||pos<0){
		return NULL;
	}

	CircleList *circleList=(CircleList *)list;
	if(circleList->length==0)return NULL;
	//链表的起始位置 也是存储第一个节点的位置
	CircleListNode *current=&(circleList->header);
	
	for (int i = 0; i < pos; ++i)
	{
		current=current->next;
	}
	// 要删除的节点
	CircleListNode *node_to_delete=current->next;
	current->next=node_to_delete->next;
	//减少一个
	circleList->length--;

	if(circleList->length==0){
		circleList->header.next=NULL;
		circleList->slider=NULL;
		return node_to_delete;
	}
	//删除头节点需要重新设置循环 pos=0判断不准 pos％len＝0或current==(CircleListNode *)(list)
	if(pos==0){
		CircleListNode *last=getCircleListNode(list,circleList->length-1);
		last->next=current->next;
		// 更改链表的起始点
		circleList->header.next=current->next;

	}
	//如果删除的节点正好是游标所指，指向下一个
	if(node_to_delete==circleList->slider){
		circleList->slider=current->next;
	}
	

	return node_to_delete;

}

CircleListNode* deleteCircleListNode(List *list,CircleListNode *node_to_delete){
	if(list==NULL||node_to_delete==NULL){
		return NULL;
	}

	CircleList *circleList=(CircleList *)list;
	if(circleList->length==0)return NULL;

	CircleListNode *current=&(circleList->header);
	CircleListNode *found=NULL;
	int i=0;
	for (; i < circleList->length; ++i)
	{
		
		current=current->next;
		if(current==node_to_delete){
			found=node_to_delete;
			break;
		}
	}

	if (found)
	{
		deleteCircleList(list,i);
	}



	return found;
}
//目的 游标指向第一个元素
void resetCircleList(List *list){
	if(list==NULL){
		return ;
	}

	CircleList *circleList=(CircleList *)list;
	CircleListNode *current=&(circleList->header);
	circleList->slider=current->next;
}

CircleListNode* currentNode(List *list){
	if(list==NULL){
		return NULL;
	}

	CircleList *circleList=(CircleList *)list;
	return circleList->slider;
}

CircleListNode* nextNode(List *list){
	if(list==NULL){
		return NULL;
	}

	CircleList *circleList=(CircleList *)list;
	CircleListNode *node=NULL;
	if(circleList->slider){
		node=circleList->slider;
		circleList->slider=node->next;
	}
	return node;
}

void printCircleList(List *list){

	if(list==NULL){
		return ;
	}

	CircleList *circleList=(CircleList *)list;

	int len=circleList->length;
	for (int i = 0; i < len; ++i)
	{
		Teacher *teacher= (Teacher *)getCircleListNode(list,i);
		printf("age%d\n", teacher->age);
	}
	printf("\n");
}



int main(int argc, char const *argv[])
{
	/* code */

	CircleList *list= (CircleList *)createCircleList();
	Teacher teachers[8];
	int  len=sizeof(teachers)/sizeof(teachers[0]);
	
	for (int i = 0; i < len; ++i)
	{
		teachers[i].age=(i+1)*10;
		insert(list,(CircleListNode *)(&teachers[i]),i);
	}

	printCircleList(list);

	Teacher *out=NULL;

	for (int i = 0; i < len; ++i)
	{
		
		for (int i = 0; i < 3; ++i)
		{
			out=(Teacher *)nextNode(list);

		}
		printf("age:%d\t", out->age);

		deleteCircleListNode(list,(CircleListNode *)out);

		
		
	}

	destoryCircleList(list);
	return 0;
}
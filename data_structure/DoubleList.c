#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef void List;

typedef struct ListNode
{
	struct ListNode *next;
	struct ListNode *pre;
}ListNode;

typedef struct DList
{
	ListNode listNode;
	ListNode *slide;
	int length;
}DList;

List* createDList() {
	DList *list=(DList *)malloc(sizeof(DList));
	if(list==NULL){
		return NULL;
	}

	list->listNode.pre=NULL;
	list->listNode.next=NULL;
	list->slide=NULL;
	list->length=0;
	return list;
}

void destroyDList(DList *list){
	if(list==NULL){
		return;
	}
	free(list);
}

int insertNode(List *list,ListNode *node,int pos){
	if(list==NULL||node==NULL||pos<0){
		return -1;
	}

	DList *dlist=(DList *)list;
	//插入点的前节点
	ListNode *current=(ListNode *)dlist;
	for (int i = 0; i < pos&&current->next; ++i)
	{
		current=current->next;
	}
	
	// 要插入位置的节点，如果不为空需要后移
	ListNode *next=current->next;
	// 当前节点指向新节点
	current->next=node;
	// 新节点指向下一个
	node->next=next;
	// 新节点指向前一个
	node->pre=current;

	//如果不是插在最后
	if(next){
		next->pre=node;
	}
	// first time
	if(dlist->length==0){
		dlist->slide=node;
	}

	//insert in pos 0
	if(current==(ListNode *)dlist){
		node->pre=NULL;
	}

	dlist->length++;
	return pos;

}

ListNode* deleteNode(List *list,int pos){
	if(list==NULLpos<0){
		return NULL;
	}

	DList *dlist=(DList *)list;

	if(dlist->length==0)return NULL;

	ListNode *current=(ListNode *)dlist;

	for (int i = 0; i < pos&&current->next; ++i)
	{
		current=current->next;
	}
	// 要删除的节点
	ListNode *node_to_delete=current->next;
	// 下一个节点，当删除的是尾节点时可能为空
	ListNode *next=node_to_delete->next;

	current->next=next;
	
	if(next){		
		next->pre=current;
		// head node
		if(current==(ListNode *)dlist){
			next->pre=NULL;
		}
	}
	if(dlist->slide=node_to_delete){
		dlist->slide=next;
	}
		
	

	dlist->length--;

	return node_to_delete;


}


int main(int argc, char const *argv[])
{
	DList *list=(DList *)createDList();

	destroyDList(list);

	return 0;
}
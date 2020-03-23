#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "SeqList.h"


typedef  struct tag_sqelist
{
	int capacity;
	int length;
	// 指针数组 存储节点的指针 操作都针对指针 效率高尤其涉及到复制
	long** node;

} TSqeList;


/*创建线性表并根据容量分配内存*/
SeqList* SeqList_Create(int capacity)
{
	TSqeList* list=(TSqeList *)malloc(sizeof(TSqeList));
	if(list==NULL) return NULL;
	// 将结构体的值都初始化为0
	memset(list,0,sizeof(TSqeList));
		//在堆上分配节点指针的内存 将首地址赋给指针数组
	list->node=(long**)malloc(sizeof(long *)*list->capacity);
	//  分配失败返回NULL
	if(list->node==NULL)return NULL;
	list->capacity=capacity;
	list->length=0;

	return list; 
}

/*销毁线性表 释放堆上分配的空间*/
void SeqList_Destroy(SeqList* list)
{
	if (list==NULL)return;
	// SeqList 类型为void，转化成我们需要的
	TSqeList* tlist=(TSqeList*)list;
	// 释放节点数组内存
	if(tlist->node!=NULL)free(tlist->node);
	// 释放顺序表内存
	free(tlist);

}

// 清空线性表 回到初始化状态
void SeqList_Clear(SeqList* list)
{
	if (list==NULL)return;
	// SeqList 类型为void，转化成我们需要的
	TSqeList* tlist=(TSqeList*)list;
	tlist->length=0;
	memset(tlist->node,0,sizeof(long*)*tlist->capacity);


}
// 获取线性表的长度
int SeqList_Length(SeqList* list)
{
	if (list==NULL)return -1;
	// SeqList 类型为void，转化成我们需要的
	TSqeList* tlist=(TSqeList*)list;
	return tlist->length;
}

// 获取线性表的容量
int SeqList_Capacity(SeqList* list)
{
	if (list==NULL)return -1;
	// SeqList 类型为void，转化成我们需要的
	TSqeList* tlist=(TSqeList*)list;
	return tlist->capacity;
}


/*插入一个节点
1.判断线性表 节点 位置是否有效
2.判断容量是否充足
3.判断插入点是否在容量范围*/
int SeqList_Insert(SeqList* list, SeqListNode* node, int pos)
{
	int ret=0;
	if (list==NULL||node==NULL||pos<0){
		ret=-1;
		printf("SeqList_Insert fun error %d\n",ret);
		return ret;
	}

	// SeqList 类型为void，转化成我们需要的
	TSqeList* tlist=(TSqeList*)list;
	// 线性表已经填满
	if(tlist->length>=tlist->capacity){
		ret=-2;
		printf("SeqList_Insert fun error %d\n", ret);
		return ret;
	}
	// 如果插入位置超过当前长度 插在表尾
	if(pos>=tlist->length){
		pos=tlist->length;
	}

	// 将线性表pos后的元素后移
	for (int i = tlist->length; i > pos; --i)
	{
		tlist->node[i]=tlist->node[i-1];
	}
	// 设置pos位的值为插入的节点
	tlist->node[pos]=node;
	//  增加长度
	tlist->length++;


	return ret;
}

// 获取指定位置节点
SeqListNode* SeqList_Get(SeqList* list, int pos)
{
	if (list==NULL)return NULL;
	TSqeList* tlist=(TSqeList*)list;
	// 判断所取节点的位置是否有效
	if(pos<0||pos>=tlist->length)return NULL;
	return (SeqListNode *)tlist->node[pos];
}


// 删除一个节点
SeqListNode* SeqList_Delete(SeqList* list, int pos)
{
	if (list==NULL)return NULL;
	TSqeList* tlist=(TSqeList*)list;
	// 判断 所取节点的位置是否有效
	if(pos<0||pos>=tlist->length)return NULL;
	// 取出要删除的节点
	SeqListNode* node=(SeqListNode *)tlist->node[pos];
	// 删除节点之后的位置前移 使用＋1判断是否是最后一个元素 防止越界
	for (int i = pos+1; i < tlist->length; ++i)
	{
		tlist->node[i-1]=tlist->node[i];
	}
	// 将长度减少
	tlist->length--;
	return node;
}

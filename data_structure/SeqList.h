#ifndef MY_SEQLIST_H
#define MY_SEQLIST_H value

/*C语言版的顺序存储，选择数组实现线性储存，插入删除麻烦但索引方便
让业务节点包含我们的节点实现业务和数据的分离*/

// 没有类型的线性表结构体
typedef void SeqList;
// 没有类型的节点结构体，不在乎具体的业务类型，都强转为void
typedef void SeqListNode;

SeqList* SeqList_Create(int capacity);

void SeqList_Destroy(SeqList* list);

void SeqList_Clear(SeqList* list);

int SeqList_Length(SeqList* list);

int SeqList_Capacity(SeqList* list);

int SeqList_Insert(SeqList* list, SeqListNode* node, int pos);

SeqListNode* SeqList_Get(SeqList* list, int pos);

SeqListNode* SeqList_Delete(SeqList* list, int pos);
#endif
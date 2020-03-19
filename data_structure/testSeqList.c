#include "SeqList.c"
/*测试线性表的顺序存储*/
typedef struct _Teacher
{
	int age;
	char name[64];
}Teacher;

void printContent(SeqList *list){
	Teacher *temp;
	int len=SeqList_Length(list);
	for (int i = 0; i < len; ++i)
	{
		temp=(Teacher *)SeqList_Get(list,i);
		if (temp)
		{
			printf("%s:%d\n", temp->name,temp->age);
		}
	}
}

int main(int argc, char const *argv[])
{

	Teacher t1,t2,t3,t4;
	t1.age=20;
	strcpy(t1.name,"hei");
	t2.age=30;
	strcpy(t2.name,"duang");
	t3.age=40;
	strcpy(t3.name,"hei2");
	t4.age=30;
	strcpy(t4.name,"duang2");

	
	SeqList* list=SeqList_Create(10);
	// 强转业务节点为void插入线性表
	SeqList_Insert(list,(SeqListNode *)&t1,0);
	SeqList_Insert(list,(SeqListNode *)&t2,0);
	SeqList_Insert(list,(SeqListNode *)&t3,4);
	SeqList_Insert(list,(SeqListNode *)&t4,7);


	int len=SeqList_Length(list);
	printf("len=%d\n", len);

	printContent(list);
	
	SeqList_Delete(list,SeqList_Length(list)-1);
	SeqList_Delete(list,0);

	printContent(list);

	SeqList_Destroy(list);
	return 0;
	
}


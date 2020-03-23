#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct name
{
	/* 使用字符指针代替字符数组，此时结构体包含的是两个指针的大小 */
	char *first;
	char *last;
	int length;
};

/*使用结构体地址作为形参*/
void getInfo(name *pst){
	char  temp[81];
	puts("first name");
	gets(temp);
	// 为名字分配合适的空间
	pst->first=(char *)malloc(strlen(temp)+1);
	// 把名字复制到分配的内存中
	strcpy(pst->first,temp);

	puts("last name");
	gets(temp);
	pst->last=(char *)malloc(strlen(temp)+1);
	strcpy(pst->last,temp);
}

void makeInfo(name *pst){
	pst->length=strlen(pst->first)+strlen(pst->last);
}

void showInfo(name *pst){
	printf("fist name %s last name %s ,the total length is %d\n",pst->first,pst->last,pst->length );

}

// 使用malloc函数分配的空间要手动释放
void freeInfo(name *pst){
	free(pst->first);
	free(pst->last);
}
/*在结构体中使用字符指针,使用malloc函数*/
int main(int argc, char const *argv[])
{
	/* code */
	struct name jack;
	getInfo(&jack);
	makeInfo(&jack);
	showInfo(&jack);
	freeInfo(&jack);
	return 0;
}

#define MAX 40

struct Film
{
	char title[MAX];
	int rating;
	struct Film *next;//下一个电影的数据结构地址
	/* data */
};
int main(int argc, char const *argv[])
{

	Film *head=NULL;
	Film *current;
	Film *previous;
	char input[MAX];
	puts("plese enter title of the file");
	while(gets(input)!=NULL&&input[0]!='\0'){
		current=(struct Film *)malloc(sizeof(struct Film));
		if(head==NULL){
			head=current;
		}else{
			previous->next=current;
		}
		current->next=NULL;
		strcpy(current->title,input);
		puts("enter Movie rating");
		scanf("%d",&current->rating);
		while(getchar()!='\n'){
			continue;
		}
		previous=current;
		puts("plesase enter next info with empty line to exit");
	}

	if(head!=NULL){
		current=head;
		while(current!=NULL){
			printf("Movie title %s,Rating:%d\n",current->title,current->rating);
			current=current->next;
		}
		current=head;
		while(current!=NULL){
			free(current);
			current=current->next;
		}
	}
		puts("endind");

	
	return 0;
}
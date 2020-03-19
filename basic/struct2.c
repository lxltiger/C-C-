#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 41
#define MAX_BOOK_NUM 30

struct book
{
	/* data */
	char title[MAX];
	char author[MAX];
	float price;
};
/* 把结构体数组保存到book.dat文件中，如果文件存在，读出数据 */

int main(int argc, char const *argv[])
{
	FILE *fp;
	if((fp=fopen("book.dat","a+b"))==NULL){
		fprintf(stderr, "%s\n", "fail to open file book.dat");
		exit(1);
	}
	struct book classic[MAX_BOOK_NUM];
	int num=0;
	// 如果文件已存在 读取数据,先到文件开始
	rewind(fp);
	while(num<MAX_BOOK_NUM&&fread(&classic[num],sizeof(book),1,fp)==1){
		printf("title:%s,author:%s,price:%.2f\n",classic[num].title,classic[num].author,classic[num].price );

		num++;
	}
	if(feof(fp)){
		printf("you already reach end of file\n");
	}else if(ferror(fp)){
		fprintf(stderr, "%s\n", "exception when reading book.dat");
	}

	int old=num;
	puts("enter title of book with empty line to exit");
	while(num<MAX_BOOK_NUM&&gets(classic[num].title)&&classic[num].title[0]!='\0'){
		puts("author");
		gets(classic[num].author);
		puts("price");
		// 假设正确输入
		int result=scanf("%f",&classic[num].price);
		// 去除多余字符，主要是换行符
		while(getchar()!='\n'){
			continue;
		}
		num++;
		if(num<MAX_BOOK_NUM){
			puts("enter title of book with empty line to exit");
		}
	}

	for (int i = old; i < num; ++i)
	{
		fwrite(&classic[i],sizeof(book),1,fp);
	}


	fclose(fp);



	return 0;
}
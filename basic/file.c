#include <stdio.h>
#include <stdlib.h>/*exit()原型*/
#include <string.h>
#define MAX 41

#define BUFFER_SIZE 1024
/*打开用户键盘输入的文件名并在控制台显示内容*/
void count(void){

	char fileName[MAX];
	FILE *fp;
	// 逐个读取的字符
	int ch;
	puts("enter file name with emtpy line to exit");
	while(gets(fileName)&&fileName[0]!='\0'){
		if((fp=fopen(fileName,"r"))==NULL){
			fprintf(stderr, "fail to open %s\n", fileName);
			puts("enter file name with emtpy line to exit");
			continue;
			// exit(1);
		}
		// 读取字符并显示
		while((ch=getc(fp))!=EOF){
			putchar(ch);
			// putc(ch,stdout)  //同上
		}

		// 判断读写错误
		if(ferror(fp))
			puts("IO error while reading ");
		else if(feof(fp))
			puts("reach end of file sucessfully ");
		

		fclose(fp);
		puts("enter file name with emtpy line to exit");

	}

}
/*文件的复制，从命令行获取源和目的文件，使用二进制模式读区和写入文件*/
void file_copy(void){
	FILE *source,*target;
	char fileSourceName[MAX];
	char fileTargetName[MAX];
	puts("please enter name of source file");
	if(gets(fileSourceName)&&fileSourceName[0]!='\0'){
		if((source=fopen(fileSourceName,"rb"))==NULL){
			fprintf(stderr, "fail to open %s\n", fileSourceName);
			exit(1);
		}
	}else{
		exit(1);
	}
	puts("please enter name of target,coverd if exist");
	while(gets(fileTargetName)&&fileTargetName[0]!='\0'){
		// 比较目标文件和源文件，不能是同一文件
		if(strcmp(fileSourceName,fileTargetName)==0){
			fprintf(stderr, "target file %s can be same with source file %s\n", fileTargetName,fileSourceName);
			puts("please enter name of target,coverd if exist");
			continue;
		}
		if((target=fopen(fileTargetName,"wb"))==NULL){
			fprintf(stderr, "fail to open %s\n", fileTargetName);
			continue;
		}
		break;
	}

	char buffer[1024];
	int count=0;
	while((count=fread(buffer,sizeof(char),1024,source))>0){
		fwrite(buffer,sizeof(char),count,target);
	}
	// 判断是非有读写错误
	if(ferror(source))
		fprintf(stderr, "%s\n","IO error while reading" );
	else if(feof(source))
		puts("reach ending sucessfully");

	if(ferror(target)){
		fprintf(stderr, "%s\n", "IO error while writing");
	}

	fclose(source);
	fclose(target);
	puts("copy done");

}
/*交替打印两个文件的每行*/
void print_line_from_files(void){
	FILE *one,*two;
	if((one=fopen("append.c","rb"))==NULL){
		fprintf(stderr, "fail to open %s\n", "append.c");
		exit(1);
	}
	if((two=fopen("reverse.c","rb"))==NULL){
		fprintf(stderr, "fail to open %s\n", "reverse.c");
		exit(1);
	}

	int ch;
	while(1){
		// 如果文件1没有结束打印一行
		if(!feof(one)){
			printf("from--1---");
			while((ch=fgetc(one))!=EOF){

				putc(ch,stdout);
				if(ch=='\n'){
					break;
				}
			}
		}
		if(!feof(two)){
			printf("from--2---");

		// 同上，如果文件2没有结束打印一行
			while((ch=fgetc(two))!=EOF){
				putc(ch,stdout);
				if(ch=='\n')
					break;
			}
		}
		

		// 如果文件1和2都到结尾退出
		if(feof(one)&&feof(two)){
			break;
		}

	}
	fclose(one);
	fclose(two);
	puts("finish print alternative");

}
/* 根据命令行参数搜素指定文件的单词位置*/
void search_word(int argc,char const *argv[]){
	if(argc!=3){
		fprintf(stderr, " %s\n","wrong paramgs" );
		exit(1);
	}
	FILE *fp;
	if((fp=fopen(argv[1],"rb"))==NULL){
		fprintf(stderr, "fail to open file %s\n", argv[1]);
		exit(1);
	}
	// 一行字符数最大值
	int max=1024;
	char buffer[max];
	int line=0;
	//  使用fgets获取一行
	while(fgets(buffer,max,fp)!=NULL){
		line++;
		// 使用字符串搜索函数
		if(strstr(buffer,argv[2])){
			printf("line %d %s\n",line,buffer );
		}

	}
	if(ferror(fp)){
		fprintf(stderr, "%s\n", "IO Exception in reading");
	}
	if(feof(fp)){
		puts("reach end of file");
	}
	fclose(fp);

}

int main1(int argc, char const *argv[])
{
	/* 使用fwrite 和 fread 合并文件 */
	FILE *source,*destination;
	// 源文件名，从键盘录入获取
	char sourceFileName[MAX];
	//目标文件名被写死
	if((destination=fopen("destination","a"))==NULL){
		fprintf(stderr, "fail to open %s\n", "destination");
		exit(1);
	}
	char buffer[BUFFER_SIZE];
	int count=0;
	char *find;
	puts("please enter sourceFileName");
	// 获取键盘录入的源文件名，空行退出
	while(fgets(sourceFileName,MAX,stdin)&&sourceFileName[0]!='\n'){
		//去除换行符
        if((find=strchr(sourceFileName,'\n'))!=NULL){
        	*find='\0';
        }
        // 看原文件和目标文件是否同名
		if(strcmp("destination",sourceFileName)==0){
			fprintf(stderr, "sourceFileName can not be %s\n", "destination");
			continue;
		}else if((source=fopen(sourceFileName,"r"))==NULL){
			fprintf(stderr, "can no open file %s\n", sourceFileName);
			continue;
		}else{
			// 追加操作
			while((count=fread(buffer,sizeof(char),BUFFER_SIZE,source))>0){
				fwrite(buffer,sizeof(char),count,destination);
			}
			// 判断是非读写错误
			if(ferror(source)){
				fprintf(stderr, "%s\n", "read exception");
			}
			if(ferror(destination)){
				fprintf(stderr, "%s\n", "write exceptin ");
			}
			// 关闭源文件
			fclose(source);
			printf("finish append file %s to %s\n",sourceFileName,"destination");
			puts("please enter file name to append,empty line to quit");
		}

	}
	puts("append finish");
// 关闭目标文件
	fclose(destination);
	return 0;
}


int main(int argc, char const *argv[])
{
	/* 文件的随机读取 */

	double buffer[1000];
	// 存储double数组的文件
	const char * fileName="rand.dat";
	FILE *fp;
	// 以二进制可写模式打开文件
	if((fp=fopen(fileName,"wb"))==NULL){
		fprintf(stderr, "fail to open file %s\n", fileName);
		exit(1);
	}
// 初始化数组
	for (int i = 0; i < MAX; ++i)
	{
		buffer[i]=i/1.3;
	}
	// 将数组写入文件中
	int result=fwrite(buffer,sizeof(double),1000,fp);
	// 判断是否有写错误
	if (ferror(fp))
	{
		fprintf(stderr, "%s\n", "write exception");
	}else{
		printf("write %d number to file %s\n", result,fileName);		
	}
	fclose(fp);
	// 关闭后以二进制可读模式打开
	if((fp=fopen(fileName,"rb"))==NULL){
		fprintf(stderr, "fail to open file %s\n", fileName);
		exit(1);
	}
	int index=0;
	long position=0;
	double random;
	puts("please choose a number between 0-999 or out of range to exit");
	while(scanf("%d",&index)==1&&index>=0&&index<1000){
		//计算偏移量
		position=(long)index*sizeof(double);
		fseek(fp,position,SEEK_SET);
		fread(&random,sizeof(double),1,fp);
		printf("you choose %d and it's value %f\n", index,random);
	puts("please choose a number between 0-999 or out of range to exit");



	}
	fclose(fp);
	return 0;
}
int main2(int argc, char const *argv[])
{
	/* reduce orgin file to one third,do not contain any Chinese characters */

	FILE *in,*out;
	char ch;
	char name[40];
	if(argc<2){
		fprintf(stderr,"Usage:%s fileName",argv[0]);
		exit(1);
	}
	if((in=fopen(argv[1],"r"))==NULL){
		fprintf(stderr,"could not open %s",argv[1]);
		exit(2);
	}

	strcpy(name,argv[2]);
	strcat(name,".red");
	if((out=fopen(name,"w"))==NULL){
		fprintf(stderr,"could not create file %s",name);
		exit(3);

	}
	int count=0;
	while((ch=getc(in))!=EOF){
		if(count++%3==0){
			putc(ch,out);
		}
	}
// 关闭指针指定的文件，同时根据需求刷新缓冲区，磁盘已满或被移走都会导致IO错误致使关闭失败
	if(fclose(in)!=0||fclose(out)!=0){
		fprintf(stderr, "fail to close file\n");
	}


	return 0;
}
int main3(int argc, char const *argv[])
{
	/* 使用fseek ftell逆转文件 只适合mac平台,暂不能颠倒中文 */
	FILE *fp;
	long last;
	char fileName[MAX];
	// fgets函数不会丢弃换行符
	fgets(fileName,MAX,stdin);
	// 找到换行符
	char  *find=strchr(fileName,'\n');
	// 改成空字符
	if(find){
		*find='\0';
	}
	// 二进制模式打开
	if((fp=fopen(fileName,"rb"))==NULL){
		fprintf(stderr, "fail to open %s\n", fileName);
		exit(1);
	}
	// 第二个参数为偏移量，第三个参数为模式，标示文件起始位置
	fseek(fp,0L,SEEK_END);
	last=ftell(fp);
	char ch;
	for (int count = 1; count < last; ++count)
	{
		fseek(fp,-count,SEEK_END);
		ch=getc(fp);
		putchar(ch);
	}

	fclose(fp);

	return 0;
}
int main(int argc, char const *argv[])
{

	// count();
	// file_copy();
	// print_line_from_files();
	search_word(argc,argv);


	
	return 0;
}
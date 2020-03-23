#include <stdio.h>
#include <string.h>
#include <stdlib.h>


enum spectrum {red,orange,blue};
const char * colors[]={"red","orange","blue"};

int main(int argc, char const *argv[])
{
	/* C中的枚举 */

	enum spectrum choice;
	char input[11];
	unsigned char found=0;
	puts("enter color withc empty line to exit");

	while(gets(input)&&input[0]!='\0'){
		puts("start");
		// 虽然枚举本质是int，但不能自增，可以赋值给int变量，但反过来不行
		for (int i = red; i <=blue; i++)
		{
			if(strcmp(colors[i],input)==0)
			{
				// 必须强制类型转化
				choice=(enum spectrum)i;
				found=1;
				break;
			}
		}
		if(found){
			switch(choice){
				case red:puts("rose is red");break;
				case orange:puts("it's orange");break;
				case blue:puts("sky is blue");break;
				
			}
			found=0;
		}else{
			puts("get nothing");
		}
		puts("try another color");

	}


	return 0;
}
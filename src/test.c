#include "common.h"


int main(int argc, char const *argv[])
{
	/* code */
	int fd=Open(argv[1],O_RDONLY,0);
	printf("fd:%d\n",fd);
	return 0;
}
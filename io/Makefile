CC = gcc

CSAPP_INC = ../include
CSAPP_SRC = ../src

CFLAGS = -Wall -O2 -I $(CSAPP_INC) -I .
LDLIBS = -lpthread

PROGS =	poll_pipe\
	# demo_inotify\
	file_map\
	# epoll\
	
# 由于makefile只能有一个目标，所以可以构造一个没有规则的终极目标all，并以冒号后面的文件作为依赖,命令可以推导出来
# 所以被省略掉了
all: $(CSAPP_SRC)/common.o $(CSAPP_SRC)/error_functions.o $(PROGS) 
$(PROGS): $(CSAPP_SRC)/common.o $(CSAPP_SRC)/error_functions.o
$(CSAPP_SRC)/common.o: $(CSAPP_SRC)/common.c $(CSAPP_INC)/common.h
$(CSAPP_SRC)/error_functions.o: $(CSAPP_SRC)/error_functions.c $(CSAPP_INC)/error_functions.h

# Programs that need more than one .o file
# echo_server: echo_server.o echo.o
 


clean:
	rm -f $(PROGS) *.o *~


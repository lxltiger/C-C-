CC = gcc

CSAPP_INC = ../include
CSAPP_SRC = ../src

CFLAGS = -Wall -O2 -I $(CSAPP_INC) -I .
LDLIBS = -lpthread

PROGS =	epoll\
	# echo_client\
	# echo_server\
	

all: $(CSAPP_SRC)/common.o $(PROGS) 
$(PROGS): $(CSAPP_SRC)/common.o
$(CSAPP_SRC)/common.o: $(CSAPP_SRC)/common.c $(CSAPP_INC)/common.h


# Programs that need more than one .o file
# echo_server: echo_server.o echo.o
 


clean:
	rm -f $(PROGS) *.o *~


CC = gcc

CSAPP_INC = ../include
CSAPP_SRC = ../src

CFLAGS = -Wall -O2 -I $(CSAPP_INC) -I .
LDLIBS = -lpthread

PROGS =	echo.o\
	echo_client\
	echo_server\
	

all: $(CSAPP_SRC)/common.o $(PROGS) 
$(PROGS): $(CSAPP_SRC)/common.o
$(CSAPP_SRC)/common.o: $(CSAPP_SRC)/common.c $(CSAPP_INC)/common.h

# tiny/tiny: tiny/tiny.c
# 	(cd tiny; make)	

# Programs that need more than one .o file
echo_server: echo_server.o echo.o
 
# tinytarfile:
# 	(cd tiny; make clean)
# 	tar cvf - tiny >tiny.tar

clean:
	rm -f $(PROGS) *.o *~
# 	(cd tiny; make clean)

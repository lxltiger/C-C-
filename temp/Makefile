psuCC = gcc

CSAPP_INC = ../include
CSAPP_SRC = ../src

CFLAGS = -Og -Wall -I $(CSAPP_INC) -I .
LDLIBS = -lpthread -lm

COUNTERARGS = -O1 -Wall -I $(CSAPP_INC)

# NOTE: we expect test.c to generate warnings
PROGS =	test\
	

# all: $(CSAPP_SRC)/common.o $(PROGS)
# $(PROGS): $(CSAPP_SRC)/common.o 
# $(CSAPP_SRC)/common.o: $(CSAPP_SRC)/common.c $(CSAPP_INC)/common.h

all: $(CSAPP_SRC)/common.o $(CSAPP_SRC)/error_functions.o $(PROGS) 
$(PROGS): $(CSAPP_SRC)/common.o $(CSAPP_SRC)/error_functions.o
$(CSAPP_SRC)/common.o: $(CSAPP_SRC)/common.c $(CSAPP_INC)/common.h
$(CSAPP_SRC)/error_functions.o: $(CSAPP_SRC)/error_functions.c $(CSAPP_INC)/error_functions.h

# Programs that need more than one .o file
# echoserveri: echoserveri.o echo.o


clean:
	rm -f $(PROGS) *.o *~

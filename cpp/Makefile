#-Werror warning当error处理
CXX_FLAGS=-Wall 
CXX=g++

# CSAPP_INC = ../include
# CSAPP_SRC = ../src

# CFLAGS = -Wall -O2 -I $(CSAPP_INC) -I .
# LDLIBS = -lpthread

PROGS =	auto
	
# $@表示目标文件  $^表示冒号后面的源文件
$(PROGS):$(PROGS).cpp
	$(CXX) -std=c++11 -o $@ $^ $(CXX_FLAGS) ;./$(PROGS)

# Programs that need more than one .o file
# echo_server: echo_server.o echo.o
 


clean:
	rm -f $(PROGS) *.o *~


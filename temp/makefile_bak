CC=gcc
# 头文件目录 与scr同级别
IDIR=../include
CFLAGS=-I${IDIR}

# 目标文件目录，src目录的子目录
ODIR=obj
# lib dir
LDIR =../lib
# math lib
LIBS=-lm

_DEPS=common.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))
# INCLUDE=include/common.h
# 如果目标文件没有改动不会重新生成
_OBJECT=common.o test.o
# 指定目标文件的位置在obj/目录下
OBJECT = $(patsubst %,$(ODIR)/%,$(_OBJECT))
# 所有.o目标文件依赖.c源文件和DEPS下的头文件编译而成
$(ODIR)/%.o: %.c $(DEPS)
# 	-c 生成目标文件，-o $@生成的目标文件内容放在：号左边文件中，比如这里就是obj/common.o
# $<表示依赖列表的第一个 不确定什么意思
	$(CC) -c -o $@ $< $(CFLAGS)
# $@表示：左边的内容，$^表示：右边的内容
test: $(OBJECT)
	$(CC) -o $@ $^ $(CFLAGS) 

# make 执行效果
# gcc -c -o obj/common.o common.c -I../include
# gcc -c -o obj/test.o test.c -I../include
# gcc -o test obj/common.o obj/test.o -I../include

# test:${OBJECT}
# 	$(CC)  ${OBJECT} -o test

# common.o:src/common.c ${INCLUDE}
# 	$(CC) -c src/common.c

# test.o:test.c ${INCLUDE}
# 	$(CC) -c test.c


# 终端执行 make clean清除中间文件
# .PHONY意思表示clean是一个“伪目标”
.PHONY : clean
# 	clean要放在最后 在rm命令前面加了一个小减号的意思就是，也许某些文件出现问题，但不要管，继续做后面的事
clean:
# 	-rm test ${OBJECT}
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
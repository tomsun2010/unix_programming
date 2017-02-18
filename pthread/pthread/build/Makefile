#################################################################

 # File Name:   Makefile
 # Author:     	sun_jichuan
 # Date:        2016年5月3日14:20:54
 # Note:        编译库及其测试程序

#################################################################
CROSS_COMPILE := arm-linux-gnueabihf-
CC	= $(CROSS_COMPILE)gcc
CPP = $(CROSS_COMPILE)g++
LD	= $(CROSS_COMPILE)ld
AR	= $(CROSS_COMPILE)ar
RANLIB  = $(CROSS_COMPILE)ranlib
STRIP   = $(CROSS_COMPILE)strip

ARCH	= arm

PWD	:= $(shell pwd)
DIRBIN = ../bin
INCLUDE = ../include
SRC = ../src

#AFLAGS += cru
AFLAGS += crs
CFLAGS = -Wall -O2 -Os
#CFLAGS  += -g -Wall -Werror
LDFLAGS	+= -lm -lpthread

##lib
INCFLAGS  += -I../include
LIB_SRCS  = ../src/*.c
LIB_OBJS = $(patsubst %.c, %.o, $(wildcard $(LIB_SRCS)))
LIB_NAME = $(DIRBIN)/pthread_lib.a


##test
TEST_SRC = ../test/*.c
TEST_OBJS = $(patsubst %.c, %.o, $(wildcard $(TEST_SRC)))
TEST_PHY = $(DIRBIN)/pthread_lib_test

##make	
lib: $(LIB_NAME)

$(LIB_NAME):$(LIB_OBJS)
	$(AR) $(AFLAGS) $@ $(LIB_OBJS)
	@rm $(SRC)/*.o 
	@cp ../include/comm_thread_i.h ../bin

$(LIB_OBJS):%.o:%.c
	$(CC) -c  $(CFLAGS) $(INCFLAGS) $(LDFLAGS) $< -o $@

test:$(TEST_PHY)

$(TEST_OBJS):%.o:%.c
	$(CC) -c $(INCFLAGS) $< -o $@
	
$(TEST_PHY):$(TEST_OBJS)
	$(CC) $(CFLAGS)  -o $(TEST_PHY) $(TEST_OBJS) $(LIB_NAME) 
	@rm ../test/*.o 	

lib_clean:
	rm   $(DIRBIN)/*.a
	rm   $(DIRBIN)/*.h
test_clean:
	rm   $(DIRBIN)/pthread_lib_test
	
	

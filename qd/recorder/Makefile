top_dir = $(PWD)
output = $(top_dir)/export
#
# 定义编译器和汇编器
#
CC := $(CROSS_COMPILE)gcc
CXX := $(CROSS_COMPILE)g++
LD := $(CROSS_COMPILE)ld
AS := $(CROSS_COMPILE)as
AR := $(CROSS_COMPILE)ar
MAKE := make
RM	 := rm

CFLAGS += -g -O0 -Wall -pipe -fPIC 
INCLUDE += -I $(top_dir)/include/

LIB += -L $(top_dir)/lib/ -lmp3lame -lortp

all: recorder rtpsend udpsend u711tomp3

recorder: main.c comm.c g711.c g711codec.c mp3decode.c 
	${CC} -o $(output)/$@ $^ ${CFLAGS} ${INCLUDE} ${LIB} 

rtpsend: test/rtpsend.c
	${CC} -o $(output)/$@ $^ ${CFLAGS} ${INCLUDE} ${LIB} 

udpsend: test/udpsend.c
	${CC} -o $(output)/$@ $^ ${CFLAGS} ${INCLUDE} 

u711tomp3: comm.c g711.c g711codec.c mp3decode.c u711tomp3.c
	${CC} -o $(output)/$@ $^ ${CFLAGS} ${INCLUDE} ${LIB} 
	
clean:
	rm -f $(output)/*

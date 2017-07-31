# flags
CC = g++
CFLAGS = -Wall
LFLAGS = 

# args
RELEASE =0
BITS = 32

# [args] 生成模式. 0代表debug模式, 1代表release模式. make RELEASE=1.
ifeq ($(RELEASE),0)
	# debug
	CFLAGS += -g
else
	# release
	CFLAGS += -static -O3 -DNDEBUG
	LFLAGS += -static
endif

# [args] 程序位数. 32代表32位程序, 64代表64位程序, 其他默认. make BITS=32.
ifeq ($(BITS),32)
	CFLAGS += -m32
	LFLAGS += -m32
else
	ifeq ($(BITS),64)
		CFLAGS += -m64
		LFLAGS += -m64
	else
	endif
endif


.PHONY : all clean

# files
TARGETS = testUseMinGWLib
OBJS = 01test.o 02testOpenCV.o

all : $(TARGETS)

testUseMinGWLib : $(OBJS)
	$(CC) $(LFLAGS) -o $@ $^ -L C:\msys64\mingw32\lib -lopencv_core.dll -lopencv_highgui.dll -lopencv_imgcodecs.dll

01test.o : 01test.cpp
	$(CC) $(CFLAGS) -c $<
02testOpenCV.o : 02testOpenCV.cpp
	$(CC) $(CFLAGS) -c $<
	
clean :
	rm -f $(OBJS) $(TARGETS) $(addsuffix .exe,$(TARGETS))
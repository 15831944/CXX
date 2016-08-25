Path := /home/jinze.ji/git22/zq/TianShan/bin64/

TOPDIR := /home/jinze.ji/git22/zq/

include $(TOPDIR)/build/defines.mk

CFLAGS = -g

TARGET := test 

OBJS   :=   main.o  aaa.o aio.o #socket.o socket_linux.o eventloop.o eventloop_linux.o 

$(TARGET):$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS) $(CFLAGS)          #-L$(Path) -lZQCommon

INCDIR += . ../Common/

LDFLAGS +=  -L$(Path) -lZQCommon  -laio #-L./libZQCommon.so #-L$(Path) -lZQCommon -lasynic 

include $(TOPDIR)/build/common.mk

clean:
	rm *.o test

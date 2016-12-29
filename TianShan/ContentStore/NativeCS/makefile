TOPDIR := ../../..

TARGET := NativeCS

OBJS := ConfigHelper.o ZQDaemon.o FileSystemOp.o CPCImpl.o ProvWrapper.o \
        ProvEventSink.o cspNative.o NativeServiceConfig.o NativeService.o

incdir += ../ ../../CPE

include $(TOPDIR)/build/common.mk

LDFLAGS += $(cslink) $(shelllink) $(commonlink) $(icelink)

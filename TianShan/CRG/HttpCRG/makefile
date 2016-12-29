TOPDIR := ../../..

include $(TOPDIR)/build/defines.mk

TARGET := HttpCRG

OBJS := ZQDaemon.o ConfigHelper.o HttpCRGConfig.o HttpCRG.o 

INCDIR += $(TOPDIR)/Common/HttpEngine $(TOPDIR)/Common/DataPostHouse 

CXXFLAGS +=  -DCONFIG_NO_SNMP

LDFLAGS +=  $(snmplink) $(commonlink) $(icelink) -lHttpEngine -lServiceShell -lDataPostHouse -lboost_regex

include $(TOPDIR)/build/common.mk  


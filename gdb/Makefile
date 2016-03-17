#LDFLAGS =
#all: functions.o
#SRCS=main.cpp functions.cpp
#OBJS= functions.o main.o
##main: $(OBJS)
##	$(CXX) -o  main $(OBJS) $(LDFLAGS)
#main.o: main.cpp functions.h  
#	$(CXX) -o main.o main.cpp functions.h $(LDFLAGS)
#functions.o: functions.h functions.cpp
#	-$(RM) $(OBJS)
#	-$(RM) $(all)
CFLAGS = -Ilib -O2 -g 
LDFLAGS= -lpthread   -Llib -lggg
TARGET = test
#OBJS= main.o
$(TARGET):$(OBJS)
	$(CXX) main.cpp -o $(TARGET)  $(CFLAGS) $(LDFLAGS)
#main.o:main.cpp
#	$(CXX) main.cpp -o main.o $(CFLAGS)  
clean:
	-$(RM)  $(TARGET)

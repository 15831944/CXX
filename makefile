CFLAGS = -O2 -g -lpthread -std=c++11
#TARGET = server client
#OBJS = server.o
#$(TARGET): $(OBJS)
#	$(CXX) -o $(TARGET) $(OBJS) $(CFLAGS)
target:server client test 
server: server.cpp
	$(CXX) -o server -O2 -g server.cpp
client: client.cpp
	$(CXX) -o client -O2 -g client.cpp
test: test.cpp test.h
	$(CXX) -o test test.cpp $(CFLAGS)
template: template.cpp template.h
	$(CXX) -o template template.cpp $(CFLAGS)
#server: server.o
#	$(CXX) -o server server.o
#server.o: server.cpp
#	$(CXX) -o -g -O2 server.o server.cpp
#client: client.o
#	$(CXX) -o client client.o 
#client.o: client.cpp
#	$(CXX) -o -g -O2 client.o client.cpp 
clean:
	-$(RM) server client 
	-$(RM) server.o  client.o


all:test
CFLAGS = -O2 -pthread -std=c++11 -g
test: test.cpp
	$(CXX) -o test $(CFLAGS) test.cpp
clean:
	-$(RM) *.o
	-$(RM) test

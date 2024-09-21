CXX = g++
CFLAGS = -Wall -Wextra -pedantic --std=c++11 -ggdb

.PHONY: all
all: day4 md5

day4: day4.cpp md5.o
	$(CXX) $(CFLAGS) -o day4.exe day4.cpp md5.o
md5: md5.cpp
	$(CXX) $(CFLAGS) -c md5.cpp
clean:
	rm -rf *.exe *.o *.dSYM *.gch
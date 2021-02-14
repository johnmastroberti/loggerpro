CXX=g++
CXXFLAGS=-std=c++20 -Wall -Wextra -Wpedantic -Werror -I/home/john/.local/lib/rapidxml
LD=g++

lptotxt: main.o
	$(LD) -o $@ $^

main.o: main.cpp
	$(CXX) -o $@ $(CXXFLAGS) -c $^

test: lptotxt
	./lptotxt test.cmbl

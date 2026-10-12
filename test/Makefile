CXX ?= g++
CXXFLAGS ?= -std=c++11 -Wall -Wextra -O1
all: run
test_dtutils: test_dtutils.cpp ../DTutils.cpp ../DTutils.h
	$(CXX) $(CXXFLAGS) -Istubs -I.. -o $@ test_dtutils.cpp ../DTutils.cpp -lm
run: test_dtutils
	./test_dtutils
clean:
	rm -f test_dtutils

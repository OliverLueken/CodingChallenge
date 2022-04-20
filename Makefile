SHELL = /bin/sh
.SUFFIXES:
.SUFFIXES: .cpp .o

CPP = g++
CPPDEBUG = -g
CPPWARNINGS = -Wall -Wpedantic -Wextra -Wconversion
CPPSANITIZER = -fsanitize=undefined,address
CPPFLAGS = -std=c++20 -O3 $(CPPWARNINGS) $(CPPSANITIZER)


all: main.out

main.out: main.cpp myList.hpp
	$(CPP) $(CPPFLAGS) main.cpp -o main.out

test: main_test.cpp myList.hpp test_myList.cpp
	$(CPP) $(CPPFLAGS) main_test.cpp -o test.out

.PHONY = clean
clean:
	rm main.out
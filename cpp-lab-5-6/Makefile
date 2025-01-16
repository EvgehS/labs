CC=g++
FLAGS=-std=c++20 -Wall -Wextra -Werror

test_bin: test.o transport.o
	$(CC) $(FLAGS) transport.o test.o -o test_bin
test.o: test.cpp transport.hpp
	$(CC) $(FLAGS) -c test.cpp
transport.o: transport.hpp transport.cpp
	$(CC) $(FLAGS) -c transport.cpp
test: 
	./test_bin
clean:
	rm -rf *.o test_bin
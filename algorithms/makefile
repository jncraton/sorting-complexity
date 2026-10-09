all: bench

bench:
	g++ -std=c++23 -O3 test.cc -o test
	./test

format:
	clang-format -i *.cc *.hh

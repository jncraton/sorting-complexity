all: bench

bench:
	g++ -std=c++23 -fno-tree-dce -O3 test.cc -o test
	./test

format:
	clang-format -i *.cc *.hh

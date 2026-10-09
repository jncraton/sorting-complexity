all: test bench

%.o: %.cc
	g++ -std=c++23 -O3 -fno-tree-dce -fno-lto -c $< -o $@

bench: list.o forward_list.o vector.o bench.o
	g++ -std=c++23 -fno-tree-dce -fno-lto -O3 $^ -o $@
	./bench

test: list.o forward_list.o vector.o test.o
	g++ -std=c++23 -fno-tree-dce -fno-lto -O3 $^ -o $@
	./test

format:
	clang-format -i *.cc *.hh

clean:
	rm -rf *.o *.csv test bench
